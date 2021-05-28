// Copyright (C) Microsoft Corporation. All rights reserved.
#include "pch.h"
#include "BaseCardElement.h"
#include "ParseContext.h"

namespace AdaptiveCards
{
    class BaseCardElementWrapper : public wrapper<BaseCardElement>
    {
    public:
        EMSCRIPTEN_WRAPPER(BaseCardElementWrapper);

        bool GetSeparator() const
        {
            return call<bool>("getSeparator");
        }

        void SetSeparator(bool value)
        {
            return call<void>("setSeparator", value);
        }
    };

    EMSCRIPTEN_BINDINGS(BaseCardElement)
    {
        class_<BaseCardElement, base<BaseElement>>("baseCardElement")
            .smart_ptr<std::shared_ptr<BaseCardElement>>("baseCardElement")
            .allow_subclass<BaseCardElementWrapper>("baseCardElementWrapper")
            .function("getSeparator", &BaseCardElement::GetSeparator)
            .function("setSeparator", &BaseCardElement::SetSeparator)
            .function("getElementType", &BaseCardElement::GetElementType)
            .class_function("deserializeBasePropertiesFromString", &BaseCardElement::DeserializeBasePropertiesFromString);
    }
}
