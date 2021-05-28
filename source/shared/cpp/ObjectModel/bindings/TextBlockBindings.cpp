// Copyright (C) Microsoft Corporation. All rights reserved.
#include "pch.h"
#include "TextBlock.h"

namespace AdaptiveCards
{
    // TODO: wrapper

    EMSCRIPTEN_BINDINGS(TextBlock)
    {
        class_<TextBlock, base<BaseCardElement>>("textBlock")
            .smart_ptr_constructor<std::shared_ptr<TextBlock>>("TextBlock", &std::make_shared<TextBlock>)
            .property("text", &TextBlock::GetText, &TextBlock::SetText);
    }
}
