// Copyright (C) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"
#include "Image.h"

namespace AdaptiveCards
{
    EMSCRIPTEN_BINDINGS(ImageBindings)
    {
        class_<Image, base<BaseCardElement>>("image")
            .smart_ptr_constructor<std::shared_ptr<Image>>("imagePtr", &std::make_shared<Image>)
            .property("url", &Image::GetUrl, &Image::SetUrl)
            .property("backgroundColor", &Image::GetBackgroundColor, &Image::SetBackgroundColor)
            .property("style", &Image::GetImageStyle, &Image::SetImageStyle)
            .property("size", &Image::GetImageSize, &Image::SetImageSize)
            .property("altText", &Image::GetAltText, &Image::SetAltText)
            .property("horizontalAlignment", &Image::GetHorizontalAlignment, &Image::SetHorizontalAlignment)
            .property("selectAction", &Image::GetSelectAction, &Image::SetSelectAction)
            .property("pixelWidth", &Image::GetPixelWidth, &Image::SetPixelWidth)
            .property("pixelHeight", &Image::GetPixelHeight, &Image::SetPixelHeight);
    }
}
