// Copyright (C) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"
#include "NumberInput.h"

namespace AdaptiveCards
{
    EMSCRIPTEN_BINDINGS(NumberInputBindings)
    {
        class_<NumberInput, base<BaseInputElement>>("numberInput")
            .smart_ptr_constructor<std::shared_ptr<NumberInput>>("numberInputPtr", &std::make_shared<NumberInput>)
            .property("placeholder", &NumberInput::GetPlaceholder, &NumberInput::SetPlaceholder)
            .property("value", &NumberInput::GetValue, &NumberInput::SetValue)
            .property("min", &NumberInput::GetMin, &NumberInput::SetMin)
            .property("max", &NumberInput::GetMax, &NumberInput::SetMax);
    }
}
