#include <string>

class Echo{

public:

    int echoInt( int i);

    int getNumCalls();

    std::string getNameOfClass();

    void printString( const char *s, int len );


private:

    static const std::string NAME_OF_CLASS;
    int numCalls;

};