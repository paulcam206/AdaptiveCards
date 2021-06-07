// Copyright (C) Microsoft Corporation. All rights reserved.
#include "pch.h"
#include "SubmitAction.h"

namespace AdaptiveCards
{
    EMSCRIPTEN_BINDINGS(SubmitAction)
    {
        class_<SubmitAction, base<BaseActionElement>>("submitAction")
            .smart_ptr_constructor<std::shared_ptr<SubmitAction>>("submitActionPtr", &std::make_shared<SubmitAction>)
            .property("dataJson", &SubmitAction::GetDataJson, select_overload<void(const std::string)>(&SubmitAction::SetDataJson));
    }
}
