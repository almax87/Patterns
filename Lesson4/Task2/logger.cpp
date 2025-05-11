#include "logger.h"

void Observable::notifyWarning(const std::string& message) const {
    for (auto observer : observers_) {
        if (observer) {
            observer->onWarning(message);
        }
    }
}

void Observable::notifyError(const std::string& message) const {
    for (auto observer : observers_) {
        if (observer) {
            observer->onError(message);
        }
    }
}

void Observable::notifyFatalError(const std::string& message) const {
    for (auto observer : observers_) {
        if (observer) {
            observer->onFatalError(message);
        }
    }
}

void Observable::warning(const std::string& message) const {
    std::cout << "Warning: " << message << std::endl;
    notifyWarning(message);
}

void Observable::error(const std::string& message) const {
    std::cout << "Error: " << message << std::endl;
    notifyError(message);
}

void Observable::fatalError(const std::string& message) const {
    std::cout << "Fatal Error: " << message << std::endl;
    notifyFatalError(message);
}