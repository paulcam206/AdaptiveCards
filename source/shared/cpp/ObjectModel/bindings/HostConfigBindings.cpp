// Copyright (C) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"
#include "HostConfig.h"

namespace AdaptiveCards
{
    EMSCRIPTEN_BINDINGS(HostConfigBindings)
    {
        class_<FontSizesConfig>("fontSizesConfig")
            .smart_ptr_constructor<std::shared_ptr<FontSizesConfig>>("fontSizesPtr", &std::make_shared<FontSizesConfig>)
            .class_function("getDefaultFontSize", &FontSizesConfig::GetDefaultFontSize)
            .function("getFontSize", &FontSizesConfig::GetFontSize)
            .function("setFontSize", &FontSizesConfig::SetFontSize);

        class_<FontWeightsConfig>("fontWeightsConfig")
            .smart_ptr_constructor<std::shared_ptr<FontWeightsConfig>>("fontWeightsConfigPtr", &std::make_shared<FontWeightsConfig>)
            .class_function("getDefaultFontWeight", &FontWeightsConfig::GetDefaultFontWeight)
            .function("getFontWeight", &FontWeightsConfig::GetFontWeight)
            .function("setFontWeight", &FontWeightsConfig::SetFontWeight);

        class_<FontTypeDefinition>("fontTypeDefinition")
            .smart_ptr_constructor<std::shared_ptr<FontTypeDefinition>>("fontTypeDefinitionPtr", &std::make_shared<FontTypeDefinition>)
            .property("fontFamily", &FontTypeDefinition::fontFamily)
            .property("sizes", &FontTypeDefinition::fontSizes)
            .property("weights", &FontTypeDefinition::fontWeights);

        class_<FontTypesDefinition>("fontTypesDefinition")
            .smart_ptr_constructor<std::shared_ptr<FontTypesDefinition>>("fontTypesDefinitionPtr", &std::make_shared<FontTypesDefinition>)
            .property("default", &FontTypesDefinition::defaultFontType)
            .property("monospace", &FontTypesDefinition::monospaceFontType);

        class_<HighlightColorConfig>("highlightColorConfig")
            .smart_ptr_constructor<std::shared_ptr<HighlightColorConfig>>("highlightColorConfigPtr", &std::make_shared<HighlightColorConfig>)
            .property("default", &HighlightColorConfig::defaultColor)
            .property("subtle", &HighlightColorConfig::subtleColor);

        class_<ColorConfig>("colorConfig")
            .smart_ptr_constructor<std::shared_ptr<ColorConfig>>("colorConfigPtr", &std::make_shared<ColorConfig>)
            .property("default", &ColorConfig::defaultColor)
            .property("subtle", &ColorConfig::subtleColor)
            .property("highlight", &ColorConfig::highlightColors);

        class_<ColorsConfig>("colorsConfig")
            .smart_ptr_constructor<std::shared_ptr<ColorsConfig>>("colorsConfigPtr", &std::make_shared<ColorsConfig>)
            .property("default", &ColorsConfig::defaultColor)
            .property("accent", &ColorsConfig::accent)
            .property("dark", &ColorsConfig::dark)
            .property("light", &ColorsConfig::light)
            .property("good", &ColorsConfig::good)
            .property("warning", &ColorsConfig::warning)
            .property("attention", &ColorsConfig::attention);

        class_<TextStyleConfig>("textStyleConfig")
            .smart_ptr_constructor<std::shared_ptr<TextStyleConfig>>("textStyleConfigPtr", &std::make_shared<TextStyleConfig>)
            .property("weight", &TextStyleConfig::weight)
            .property("size", &TextStyleConfig::size)
            .property("isSubtle", &TextStyleConfig::isSubtle)
            .property("color", &TextStyleConfig::color)
            .property("fontType", &TextStyleConfig::fontType);

        class_<FactSetTextConfig, base<TextStyleConfig>>("factSetTextConfig")
            .smart_ptr_constructor<std::shared_ptr<FactSetTextConfig>>("factSetTextConfigPtr", &std::make_shared<FactSetTextConfig>)
            .property("wrap", &FactSetTextConfig::wrap)
            .property("maxWidth", &FactSetTextConfig::maxWidth);

        class_<TextStylesConfig>("textStylesConfig")
            .smart_ptr_constructor<std::shared_ptr<TextStylesConfig>>("textStylesConfigPtr", &std::make_shared<TextStylesConfig>)
            .property("heading", &TextStylesConfig::heading)
            .property("columnHeader", &TextStylesConfig::columnHeader);

        class_<SpacingConfig>("spacingConfig")
            .smart_ptr_constructor<std::shared_ptr<SpacingConfig>>("spacingConfigPtr", &std::make_shared<SpacingConfig>)
            .property("smallSpacing", &SpacingConfig::smallSpacing)
            .property("defaultSpacing", &SpacingConfig::defaultSpacing)
            .property("mediumSpacing", &SpacingConfig::mediumSpacing)
            .property("largeSpacing", &SpacingConfig::largeSpacing)
            .property("extraLargeSpacing", &SpacingConfig::extraLargeSpacing)
            .property("paddingSpacing", &SpacingConfig::paddingSpacing);

        class_<SeparatorConfig>("separatorConfig")
            .smart_ptr_constructor<std::shared_ptr<SeparatorConfig>>("separatorConfigPtr", &std::make_shared<SeparatorConfig>)
            .property("lineThickness", &SeparatorConfig::lineThickness)
            .property("lineColor", &SeparatorConfig::lineColor);

        class_<ImageSizesConfig>("imageSizesConfig")
            .smart_ptr_constructor<std::shared_ptr<ImageSizesConfig>>("imageSizesConfigPtr", &std::make_shared<ImageSizesConfig>)
            .property("smallSize", &ImageSizesConfig::smallSize)
            .property("mediumSize", &ImageSizesConfig::mediumSize)
            .property("largeSize", &ImageSizesConfig::largeSize);

        class_<ImageSetConfig>("imageSetConfig")
            .smart_ptr_constructor<std::shared_ptr<ImageSetConfig>>("imageSetConfigPtr", &std::make_shared<ImageSetConfig>)
            .property("imageSize", &ImageSetConfig::imageSize)
            .property("maxImageHeight", &ImageSetConfig::maxImageHeight);

        class_<ImageConfig>("imageConfig")
            .smart_ptr_constructor<std::shared_ptr<ImageConfig>>("imageConfigPtr", &std::make_shared<ImageConfig>)
            .property("size", &ImageConfig::imageSize);

        class_<AdaptiveCardConfig>("adaptiveCardConfig")
            .smart_ptr_constructor<std::shared_ptr<AdaptiveCardConfig>>("adaptiveCardConfigPtr", &std::make_shared<AdaptiveCardConfig>)
            .property("allowCustomStyle", &AdaptiveCardConfig::allowCustomStyle);

        class_<FactSetConfig>("factSetConfig")
            .smart_ptr_constructor<std::shared_ptr<FactSetConfig>>("factSetConfigPtr", &std::make_shared<FactSetConfig>)
            .property("title", &FactSetConfig::title)
            .property("value", &FactSetConfig::value)
            .property("spacing", &FactSetConfig::spacing);

        class_<ContainerStyleDefinition>("containerStyleDefinition")
            .smart_ptr_constructor<std::shared_ptr<ContainerStyleDefinition>>("containerStyleDefinitionPtr", &std::make_shared<ContainerStyleDefinition>)
            .property("backgroundColor", &ContainerStyleDefinition::backgroundColor)
            .property("borderColor", &ContainerStyleDefinition::borderColor)
            .property("borderThickness", &ContainerStyleDefinition::borderThickness)
            .property("foregroundColors", &ContainerStyleDefinition::foregroundColors);

        class_<ContainerStylesDefinition>("containerStylesDefinition")
            .smart_ptr_constructor<std::shared_ptr<ContainerStylesDefinition>>("containerStylesDefinitionPtr", &std::make_shared<ContainerStylesDefinition>)
            .property("defaultPalette", &ContainerStylesDefinition::defaultPalette)
            .property("emphasisPalette", &ContainerStylesDefinition::emphasisPalette)
            .property("goodPalette", &ContainerStylesDefinition::goodPalette)
            .property("attentionPalette", &ContainerStylesDefinition::attentionPalette)
            .property("warningPalette", &ContainerStylesDefinition::warningPalette)
            .property("accentPalette", &ContainerStylesDefinition::accentPalette);

        class_<ShowCardActionConfig>("showCardActionConfig")
            .smart_ptr_constructor<std::shared_ptr<ShowCardActionConfig>>("showCardActionConfigPtr", &std::make_shared<ShowCardActionConfig>)
            .property("actionMode", &ShowCardActionConfig::actionMode)
            .property("style", &ShowCardActionConfig::style)
            .property("inlineTopMargin", &ShowCardActionConfig::inlineTopMargin);

        class_<ActionsConfig>("actionsConfig")
            .smart_ptr_constructor<std::shared_ptr<ActionsConfig>>("actionsConfigPtr", &std::make_shared<ActionsConfig>)
            .property("showCard", &ActionsConfig::showCard)
            .property("actionsOrientation", &ActionsConfig::actionsOrientation)
            .property("actionAlignment", &ActionsConfig::actionAlignment)
            .property("buttonSpacing", &ActionsConfig::buttonSpacing)
            .property("maxActions", &ActionsConfig::maxActions)
            .property("spacing", &ActionsConfig::spacing)
            .property("iconPlacement", &ActionsConfig::iconPlacement)
            .property("iconSize", &ActionsConfig::iconSize);

        class_<InputLabelConfig>("inputLabelConfig")
            .smart_ptr_constructor<std::shared_ptr<InputLabelConfig>>("inputLabelConfigPtr", &std::make_shared<InputLabelConfig>)
            .property("color", &InputLabelConfig::color)
            .property("isSubtle", &InputLabelConfig::isSubtle)
            .property("size", &InputLabelConfig::size)
            .property("suffix", &InputLabelConfig::suffix)
            .property("weight", &InputLabelConfig::weight);

        class_<LabelConfig>("labelConfig")
            .smart_ptr_constructor<std::shared_ptr<LabelConfig>>("labelConfigPtr", &std::make_shared<LabelConfig>)
            .property("inputSpacing", &LabelConfig::inputSpacing)
            .property("requiredInputs", &LabelConfig::requiredInputs)
            .property("optionalInputs", &LabelConfig::optionalInputs);

        class_<ErrorMessageConfig>("errorMessageConfig")
            .smart_ptr_constructor<std::shared_ptr<ErrorMessageConfig>>("errorMessageConfigPtr", &std::make_shared<ErrorMessageConfig>)
            .property("size", &ErrorMessageConfig::size)
            .property("spacing", &ErrorMessageConfig::spacing)
            .property("weight", &ErrorMessageConfig::weight);

        class_<InputsConfig>("inputsConfig")
            .smart_ptr_constructor<std::shared_ptr<InputsConfig>>("inputsConfigPtr", &std::make_shared<InputsConfig>)
            .property("label", &InputsConfig::label)
            .property("errorMessage", &InputsConfig::errorMessage);

        class_<MediaConfig>("mediaConfig")
            .smart_ptr_constructor<std::shared_ptr<MediaConfig>>("mediaConfigPtr", &std::make_shared<MediaConfig>)
            .property("defaultPoster", &MediaConfig::defaultPoster)
            .property("playButton", &MediaConfig::playButton)
            .property("allowInlinePlayback", &MediaConfig::allowInlinePlayback);

        class_<TextBlockConfig>("textBlockConfig")
            .smart_ptr_constructor<std::shared_ptr<TextBlockConfig>>("textBlockConfigPtr", &std::make_shared<TextBlockConfig>)
            .property("headingLevel", &TextBlockConfig::headingLevel);

        class_<TableConfig>("tableConfig")
            .smart_ptr_constructor<std::shared_ptr<TableConfig>>("tableConfigPtr", &std::make_shared<TableConfig>)
            .property("cellSpacing", &TableConfig::cellSpacing);

        class_<HostConfig>("hostConfig")
            .smart_ptr_constructor<std::shared_ptr<HostConfig>>("hostConfigPtr", &std::make_shared<HostConfig>)
            .class_function("deserialize", &HostConfig::DeserializeFromString)
            .function("getFontType", &HostConfig::GetFontType)
            .function("getFontFamily", select_overload<std::string(FontType)const>(&HostConfig::GetFontFamily))
            .function("getFontSize", &HostConfig::GetFontSize)
            .function("getFontWeight", &HostConfig::GetFontWeight)
            .function("getBackgroundColor", &HostConfig::GetBackgroundColor)
            .function("getForegroundColor", &HostConfig::GetForegroundColor)
            .function("getHighlightColor", &HostConfig::GetHighlightColor)
            .function("getBorderColor", &HostConfig::GetBorderColor)
            .function("getBorderThickness", &HostConfig::GetBorderThickness)
            .property("fontFamily", select_overload<std::string()const>(&HostConfig::GetFontFamily), &HostConfig::SetFontFamily)
            .property("fontSizes", &HostConfig::GetFontSizes, &HostConfig::SetFontSizes)
            .property("fontWeights", &HostConfig::GetFontWeights, &HostConfig::SetFontWeights)
            .property("fontTypes", &HostConfig::GetFontTypes, &HostConfig::SetFontTypes)
            .property("supportsInteractivity", &HostConfig::GetSupportsInteractivity, &HostConfig::SetSupportsInteractivity)
            .property("imageBaseUrl", &HostConfig::GetImageBaseUrl, &HostConfig::SetImageBaseUrl)
            .property("imageSizes", &HostConfig::GetImageSizes, &HostConfig::SetImageSizes)
            .property("image", &HostConfig::GetImage, &HostConfig::SetImage)
            .property("separator", &HostConfig::GetSeparator, &HostConfig::SetSeparator)
            .property("spacing", &HostConfig::GetSpacing, &HostConfig::SetSpacing)
            .property("adaptiveCard", &HostConfig::GetAdaptiveCard, &HostConfig::SetAdaptiveCard)
            .property("imageSet", &HostConfig::GetImageSet, &HostConfig::SetImageSet)
            .property("factSet", &HostConfig::GetFactSet, &HostConfig::SetFactSet)
            .property("actions", &HostConfig::GetActions, &HostConfig::SetActions)
            .property("containerStyles", &HostConfig::GetContainerStyles, &HostConfig::SetContainerStyles)
            .property("media", &HostConfig::GetMedia, &HostConfig::SetMedia)
            .property("inputs", &HostConfig::GetInputs, &HostConfig::SetInputs)
            .property("textStyles", &HostConfig::GetTextStyles, &HostConfig::SetTextStyles)
            .property("textBlock", &HostConfig::GetTextBlock, &HostConfig::SetTextBlock)
            .property("table", &HostConfig::GetTable, &HostConfig::SetTable);
    }
}
