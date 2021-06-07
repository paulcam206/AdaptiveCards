import * as React from 'react';
import { AdaptiveCardsConfiguration } from './Initialization'
import { AdaptiveCardsComponents } from './render'

export function Container(props) {
    const element = props.element;
    let containerStyle;
    switch(element.style) {
        case AdaptiveCardsConfiguration.sharedModel.ContainerStyle.None:
        case AdaptiveCardsConfiguration.sharedModel.ContainerStyle.Default:
            containerStyle = AdaptiveCardsConfiguration.hostConfig.containerStyles.defaultPalette;
            break;
            
        case AdaptiveCardsConfiguration.sharedModel.ContainerStyle.Emphasis:
            containerStyle = AdaptiveCardsConfiguration.hostConfig.containerStyles.emphasisPalette;
            break;
            
        case AdaptiveCardsConfiguration.sharedModel.ContainerStyle.Good:
            containerStyle = AdaptiveCardsConfiguration.hostConfig.containerStyles.goodPalette;
            break;
            
        case AdaptiveCardsConfiguration.sharedModel.ContainerStyle.Attention:
            containerStyle = AdaptiveCardsConfiguration.hostConfig.containerStyles.attentionPalette;
            break;
            
        case AdaptiveCardsConfiguration.sharedModel.ContainerStyle.Warning:
            containerStyle = AdaptiveCardsConfiguration.hostConfig.containerStyles.warningPalette;
            break;
            
        case AdaptiveCardsConfiguration.sharedModel.ContainerStyle.Accent:
            containerStyle = AdaptiveCardsConfiguration.hostConfig.containerStyles.accentPalette;
            break;
    }

    let inlineStyle = {};
    inlineStyle["color"] = containerStyle.foregroundColors.defaultColor; // this is wrong
    inlineStyle["backgroundColor"] = containerStyle.backgroundColor;
    inlineStyle["border"] = `solid ${containerStyle.borderThickness} ${containerStyle.borderColor}`;

    let children = [];
    const childElements = element.getItems();
    for (let i = 0; i < childElements.size(); i++) {
        children = [...children, <AdaptiveCardsComponents.Element element={childElements.get(i)} />];
    }

    return <div style={inlineStyle}>{...children}</div>;
}
