// Copyright (C) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"
#include "Table.h"

namespace AdaptiveCards
{
    EMSCRIPTEN_BINDINGS(TableBindings)
    {
        register_vector<std::shared_ptr<TableRow>>("tableRowVector");

        class_<Table>("table")
            .smart_ptr_constructor<std::shared_ptr<Table>>("tablePtr", &std::make_shared<Table>)
            .property("showGridLines", &Table::GetShowGridLines, &Table::SetShowGridLines)
            .property("firstRowAsHeaders", &Table::GetFirstRowAsHeaders, &Table::SetFirstRowAsHeaders)
            .property("horizontalCellContentAlignment", &Table::GetHorizontalCellContentAlignment, &Table::SetHorizontalCellContentAlignment)
            .property("veritcalCellContentAlignment", &Table::GetVerticalCellContentAlignment, &Table::SetVerticalCellContentAlignment)
            .property("gridStyle", &Table::GetGridStyle, &Table::SetGridStyle)
            .function("getRows", select_overload<std::vector<std::shared_ptr<TableRow>>&()>(&Table::GetRows))
            .function("setRows", &Table::SetRows);
    }
}
