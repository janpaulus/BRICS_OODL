#include <iostream>

#include "LaserScannerConfiguration.h"
#include "SickLDConfiguration.h"
#include "LaserScannerData.h"
#include "LaserScannerDataWithIntensities.h"
#include "LaserScanner.h"
#include "SickLD.h"
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
  SickLDConfiguration config;

  config.scan_angle = 2 *radian;
  double test = config.scan_angle.value(); //mm
  config.scan_resolution = 2 *radian;


  std::cout << "min Range: " << config.scan_angle <<std::endl
            << "max Range: " << config.scan_resolution <<std::endl
            << "test: " << test <<std::endl;
*/
  
  SickLDConfiguration config;
  config.device_path = "/dev/ttyUSB0"; // Device path of the Sick LMS 2xx



  SickLD scanner;

  Errors errors;

  LaserScannerData scanData(180);

  if(!scanner.setConfiguration(config, errors))
    return 0;

  if(!scanner.getConfiguration(config, errors))
    return 0;

  if(!scanner.getData(scanData, errors))
    return 0;


  return 0;
}