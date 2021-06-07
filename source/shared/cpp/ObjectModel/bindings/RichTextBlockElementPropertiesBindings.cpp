// Copyright (C) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"
#include "RichTextElementProperties.h"

namespace AdaptiveCards
{
    EMSCRIPTEN_BINDINGS(RichTextElementPropertiesBindings)
    {
        class_<RichTextElementProperties, base<TextElementProperties>>("richTextElementProperties")
            .smart_ptr_constructor<std::shared_ptr<RichTextElementProperties>>("richTextElementPropertiesPtr", &std::make_shared<RichTextElementProperties>)
            .property("italic", &RichTextElementProperties::GetItalic, &RichTextElementProperties::SetItalic)
            .property("strikethrough", &RichTextElementProperties::GetStrikethrough, &RichTextElementProperties::SetStrikethrough)
            .property("underline", &RichTextElementProperties::GetUnderline, &RichTextElementProperties::SetUnderline);
    }
}
