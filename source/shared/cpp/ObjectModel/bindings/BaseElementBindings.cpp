// Copyright (C) Microsoft Corporation. All rights reserved.
#include "pch.h"
#include "BaseElement.h"

namespace AdaptiveCards
{
    class BaseElementWrapper : public wrapper<BaseElement>
    {
    public:
        EMSCRIPTEN_WRAPPER(BaseElementWrapper);
        void setId(const std::string& value) { return call<void>("setId", value); }
        const std::string& getId() { return call<const std::string&>("getId"); }
        std::string toString() { return call<std::string>("toString"); }
    };

    EMSCRIPTEN_BINDINGS(BaseElement)
    {
        class_<BaseElement>("baseElement")
            .smart_ptr_constructor<std::shared_ptr<BaseElement>>("baseElement", &std::make_shared<BaseElement>)
            .allow_subclass<BaseElementWrapper>("baseElementWrapper")
            .property("elementType", &BaseElement::GetElementTypeString, select_overload<void(const std::string&)>(&BaseElement::SetElementTypeString))
            .property("id", &BaseElement::GetId, select_overload<void(const std::string&)>(&BaseElement::SetId))
            .function("getFallbackType", &BaseElement::GetFallbackType)
            .function("toString", &BaseElement::Serialize)
            .function("deserializeBaseProperties", &BaseElement::DeserializeBaseProperties)
            .function("deserializeBasePropertiesFromString", &BaseElement::DeserializeBasePropertiesFromString);
    }
}
