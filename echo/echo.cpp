    #include "echo.h"
    #include "mbed.h"
    
    int Echo::echoInt( int i)
    {
        numCalls++;
        return i;
    }

    int Echo::getNumCalls()
    {
        return numCalls;
    }

    std::string Echo::getNameOfClass(){
        
        return NAME_OF_CLASS;
    }

    void Echo::printString( const char *s )
    {
        printf("%s\r\n", s);
    }

    const std::string Echo::NAME_OF_CLASS = "Echo";