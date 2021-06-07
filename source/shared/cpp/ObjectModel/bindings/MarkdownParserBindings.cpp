// Copyright (C) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"
#include "MarkDownParser.h"

namespace AdaptiveCards
{
    EMSCRIPTEN_BINDINGS(MarkDownParserBindings)
    {
        class_<MarkDownParser>("markdownParser")
            .smart_ptr_constructor<std::shared_ptr<MarkDownParser>, const std::string&>("markdownParserPtr", &std::make_shared<MarkDownParser>)
            .function("getHtml", &MarkDownParser::TransformToHtml)
            .function("getRawText", &MarkDownParser::GetRawText)
            .function("hasTags", &MarkDownParser::HasHtmlTags);
    }
}
