// Copyright (C) Microsoft Corporation. All rights reserved.
#include "pch.h"
#include "ActionParserRegistration.h"
#include "ElementParserRegistration.h"
#include "ParseContext.h"

namespace AdaptiveCards
{
    // EM prefix because we already have a BaseCardElementParserWrapper
    class EMBaseCardElementParserWrapper : public wrapper<BaseCardElementParser>
    {
    public:
        EMSCRIPTEN_WRAPPER(EMBaseCardElementParserWrapper);

        std::shared_ptr<BaseCardElement> Deserialize(ParseContext& context, const Json::Value& value)
        {
            return call<std::shared_ptr<BaseCardElement>>("deserialize", context, value);
        }

        std::shared_ptr<BaseCardElement> DeserializeFromString(ParseContext& context, const std::string& value)
        {
            return call<std::shared_ptr<BaseCardElement>>("deserializeFromString", context, value);
        }
    };

    EMSCRIPTEN_BINDINGS(BaseCardElementParser)
    {
        class_<BaseCardElementParser>("baseCardElementParser")
            .smart_ptr<std::shared_ptr<BaseCardElementParser>>("baseCardElementParser")
            .allow_subclass<EMBaseCardElementParserWrapper, std::shared_ptr<EMBaseCardElementParserWrapper>>("baseCardElementParserWrapper", "baseCardElementParserWrapperPtr")
            .function("deserialize", &BaseCardElementParser::Deserialize, pure_virtual())
            .function("deserializeFromString", &BaseCardElementParser::DeserializeFromString, pure_virtual());
    }


    EMSCRIPTEN_BINDINGS(ElementParserRegistration)
    {
        class_<ElementParserRegistration>("elementParserRegistration")
            .smart_ptr_constructor<std::shared_ptr<ElementParserRegistration>>("elementParserRegistration", &std::make_shared<ElementParserRegistration>)
            .function("addParser", &ElementParserRegistration::AddParser)
            .function("removeParser", &ElementParserRegistration::RemoveParser)
            .function("getParser", &ElementParserRegistration::GetParser);
    }

    // EM prefix because we already have a BaseCardElementParserWrapper
    class EMActionElementParserWrapper : public wrapper<ActionElementParser>
    {
    public:
        EMSCRIPTEN_WRAPPER(EMActionElementParserWrapper);

        std::shared_ptr<BaseActionElement> Deserialize(ParseContext& context, const Json::Value& value)
        {
            return call<std::shared_ptr<BaseActionElement>>("deserialize", context, value);
        }

        std::shared_ptr<BaseActionElement> DeserializeFromString(ParseContext& context, const std::string& value)
        {
            return call<std::shared_ptr<BaseActionElement>>("deserializeFromString", context, value);
        }
    };

    EMSCRIPTEN_BINDINGS(ActionElementParser)
    {
        class_<ActionElementParser>("actionElementParser")
            .smart_ptr<std::shared_ptr<ActionElementParser>>("actionElementParser")
            .allow_subclass<EMActionElementParserWrapper, std::shared_ptr<EMActionElementParserWrapper>>("actionElementParserWrapper", "actionElementParserWrapperPtr")
            .function("deserialize", &ActionElementParser::Deserialize, pure_virtual())
            .function("deserializeFromString", &ActionElementParser::DeserializeFromString, pure_virtual());
    }

    EMSCRIPTEN_BINDINGS(ActionParserRegistration)
    {
        class_<ActionParserRegistration>("actionParserRegistration")
            .smart_ptr_constructor<std::shared_ptr<ActionParserRegistration>>("actionParserRegistration", &std::make_shared<ActionParserRegistration>)
            .function("addParser", &ActionParserRegistration::AddParser)
            .function("removeParser", &ActionParserRegistration::RemoveParser)
            .function("getParser", &ActionParserRegistration::GetParser);
    }
}
