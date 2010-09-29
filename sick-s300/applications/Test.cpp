#include <iostream>
#include <fstream>

#include "generic-laser-scanner/LaserScannerConfiguration.h"
#include "sick-s300/SickS300Configuration.h"
#include "generic-laser-scanner/LaserScannerData.h"
#include "generic-laser-scanner/LaserScannerDataWithIntensities.h"
#include "generic-laser-scanner/LaserScanner.h"
#include "sick-s300/SickS300.h"
#include "generic/Errors.h"
#include "generic/Logger.h"
#include "generic/Units.h"




using namespace std;


int main(){
/*
  SickLMS2xxConfiguration config;

  config.scan_angle = 2 *radian;
  double test = config.scan_angle.value(); //mm
  config.scan_resolution = 2 *radian;


  std::cout << "min Range: " << config.scan_angle <<std::endl
            << "max Range: " << config.scan_resolution <<std::endl
            << "test: " << test <<std::endl;
*/

// Read logging settings from a file
  //  std::ifstream file("log_settings.ini");
 //   logging::init_from_stream(file);

  (Logger::getInstance()).init();



  SickS300Configuration config;
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