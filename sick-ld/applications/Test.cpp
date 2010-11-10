#include <iostream>

#include "generic-laser-scanner/LaserScannerConfiguration.hpp"
#include "sick-ld/SickLDConfiguration.hpp"
#include "generic-laser-scanner/LaserScannerData.hpp"
#include "generic-laser-scanner/LaserScannerDataWithIntensities.hpp"
#include "generic-laser-scanner/LaserScanner.hpp"
#include "sick-ld/SickLD.hpp"
#include "generic/Errors.hpp"
#include "generic/Units.hpp"
#include "generic/Logger.hpp"


using namespace std;

//using namespace SickToolbox;

int main(){
/*
  SickLDConfiguration config;

  config.scan_angle = 2 *radian;
  double test = config.scan_angle.value(); //mm
  config.scan_resolution = 2 *radian;


  std::cout << "min Range: " << config.scan_angle <<std::endl
            << "max Range: " << config.scan_resolution <<std::endl
            << "test: " << test <<std::endl;
*/
  
  SickLDConfiguration config;
  config.devicePath = "/dev/ttyUSB0"; // Device path of the Sick LMS 2xx



  SickLD scanner;

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