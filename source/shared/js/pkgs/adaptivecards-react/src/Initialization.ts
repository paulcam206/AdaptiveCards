import { ACSM } from 'adaptivecards-sharedmodel';

export type OnSubmitCallback = (theSubmitAction) => void;

export interface Callbacks {
    submit?: OnSubmitCallback;
}

export class AdaptiveCardsConfiguration {
    private static _sharedModel = null;
    private static _callbacks : Callbacks = null;
    private static _hostConfig = null;

    public static get sharedModel() {
        return AdaptiveCardsConfiguration._sharedModel;
    }
    public static async initialize(sharedModel?) {
        if (AdaptiveCardsConfiguration._sharedModel === null) {
            AdaptiveCardsConfiguration._sharedModel = sharedModel ?? await ACSM.getInstance();
        }
    }

    public static get hostConfig() {
        return AdaptiveCardsConfiguration._hostConfig;
    }

    public static set hostConfig(value) {
        AdaptiveCardsConfiguration._hostConfig = value;
    }

    public static get callbacks() {
        return AdaptiveCardsConfiguration._callbacks;
    }

    public static set callbacks(value: Callbacks) {
        AdaptiveCardsConfiguration._callbacks = value;
    }
}
