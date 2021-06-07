// Copyright (C) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"
#include "CollectionTypeElement.h"

namespace AdaptiveCards
{
    EMSCRIPTEN_BINDINGS(CollectionTypeElementBindings)
    {
        class_<CollectionTypeElement, base<BaseCardElement>>("collectionTypeElement")
            .smart_ptr<std::shared_ptr<CollectionTypeElement>>("collectionTypeElementPtr")
            .property("style", &CollectionTypeElement::GetStyle, &CollectionTypeElement::SetStyle)
            .property("verticalContentAlignment", &CollectionTypeElement::GetVerticalContentAlignment, &CollectionTypeElement::SetVerticalContentAlignment)
            .property("padding", &CollectionTypeElement::GetPadding, &CollectionTypeElement::SetPadding)
            .property("bleed", &CollectionTypeElement::GetBleed, &CollectionTypeElement::SetBleed)
            .property("canBleed", &CollectionTypeElement::GetCanBleed)
            .property("bleedDirection", &CollectionTypeElement::GetBleedDirection)
            .property("selectAction", &CollectionTypeElement::GetSelectAction, &CollectionTypeElement::SetSelectAction)
            .property("backgroundImage", &CollectionTypeElement::GetBackgroundImage, &CollectionTypeElement::SetBackgroundImage)
            .property("minHeight", &CollectionTypeElement::GetMinHeight, &CollectionTypeElement::SetMinHeight);
    }
}
