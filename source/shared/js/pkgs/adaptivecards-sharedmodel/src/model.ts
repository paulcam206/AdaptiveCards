import AdaptiveCardsModule from './AdaptiveCardsSharedModel.js';
const AdaptiveCardsModuleWasm = require('./AdaptiveCardsSharedModel.wasm');
//import AdaptiveCardsModuleWasm from './AdaptiveCardsSharedModel.wasm';

export class ACSM {
    public static lazyLoad() {
        ACSM.internalInit();
    }

    public static async getInstance() {
        if (!ACSM.acModuleInstance) {
            await ACSM.internalInit();
        }

        return ACSM.acModuleInstance;
    }

    private static async internalInit() {
        if (!ACSM.acModuleInstance) {
            ACSM.acModuleInstance = await AdaptiveCardsModule({locateFile: f => {
                return AdaptiveCardsModuleWasm;
            }});
        }
    }

    private static acModuleInstance;
}
