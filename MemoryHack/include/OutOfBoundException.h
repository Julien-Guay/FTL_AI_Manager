#ifndef OUTOFBOUNDEXCEPTION_H
#define OUTOFBOUNDEXCEPTION_H

#include <exception>

using namespace std;

class OutOfBoundException : public exception
{
    public:
        /** Default constructor */
        OutOfBoundException();
        /** Default destructor */
        virtual ~OutOfBoundException();
    protected:
    private:
};

#endif // OUTOFBOUNDEXCEPTION_H
