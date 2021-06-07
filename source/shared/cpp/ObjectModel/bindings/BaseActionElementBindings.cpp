// Copyright (C) Microsoft Corporation. All rights reserved.
#include "pch.h"
#include "BaseActionElement.h"

namespace AdaptiveCards
{
    class BaseActionElementWrapper : public wrapper<BaseActionElement>
    {
    public:
        EMSCRIPTEN_WRAPPER(BaseActionElementWrapper);
    };

    EMSCRIPTEN_BINDINGS()
    {
        class_<BaseActionElement, base<BaseElement>>("baseActionElement")
            .smart_ptr<std::shared_ptr<BaseActionElement>>("baseActionElementPtr")
            .allow_subclass<BaseActionElementWrapper, std::shared_ptr<BaseActionElementWrapper>>("baseActionElementWrapper", "baseActionElementWrapperPtr")
            .property("title", &BaseActionElement::GetTitle, select_overload<void(const std::string&)>(&BaseActionElement::SetTitle))
            .property("iconUrl", &BaseActionElement::GetIconUrl, select_overload<void(const std::string&)>(&BaseActionElement::SetIconUrl))
            .property("style", &BaseActionElement::GetStyle, select_overload<void(const std::string&)>(&BaseActionElement::SetStyle))
            .property("tooltip", &BaseActionElement::GetTooltip, select_overload<void(const std::string&)>(&BaseActionElement::SetTooltip));
    }
}
