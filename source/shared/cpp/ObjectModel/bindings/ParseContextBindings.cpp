// Copyright (C) Microsoft Corporation. All rights reserved.
#include "pch.h"
#include "ParseContext.h"

namespace AdaptiveCards
{
    EMSCRIPTEN_BINDINGS(ParseContext)
    {
        class_<ParseContext>("parseContext")
            .smart_ptr_constructor<std::shared_ptr<ParseContext>>("parseContext", &std::make_shared<ParseContext>)
            .property("elementParserRegistration", &ParseContext::elementParserRegistration);
    }
}
