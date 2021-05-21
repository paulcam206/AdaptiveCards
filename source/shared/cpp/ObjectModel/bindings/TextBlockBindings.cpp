// Copyright (C) Microsoft Corporation. All rights reserved.
#include "pch.h"
#include "TextBlock.h"

namespace AdaptiveCards
{
    // TODO: wrapper

    EMSCRIPTEN_BINDINGS(TextBlock)
    {
        class_<TextBlock, base<BaseCardElement>>("textBlock")
            .smart_ptr<std::shared_ptr<TextBlock>>("TextBlock")
            .property("text", &TextBlock::GetText, &TextBlock::SetText);
    }
}
