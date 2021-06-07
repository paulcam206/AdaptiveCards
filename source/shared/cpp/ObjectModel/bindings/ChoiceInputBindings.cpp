// Copyright (C) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"
#include "ChoiceInput.h"

namespace AdaptiveCards
{
    EMSCRIPTEN_BINDINGS(ChoiceInput)
    {
        class_<ChoiceInput>("choiceInput")
            .smart_ptr_constructor<std::shared_ptr<ChoiceInput>>("choiceInputPtr", &std::make_shared<ChoiceInput>)
            .property("title", &ChoiceInput::GetTitle, &ChoiceInput::SetTitle)
            .property("value", &ChoiceInput::GetValue, &ChoiceInput::SetValue);
    }
}
