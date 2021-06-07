import * as React from 'react';
import { AdaptiveCardsConfiguration } from './Initialization'

export function SubmitAction(props) {
    return <button onClick={AdaptiveCardsConfiguration.callbacks.submit.bind(null, props.element)}>
        {props.element.iconUrl &&
         <img src={props.element.iconUrl} width="18px" height="18px" />
        }
        {props.element.title}
    </button>;
}
