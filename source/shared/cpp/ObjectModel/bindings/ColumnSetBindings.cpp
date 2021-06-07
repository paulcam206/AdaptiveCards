// Copyright (C) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"
#include "ColumnSet.h"

namespace AdaptiveCards
{
    EMSCRIPTEN_BINDINGS(ColumnSetBindings)
    {
        register_vector<std::shared_ptr<Column>>("columnVector");

        class_<ColumnSet, base<CollectionTypeElement>>("columnSet")
            .smart_ptr_constructor<std::shared_ptr<ColumnSet>>("columnSetPtr", &std::make_shared<ColumnSet>)
            .function("getColumns", select_overload<std::vector<std::shared_ptr<Column>>&()>(&ColumnSet::GetColumns));
    }
}
