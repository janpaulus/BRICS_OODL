
#include <stdlib.h>
#include <string>
#include <vector>
#include <signal.h>
#include <iostream>

#include "generic-laser-scanner/LaserScannerConfiguration.hpp"
#include "generic-laser-scanner/LaserScannerData.hpp"
#include "generic-laser-scanner/LaserScannerDataWithIntensities.hpp"
#include "generic-laser-scanner/LaserScanner.hpp"
#include "generic/Errors.hpp"
#include "generic/Logger.hpp"
#include "generic/Units.hpp"
#include "generic-laser-scanner/applications/LaserScannerTools.hpp"
#include "hokuyo-urg/HokuyoURG.hpp"
#include "hokuyo-urg/HokuyoURGConfiguration.hpp"


using namespace std;


void sigintHandler(int signal);

int main(int argc, char * argv[]) {

  (Logger::getInstance()).init();

  HokuyoURGConfiguration config;
  config.devicePath = "/dev/ttyACM0"; // Device path of the Sick LMS 2xx
  config.baud = BAUD_115200;
  config.scanAngleStart = 0 *radian;
  config.scanAngleStop = 1.5 *radian;

  HokuyoURG scanner;

  Errors errors;

  if (!scanner.setConfiguration(config, errors)) {
    errors.printErrorsToConsole();
    return -1;
  }


  
  LaserScannerTools tools;

 // tools.plot_laserscanner_values(scanner, errors);

  /*
   * Uninitialize the device
   */
  try {
    scanner.close(errors);
  } catch (...) {
    cerr << "Uninitialize failed!" << endl;
    return -1;
  }

  /* Success! */
  return 0;

}

