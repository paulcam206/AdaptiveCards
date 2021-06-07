import * as React from 'react';
//import { AdaptiveCardsConfiguration } from './Initialization'
import { AdaptiveCardsComponents, AcElement } from './render'

export function AdaptiveCard(props) {
    // blah blah handle direct properties
    const theCard = props.card;

    const cardBody = theCard.getBody();
    let renderedBodyChildren = [];
    for (let i = 0; i < cardBody.size(); i++) {
        renderedBodyChildren = [...renderedBodyChildren, <AdaptiveCardsComponents.Element element={cardBody.get(i)} />];
    }

    const cardActions = theCard.getActions();
    let renderedActionChildren = [];
    for (let i = 0; i < cardActions.size(); i++) {
        renderedActionChildren = [...renderedActionChildren, <AdaptiveCardsComponents.Element element={cardActions.get(i)} />];
    }

    return <React.Fragment>
    <div>{...renderedBodyChildren}</div>
    <div>{...renderedActionChildren}</div>
    </React.Fragment>;
}
