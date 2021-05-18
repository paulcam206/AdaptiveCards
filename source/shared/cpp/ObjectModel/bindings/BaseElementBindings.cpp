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

    EMSCRIPTEN_BINDINGS(ACBaseElement)
    {
        class_<BaseElement>("baseElement")
            .allow_subclass<BaseElementWrapper>("BaseElementWrapper")
            .constructor()
            .function("getElementType", &BaseElement::GetElementTypeString)
            .function("setElementType", select_overload<void(const std::string&)>(&BaseElement::SetElementTypeString))
            .function("getId", &BaseElement::GetId)
            .function("setId", select_overload<void(const std::string&)>(&BaseElement::SetId))
            .function("toString", &BaseElement::Serialize);
    }
}
