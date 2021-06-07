// Copyright (C) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"
#include "FeatureRegistration.h"
#include "SemanticVersion.h"

namespace AdaptiveCards
{
    EMSCRIPTEN_BINDINGS(FeatureRegistrationBindings)
    {
        class_<FeatureRegistration>("featureRegistration")
            .smart_ptr_constructor<std::shared_ptr<FeatureRegistration>>("featureRegistration", &std::make_shared<FeatureRegistration>)
            .function("add", &FeatureRegistration::AddFeature)
            .function("remove", &FeatureRegistration::RemoveFeature)
            .property("adaptiveCardsVersion", &FeatureRegistration::GetAdaptiveCardsVersion)
            .function("getFeatureVersion", &FeatureRegistration::GetFeatureVersion);
    }
}
