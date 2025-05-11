#include <iostream>
#include <fstream>
#include <string>

class LogCommand {
public:
    virtual ~LogCommand() = default;
    virtual void print(const std::string& message) = 0;
};

// Реализация вывода в консоль
class ConsoleLogCommand : public LogCommand {
public:
    void print(const std::string& message) override {
        std::cout << message << std::endl;
    }
};

// Реализация вывода в файл
class FileLogCommand : public LogCommand {
public:
    explicit FileLogCommand(const std::string& file_path) 
        : file_path_(file_path) {}

    void print(const std::string& message) override {
        std::ofstream file(file_path_, std::ios::app);
        if (file.is_open()) {
            file << message << std::endl;
        } else {
            std::cerr << "Failed to open file: " << file_path_ << std::endl;
        }
    }

private:
    std::string file_path_;
};

// Функция для выполнения команды логирования
void print(LogCommand& logger, const std::string& message) {
    logger.print(message);
}