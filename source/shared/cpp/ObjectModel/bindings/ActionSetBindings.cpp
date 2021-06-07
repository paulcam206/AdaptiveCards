// Copyright (C) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"
#include "ActionSet.h"

namespace AdaptiveCards
{
    EMSCRIPTEN_BINDINGS(ActionSetBindings)
    {
        class_<ActionSet, base<BaseCardElement>>("actionSet")
            .function("getActions", select_overload<std::vector<std::shared_ptr<BaseActionElement>>&()>(&ActionSet::GetActions));
    }
}
