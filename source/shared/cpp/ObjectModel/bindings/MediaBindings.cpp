// Copyright (C) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"
#include "Media.h"

namespace AdaptiveCards
{
    EMSCRIPTEN_BINDINGS(MediaBindings)
    {
        register_vector<std::shared_ptr<MediaSource>>("mediaSourceVector");

        class_<Media, base<BaseCardElement>>("media")
            .smart_ptr_constructor<std::shared_ptr<Media>>("mediaPtr", &std::make_shared<Media>)
            .property("poster", &Media::GetPoster, &Media::SetPoster)
            .property("altText", &Media::GetAltText, &Media::SetAltText)
            .function("getSources", &Media::GetSources);
    }
}
