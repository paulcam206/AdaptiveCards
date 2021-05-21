// Copyright (C) Microsoft Corporation. All rights reserved.
#include "pch.h"
#include "Enums.h"

namespace AdaptiveCards
{
    EMSCRIPTEN_BINDINGS(Enums)
    {
        enum_<FallbackType>("FallbackType")
            .value("None", FallbackType::None)
            .value("Drop", FallbackType::Drop)
            .value("Content", FallbackType::Content);

        enum_<CardElementType>("CardElementType")
            .value("ActionSet", CardElementType::ActionSet)
            .value("AdaptiveCard", CardElementType::AdaptiveCard)
            .value("ChoiceInput", CardElementType::ChoiceInput)
            .value("ChoiceSetInput", CardElementType::ChoiceSetInput)
            .value("Column", CardElementType::Column)
            .value("ColumnSet", CardElementType::ColumnSet)
            .value("Container", CardElementType::Container)
            .value("Custom", CardElementType::Custom)
            .value("DateInput", CardElementType::DateInput)
            .value("Fact", CardElementType::Fact)
            .value("FactSet", CardElementType::FactSet)
            .value("Image", CardElementType::Image)
            .value("ImageSet", CardElementType::ImageSet)
            .value("Media", CardElementType::Media)
            .value("NumberInput", CardElementType::NumberInput)
            .value("RichTextBlock", CardElementType::RichTextBlock)
            .value("Table", CardElementType::Table)
            .value("TableCell", CardElementType::TableCell)
            .value("TableRow", CardElementType::TableRow)
            .value("TextBlock", CardElementType::TextBlock)
            .value("TextInput", CardElementType::TextInput)
            .value("TimeInput", CardElementType::TimeInput)
            .value("ToggleInput", CardElementType::ToggleInput)
            .value("Unknown", CardElementType::Unknown);
    }
}
