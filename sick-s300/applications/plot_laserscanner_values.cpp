
#include <stdlib.h>
#include <string>
#include <vector>
#include <signal.h>
#include <iostream>

#include "generic/Errors.h"
#include "generic/Units.h"
#include "generic/Logger.h"
#include "generic-laser-scanner/LaserScannerConfiguration.h"
#include "generic-laser-scanner/LaserScannerData.h"
#include "generic-laser-scanner/LaserScannerDataWithIntensities.h"
#include "generic-laser-scanner/LaserScanner.h"
#include "sick-s300/SickS300.h"
#include "sick-s300/SickS300Configuration.h"
#include "generic-laser-scanner/applications/LaserScannerTools.h"




using namespace std;




int main(int argc, char * argv[]) {

  // Initialize logging to std::cout
  logging::init_log_to_console(std::cout);
  // Initialize logging to the "test.log" file
  logging::init_log_to_file("log.txt");

  SickS300Configuration config;
  config.devicePath = "/dev/ttyUSB0"; // Device path of the Sick S300
  config.baud = BAUD_500K;

  SickS300 scanner;

  Errors errors;

  if (!scanner.setConfiguration(config, errors)) {
    errors.printErrorsToConsole();
    return -1;
  }


  LaserScannerTools tools;

  tools.plot_laserscanner_values(scanner, errors);
  

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
