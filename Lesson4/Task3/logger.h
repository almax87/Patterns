#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>
#include <memory>

enum class Type {
    WARNING,
    ERROR,
    FATAL_ERROR,
    UNKNOWN
};

class LogMessage {
public:
    LogMessage(Type type, const std::string& message) 
        : type_(type), message_(message) {}

    Type type() const { return type_; }
    const std::string& message() const { return message_; }

private:
    Type type_;
    std::string message_;
};

class Handler {
    public:
        virtual ~Handler() = default;
        
        void setNext(std::shared_ptr<Handler> next) {
            next_ = next;
        }
        
        virtual void handle(const LogMessage& message) {
            if (next_) {
                next_->handle(message);
            }
        }

    protected:
        std::shared_ptr<Handler> next_;
};

class FatalErrorHandler : public Handler {
    public:
        void handle(const LogMessage& message) override {
            if (message.type() == Type::FATAL_ERROR) {
                throw std::runtime_error("Fatal error: " + message.message());
            }
            Handler::handle(message);
        }
    };

class ErrorHandler : public Handler {
    public:
        explicit ErrorHandler(const std::string& filePath) 
            : filePath_(filePath) {}
    
        void handle(const LogMessage& message) override {
            if (message.type() == Type::ERROR) {
                std::ofstream file(filePath_, std::ios::app);
                if (file.is_open()) {
                    file << "Error: " << message.message() << std::endl;
                }
                return;
            }
            Handler::handle(message);
        }
    
    private:
        std::string filePath_;
    };


class WarningHandler : public Handler {
    public:
        void handle(const LogMessage& message) override {
            if (message.type() == Type::WARNING) {
                std::cout << "Warning: " << message.message() << std::endl;
                return;
            }
            Handler::handle(message);
        }
    };


class UnknownHandler : public Handler {
    public:
        void handle(const LogMessage& message) override {
            if (message.type() == Type::UNKNOWN) {
                throw std::runtime_error("Unknown message: " + message.message());
            }
            Handler::handle(message);
        }
    };


    