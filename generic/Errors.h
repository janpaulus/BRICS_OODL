#ifndef _ERRORS_H
#define _ERRORS_H


#include <map>
using namespace std;

#include <string>
#include <iostream>
/**
 * \brief 
 *
 */
class Errors {
  public:
    Errors();

    virtual ~Errors();

    void getNextError(std::string& name, std::string& description);

    void getAllErrors(map<std::string, std::string>& allErrors);

    unsigned int getAmountOfErrors();

    void addError(std::string name, std::string description);

    void deleteAllErrors();


  private:
    //map of error name and error description
    map<std::string, std::string> occurredErrors;

    map<std::string,std::string>::iterator iter;

};
#endif
