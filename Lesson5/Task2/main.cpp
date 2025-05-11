#include <fstream>
#include <memory>
#include <stdexcept>

// Абстракция для форматирования данных (Strategy pattern)
class IDataFormatter {
public:
    virtual ~IDataFormatter() = default;
    virtual std::string format(const std::string& data) const = 0;
};

// Конкретные реализации форматирования
class HTMLFormatter : public IDataFormatter {
public:
    std::string format(const std::string& data) const override {
        return "<html>" + data + "</html>";
    }
};

class TextFormatter : public IDataFormatter {
public:
    std::string format(const std::string& data) const override {
        return data;
    }
};

class JSONFormatter : public IDataFormatter {
public:
    std::string format(const std::string& data) const override {
        return "{ \"data\": \"" + data + "\" }";
    }
};

// Базовый класс для данных (теперь без логики форматирования)
class Data {
public:
    explicit Data(std::string data) : data_(std::move(data)) {}
    virtual ~Data() = default;

    const std::string& getRawData() const { return data_; }

private:
    std::string data_;
};

// Функции для сохранения в разных форматах
void saveTo(std::ofstream& file, const Data& data, const IDataFormatter& formatter) {
    file << formatter.format(data.getRawData());
}

void saveToAsHTML(std::ofstream& file, const Data& data) {
    HTMLFormatter formatter;
    saveTo(file, data, formatter);
}

void saveToAsText(std::ofstream& file, const Data& data) {
    TextFormatter formatter;
    saveTo(file, data, formatter);
}

void saveToAsJSON(std::ofstream& file, const Data& data) {
    JSONFormatter formatter;
    saveTo(file, data, formatter);
}

// Пример использования
int main() {
    Data myData("Hello, World!");
    std::ofstream outFile("output.html");
    
    saveToAsHTML(outFile, myData);
    
    return 0;
}