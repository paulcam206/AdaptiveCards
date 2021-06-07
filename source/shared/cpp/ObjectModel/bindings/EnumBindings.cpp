// Copyright (C) Microsoft Corporation. All rights reserved.
#include "pch.h"
#include "Enums.h"

namespace AdaptiveCards
{
    EMSCRIPTEN_BINDINGS(Enums)
    {
        enum_<FallbackType>("FallbackType")
            .value("None", FallbackType::None)
            .value("Drop", FallbackType::Drop)
            .value("Content", FallbackType::Content);

        enum_<CardElementType>("CardElementType")
            .value("ActionSet", CardElementType::ActionSet)
            .value("AdaptiveCard", CardElementType::AdaptiveCard)
            .value("ChoiceInput", CardElementType::ChoiceInput)
            .value("ChoiceSetInput", CardElementType::ChoiceSetInput)
            .value("Column", CardElementType::Column)
            .value("ColumnSet", CardElementType::ColumnSet)
            .value("Container", CardElementType::Container)
            .value("Custom", CardElementType::Custom)
            .value("DateInput", CardElementType::DateInput)
            .value("Fact", CardElementType::Fact)
            .value("FactSet", CardElementType::FactSet)
            .value("Image", CardElementType::Image)
            .value("ImageSet", CardElementType::ImageSet)
            .value("Media", CardElementType::Media)
            .value("NumberInput", CardElementType::NumberInput)
            .value("RichTextBlock", CardElementType::RichTextBlock)
            .value("Table", CardElementType::Table)
            .value("TableCell", CardElementType::TableCell)
            .value("TableRow", CardElementType::TableRow)
            .value("TextBlock", CardElementType::TextBlock)
            .value("TextInput", CardElementType::TextInput)
            .value("TimeInput", CardElementType::TimeInput)
            .value("ToggleInput", CardElementType::ToggleInput)
            .value("Unknown", CardElementType::Unknown);

        enum_<InlineElementType>("InlineElementType")
            .value("TextRun", InlineElementType::TextRun);

        enum_<TextStyle>("TextStyle")
            .value("Default", TextStyle::Default)
            .value("Heading", TextStyle::Heading);

        enum_<TextSize>("TextSize")
            .value("Small", TextSize::Small)
            .value("Default", TextSize::Default)
            .value("Medium", TextSize::Medium)
            .value("Large", TextSize::Large)
            .value("ExtraLarge", TextSize::ExtraLarge);

        enum_<TextWeight>("TextWeight")
            .value("Lighter", TextWeight::Lighter)
            .value("Default", TextWeight::Default)
            .value("Bolder", TextWeight::Bolder);

        enum_<FontType>("FontType")
            .value("Default", FontType::Default)
            .value("Monospace", FontType::Monospace);

        enum_<ForegroundColor>("ForegroundColor")
            .value("Default", ForegroundColor::Default)
            .value("Dark", ForegroundColor::Dark)
            .value("Light", ForegroundColor::Light)
            .value("Accent", ForegroundColor::Accent)
            .value("Good", ForegroundColor::Good)
            .value("Warning", ForegroundColor::Warning)
            .value("Attention", ForegroundColor::Attention);

        enum_<HorizontalAlignment>("HorizontalAlignment")
            .value("Left", HorizontalAlignment::Left)
            .value("Center", HorizontalAlignment::Center)
            .value("Right", HorizontalAlignment::Right);

        enum_<VerticalAlignment>("VerticalAlignment")
            .value("Top", VerticalAlignment::Top)
            .value("Center", VerticalAlignment::Center)
            .value("Bottom", VerticalAlignment::Bottom);

        enum_<ImageFillMode>("ImageFillMode")
            .value("Cover", ImageFillMode::Cover)
            .value("RepeatHorizontally", ImageFillMode::RepeatHorizontally)
            .value("RepeatVertically", ImageFillMode::RepeatVertically)
            .value("Repeat", ImageFillMode::Repeat);

        enum_<ImageStyle>("ImageStyle")
            .value("Default", ImageStyle::Default)
            .value("Person", ImageStyle::Person);

            enum_<ImageSize>("ImageSize")
            .value("None", ImageSize::None)
            .value("Auto", ImageSize::Auto)
            .value("Stretch", ImageSize::Stretch)
            .value("Small", ImageSize::Small)
            .value("Medium", ImageSize::Medium)
            .value("Large", ImageSize::Large);

        enum_<TextInputStyle>("TextInputStyle")
            .value("Text", TextInputStyle::Text)
            .value("Tel", TextInputStyle::Tel)
            .value("Url", TextInputStyle::Url)
            .value("Email", TextInputStyle::Email);

        enum_<ActionType>("ActionType")
            .value("Unsupported", ActionType::Unsupported)
            .value("Execute", ActionType::Execute)
            .value("OpenUrl", ActionType::OpenUrl)
            .value("ShowCard", ActionType::ShowCard)
            .value("Submit", ActionType::Submit)
            .value("ToggleVisibility", ActionType::ToggleVisibility)
            .value("Custom", ActionType::Custom)
            .value("UnknownAction", ActionType::UnknownAction)
            .value("Overflow", ActionType::Overflow);

        enum_<ActionAlignment>("ActionAlignment")
            .value("Left", ActionAlignment::Left)
            .value("Center", ActionAlignment::Center)
            .value("Right", ActionAlignment::Right)
            .value("Stretch", ActionAlignment::Stretch);

        enum_<AssociatedInputs>("AssociatedInputs")
            .value("Auto", AssociatedInputs::Auto)
            .value("None", AssociatedInputs::None);

        enum_<ChoiceSetStyle>("ChoiceSetStyle")
            .value("Compact", ChoiceSetStyle::Compact)
            .value("Expanded", ChoiceSetStyle::Expanded);

        enum_<SeparatorThickness>("SeparatorThickness")
            .value("Default", SeparatorThickness::Default)
            .value("Thick", SeparatorThickness::Thick);

        enum_<Spacing>("Spacing")
            .value("Default", Spacing::Default)
            .value("None", Spacing::None)
            .value("Small", Spacing::Small)
            .value("Medium", Spacing::Medium)
            .value("Large", Spacing::Large)
            .value("ExtraLarge", Spacing::ExtraLarge)
            .value("Padding", Spacing::Padding);

        enum_<ActionsOrientation>("ActionsOrientation")
            .value("Vertical", ActionsOrientation::Vertical)
            .value("Horizontal", ActionsOrientation::Horizontal);

        enum_<ActionMode>("ActionMode")
            .value("Inline", ActionMode::Inline)
            .value("Popup", ActionMode::Popup);

        enum_<ContainerStyle>("ContainerStyle")
            .value("None", ContainerStyle::None)
            .value("Default", ContainerStyle::Default)
            .value("Emphasis", ContainerStyle::Emphasis)
            .value("Good", ContainerStyle::Good)
            .value("Attention", ContainerStyle::Attention)
            .value("Warning", ContainerStyle::Warning)
            .value("Accent", ContainerStyle::Accent);

        enum_<Mode>("Mode")
            .value("Primary", Mode::Primary)
            .value("Secondary", Mode::Secondary);

        enum_<ErrorStatusCode>("ErrorStatusCode")
            .value("InvalidJson", ErrorStatusCode::InvalidJson)
            .value("RenderFailed", ErrorStatusCode::RenderFailed)
            .value("RequiredPropertyMissing", ErrorStatusCode::RequiredPropertyMissing)
            .value("InvalidPropertyValue", ErrorStatusCode::InvalidPropertyValue)
            .value("UnsupportedParserOverride", ErrorStatusCode::UnsupportedParserOverride)
            .value("IdCollision", ErrorStatusCode::IdCollision)
            .value("CustomError", ErrorStatusCode::CustomError);

        enum_<WarningStatusCode>("WarningStatusCode")
            .value("UnknownElementType", WarningStatusCode::UnknownElementType)
            .value("UnknownActionElementType", WarningStatusCode::UnknownActionElementType)
            .value("UnknownPropertyOnElement", WarningStatusCode::UnknownPropertyOnElement)
            .value("UnknownEnumValue", WarningStatusCode::UnknownEnumValue)
            .value("NoRendererForType", WarningStatusCode::NoRendererForType)
            .value("InteractivityNotSupported", WarningStatusCode::InteractivityNotSupported)
            .value("MaxActionsExceeded", WarningStatusCode::MaxActionsExceeded)
            .value("AssetLoadFailed", WarningStatusCode::AssetLoadFailed)
            .value("UnsupportedSchemaVersion", WarningStatusCode::UnsupportedSchemaVersion)
            .value("UnsupportedMediaType", WarningStatusCode::UnsupportedMediaType)
            .value("InvalidMediaMix", WarningStatusCode::InvalidMediaMix)
            .value("InvalidColorFormat", WarningStatusCode::InvalidColorFormat)
            .value("InvalidDimensionSpecified", WarningStatusCode::InvalidDimensionSpecified)
            .value("InvalidLanguage", WarningStatusCode::InvalidLanguage)
            .value("InvalidValue", WarningStatusCode::InvalidValue)
            .value("CustomWarning", WarningStatusCode::CustomWarning)
            .value("EmptyLabelInRequiredInput", WarningStatusCode::EmptyLabelInRequiredInput)
            .value("RequiredPropertyMissing", WarningStatusCode::RequiredPropertyMissing);

        enum_<DateTimePreparsedTokenFormat>("DateTimePreparsedTokenFormat")
            .value("RegularString", DateTimePreparsedTokenFormat::RegularString)
            .value("Time", DateTimePreparsedTokenFormat::Time)
            .value("DateCompact", DateTimePreparsedTokenFormat::DateCompact)
            .value("DateShort", DateTimePreparsedTokenFormat::DateShort)
            .value("DateLong", DateTimePreparsedTokenFormat::DateLong);

        enum_<ContainerBleedDirection>("ContainerBleedDirection")
            .value("BleedRestricted", ContainerBleedDirection::BleedRestricted)
            .value("BleedLeft", ContainerBleedDirection::BleedLeft)
            .value("BleedRight", ContainerBleedDirection::BleedRight)
            .value("BleedLeftRight", ContainerBleedDirection::BleedLeftRight)
            .value("BleedUp", ContainerBleedDirection::BleedUp)
            .value("BleedLeftUp", ContainerBleedDirection::BleedLeftUp)
            .value("BleedRightUp", ContainerBleedDirection::BleedRightUp)
            .value("BleedLeftRightUp", ContainerBleedDirection::BleedLeftRightUp)
            .value("BleedDown", ContainerBleedDirection::BleedDown)
            .value("BleedLeftDown", ContainerBleedDirection::BleedLeftDown)
            .value("BleedRightDown", ContainerBleedDirection::BleedRightDown)
            .value("BleedLeftRightDown", ContainerBleedDirection::BleedLeftRightDown)
            .value("BleedUpDown", ContainerBleedDirection::BleedUpDown)
            .value("BleedLeftUpDown", ContainerBleedDirection::BleedLeftUpDown)
            .value("BleedRightUpDown", ContainerBleedDirection::BleedRightUpDown)
            .value("BleedAll", ContainerBleedDirection::BleedAll);

    enum_<IconPlacement>("IconPlacement")
            .value("AboveTitle", IconPlacement::AboveTitle)
            .value("LeftOfTitle", IconPlacement::LeftOfTitle);

    enum_<VerticalContentAlignment>("VerticalContentAlignment")
            .value("Top", VerticalContentAlignment::Top)
            .value("Center", VerticalContentAlignment::Center)
            .value("Bottom", VerticalContentAlignment::Bottom);

    enum_<HeightType>("HeightType")
            .value("Auto", HeightType::Auto)
            .value("Stretch", HeightType::Stretch);
    }
}
