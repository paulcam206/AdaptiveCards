// Copyright (C) Microsoft Corporation. All rights reserved.
#include "pch.h"
#include "BaseInputElement.h"

namespace AdaptiveCards
{
    class BaseInputElementWrapper : public wrapper<BaseInputElement>
    {
    public:
        EMSCRIPTEN_WRAPPER(BaseInputElementWrapper);
        // TODO: something?
    };

    EMSCRIPTEN_BINDINGS(AdaptiveCards)
    {
        class_<BaseInputElement, base<BaseCardElement>>("baseInputElement")
            .smart_ptr<std::shared_ptr<BaseInputElement>>("baseInputElementPtr")
            .allow_subclass<BaseInputElementWrapper, std::shared_ptr<BaseInputElementWrapper>>("baseInputElementWrapper", "baseInputElementWrapperPtr")
            .property("label", &BaseInputElement::GetLabel, &BaseInputElement::SetLabel)
            .property("isRequired", &BaseInputElement::GetIsRequired, &BaseInputElement::SetIsRequired)
            .property("errorMessage", &BaseInputElement::GetErrorMessage, &BaseInputElement::SetErrorMessage)
            .class_function("deserializeBaseProperties", &BaseInputElement::DeserializeBasePropertiesFromString);
    }
}
