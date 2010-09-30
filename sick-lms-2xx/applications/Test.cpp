#include <iostream>

#include "generic/Errors.h"
#include "generic/Units.h"
#include "generic/Logger.h"
#include "generic-laser-scanner/LaserScanner.h"
#include "generic-laser-scanner/LaserScannerConfiguration.h"
#include "generic-laser-scanner/LaserScannerData.h"
#include "generic-laser-scanner/LaserScannerDataWithIntensities.h"
#include "sick-lms-2xx/SickLMS2xx.h"
#include "sick-lms-2xx/SickLMS2xxConfiguration.h"


using namespace std;


using namespace SickToolbox;

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
  SickLMS2xxConfiguration config;
  config.devicePath = "/dev/ttyUSB0"; // Device path of the Sick LMS 2xx
  config.baud = BAUD_500K;
  config.measuringMode = SickLMS::SICK_MS_MODE_REFLECTIVITY;
  config.availabilityLevel = SickLMS::SICK_FLAG_AVAILABILITY_DEFAULT;
  config.sensitivity = SickLMS::SICK_SENSITIVITY_STANDARD;
  config.scanResolution = 0.25 * M_PI/180.0 *radian;
  config.scanAngleStart = -100.0 * M_PI/180.0 *radian;
  config.scanAngleStop = 100.0 * M_PI/180.0 *radian;

  SickLMS2xx scanner;

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