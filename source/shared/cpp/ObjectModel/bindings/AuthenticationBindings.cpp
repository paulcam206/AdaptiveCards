// Copyright (C) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"
#include "Authentication.h"
#include "AuthCardButton.h"

namespace AdaptiveCards
{
    EMSCRIPTEN_BINDINGS(Authentication)
    {
        register_vector<std::shared_ptr<AuthCardButton>>("authCardButtonPtrArray");

        class_<Authentication>("authentication")
            .function("getButtons", select_overload<std::vector<std::shared_ptr<AuthCardButton>>&()>(&Authentication::GetButtons))
            .function("setButtons", &Authentication::SetButtons)
            .function("getConnectionName", select_overload<std::string()>(&Authentication::GetConnectionName))
            .function("setConnectionName", &Authentication::SetConnectionName)
            .function("getText", select_overload<std::string()>(&Authentication::GetText))
            .function("setText", &Authentication::SetText)
            .function("toString", &Authentication::Serialize);
    }
}
