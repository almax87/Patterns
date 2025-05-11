#include "logger.h"

int main() {
    Observable logger;
    
    WarningObserver warningObserver;
    ErrorObserver errorObserver("errors.log");
    FatalErrorObserver fatalErrorObserver("fatal_errors.log");
    
    logger.addObserver(&warningObserver);
    logger.addObserver(&errorObserver);
    logger.addObserver(&fatalErrorObserver);
    
    logger.warning("This is a warning message");
    logger.error("This is an error message");
    logger.fatalError("This is a fatal error message");
    
    // Удаляем одного из наблюдателей
    logger.removeObserver(&errorObserver);
    logger.error("This error won't be logged to file");
    
    return 0;
}