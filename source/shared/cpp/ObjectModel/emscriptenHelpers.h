#pragma once

#ifndef EMSCRIPTEN_BINDINGS_REGISTER_STD_OPTIONAL_HPP_
#define EMSCRIPTEN_BINDINGS_REGISTER_STD_OPTIONAL_HPP_

#include <optional>
#include <emscripten/bind.h>

namespace emscripten
{
    template<typename T>
        class_<std::optional<T>> register_optional(const char* name) {
        using emscripten::val;
        using OptionalType = std::optional<T>;
        bool (*has_value)(const OptionalType&) = [](const OptionalType& op){ return op.has_value(); };
        val (*value)(const OptionalType&) = [](const OptionalType& op) { return val(op.value()); };
        void (*reset)(OptionalType&) = [](OptionalType& op) { op.reset(); };
        return emscripten::class_<OptionalType>(name)
            .template constructor<>()
            .function("has_value", has_value)
            .function("value", value)
            .function("reset", reset);
    }
}

#endif //EMSCRIPTEN_BINDINGS_REGISTER_STD_OPTIONAL_HPP_
