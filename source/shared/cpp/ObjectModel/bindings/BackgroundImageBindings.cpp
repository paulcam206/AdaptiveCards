// Copyright (C) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"
#include "BackgroundImage.h"

namespace AdaptiveCards
{
    EMSCRIPTEN_BINDINGS(BackgroundImage)
    {
        class_<BackgroundImage>("backgroundImage")
            .smart_ptr_constructor<std::shared_ptr<BackgroundImage>>("backgroundImagePtr", &std::make_shared<BackgroundImage>)
            .property("url", &BackgroundImage::GetUrl, &BackgroundImage::SetUrl)
            .property("fillMode", &BackgroundImage::GetFillMode, &BackgroundImage::SetFillMode)
            .property("horizontalAlignment", &BackgroundImage::GetHorizontalAlignment, &BackgroundImage::SetHorizontalAlignment)
            .property("verticalAlignment", &BackgroundImage::GetVerticalAlignment, &BackgroundImage::SetVerticalAlignment)
            .function("toString", &BackgroundImage::Serialize);
    }
}
