#include <iostream>
#include <fstream>

#include "SickS300.hpp"



using namespace std;
using namespace brics_oodl;


int main(){

  (Logger::getInstance()).init();



  LaserScannerConfiguration config;
  config.devicePath = "/dev/ttyUSB0"; // Device path of the Sick LMS 2xx
  config.baud = BAUD_500K;

  SickS300 scanner;

  Errors errors;

  LaserScannerData scanData;

  if(!scanner.setConfiguration(config, errors))
    return 0;

  if(!scanner.getConfiguration(config, errors))
    return 0;

  if(!scanner.getData(scanData, errors))
    return 0;


  return 0;
}
