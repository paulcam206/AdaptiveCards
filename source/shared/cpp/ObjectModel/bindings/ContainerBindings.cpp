// Copyright (C) Microsoft Corporation. All rights reserved.
#include "pch.h"
#include "Container.h"

namespace AdaptiveCards
{
    EMSCRIPTEN_BINDINGS(Container)
    {
        register_vector<std::shared_ptr<BaseCardElement>>("vector<BaseCardElementPtr>");

        class_<Container, base<CollectionTypeElement>>("Container")
            .smart_ptr_constructor<std::shared_ptr<Container>>("ContainerPtr", &std::make_shared<Container>)
            .property("rtl", &Container::GetRtl, &Container::SetRtl)
            .function("getItems", select_overload<std::vector<std::shared_ptr<BaseCardElement>>&()>(&Container::GetItems));
    }
}
