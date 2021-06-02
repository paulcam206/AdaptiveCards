// Copyright (C) Microsoft Corporation. All rights reserved.
#include "pch.h"
#include "SharedAdaptiveCard.h"
#include "ParseResult.h"

namespace AdaptiveCards
{
    EMSCRIPTEN_BINDINGS(AdaptiveCard)
    {
        class_<ParseResult>("parseResult")
            .smart_ptr<std::shared_ptr<ParseResult>>("parseResultPtr")
            .property("card", &ParseResult::GetAdaptiveCard);

        class_<AdaptiveCard>("adaptiveCard")
            .smart_ptr_constructor<std::shared_ptr<AdaptiveCard>>("adaptiveCardPtr", &std::make_shared<AdaptiveCard>)
            .function("getBody", select_overload<std::vector<std::shared_ptr<BaseCardElement>>&()>(&AdaptiveCard::GetBody))
            .property("version", &AdaptiveCard::GetVersion, &AdaptiveCard::SetVersion)
            .function("toString", &AdaptiveCard::Serialize)
            .class_function("fromString", select_overload<std::shared_ptr<ParseResult>(const std::string&, const std::string&)>(&AdaptiveCard::DeserializeFromString));
    }
}
