// Copyright (C) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"
#include "ExecuteAction.h"

namespace AdaptiveCards
{
    EMSCRIPTEN_BINDINGS(ExecuteActionBindings)
    {
        class_<ExecuteAction, base<BaseActionElement>>("executeAction")
            .smart_ptr_constructor<std::shared_ptr<ExecuteAction>>("executeActionPtr", &std::make_shared<ExecuteAction>)
            .property("data", &ExecuteAction::GetDataJson, select_overload<void(const std::string)>(&ExecuteAction::SetDataJson))
            .property("verb", &ExecuteAction::GetVerb, &ExecuteAction::SetVerb);
    }
}
