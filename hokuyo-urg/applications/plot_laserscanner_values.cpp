
#include <stdlib.h>
#include <string>
#include <vector>
#include <signal.h>
#include <iostream>

#include "generic-laser-scanner/LaserScannerConfiguration.h"
#include "generic-laser-scanner/LaserScannerData.h"
#include "generic-laser-scanner/LaserScannerDataWithIntensities.h"
#include "generic-laser-scanner/LaserScanner.h"
#include "generic/Errors.h"
#include "generic/Logger.h"
#include "generic/Units.h"
#include "generic-laser-scanner/applications/LaserScannerTools.h"
#include "hokuyo-urg/HokuyoURG.h"
#include "hokuyo-urg/HokuyoURGConfiguration.h"


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

