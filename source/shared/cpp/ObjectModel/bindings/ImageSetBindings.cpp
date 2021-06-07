// Copyright (C) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"
#include "ImageSet.h"

namespace AdaptiveCards
{
    EMSCRIPTEN_BINDINGS(ImageSetBindings)
    {
        register_vector<std::shared_ptr<Image>>("imageVector");

        class_<ImageSet, base<BaseCardElement>>("imageSet")
            .smart_ptr_constructor<std::shared_ptr<ImageSet>>("imageSetPtr", &std::make_shared<ImageSet>)
            .property("imageSize", &ImageSet::GetImageSize, &ImageSet::SetImageSize)
            .function("getImages", select_overload<std::vector<std::shared_ptr<Image>>&()>(&ImageSet::GetImages));
    }
}
