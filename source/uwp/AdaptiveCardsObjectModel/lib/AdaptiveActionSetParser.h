// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "ActionSet.h"

namespace AdaptiveNamespace
{
    class AdaptiveActionSetParser
        : public Microsoft::WRL::RuntimeClass<Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
                                              ABI::AdaptiveNamespace::IAdaptiveElementParser>
    {
        InspectableClass(RuntimeClass_AdaptiveCards_ObjectModel_Uwp_AdaptiveActionSetParser, BaseTrust);

    public:
        HRESULT RuntimeClassInitialize() noexcept;

        IFACEMETHODIMP FromJson(_In_ ABI::Windows::Data::Json::IJsonObject*,
                                _In_ ABI::AdaptiveNamespace::IAdaptiveElementParserRegistration* elementParsers,
                                _In_ ABI::AdaptiveNamespace::IAdaptiveActionParserRegistration* actionParsers,
                                _In_ ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveNamespace::AdaptiveWarning*>* adaptiveWarnings,
                                _COM_Outptr_ ABI::AdaptiveNamespace::IAdaptiveCardElement** element) noexcept;
    };

    ActivatableClass(AdaptiveActionSetParser);
}
