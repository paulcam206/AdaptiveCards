// Copyright (C) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"
#include "TableCell.h"

namespace AdaptiveCards
{
    EMSCRIPTEN_BINDINGS(TableCellBindings)
    {
        class_<TableCell, base<Container>>("tableCell")
            .smart_ptr_constructor<std::shared_ptr<TableCell>>("tableCellPtr", &std::make_shared<TableCell>);
    }
}
