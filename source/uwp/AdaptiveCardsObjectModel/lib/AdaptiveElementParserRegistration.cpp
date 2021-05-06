// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"
#include "AdaptiveElementParserRegistration.h"
#include "AdaptiveActionParserRegistration.h"
#include "AdaptiveActionSetParser.h"
#include "AdaptiveChoiceSetInputParser.h"
#include "AdaptiveColumnParser.h"
#include "AdaptiveColumnSetParser.h"
#include "AdaptiveContainerParser.h"
#include "AdaptiveDateInputParser.h"
#include "AdaptiveFactSetParser.h"
#include "AdaptiveImageParser.h"
#include "AdaptiveImageSetParser.h"
#include "AdaptiveMediaParser.h"
#include "AdaptiveNumberInputParser.h"
#include "AdaptiveRichTextBlockParser.h"
#include "AdaptiveTextBlockParser.h"
#include "AdaptiveTextInputParser.h"
#include "AdaptiveTimeInputParser.h"
#include "AdaptiveToggleInputParser.h"
#include "CustomElementWrapper.h"
#include "Util.h"
#include "Vector.h"

using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;
using namespace ABI::AdaptiveNamespace;
using namespace ABI::Windows::UI;

namespace AdaptiveNamespace
{
    AdaptiveElementParserRegistration::AdaptiveElementParserRegistration() {}

    HRESULT AdaptiveElementParserRegistration::RuntimeClassInitialize() noexcept
    try
    {
        m_registration = std::make_shared<RegistrationMap>();
        m_sharedParserRegistration = std::make_shared<ElementParserRegistration>();

        m_isInitializing = true;
        RegisterDefaultElementParsers(this);

        // Register this (UWP) registration with a well known guid string in the shared model
        // registration so we can get it back again
        m_sharedParserRegistration->AddParser(c_uwpElementParserRegistration, std::make_shared<SharedModelElementParser>(this));

        m_isInitializing = false;
        return S_OK;
    }
    CATCH_RETURN;

    HRESULT AdaptiveElementParserRegistration::Set(_In_ HSTRING type, _In_ IAdaptiveElementParser* Parser) noexcept
    try
    {
        std::string typeString = HStringToUTF8(type);

        // During initialization we will add the known parsers to m_registration. These are already present in the corresponding
        // shared model registration (m_sharedParserRegistration) which will throw if we attempt to modify them by adding them again.
        if (!m_isInitializing)
        {
            m_sharedParserRegistration->AddParser(typeString, std::make_shared<SharedModelElementParser>(this));
        }

        ComPtr<IAdaptiveElementParser> localParser(Parser);
        (*m_registration)[typeString] = localParser;

        return S_OK;
    }
    CATCH_RETURN;

    HRESULT AdaptiveElementParserRegistration::Get(_In_ HSTRING type, _COM_Outptr_ IAdaptiveElementParser** result) noexcept
    try
    {
        *result = nullptr;

        RegistrationMap::iterator found = m_registration->find(HStringToUTF8(type));
        if (found != m_registration->end())
        {
            RETURN_IF_FAILED(found->second.CopyTo(result));
        }
        return S_OK;
    }
    CATCH_RETURN;

    HRESULT AdaptiveElementParserRegistration::Remove(_In_ HSTRING type) noexcept
    try
    {
        std::string typeString = HStringToUTF8(type);

        m_sharedParserRegistration->RemoveParser(typeString);
        m_registration->erase(typeString);

        return S_OK;
    }
    CATCH_RETURN;

    std::shared_ptr<ElementParserRegistration> AdaptiveElementParserRegistration::GetSharedParserRegistration()
    {
        return m_sharedParserRegistration;
    }

    HRESULT AdaptiveElementParserRegistration::RegisterDefaultElementParsers(ABI::AdaptiveNamespace::IAdaptiveElementParserRegistration* registration)
    {
        RETURN_IF_FAILED(registration->Set(HStringReference(L"ActionSet").Get(),
                                           Make<AdaptiveNamespace::AdaptiveActionSetParser>().Get()));
        RETURN_IF_FAILED(registration->Set(HStringReference(L"Column").Get(),
                                           Make<AdaptiveNamespace::AdaptiveColumnParser>().Get()));
        RETURN_IF_FAILED(registration->Set(HStringReference(L"ColumnSet").Get(),
                                           Make<AdaptiveNamespace::AdaptiveColumnSetParser>().Get()));
        RETURN_IF_FAILED(registration->Set(HStringReference(L"Container").Get(),
                                           Make<AdaptiveNamespace::AdaptiveContainerParser>().Get()));
        RETURN_IF_FAILED(registration->Set(HStringReference(L"FactSet").Get(),
                                           Make<AdaptiveNamespace::AdaptiveFactSetParser>().Get()));
        RETURN_IF_FAILED(
            registration->Set(HStringReference(L"Image").Get(), Make<AdaptiveNamespace::AdaptiveImageParser>().Get()));
        RETURN_IF_FAILED(registration->Set(HStringReference(L"ImageSet").Get(),
                                           Make<AdaptiveNamespace::AdaptiveImageSetParser>().Get()));
        RETURN_IF_FAILED(registration->Set(HStringReference(L"Input.ChoiceSet").Get(),
                                           Make<AdaptiveNamespace::AdaptiveChoiceSetInputParser>().Get()));
        RETURN_IF_FAILED(registration->Set(HStringReference(L"Input.Date").Get(),
                                           Make<AdaptiveNamespace::AdaptiveDateInputParser>().Get()));
        RETURN_IF_FAILED(registration->Set(HStringReference(L"Input.Number").Get(),
                                           Make<AdaptiveNamespace::AdaptiveNumberInputParser>().Get()));
        RETURN_IF_FAILED(registration->Set(HStringReference(L"Input.Text").Get(),
                                           Make<AdaptiveNamespace::AdaptiveTextInputParser>().Get()));
        RETURN_IF_FAILED(registration->Set(HStringReference(L"Input.Time").Get(),
                                           Make<AdaptiveNamespace::AdaptiveTimeInputParser>().Get()));
        RETURN_IF_FAILED(registration->Set(HStringReference(L"Input.Toggle").Get(),
                                           Make<AdaptiveNamespace::AdaptiveToggleInputParser>().Get()));
        RETURN_IF_FAILED(
            registration->Set(HStringReference(L"Media").Get(), Make<AdaptiveNamespace::AdaptiveMediaParser>().Get()));
        RETURN_IF_FAILED(registration->Set(HStringReference(L"RichTextBlock").Get(),
                                           Make<AdaptiveNamespace::AdaptiveRichTextBlockParser>().Get()));
        RETURN_IF_FAILED(registration->Set(HStringReference(L"TextBlock").Get(),
                                           Make<AdaptiveNamespace::AdaptiveTextBlockParser>().Get()));

        return S_OK;
    }

    std::shared_ptr<BaseCardElement> SharedModelElementParser::DeserializeFromString(ParseContext& context, const std::string& jsonString)
    {
        return Deserialize(context, ParseUtil::GetJsonValueFromString(jsonString));
    }

    SharedModelElementParser::SharedModelElementParser(AdaptiveNamespace::AdaptiveElementParserRegistration* parserRegistration)
    {
        ComPtr<AdaptiveElementParserRegistration> localParserRegistration(parserRegistration);
        localParserRegistration.AsWeak(&m_parserRegistration);
    }

    std::shared_ptr<BaseCardElement> SharedModelElementParser::Deserialize(ParseContext& context, const Json::Value& value)
    {
        std::string type = ParseUtil::GetTypeAsString(value);

        HString typeAsHstring;
        THROW_IF_FAILED(UTF8ToHString(type, typeAsHstring.GetAddressOf()));

        ComPtr<IAdaptiveElementParserRegistration> adaptiveElementParserRegistration;
        THROW_IF_FAILED(GetAdaptiveParserRegistration(&adaptiveElementParserRegistration));

        ComPtr<IAdaptiveElementParser> parser;
        THROW_IF_FAILED(adaptiveElementParserRegistration->Get(typeAsHstring.Get(), &parser));

        ComPtr<ABI::Windows::Data::Json::IJsonObject> jsonObject;
        THROW_IF_FAILED(JsonCppToJsonObject(value, &jsonObject));

        // Get the action parser registration from the shared model
        ComPtr<IAdaptiveActionParserRegistration> adaptiveActionParserRegistration;
        THROW_IF_FAILED(GetAdaptiveActionParserRegistrationFromSharedModel(context.actionParserRegistration,
                                                                           &adaptiveActionParserRegistration));

        ComPtr<IAdaptiveCardElement> cardElement;
        ComPtr<ABI::Windows::Foundation::Collections::IVector<AdaptiveWarning*>> adaptiveWarnings =
            Make<Vector<AdaptiveWarning*>>();
        THROW_IF_FAILED(parser->FromJson(jsonObject.Get(),
                                         adaptiveElementParserRegistration.Get(),
                                         adaptiveActionParserRegistration.Get(),
                                         adaptiveWarnings.Get(),
                                         &cardElement));

        THROW_IF_FAILED(AdaptiveWarningsToSharedWarnings(adaptiveWarnings.Get(), context.warnings));

        std::shared_ptr<CustomElementWrapper> elementWrapper = std::make_shared<CustomElementWrapper>(cardElement.Get());
        return elementWrapper;
    }

    HRESULT SharedModelElementParser::GetAdaptiveParserRegistration(_COM_Outptr_ IAdaptiveElementParserRegistration** elementParserRegistration)
    {
        return m_parserRegistration.CopyTo<IAdaptiveElementParserRegistration>(elementParserRegistration);
    }
}
