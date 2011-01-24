#ifndef _EXCEPTION_OODL_HPP
#define _EXCEPTION_OODL_HPP





#include <exception>
#include <iostream>
#include <string>
#include "generic/Logger.hpp"

using namespace std;
namespace brics_oodl {

    class ExceptionOODL : public exception {
        string msg;

    public:
        // Takes a character string describing the error.
        explicit ExceptionOODL(const string& message) throw () {
            msg = message;
            LOG(oodl_exception) << message;
        };

        virtual ~ExceptionOODL() throw () {
        };

        // Returns a C-style character string describing the general cause of the current error
        virtual const char* what() const throw () {
            return msg.c_str();
        };
    };

    class FileNotFoundException : public std::ios_base::failure {
        string msg;

    public:
        // Takes a character string describing the error.
        explicit FileNotFoundException(const string& message) throw () :std::ios_base::failure(message) {
            msg = message;
            LOG(oodl_exception) << message;
        };

        virtual ~FileNotFoundException() throw () {
        };

        // Returns a C-style character string describing the general cause of the current error
        virtual const char* what() const throw () {
            return msg.c_str();
        };
    };




} // namespace brics_oodl
#endif //_EXCEPTION_OODL_HPP
