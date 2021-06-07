// Copyright (C) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"
#include "ShowCardAction.h"

namespace AdaptiveCards
{
    EMSCRIPTEN_BINDINGS(ShowCardActionBindings)
    {
        class_<ShowCardAction, base<BaseActionElement>>("showCardAction")
            .smart_ptr_constructor<std::shared_ptr<ShowCardAction>>("showCardActionPtr", &std::make_shared<ShowCardAction>)
            .property("card", &ShowCardAction::GetCard, &ShowCardAction::SetCard)
            .function("setLanguage", &ShowCardAction::SetLanguage);
    }
}
