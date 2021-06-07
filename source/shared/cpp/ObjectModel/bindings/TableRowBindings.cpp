// Copyright (C) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"
#include "TableRow.h"

namespace AdaptiveCards
{
    EMSCRIPTEN_BINDINGS(TableRowBindings)
    {
        register_vector<std::shared_ptr<TableCell>>("tableCellVector");

        class_<TableRow, base<BaseCardElement>>("tableRow")
            .smart_ptr_constructor<std::shared_ptr<TableRow>>("tableRowPtr", &std::make_shared<TableRow>)
            .function("getCells", select_overload<std::vector<std::shared_ptr<TableCell>>&()>(&TableRow::GetCells))
            .function("setCells", &TableRow::SetCells)
            .property("verticalCellContentAlignment", &TableRow::GetVerticalCellContentAlignment, &TableRow::SetVerticalCellContentAlignment)
            .property("horizontalCellContentAlignment", &TableRow::GetHorizontalCellContentAlignment, &TableRow::SetHorizontalCellContentAlignment)
            .property("style", &TableRow::GetStyle, &TableRow::SetStyle);
    }
}
