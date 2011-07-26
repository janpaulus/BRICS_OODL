#ifndef _EXCEPTIONS_HPP
#define _EXCEPTIONS_HPP


#include <exception>
#include <iostream>
#include <string>
#include "Logger.hpp"

using namespace std;
namespace brics_oodl {

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

    class JointParameterException : public std::runtime_error {
        string msg;

    public:
        // Takes a character string describing the error.
        explicit JointParameterException(const string& message) throw () :std::runtime_error(message) {
            msg = message;
            LOG(oodl_exception) << message;
        };

        virtual ~JointParameterException() throw () {
        };

        // Returns a C-style character string describing the general cause of the current error
        virtual const char* what() const throw () {
            return msg.c_str();
        };
    };

   class JointErrorException : public std::runtime_error {
        string msg;

    public:
        // Takes a character string describing the error.
        explicit JointErrorException(const string& message) throw () :std::runtime_error(message) {
            msg = message;
            LOG(oodl_exception) << message;
        };

        virtual ~JointErrorException() throw () {
        };

        // Returns a C-style character string describing the general cause of the current error
        virtual const char* what() const throw () {
            return msg.c_str();
        };
    };





} // namespace brics_oodl
#endif //_EXCEPTIONS_HPP
