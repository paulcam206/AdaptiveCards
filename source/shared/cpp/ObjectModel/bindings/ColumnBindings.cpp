// Copyright (C) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"
#include "Column.h"
#include "CollectionTypeElement.h"

namespace AdaptiveCards
{
    EMSCRIPTEN_BINDINGS(ColumnBindings)
    {
        class_<Column, base<CollectionTypeElement>>("column")
            .smart_ptr_constructor<std::shared_ptr<Column>>("columnPtr", &std::make_shared<Column>)
            .function("toString", &Column::Serialize)
            .property("width", &Column::GetWidth, select_overload<void(const std::string&)>(&Column::SetWidth))
            .property("pixelWidth", &Column::GetPixelWidth, &Column::SetPixelWidth)
            .function("getItems", select_overload<std::vector<std::shared_ptr<BaseCardElement>>&()>(&Column::GetItems))
            .property("rtl", &Column::GetRtl, &Column::SetRtl);
    }
}
