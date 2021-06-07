// Copyright (C) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"
#include "FactSet.h"

namespace AdaptiveCards
{
    EMSCRIPTEN_BINDINGS(FactSetBindings)
    {
        register_vector<std::shared_ptr<Fact>>("factVector");

        class_<FactSet, base<BaseCardElement>>("factSet")
            .smart_ptr_constructor<std::shared_ptr<FactSet>>("factSetPtr", &std::make_shared<FactSet>)
            .function("getFacts", select_overload<std::vector<std::shared_ptr<Fact>>&()>(&FactSet::GetFacts));
    }
}
