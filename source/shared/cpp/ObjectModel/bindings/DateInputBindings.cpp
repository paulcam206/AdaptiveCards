// Copyright (C) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"
#include "DateInput.h"

namespace AdaptiveCards
{
    EMSCRIPTEN_BINDINGS(DateInputBindings)
    {
        class_<DateInput, base<BaseInputElement>>("dateInput")
            .smart_ptr_constructor<std::shared_ptr<DateInput>>("dateInputPtr", &std::make_shared<DateInput>)
            .property("max", &DateInput::GetMax, &DateInput::SetMax)
            .property("min", &DateInput::GetMin, &DateInput::SetMin)
            .property("placeholder", &DateInput::GetPlaceholder, &DateInput::SetPlaceholder)
            .property("value", &DateInput::GetValue, &DateInput::SetValue);
    }
}
