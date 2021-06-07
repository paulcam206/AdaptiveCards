import { ACSM } from 'adaptivecards-sharedmodel';
import { AdaptiveCard, /* AdaptiveCardsComponents, */ AdaptiveCardsConfiguration } from 'adaptivecards-react';
import * as React from 'react';
import * as ReactDOM from 'react-dom';

async function testAc() {
    const myCard = JSON.stringify({
        "$schema": "http://adaptivecards.io/schemas/adaptive-card.json",
        "type": "AdaptiveCard",
        "version": "1.5",
        "body": [
            {
                "type": "TextBlock",
                "text": "an actual card!"
            },
            {
                "type": "Container",
                "items": [
                    {
                        "type": "TextBlock",
                        "color": "good",
                        "weight": "bolder",
                        "text": "this is ridiculous"
                    },
                    {
                        "type": "MyCustomElement",
                        "id": "bleh",
                        "customProperty": 1024
                    }
                ]
            }
        ],
        "actions": [
            {
                "type": "Action.Submit",
                "title": "Hello WASM",
                "iconUrl": "https://upload.wikimedia.org/wikipedia/commons/thumb/1/1f/WebAssembly_Logo.svg/1200px-WebAssembly_Logo.svg.png"
            }
        ]
    });

    const ac = await ACSM.getInstance();
    const result = ac.adaptiveCard.fromString(myCard, "1.5");
    const body = result.card.getBody();
    const actions = result.card.getActions();
    console.log(`serialized as "${result.card.toString()}"`);
    console.log(`body: ${body.size()} toplevel elements`);
    console.log(`actions: ${actions.size()} actions`);
    for (let i = 0; i < actions.size(); ++i) {
        console.log(`\t${actions.get(i).toString()}`);
    }
}

async function exploreHostConfig() {
    const hostConfigFetch = await fetch('hostConfig.json');
    const hostConfigJson = await hostConfigFetch.json();
    const ac = await ACSM.getInstance();
    let hostConfig = ac.hostConfig.deserialize(JSON.stringify(hostConfigJson));
    console.log(`textBlock default font is ${hostConfig.getFontType(ac.FontType.Default).fontFamily}`);
}

function addHostConfigButton() {
    let hcButton = document.createElement('button') as HTMLButtonElement;
    hcButton.textContent = "hostConfig";
    hcButton.onclick = exploreHostConfig;
    document.body.appendChild(hcButton);
}

function addTestButton() {
    let testButton = document.createElement('button') as HTMLButtonElement;
    testButton.textContent = "test shared model";
    testButton.onclick = testAc;
    document.body.appendChild(testButton);
}

function addLazyLoadButton() {
    let llButton = document.createElement('button') as HTMLButtonElement;
    llButton.textContent = "perform lazy load";
    llButton.onclick = () => {
        ACSM.lazyLoad();
    };
    document.body.appendChild(llButton);
}

function addTextBlockButton() {
    let tbButton = document.createElement('button') as HTMLButtonElement;
    tbButton.textContent = "render card";
    tbButton.onclick = async () => {
        const hostConfigFetch = await fetch('hostConfig.json');
        const hostConfigJson = await hostConfigFetch.json();

        await AdaptiveCardsConfiguration.initialize();
        let acr = await AdaptiveCardsConfiguration.sharedModel;
        AdaptiveCardsConfiguration.hostConfig = await acr.hostConfig.deserialize(JSON.stringify(hostConfigJson));
        AdaptiveCardsConfiguration.callbacks = {
            submit: ((element) => { alert(`submit action!\ntitle: ${element.title}\ntype: ${element.elementType}`); })
        };

        const myCard = JSON.stringify({
            "$schema": "http://adaptivecards.io/schemas/adaptive-card.json",
            "type": "AdaptiveCard",
            "version": "1.5",
            "body": [
                {
                    "type": "TextBlock",
                    "color": "good",
                    "weight": "bolder",
                    "size": "extraLarge",
                    "text": "an actual card!"
                },
                {
                    "type": "Container",
                    "items": [
                        {
                            "type": "TextBlock",
                            "text": "this is ridiculous"
                        },
                        {
                            "type": "TextBlock",
                            "text": "*another one!*"
                        }
                    ]
                }
            ],
            "actions": [
                {
                    "type": "Action.Submit",
                    "title": "Hello WASM",
                    "iconUrl": "https://upload.wikimedia.org/wikipedia/commons/thumb/1/1f/WebAssembly_Logo.svg/1200px-WebAssembly_Logo.svg.png"
                }
            ]
        });

        const result = await acr.adaptiveCard.fromString(myCard, "1.5");
        ReactDOM.render(<AdaptiveCard card={result.card} />, document.querySelector("#renderedStuff"));
    };
    document.body.appendChild(tbButton);
}

addTestButton();
addLazyLoadButton();
addTextBlockButton();
addHostConfigButton();

let target = document.createElement('div') as HTMLDivElement;
target.id = "renderedStuff";
target.style.border = "solid";
document.body.appendChild(document.createElement('hr'));
document.body.appendChild(target);
