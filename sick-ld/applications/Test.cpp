#include <iostream>

#include "LaserScannerConfiguration.h"
//#include "SickLDConfiguration.h"
#include "LaserScannerData.h"
#include "LaserScannerDataWithIntensities.h"
#include "LaserScanner.h"
//#include "SickLD.h"
#include "Errors.h"



#include <boost/units/systems/si.hpp>
#include <boost/units/make_scaled_unit.hpp>
#include <boost/units/systems/si/prefixes.hpp>


using namespace std;
using namespace boost::units;
using namespace boost::units::si;
using namespace boost::units::angle;

//using namespace SickToolbox;

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
  /*
  SickLMS2xxConfiguration config;
  config.device_path = "/dev/ttyUSB0"; // Device path of the Sick LMS 2xx
  config.boud = BAUD_500K;
  config.measuring_mode = SickLMS::SICK_MS_MODE_REFLECTIVITY;
  config.availability_level = SickLMS::SICK_FLAG_AVAILABILITY_DEFAULT;
  config.sensitivity = SickLMS::SICK_SENSITIVITY_STANDARD;
  config.scan_resolution = 0.25 * M_PI/180.0 *radian;
  config.scan_angle = 100.0 * M_PI/180.0 *radian;

  SickLMS2xx scanner;

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