// Copyright (C) Microsoft Corporation. All rights reserved.
#include "pch.h"
#include "json/json.h"

namespace Json
{
    EMSCRIPTEN_BINDINGS(Value)
    {
        class_<Value>("jsonValue")
            //.smart_ptr<std::shared_ptr<Json::Value>>("jsonValue")
            .smart_ptr_constructor<std::shared_ptr<Json::Value>>("jsonValue", &std::make_shared<Json::Value>);

            //.constructor();
    }
}
