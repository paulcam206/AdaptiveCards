// Copyright (C) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"
#include "Inline.h"

namespace AdaptiveCards
{
    EMSCRIPTEN_BINDINGS(InlineBindings)
    {
        class_<Inline>("inline")
            .smart_ptr_constructor<std::shared_ptr<Inline>>("inlinePtr", &std::make_shared<Inline>)
            .property("type", &Inline::GetInlineTypeString);
    }
}
