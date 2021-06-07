import * as React from 'react';
import { AdaptiveCardsConfiguration } from './Initialization'

export function TextBlock (props) {
    const element = props.element;
    let inlineStyle = {};

    // color
    const textBlockColor = element.color.has_value() ? element.color.value() : AdaptiveCardsConfiguration.sharedModel.ForegroundColor.Default;
    const isSubtle = element.subtle.has_value() ? element.subtle.value() : false;
    inlineStyle["color"] = AdaptiveCardsConfiguration.hostConfig.getForegroundColor(AdaptiveCardsConfiguration.sharedModel.ContainerStyle.None, textBlockColor, isSubtle);

    // font stuff
    const fontType = element.fontType.has_value() ? element.fontType.value() : AdaptiveCardsConfiguration.sharedModel.FontType.Default;
    const fontWeight = element.weight.has_value() ? element.weight.value() : AdaptiveCardsConfiguration.sharedModel.TextWeight.Default;
    const fontSize = element.size.has_value() ? element.size.value() : AdaptiveCardsConfiguration.sharedModel.TextSize.Default;
    
    inlineStyle["fontFamily"] = AdaptiveCardsConfiguration.hostConfig.getFontFamily(fontType);
    inlineStyle["fontWeight"] = AdaptiveCardsConfiguration.hostConfig.getFontWeight(fontType, fontWeight);
    inlineStyle["fontSize"] = AdaptiveCardsConfiguration.hostConfig.getFontSize(fontType, fontSize);

    const hAlignment = element.horizontalAlignment.has_value() ? element.horizontalAlignment.value() : AdaptiveCardsConfiguration.sharedModel.HorizontalAlignment.Left;
    let alignString;
    switch(hAlignment) {
        case AdaptiveCardsConfiguration.sharedModel.HorizontalAlignment.Left:
            alignString = "left";
            break;
        case AdaptiveCardsConfiguration.sharedModel.HorizontalAlignment.Center:
            alignString = "center";
            break;
        case AdaptiveCardsConfiguration.sharedModel.HorizontalAlignment.Right:
            alignString = "right";
            break;
    }
    inlineStyle["textAlign"] = alignString;

    const mdParser = new AdaptiveCardsConfiguration.sharedModel.markdownParser(element.text);
    const transformed = mdParser.getHtml();
    
    if (mdParser.hasTags()) {
        const htmlPayload = { __html: transformed };
        return <div style={inlineStyle} dangerouslySetInnerHTML={htmlPayload}></div>;
    } else {
        return <div style={inlineStyle}>{mdParser.getRawText()}</div>;
    }
}
