#include "logger.h"

int main() {
    ConsoleLogCommand console_logger;
    FileLogCommand file_logger("log.txt");

    print(console_logger, "This message goes to console");
    print(file_logger, "This message goes to file");
    
    return 0;
}