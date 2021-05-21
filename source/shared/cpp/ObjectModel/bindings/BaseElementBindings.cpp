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
    };

    EMSCRIPTEN_BINDINGS(BaseElement)
    {
        class_<BaseElement>("baseElement")
            .smart_ptr<std::shared_ptr<BaseElement>>("BaseElement")
            .allow_subclass<BaseElementWrapper>("BaseElementWrapper")
            .constructor()
            .function("getElementType", &BaseElement::GetElementTypeString)
            .function("setElementType", select_overload<void(const std::string&)>(&BaseElement::SetElementTypeString))
            .function("getId", &BaseElement::GetId)
            .function("setId", select_overload<void(const std::string&)>(&BaseElement::SetId))
            .function("getFallbackType", &BaseElement::GetFallbackType)
            .function("toString", &BaseElement::Serialize);
    }
}
