// Copyright (C) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"
#include "MediaSource.h"

namespace AdaptiveCards
{
    EMSCRIPTEN_BINDINGS(MediaSourceBindings)
    {
        class_<MediaSource>("mediaSource")
            .smart_ptr_constructor<std::shared_ptr<MediaSource>>("mediaSourcePtr", &std::make_shared<MediaSource>)
            .property("mimeType", &MediaSource::GetMimeType, &MediaSource::SetMimeType)
            .property("url", &MediaSource::GetUrl, &MediaSource::SetUrl);
    }
}
