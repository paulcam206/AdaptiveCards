// Copyright (C) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"
#include "AuthCardButton.h"

namespace AdaptiveCards
{
    EMSCRIPTEN_BINDINGS(AuthCardButton)
    {
        class_<AuthCardButton>("authCardButton")
            .function("getType", select_overload<std::string()>(&AuthCardButton::GetType))
            .function("setType", &AuthCardButton::SetType)
            .function("getTitle", select_overload<std::string()>(&AuthCardButton::GetTitle))
            .function("setTitle", &AuthCardButton::SetTitle)
            .function("getImage", select_overload<std::string()>(&AuthCardButton::GetImage))
            .function("setImage", &AuthCardButton::SetImage)
            .function("getValue", select_overload<std::string()>(&AuthCardButton::GetValue))
            .function("setValue", &AuthCardButton::SetValue)
            .function("toString", &AuthCardButton::Serialize);
    }
}
