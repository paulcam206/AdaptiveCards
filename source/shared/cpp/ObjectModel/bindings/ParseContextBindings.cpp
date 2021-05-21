// Copyright (C) Microsoft Corporation. All rights reserved.
#include "pch.h"
#include "ParseContext.h"

namespace AdaptiveCards
{
    EMSCRIPTEN_BINDINGS(ParseContext)
    {
        class_<ParseContext>("parseContext")
            .constructor()
            .property("elementParserRegistration", &ParseContext::elementParserRegistration);
    }
}
