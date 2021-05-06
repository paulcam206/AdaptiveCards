// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "AdaptiveCards.ObjectModel.Uwp.h"

namespace AdaptiveNamespace
{
    class AdaptiveSubmitActionParser
        : public Microsoft::WRL::RuntimeClass<Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>, ABI::AdaptiveNamespace::IAdaptiveActionParser>
    {
        AdaptiveRuntime(AdaptiveSubmitActionParser);

    public:
        HRESULT RuntimeClassInitialize() noexcept;

        IFACEMETHODIMP FromJson(_In_ ABI::Windows::Data::Json::IJsonObject* jsonObject,
                                _In_ ABI::AdaptiveNamespace::IAdaptiveElementParserRegistration* elementParserRegistration,
                                _In_ ABI::AdaptiveNamespace::IAdaptiveActionParserRegistration* actionParserRegistration,
                                _In_ ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveNamespace::AdaptiveWarning*>* adaptiveWarnings,
                                _COM_Outptr_ ABI::AdaptiveNamespace::IAdaptiveActionElement** element) noexcept override;
    };

    ActivatableClass(AdaptiveSubmitActionParser);
}
