// Copyright (C) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"
#include "OpenUrlAction.h"

namespace AdaptiveCards
{
    EMSCRIPTEN_BINDINGS(OpenUrlActionBindings)
    {
        class_<OpenUrlAction, base<BaseActionElement>>("openUrlAction")
            .smart_ptr_constructor<std::shared_ptr<OpenUrlAction>>("openUrlActionPtr", &std::make_shared<OpenUrlAction>)
            .property("url", &OpenUrlAction::GetUrl, &OpenUrlAction::SetUrl);
    }
}
