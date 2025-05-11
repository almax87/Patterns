#include "logger.h"

int main() {
    try {
        // Создаем обработчики
        auto fatalHandler = std::make_shared<FatalErrorHandler>();
        auto errorHandler = std::make_shared<ErrorHandler>("errors.log");
        auto warningHandler = std::make_shared<WarningHandler>();
        auto unknownHandler = std::make_shared<UnknownHandler>();

        // Строим цепочку ответственности
        fatalHandler->setNext(errorHandler);
        errorHandler->setNext(warningHandler);
        warningHandler->setNext(unknownHandler);

        // Создаем сообщения для тестирования
        LogMessage warning(Type::WARNING, "This is a warning message");
        LogMessage error(Type::ERROR, "This is an error message");
        LogMessage fatal(Type::FATAL_ERROR, "This is a fatal error");
        LogMessage unknown(Type::UNKNOWN, "This is unknown message type");

        // Обрабатываем сообщения
        fatalHandler->handle(warning);   // Выведет в консоль
        fatalHandler->handle(error);     // Запишет в файл
        // fatalHandler->handle(fatal);  // Выбросит исключение
        // fatalHandler->handle(unknown); // Выбросит исключение

    } catch (const std::exception& e) {
        std::cerr << "Exception caught: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}