# Exposing the Shared Model to Javascript

## TL;DR: What am I proposing?

Put simply, we should replace the core of our existing Javascript renderer with a Web Assembly version of our C++ Shared Model library. How? Keep reading. :shipit:

## Motivation

The promise of Adaptive Cards is to deliver high quality and consistent experiences on each supported platform. Today, there are three distinct supported implementations -- .NET, Shared Model (C++), and Javascript. The .NET library is used as a base for our WPF and .NET HTML renderers. The C++ Shared Model supports our iOS, Android, and UWP efforts. The Javascript implementation is used for our web offerings.

As our customer base has expanded, the team has found itself dealing with the consequences of delivering across three base platforms:
* increased development costs
* siloing of dev talent
* cross-platform inconsistencies
* diverging developer experiences as the base platforms skew relative to each other

### A Little History

As I understand it, the .NET platform was the first renderer to be developed and was used as to prototype features. The Shared Model and Javascript platforms came shortly thereafter. In the early days, having distinct implmentations was deemed as somewhat important to prove that Adaptive Cards as a platform could be arbitrarily replicated -- meaning that we didn't have any platform-specific ties, and thus could deliver the promise of Adaptive Cards across any platform. This was crucial to set the team up for delivering cross-platform experiences.

C#/.NET was an obvious choice as a base for the WPF and server-side HTML renderers. Javascript made sense for client-side HTML rendering. C++ was chosen as the language for the Shared Model used across the other platforms since it was greatest common denominator for iOS, Android, and UWP.

### Enter WASM

[Web Assembly](https://webassembly.org/) is a relatively new technology (started in 2015) that defines portable executable code that can be consumed by web browsers. In the past couple of years, it has begun to gain traction as tooling and support improves. Of particular interest to us is a compiler toolchain called [Emscripten](https://emscripten.org/), which provides support for cross-compiling C++ to WASM (in addition to loaders and runtime support).

This critical bit of compiler tech can open the door for us to base our Javascript/client-side efforts on the same underlying Shared Model that we use elsewhere.

## Benefits

* Write once, use everywhere
* A common cross-platform core necessarily means common cross-platform behavior (at least from the object model perspective)
* Able to leverage broad familiarity with the C++ Shared Model to deliver new features in a more timely manner (and work is more parallelizable)
* Fewer CI pipelines to manage
* A common set of dependencies to manage
* Existing code quality tooling benefits more platforms
* The Javascript renderer can be a much thinner layer focused directly on rendering
* The Shared Model has extensive unit tests, where the Javascript renderer does not, so we will benefit from better coverage
* While not measured in the prototype, it's likely that performance will be better (anecdotal based on impressions gathered from the web)
* Establishes a pattern we can use for future expansion should we decide to pursue new platforms
* Further enforces separation of object model from rendering

## Risks

* Compiler toolchain appears to be relatively well fleshed out, but the debugging story isn't well integrated at the moment
* Existing customers with custom rendering or custom parsing will need to do work in order to adopt new version
    * Investigate if it's possible to provide a translation layer to allow existing extensions to work
    * Coordinate with partners to get a sense for how big an issue it will be
* Some functionality available in the Javascript is not available to Shared Model parsers with no timeline
    * In particular, templating isn't available, though perhaps that's not too big a deal since `adaptivecards-templating` is a distinct package...
    * The "extras" package won't be supported unless we schedule work to enable it
* While Web Assembly is widely adopted, it's still fairly new tech, so it's possible that there are unforeseen challenges in deploying it
    * Electron is confirmed to support WASM, as does [every major browser](https://caniuse.com/wasm)
    * NodeJS supports WASM via [WASI](https://nodejs.org/docs/latest-v14.x/api/wasi.html) at least as far back as v12, but it's listed as `Stability: 1 - Experimental`
        * It's unclear how deep this support goes -- the sample simply executes a full program
        * More investigation will be needed here if we want to ensure this capability
        * One possible mitigation would be to further investigate NodeJS<->C++ interop, but that would be another spec and another chunk of work
* The prototype didn't surface any porting issues that couldn't be resolved by either being selective/creative with bindings or by adding new helpers in the Shared Model. It's possible that there's still something inexpressible just waiting to show up.

## Engineering Plan

1. Evaluate existing Javascript API
    * Determine what capabilities are exposed by existing codebase
        * **Important**: enumerate designer requirements
    * Document everything unique to Javascript renderer to make sure we aren't introducing unintentional gaps
1. Establish Javascript API surface coding standards
    * Naming
    * Properties vs. explicit get/set methods (note: need to figure out if we can overload properties via JS-derived classes)
    * TypeScript bindings?
1. Initial bring-up
    * Bootstrap project with initial build system (with CI)
    * Author test suite that attempts to parse every sample card we have (follow TDD here -- tests should trend to 100% pass)
1. Implementation
    * Shared Model Bindings and wrappers
        * Prioritize work around parsers and elements
        * Should be pretty parallelizable
    * Flesh out test suite to include exercising of wrapped interface
    * Implement Javascript renderer
        * We should attempt to reuse existing renderer code to the furthest extent possible. At minimum, we should continue to emit the same CSS class names
        * Work can be parallelized as elements start lighting up
1. Documentation
    * Javascript API surface docs
        * Extension story
    * Build environment
    * Howto docs

## The Prototype

As of right now, I've gotten a prototype stood up that:
* Supports custom elements and custom parsing
* Can parse a card with Containers, TextBlocks, and custom elements
* Builds alongside existing Shared Model code

It's implemented using Emscripten's [`embind`](https://emscripten.org/docs/porting/connecting_cpp_and_javascript/embind.html#embind) library, which supports bidirectional communication between C++ and Javascript. C++ classes can serve as a base for a Javascript-derived class, which is necessary to support our custom parsing and custom elements story.

### Design Decisions

To support anything beyond simply *running* C++ code in a browser, the author must provide a means by which to bind objects on the C++ side over to the Javascript side of things. There are two main options for providing these bindings:

#### WebIDL

Short version: author a [WebIDL](https://developer.mozilla.org/en-US/docs/Glossary/WebIDL) interface, run a tool that generates glue code, then include the glue code when building the underlying library.

There are some advantages to using this approach as it keeps interface definitions distinct from actual code, and projects cleanly into Javascript. There are some downsides to this approach, but it's not really worth enumerating them here because there's one problem that precludes our use of the WebIDL binding method: there's no support for `std::shared_ptr<T>` or `std::unique_ptr<T>`, which are ubiquitous in the Shared Model's public API surface. We would require a pretty large overhaul of the Shared Model (with lots of breaking changes) in order to be able to adopt this approach. Even then, I'm not 100% sure that it would fulfill our needs.

#### `embind`

`embind` is implemented in a header that you include in your project. It provides facilities to describe and define the projected API surface of a C++ project into Javascript. Of particular interest to us is support for `std::shared_ptr<T>`, but there are other benefits over the WebIDL approach. Because the mapping is manual, we can reshape the API surface to make Adaptive Cards Shared Model feel more like a native Javascript library. Consider, for example, this condensed version of `BaseElement`:

```c++
class BaseElement
{
public:
    std::string GetId() const;
    void SetId(std::string id);
};
```

If we took a direct mapping approach for `BaseElement`, you'd probably end up with a Javascript experience that looked like this:

```javascript
let myElement = new BaseElement();
myElement.SetId("some-identifier");
let myId = myElement.GetId();
```

This approach would, of course, work, but we can do better by taking a little extra care while defining the binding so that we end up with Javascript more like this:

```javascript
let myElement = new baseElement(); // camelCase!
myElement.id = "some-identifier";
let myId = myElement.id;
// myId === "some-identifier"
```

It's probably worth noting that I haven't worked out if it's possible to override getters and setters when deriving a new class, so we *may not* be able to smooth all of the edges.

Another interesting bit of functionality we have access to via `embind` is the ability to [transliterate Javascript calls](https://emscripten.org/docs/porting/connecting_cpp_and_javascript/embind.html#using-val-to-transliterate-javascript-to-c) such that they can be written in and called from C++. I'm not sure that we have a use-case for this at the moment, but it could potentially open some doors for us in the future.

### How It Works

**A word before we dig in** - this prototype was incrementally developed. The examples given should not be considered best practices (indeed, you may notice that over time I tried different approaches as I got a better feel for what was possible). Things like nomenclature and API surface design choices will need to be further investigated before implementing For Real.

Most of the interesting Javascript-facing bits are exercised in the (definitely not shipping) [foo.html](https://github.com/paulcam206/AdaptiveCards/blob/paulcam/embind-build/source/shared/cpp/ObjectModel/foo.html).

Here's us loading the Javascript bit that chains to load our WASM file:

```javascript
<script async type="text/javascript" src="ObjectModel.js"></script>
```

This bit is a test to see if we can create a custom element purely in Javascript:

```javascript
let myCustomElement = Module.baseCardElement.extend("baseCardElement", {
  __construct: function() {
    this.__parent.__construct.call(this);
  },
  setId: function(str) {
    Module.baseElement.prototype.setId.call(this, `JS? '${str}'`); // just to prove this function is getting called
  },
  getId: function() {
    return Module.baseElement.prototype.getId.call(this);
  },
  toString: function() {
    const baseSerialize = Module.baseElement.prototype.toString.call(this);
    let baseObj = JSON.parse(baseSerialize);
    baseObj["customProperty"] = this.customProperty;
    baseObj["type"] = this.getElementType();
    return JSON.stringify(baseObj);
  },
  getElementType: function() {
    return "MyCustomElement";
  },
  customProperty: 8
});
```

Here's a custom parser purely in Javascript:

```javascript
let customParser = Module.baseCardElementParser.extend("baseCardElementParser", {
  __construct: function() {
    this.__parent.__construct.call(this);
  },
  deserialize: function(ctx, jsonObj) {
    let retval = new myCustomElement();
    retval.deserializeBaseProperties(ctx, jsonObj);
    let customProp = jsonObj.get("customProperty", new Module.jsonValue());
    if (customProp?.isInt())
    {
      retval.customProperty = customProp.asInt();
    }

    return retval;
  },
  deserializeFromString: function(ctx, jsonStr) {
    let customElem = new myCustomElement();
    customElem.deserializeBasePropertiesFromString(ctx, jsonStr);

    let jsonObj = JSON.parse(jsonStr);
    if (jsonObj["customProperty"]) {
      customElem.customProperty = jsonObj["customProperty"];
    }
    return customElem;
  }
});
```

Here's us registering our new custom parser:

```javascript
let parseContext = new Module.parseContext();
let registration = parseContext.elementParserRegistration;
let customParserPreInsert = new customParser();
registration.addParser("MyCustomElement", customParserPreInsert);
```

Here's us parsing an Adaptive Card that contains our custom-parsed custom element:
```javascript
let myCard = JSON.stringify({
  "$schema": "http://adaptivecards.io/schemas/adaptive-card.json",
  "type": "AdaptiveCard",
  "version": "1.5",
  "body": [
    {
      "type": "TextBlock",
      "text": "an actual card!"
    },
    {
      "type": "Container",
      "items": [
        {
          "type": "TextBlock",
          "text": "this is ridiculous"
        },
        {
          "type": "MyCustomElement",
          "id": "bleh",
          "customProperty": 1024
        }
      ]
    }
  ]
});

let parseResult = Module.adaptiveCard.fromString(myCard, "1.5");
```

Now that you've seen the Javascript side of things, we should probably take a look under the hood to see how this is all generated. Let's start with `BaseElement`, since it underlies all elements in Adaptive Cards. Here's [BaseElement.h](https://github.com/paulcam206/AdaptiveCards/blob/paulcam/embind-build/source/shared/cpp/ObjectModel/BaseElement.h) with irrelevant bits (or bits not used by the prototype) stripped out:

```c++
   class BaseElement
    {
    public:
        BaseElement() {}

        BaseElement(const BaseElement&) = default;
        BaseElement(BaseElement&&) = default;
        BaseElement& operator=(const BaseElement&) = default;
        BaseElement& operator=(BaseElement&&) = default;
        virtual ~BaseElement() = default;

        // Element type and identity
        const std::string& GetElementTypeString() const;
        void SetElementTypeString(std::string&& value);
        void SetElementTypeString(const std::string& value);

        const std::string& GetId() const;
        virtual void SetId(std::string&& value);
        virtual void SetId(const std::string& value);

        template<typename T> void DeserializeBase(AdaptiveCards::ParseContext& context, const Json::Value& json);

        virtual std::string Serialize() const;

        // Fallback and Requires support
        FallbackType GetFallbackType() const { return m_fallbackType; }

        void DeserializeBaseProperties(ParseContext& context, const Json::Value& json);
        void DeserializeBasePropertiesFromString(ParseContext& context, const std::string& jsonString);
    };
```

The astute among you may note that here we're making use of overloaded functions which is not natively supported in Javascript. Thankfully, that doesn't pose a real problem for us due to the facilities provided by `embind`. Here's the [`embind` glue](https://github.com/paulcam206/AdaptiveCards/blob/paulcam/embind-build/source/shared/cpp/ObjectModel/bindings/BaseElementBindings.cpp) we use to project this class into Javascript:

```c++
EMSCRIPTEN_BINDINGS(BaseElement)
{
    class_<BaseElement>("baseElement")
        .smart_ptr_constructor<std::shared_ptr<BaseElement>>("baseElement", &std::make_shared<BaseElement>)
        .allow_subclass<BaseElementWrapper>("baseElementWrapper")
        .function("getElementType", &BaseElement::GetElementTypeString)
        .function("setElementType", select_overload<void(const std::string&)>(&BaseElement::SetElementTypeString))
        .function("getId", &BaseElement::GetId)
        .function("setId", select_overload<void(const std::string&)>(&BaseElement::SetId))
        .function("getFallbackType", &BaseElement::GetFallbackType)
        .function("toString", &BaseElement::Serialize)
        .function("deserializeBaseProperties", &BaseElement::DeserializeBaseProperties)
        .function("deserializeBasePropertiesFromString", &BaseElement::DeserializeBasePropertiesFromString);
}
```

Every bindings declaration is wrapped in a `EMSCRIPTEN_BINDINGS(SOMETHING) {}` block. As far as I can tell, what goes inside the `()` is just a label -- there's no tie to the types being bound. The real magic starts with `class_<T>("string")`. Here `T` is the class type you're wrapping, and `"string"` is the name you want it projected as. So in this case, we're writing bindings for `class BaseElement`, which will be called `baseElement` in Javascript.

The next line, `.smart_ptr_constructor<>()` describes what type of smart pointer to use (`std::shared_ptr<BaseElement>`), what to call the smart pointer (`"baseElement"` -- should probably be `"baseElementPtr"`), and how to instantiate it (`std::make_shared<BaseElement>`).

The line after that, `.allow_subclass<>()` I'll come back to, but for now, just know that we're telling `embind` that we want to be able to subclass (derive from) this class.

The remaining lines (`.function("", ...)`) describe a mapping from a function name (to be used on the Javascript side) to an actual method to call. Of note, `BaseElement` has two versions of `BaseElement::SetElementTypeString()` -- the `select_overload` macro lets us specify which one to call. If we wanted, we could expose both versions under different names to allow each to be called independently from Javascript. The syntax for `select_overload` might look a bit strange, but it's templated on method signature like this: `select_overload<return_type (comma-separated parameter list) method modifiers>(reference to method)`. "Method modifiers" here refers to bits after the parameter list like `const` or `noexcept`. It's probably also worth noting that the name we choose to expose to Javascript is entirely arbitrary, allowing us to do things like map `toString()` to `Serialize()`.

Now, back to that `.allow_subclass` bit -- I left out an important chunk of code:

```c++
class BaseElementWrapper : public wrapper<BaseElement>
{
public:
    EMSCRIPTEN_WRAPPER(BaseElementWrapper);
    void setId(const std::string& value) { return call<void>("setId", value); }
    const std::string& getId() { return call<const std::string&>("getId"); }
    std::string toString() { return call<std::string>("toString"); }
};
```

`wrapper<T>` is provided by `embind`, as is `EMSCRIPTEN_WRAPPER()`. In order to support base classes and `virtual` methods, we need to be able to indirect through the emscripten runtime so that it can choose the right methods to call. I suspect that *most* of our wrappers will look pretty much like the above -- no special processing really, just a simple `call` invocation.

One bit that I'm not particularly happy about is dealing with `enum` in this world -- we basically have to duplicate our `enum`s like [this](https://github.com/paulcam206/AdaptiveCards/blob/paulcam/embind-build/source/shared/cpp/ObjectModel/bindings/EnumBindings.cpp):

```c++
enum_<FallbackType>("FallbackType")
    .value("None", FallbackType::None)
    .value("Drop", FallbackType::Drop)
    .value("Content", FallbackType::Content);
```

I suspect that we'll want to write a script or something to generate this for us.

### Performance

A few things to note about the prototype:
* uncompressed payload size is ~400KB (compared to 3.8MB for the existing JS library)
* `embind` has been used successfully to port games written in SDL or GL to run at >60fps in the browser (fun example [here](https://beta.unity3d.com/jonas/AngryBots/), more [here](https://www.webassemblygames.com/))
* I have not measured runtime memory use

### Try it out

The only tested configuration for building/running the prototype is currently in Linux or via WSL. The various tools involved ostensibly work on Windows natively, but I haven't gone through the effort of validating it. Here are instructions for building/running the prototype in Ubuntu 20.04+ either natively or via WSL:
1. Install prerequisites
    1. `sudo apt install git build-essential python3 cmake`
1. Clone AC fork
    1. `git clone https://github.com/paulcam206/AdaptiveCards <ac-location>`
    1. `cd <clone location> && git checkout paulcam/embind-build`
1. Install `emscripten`
    1. `git clone https://github.com/emscripten-core/emsdk.git ~/emsdk`
    1. `cd ~/emsdk && git pull && ./emsdk install latest && ./emsdk activate latest`
1. Build `ObjectModel` and test
    1. `source ~/emsdk/emsdk_env.sh`
    1. `cd <ac-location>/source/shared/ObjectModel`
    1. `emcmake cmake .`
    1. `cmake --build . --parallel`
    1. `python3 -m http.server`
    1. Start a web browser, point it at `http://localhost:8000/foo.html`, and poke around in devtools

# Appendices

## Appendix: Helpful Resources

* [`embind` walkthrough docs](https://emscripten.org/docs/porting/connecting_cpp_and_javascript/embind.html)
* [bind.h API docs](https://emscripten.org/docs/api_reference/bind.h.html)
* [`embind` test suite](https://github.com/emscripten-core/emscripten/tree/main/tests/embind) (has useful examples for different scenarios)
* [Chrome WASM debugging](https://developer.chrome.com/blog/wasm-debugging-2020/)
    * Note that source mapping doesn't *quite* work if building via WSL, because paths are based on the WSL filesystem
    * I should also note that I haven't tried to get this working in Edge, so it may or may not work...
* [Loading WASM efficiently via script](https://developers.google.com/web/updates/2018/04/loading-wasm)
* [Official `emscripten` build env docker image](https://hub.docker.com/repository/r/emscripten/emsdk)
* [Docs for shipping WASM as an npm package](https://developers.google.com/web/updates/2019/01/emscripten-npm)

## Appendix: Open Questions

* How do we reconcile native Javascript JSON support with jsoncpp? Maybe we write some helpers?
* Do we need a Javascript wrapper layer? Might be nice (e.g. to make authoring custom elements and parsing easier), but unclear if strictly required.

## Appendix: `embind` Cookbook

Prototype development took a fair bit of time. A good deal of that time was spent fighting with embind syntax or other toolchain issues. Some seemingly intractable problems were ultimately resolveable, but only after some deep digging. Most of the issues stemmed from an incomplete understanding of the toolchain or the operating environment. Below are some things I wish I'd known before I started.

The prototype generates two outputs of interest -- `ObjectModel.wasm` and `ObjectModel.js`. The `.wasm` file is really what was compiled. The `.js` file serves as the loader for the `.wasm` file and is, as far as I can tell, boilerplate code that doesn't change build-to-build. The Javascript glue is, however, critically important to the runtime environment -- it serves as the layer that translates inputs and outputs across the Javascript<->C++ boundary. Because the `.js` isn't specialized in any way at build time, **a successful build does not necessarily mean that your code is actually going to work or that you authored a binding correctly**.

### A most unfortunate occurrance

Consider this scenario:

```c++
class Sneaky
{
    // has some stuff... doesn't really matter.
};

class ClassToExpose
{
public:
    int GetRandomInteger();
    Sneaky GimmeTheSneaky();
};

EMSCRIPTEN_BINDINGS(OhNo)
{
    class_<ClassToExpose>("classToExpose")
        .constructor()
        .function("rand", &ClassToExpose::GetRandomInteger)
        .function("getTheSneaky", &ClassToExpose::GimmeTheSneaky);
}
```

This code will compile just fine. You'll even be able to instantiate `ClassToExpose` e.g. `let instance = new Module.classToExpose()`. Indeed, a subsequent call to `instance.rand()` will return without incident. However (and you might've already guessed this), a call to `instance.getTheSneaky()` will throw an exception on return because *there are no bindings for `Sneaky`*, and so there's no Javascript-world representation of the result. You'll see something like this in the dev console:

```
BindingError: parameter 2 has unknown type N4Json5ValueE
    at BindingError.<anonymous> (http://localhost:8000/ObjectModel.js:1659:24)
    at new BindingError (eval at createNamedFunction (http://localhost:8000/ObjectModel.js:1602:14), <anonymous>:4:34)
    at throwBindingError (http://localhost:8000/ObjectModel.js:1736:13)
    at requireRegisteredType (http://localhost:8000/ObjectModel.js:1775:11)
    at __emval_lookupTypes (http://localhost:8000/ObjectModel.js:3531:18)
    at __emval_get_method_caller (http://localhost:8000/ObjectModel.js:3590:19)
    at emscripten::internal::Signature<std::__2::shared_ptr<AdaptiveCards::BaseCardElement>, AdaptiveCards::ParseContext&, Json::Value const&>::init_method_caller() (http://localhost:8000/ObjectModel.wasm:wasm-function[20062]:0x9286d)
    at emscripten::internal::Signature<std::__2::shared_ptr<AdaptiveCards::BaseCardElement>, AdaptiveCards::ParseContext&, Json::Value const&>::get_method_caller() (http://localhost:8000/ObjectModel.wasm:wasm-function[20058]:0x927b8)
    at emscripten::internal::MethodCaller<std::__2::shared_ptr<AdaptiveCards::BaseCardElement>, AdaptiveCards::ParseContext&, Json::Value const&>::call(emscripten::internal::_EM_VAL*, char const*, AdaptiveCards::ParseContext&, Json::Value const&) (http://localhost:8000/ObjectModel.wasm:wasm-function[20057]:0x9274a)
    at std::__2::shared_ptr<AdaptiveCards::BaseCardElement> emscripten::val::call<std::__2::shared_ptr<AdaptiveCards::BaseCardElement>, AdaptiveCards::ParseContext&, Json::Value const&>(char const*, AdaptiveCards::ParseContext&, Json::Value const&) const (http://localhost:8000/ObjectModel.wasm:wasm-function[20056]:0x92736)
```

*(in this case, I deleted bindings for `Json::Value`)*

I should note that I had to dig into the `BindingError` to get this detail and that sometimes the stack is... less helpful.

### Virtually virtual

Going from a completely unbound (i.e. there are no `EMSCRIPTEN_BINDINGS` authored) class to something fully usable and extendable in Javascript is a bit of A Journey.

I'm going to do this example in the abstract<a id="sup1" href="#note1"><sup>1</sup></a>. Consider:

```c++
class AbstractClass
{
public:
    virtual void AbstractMethod() = 0;
};

class ConcreteClass : public AbstractClass
{
public:
    ConcreteClass() = default;

    void AbstractMethod() override
    {
        // do some work
    }
};

class ThingDoer
{
public:
    static void DoTheThing(std::shared_ptr<AbstractClass> theAbstractClass)
    {
        theAbstractClass->AbstractMethod();
    }
};
```

We want to be able to do something like this:

```javascript
// instantiate and pass ConcreteClass
let myInstance = new Module.concreteClass();
Module.thingDoer.doTheThing(myInstance);
```

In my experience, the best way to go about wiring this up is to go inside-out:

```c++
// start with bindings for AbstractClass

EMSCRIPTEN_BINDINGS(AbstractClass)
{
    class_<AbstractClass>("abstractClass") // we'll refer to this as "abstractClass" in Javascript
        .smart_ptr<std::shared_ptr<AbstractClass>>("abstractClassPtr") // make sure we know how to use smart pointers for this class
        .function("abstractMethod", &AbstractClass::AbstractMethod, pure_virtual());
        //   requires Javascript-derived classes to implement ------^
}

// now we need to add bindings for ConcreteClass in order to be able to instantiate it in Javascript
EMSCRIPTEN_BINDINGS(ConcreteClass)
{
    class_<ConcreteClass, base<AbstractClass>>("concreteClass")
        .smart_ptr_constructor<std::shared_ptr<ConcreteClass>>("concreteClassPtr", &std::make_shared<ConcreteClass>)
        .function("abstractMethod, &ConcreteClass::AbstractMethod);
}

// and finally, expose ThingDoer's static method
EMSCRIPTEN_BINDINGS(ThingDoer)
{
    class_<ThingDoer>("thingDoer")
        .class_function("doTheThing", &ThingDoer::DoTheThing);
        // ^-- class function == static method
}
```
*(see "Who's the smart one now?" below for more details about smart pointers)*

At this point, the target Javascript blurb will work, **but** there's no way for Javascript authors to create their own implementation of `AbstractClass`. In order to do that, the runtime needs to be able to make a runtime decision about how to direct calls from both the Javascript and C++ side. With `embind`, this is enabled through a wrapper class:

```diff
class AbstractClass
{
public:
    virtual void AbstractMethod() = 0;
};

+ class AbstractClassWrapper : public wrapper<AbstractClass>
+ {
+ public:
+     EMSCRIPTEN_WRAPPER(AbstractClassWrapper);
+
+     void AbstractMethod()
+     {
+         return call<void>("abstractMethod");
+     }
+ };

EMSCRIPTEN_BINDINGS(AbstractClass)
{
    class_<AbstractClass>("abstractClass") // we'll refer to this as "abstractClass" in Javascript
        .smart_ptr<std::shared_ptr<AbstractClass>>("abstractClassPtr") // make sure we know how to use smart pointers for this class
+       .allow_subclass<AbstractClassWrapper, std::shared_ptr<AbstractClassWrapper>>("abstractClassWrapper, "abstractClassWrapperPtr")
        .function("abstractMethod", &AbstractClass::AbstractMethod, pure_virtual());
        //   requires Javascript-derived classes to implement ------^
}
```

The `.allow_subclass` directive causes `embind` to emit some extra Javascript goo to allow authors to use the [`implement`](https://emscripten.org/docs/porting/connecting_cpp_and_javascript/embind.html#implement-example) or [`extend`](https://emscripten.org/docs/porting/connecting_cpp_and_javascript/embind.html#extend-example) mechanism to derive a class:

```javascript
let javascriptConcreteClass = Module.abstractClass.extend("abstractClass", {
  abstractMethod: function() {
    // do some stuff
  }
});

let foo = new javascriptConcreteClass();
Module.ThingDoer.doTheThing(foo); // works!
```

We're in pretty good shape now, but what if we want to derive from *`ConcreteClass`* in Javascript?

```diff
class ConcreteClass : public AbstractClass
{
public:
    ConcreteClass() = default;

    void AbstractMethod() override
    {
        // do some work
    }
};

EMSCRIPTEN_BINDINGS(ConcreteClass)
{
    class_<ConcreteClass, base<AbstractClass>>("concreteClass")
        .smart_ptr_constructor<std::shared_ptr<ConcreteClass>>("concreteClassPtr", &std::make_shared<ConcreteClass>)
+       .allow_subclass<AbstractClassWrapper, std::shared_ptr<AbstractClassWrapper>>("abstractClassWrapper, "abstractClassWrapperPtr")
        .function("abstractMethod, &ConcreteClass::AbstractMethod);
}
```

And now in Javascript:

```javascript
let javascriptConcreteDerivedClass = Module.concreteClass.extend("concreteClass", {
  __construct: function() {
    // call ConcreteClass's ctor
    this.__parent.__construct.call(this);
  },
  abstractMethod: function() {
    // perhaps do some stuff and/or
    this.__parent.abstractMethod.call(this); // optionally invoke ConcreteClass's impl
  }
});
```

### Who's the smart one now?

Another similar problem I ran into that required some learning was encountering this `UnboundTypeError`:

```
UnboundTypeError: Cannot call baseCardElementParser.deserializeFromString due to unbound types: NSt3__210shared_ptrIN13AdaptiveCards15BaseCardElementEEE
    at UnboundTypeError.<anonymous> (http://localhost:8000/ObjectModel.js:1659:24)
    at new UnboundTypeError (eval at createNamedFunction (http://localhost:8000/ObjectModel.js:1602:14), <anonymous>:4:34)
    at throwUnboundTypeError (http://localhost:8000/ObjectModel.js:2592:13)
    at baseCardElementParser.unboundTypesHandler [as deserializeFromString] (http://localhost:8000/ObjectModel.js:2962:15)
    at Object.onRuntimeInitialized (http://localhost:8000/foo.html:75:47)
    at doRun (http://localhost:8000/ObjectModel.js:4350:71)
    at run (http://localhost:8000/ObjectModel.js:4365:5)
    at runCaller (http://localhost:8000/ObjectModel.js:4320:19)
    at removeRunDependency (http://localhost:8000/ObjectModel.js:1214:7)
    at receiveInstance (http://localhost:8000/ObjectModel.js:1349:5)
```

This issue was particularly vexing because I *had* defined bindings for `BaseCardElement`. Thoroughly.

... but not thoroughly enough, as it would seem. My bindings looked something like this:

```c++
// imagine a perfectly correct implementation of BaseCardElementWrapper and EMBaseCardElementParserWrapper here

EMSCRIPTEN_BINDINGS(BaseCardElement)
{
    class_<BaseCardElement, base<BaseElement>>("baseCardElement")
        .constructor()
        .allow_subclass<BaseCardElementWrapper, std::shared_ptr<BaseCardElementWrapper>>("baseCardElementWrapper", "baseCardElementWrapperPtr")
        .function("getSeparator", &BaseCardElement::GetSeparator)
        .function("setSeparator", &BaseCardElement::SetSeparator)
        .function("getElementType", &BaseCardElement::GetElementType)
        .class_function("deserializeBasePropertiesFromString", &BaseCardElement::DeserializeBasePropertiesFromString);
}

class BaseCardElementParser
{
public:
    virtual ~BaseCardElementParser() = default;
    virtual std::shared_ptr<BaseCardElement> Deserialize(ParseContext& context, const Json::Value& value) = 0;
    virtual std::shared_ptr<BaseCardElement> DeserializeFromString(ParseContext& context, const std::string& value) = 0;
};

EMSCRIPTEN_BINDINGS(BaseCardElementParser)
{
    class_<BaseCardElementParser>("baseCardElementParser")
        .smart_ptr<std::shared_ptr<BaseCardElementParser>>("baseCardElementParser")
        .allow_subclass<EMBaseCardElementParserWrapper, std::shared_ptr<EMBaseCardElementParserWrapper>>("baseCardElementParserWrapper", "baseCardElementParserWrapperPtr")
        .function("deserialize", &BaseCardElementParser::Deserialize, pure_virtual())
        .function("deserializeFromString", &BaseCardElementParser::DeserializeFromString, pure_virtual());
}
```

I had a custom element parser, authored in Javascript, that was ultimately hitting the `UnboundTypeError` noted above when invoked. This particular issue took quite a while to track down. The hint is right there in the unbound type name: `NSt3__210shared_ptrIN13AdaptiveCards15BaseCardElementEEE`. shared_ptr... *shared_ptr*... What we're missing is goo to map smart pointers for `BaseCardElement`:

```diff
    class_<BaseCardElement, base<BaseElement>>("baseCardElement")
-       .constructor()
+       .smart_ptr<std::shared_ptr<BaseCardElement>>("baseCardElementPtr")
        .allow_subclass<BaseCardElementWrapper, std::shared_ptr<BaseCardElementWrapper>>("baseCardElementWrapper", "baseCardElementWrapperPtr")
```

A quick note on `.constructor` vs. `.smart_ptr` vs. `.smart_ptr_constructor`:
* `.constructor` defines a plain constructor to use (e.g. what's called here: `let foo = new Module.foo();`)
* `.smart_ptr` defines the type of a smart pointer to use when referencing the bound type (i.e. when we pass around a "smart pointer" to one of these things, what's the type look like?) - `smart_ptr` and `constructor` are not exclusive... if you use both, then `new Module.foo()` will return a bare pointer rather than a smart pointer
* `.smart_ptr_constructor` defines the type of a smart pointer and a means by which one can instantiate a smart-pointer-wrapped instance of a class (think `std::make_shared<BaseCardElement>()`)

---
<a id="note1" href="#sup1">1</a>:

![image](https://media1.tenor.com/images/8dd2f5811711a610e6ad24a7d36ac79d/tenor.gif)
