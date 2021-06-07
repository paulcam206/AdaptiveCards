// Copyright (C) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"
#include "TableColumnDefinition.h"

namespace AdaptiveCards
{
    EMSCRIPTEN_BINDINGS(TableColumnDefinitionBindings)
    {
        class_<TableColumnDefinition>("tableColumnDefinition")
            .smart_ptr_constructor<std::shared_ptr<TableColumnDefinition>>("tableColumnDefinitionPtr", &std::make_shared<TableColumnDefinition>)
            .function("toString", &TableColumnDefinition::Serialize)
            .property("horizontalCellContentAlignment", &TableColumnDefinition::GetHorizontalCellContentAlignment, &TableColumnDefinition::SetHorizontalCellContentAlignment)
            .property("verticalCellContentAlignment", &TableColumnDefinition::GetVerticalCellContentAlignment, &TableColumnDefinition::SetVerticalCellContentAlignment)
            .property("width", &TableColumnDefinition::GetWidth, &TableColumnDefinition::SetWidth)
            .property("pixelWidth", &TableColumnDefinition::GetPixelWidth, &TableColumnDefinition::SetPixelWidth);
    }
}
