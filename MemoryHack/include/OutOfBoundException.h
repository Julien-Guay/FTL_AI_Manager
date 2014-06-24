#ifndef OUTOFBOUNDEXCEPTION_H
#define OUTOFBOUNDEXCEPTION_H

#include <exception>
#include <windows.h>

using namespace std;

class OutOfBoundException : public exception
{
public:
    /** Default constructor */
    OutOfBoundException();
//        /** Default destructor */
//        virtual ~OutOfBoundException() throw();
    virtual const char* what() const throw();
protected:
private:

};

#endif // OUTOFBOUNDEXCEPTION_H
