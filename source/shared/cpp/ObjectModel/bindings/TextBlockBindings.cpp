// Copyright (C) Microsoft Corporation. All rights reserved.
#include "pch.h"
#include "TextBlock.h"

namespace AdaptiveCards
{
    // TODO: wrapper?

    EMSCRIPTEN_BINDINGS(TextBlock)
    {
        register_optional<bool>("optionalBool");
        register_optional<TextStyle>("optionalTextStyle");
        register_optional<TextSize>("optionalTextSize");
        register_optional<TextWeight>("optionalTextWeight");
        register_optional<FontType>("optionalFontType");
        register_optional<ForegroundColor>("optionalForegroundColor");
        register_optional<HorizontalAlignment>("optionalHorizontalAlignment");

        class_<TextBlock, base<BaseCardElement>>("textBlock")
            .smart_ptr_constructor<std::shared_ptr<TextBlock>>("textBlockPtr", &std::make_shared<TextBlock>)
            .property("text", &TextBlock::GetText, &TextBlock::SetText)
            .property("style", &TextBlock::GetStyle, &TextBlock::SetStyle)
            .property("size", &TextBlock::GetTextSize, &TextBlock::SetText)
            .property("weight", &TextBlock::GetTextWeight, &TextBlock::SetTextWeight)
            .property("fontType", &TextBlock::GetFontType, &TextBlock::SetFontType)
            .property("color", &TextBlock::GetTextColor, &TextBlock::SetTextColor)
            .property("wrap", &TextBlock::GetWrap, &TextBlock::SetWrap)
            .property("subtle", &TextBlock::GetIsSubtle, &TextBlock::SetIsSubtle)
            .property("maxLines", &TextBlock::GetMaxLines, &TextBlock::SetMaxLines)
            .property("horizontalAlignment", &TextBlock::GetHorizontalAlignment, &TextBlock::SetHorizontalAlignment)
            .property("language", &TextBlock::GetLanguage, &TextBlock::SetLanguage);
    }
}
