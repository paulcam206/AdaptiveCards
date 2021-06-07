import React from 'react';
//import {ACSM} from 'adaptivecards-sharedmodel';
import { TextBlock } from './TextBlock';
import { Container } from './Container';
import { SubmitAction } from './SubmitAction';

export function AcElement(props) {
    return React.createElement(AdaptiveCardsComponents[props.element.elementType], props);
}

export const AdaptiveCardsComponents = {
    Element: AcElement,
    Container: Container,
    TextBlock: TextBlock,
    "Action.Submit": SubmitAction
};
