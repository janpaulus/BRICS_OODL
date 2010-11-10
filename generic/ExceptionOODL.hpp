#ifndef _EXCEPTION_OODL_H
#define _EXCEPTION_OODL_H



using namespace std;

#include <exception>
#include <string>
#include "generic/Logger.hpp"

class ExceptionOODL : public exception {
    string msg;

public:
    // Takes a character string describing the error.
    explicit ExceptionOODL(const string& __arg);

    virtual ~ExceptionOODL() throw ();

    // Returns a C-style character string describing the general cause of the current error
    virtual const char* what() const throw ();
};

#endif //_EXCEPTION_OODL_H
