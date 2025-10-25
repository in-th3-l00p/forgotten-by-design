//
// Created by Tisca Catalin on 26.10.2025.
//

#ifndef LOGGING_H
#define LOGGING_H

#include <string>
#include <print>

namespace logging {
    template<typename... Args>
    static void info(std::format_string<Args...> fmt, Args&&... args) {
        auto msg = std::format(fmt, std::forward<Args>(args)...);
        std::print("[INFO] {}\n", msg);
    }

    template<typename... Args>
    static void error(std::format_string<Args...> fmt, Args&&... args) {
        auto msg = std::format(fmt, std::forward<Args>(args)...);
        std::print("[ERROR] {}\n", msg);
    }
}

#endif //LOGGING_H
