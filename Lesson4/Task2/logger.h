#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <memory>

class Observer {
    public:
        virtual ~Observer() = default;
        virtual void onWarning(const std::string& message) {}
        virtual void onError(const std::string& message) {}
        virtual void onFatalError(const std::string& message) {}
    };

class Observable {
public:
    void addObserver(Observer* observer) {
        observers_.push_back(observer);
    }

    void removeObserver(Observer* observer) {
        observers_.erase(std::remove(observers_.begin(), observers_.end(), observer), observers_.end());
    }

    void warning(const std::string& message) const;
    void error(const std::string& message) const;
    void fatalError(const std::string& message) const;

protected:
    void notifyWarning(const std::string& message) const;
    void notifyError(const std::string& message) const;
    void notifyFatalError(const std::string& message) const;

private:
    std::vector<Observer*> observers_;
};

class WarningObserver : public Observer {
    public:
        void onWarning(const std::string& message) override {
            std::cout << "Warning Observer: " << message << std::endl;
        }
    };


class ErrorObserver : public Observer {
    public:
        explicit ErrorObserver(const std::string& filePath) : filePath_(filePath) {}
    
        void onError(const std::string& message) override {
            std::ofstream file(filePath_, std::ios::app);
            if (file.is_open()) {
                file << "Error Observer: " << message << std::endl;
            }
        }
    
    private:
        std::string filePath_;
    };


class FatalErrorObserver : public Observer {
    public:
        explicit FatalErrorObserver(const std::string& filePath) : filePath_(filePath) {}
    
        void onFatalError(const std::string& message) override {
            std::cout << "Fatal Error Observer (console): " << message << std::endl;
            
            std::ofstream file(filePath_, std::ios::app);
            if (file.is_open()) {
                file << "Fatal Error Observer (file): " << message << std::endl;
            }
        }
    
    private:
        std::string filePath_;
    };