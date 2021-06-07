// Copyright (C) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"
#include "SemanticVersion.h"

namespace AdaptiveCards
{
    EMSCRIPTEN_BINDINGS(SemanticVersionBindings)
    {
        class_<SemanticVersion>("semanticVersion")
            .smart_ptr_constructor<std::shared_ptr<SemanticVersion>>("semanticVersionPtr", &std::make_shared<SemanticVersion, std::string>)
            .property("major", &SemanticVersion::GetMajor)
            .property("minor", &SemanticVersion::GetMinor)
            .property("build", &SemanticVersion::GetBuild)
            .property("revision", &SemanticVersion::GetRevision)
            .function("toString", &SemanticVersion::operator std::string);
    }
}
