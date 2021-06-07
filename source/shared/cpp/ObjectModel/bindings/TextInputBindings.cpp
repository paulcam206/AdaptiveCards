// Copyright (C) Microsoft Corporation. All rights reserved.
#include "pch.h"
#include "TextInput.h"

namespace AdaptiveCards
{
    EMSCRIPTEN_BINDINGS(TextInput)
    {
        class_<TextInput, base<BaseInputElement>>("textInput")
            .smart_ptr_constructor<std::shared_ptr<TextInput>>("textInputPtr", &std::make_shared<TextInput>)
            .property("placeholder", &TextInput::GetPlaceholder, &TextInput::SetPlaceholder)
            .property("value", &TextInput::GetValue, &TextInput::SetValue)
            .property("isMultiline", &TextInput::GetIsMultiline, &TextInput::SetIsMultiline)
            .property("maxLength", &TextInput::GetMaxLength, &TextInput::SetMaxLength)
            .property("regex", &TextInput::GetRegex, &TextInput::SetRegex);
    }
}
