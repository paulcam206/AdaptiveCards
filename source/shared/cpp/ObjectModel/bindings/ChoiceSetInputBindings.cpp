// Copyright (C) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"
#include "ChoiceSetInput.h"
#include "ChoiceInput.h"

namespace AdaptiveCards
{
    EMSCRIPTEN_BINDINGS(ChoiceSetInput)
    {
        register_vector<std::shared_ptr<ChoiceInput>>("choiceInputArray");

        class_<ChoiceSetInput, base<BaseInputElement>>("choiceSetInput")
            .smart_ptr_constructor<std::shared_ptr<ChoiceSetInput>>("choiceSetInputPtr", &std::make_shared<ChoiceSetInput>)
            .property("isMultiSelect", &ChoiceSetInput::GetIsMultiSelect, &ChoiceSetInput::SetIsMultiSelect)
            .property("choiceSetStyle", &ChoiceSetInput::GetChoiceSetStyle, &ChoiceSetInput::SetChoiceSetStyle)
            .function("getChoices", select_overload<std::vector<std::shared_ptr<ChoiceInput>>&()>(&ChoiceSetInput::GetChoices));
    }
}
