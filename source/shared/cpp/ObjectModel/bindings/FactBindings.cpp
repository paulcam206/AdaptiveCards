// Copyright (C) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"
#include "Fact.h"

namespace AdaptiveCards
{
    EMSCRIPTEN_BINDINGS(FactBindings)
    {
        class_<Fact>("fact")
            .smart_ptr_constructor<std::shared_ptr<Fact>>("factPtr", &std::make_shared<Fact>)
            .property("title", &Fact::GetTitle, &Fact::SetTitle)
            .property("value", &Fact::GetValue, &Fact::SetValue)
            .property("language", &Fact::GetLanguage, &Fact::SetLanguage)
            .function("toString", &Fact::Serialize);
    }
}
