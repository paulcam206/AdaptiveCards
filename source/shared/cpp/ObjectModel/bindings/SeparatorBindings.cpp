// Copyright (C) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"
#include "Separator.h"

namespace AdaptiveCards
{
    EMSCRIPTEN_BINDINGS(SeparatorBindings)
    {
        class_<Separator>("separator")
            .smart_ptr_constructor<std::shared_ptr<Separator>>("separatorPtr", &std::make_shared<Separator>)
            .property("thickness", &Separator::GetThickness, &Separator::SetThickness)
            .property("color", &Separator::GetColor, &Separator::SetColor);
    }
}
