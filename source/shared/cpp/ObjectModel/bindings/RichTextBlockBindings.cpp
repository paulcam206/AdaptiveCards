// Copyright (C) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"
#include "RichTextBlock.h"

namespace AdaptiveCards
{
    EMSCRIPTEN_BINDINGS(RichTextBlockBindings)
    {
        register_vector<std::shared_ptr<Inline>>("inlineVector");

        class_<RichTextBlock, base<BaseCardElement>>("richTextBlock")
            .smart_ptr_constructor<std::shared_ptr<RichTextBlock>>("richTextBlockPtr", &std::make_shared<RichTextBlock>)
            .property("horizontalAlignment", &RichTextBlock::GetHorizontalAlignment, &RichTextBlock::SetHorizontalAlignment)
            .function("getInlines", select_overload<std::vector<std::shared_ptr<Inline>>&()>(&RichTextBlock::GetInlines));
    }
}
