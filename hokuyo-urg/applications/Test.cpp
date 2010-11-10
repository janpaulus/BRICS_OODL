#include <iostream>

#include "generic-laser-scanner/LaserScannerConfiguration.hpp"
#include "generic-laser-scanner/LaserScannerData.hpp"
#include "generic-laser-scanner/LaserScannerDataWithIntensities.hpp"
#include "generic-laser-scanner/LaserScanner.hpp"
#include "generic/Errors.hpp"
#include "generic/Units.hpp"
#include "generic/Logger.hpp"

#include "UrgCtrl.h"

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
 /* SickS300Configuration config;
  config.device_path = "/dev/ttyUSB0"; // Device path of the Sick LMS 2xx
  config.boud = BAUD_500K;

  SickS300 scanner;

  Errors errors;

  LaserScannerData scanData(180);

  if(!scanner.setConfiguration(config, errors))
    return 0;

  if(!scanner.getConfiguration(config, errors))
    return 0;

  if(!scanner.getData(scanData, errors))
    return 0;
*/

  return 0;
}