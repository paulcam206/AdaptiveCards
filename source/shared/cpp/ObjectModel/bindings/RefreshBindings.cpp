// Copyright (C) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"
#include "Refresh.h"

namespace AdaptiveCards
{
    EMSCRIPTEN_BINDINGS(RefreshBindings)
    {
        class_<Refresh>("refresh")
            .smart_ptr_constructor<std::shared_ptr<Refresh>>("refreshPtr", &std::make_shared<Refresh>)
            .function("getAction", select_overload<std::shared_ptr<BaseActionElement>()>(&Refresh::GetAction))
            .function("setAction", &Refresh::SetAction)
            .function("getUserIds", select_overload<std::vector<std::string>&()>(&Refresh::GetUserIds))
            .function("setUserIds", &Refresh::SetUserIds)
            .function("toString", &Refresh::Serialize);
    }
}
