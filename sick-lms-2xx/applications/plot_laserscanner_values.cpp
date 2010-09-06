
#include <stdlib.h>
#include <string>
#include <vector>
#include <signal.h>
#include <iostream>

#include "LaserScannerConfiguration.h"
#include "SickLMS2xxConfiguration.h"
#include "LaserScannerData.h"
#include "LaserScannerDataWithIntensities.h"
#include "LaserScanner.h"
#include "SickLMS2xx.h"
#include "Errors.h"
#include "Logger.h"
#include "Units.h"



using namespace std;


#include "gnuplot_i.h"

using namespace std;

bool running = true;
void sigintHandler(int signal);

int main(int argc, char * argv[]) {

  // Initialize logging to std::cout
  logging::init_log_to_console(std::cout);
  // Initialize logging to the "test.log" file
  logging::init_log_to_file("log.txt");

  SickLMS2xxConfiguration config;
  config.devicePath = "/dev/ttyUSB0"; // Device path of the Sick LMS 2xx
  config.baud = BAUD_500K;

  SickLMS2xx scanner;

  Errors errors;

  if (!scanner.setConfiguration(config, errors)) {
    errors.printErrorsToConsole();
    return -1;
  }


  LaserScannerData scanData;

  /* Signal handler */
  signal(SIGINT, sigintHandler);

  /* Define the plot */
  Gnuplot data_plot("points");
  string plot_label("Range");

  try {

    /*
     * Check whether the device is returning reflectivity
     */
  //  plot_label = "Reflectivity";
    vector<double> scan;
    std::vector< quantity<length> >::iterator rangesIterator;
    std::vector< quantity<length> > ranges;
    std::vector< quantity<plane_angle> > rangeAngles;

    /*
     * Acquire measurements from Sick LMS 2xx and plot
     * them using gnuplot_i++
     */
    cout << "\tGrabbing 100 measurements..." << endl << endl;
    for (unsigned int i = 0; i < 100 && running; i++) {

      /* Acquire the most recent scan from the Sick */
      if (!scanner.getData(scanData, errors))
        return -1;

      scanData.getMeasurements(ranges, rangeAngles);

      std::cout << ranges.size() << " "<< rangeAngles.size()<< std::endl;

      for (rangesIterator = ranges.begin(); rangesIterator != ranges.end(); rangesIterator++) {
        scan.push_back(rangesIterator->value());
      }


      /* Plot the values */
      data_plot.plot_x(scan, plot_label.c_str());

      /* Sleep a bit (gnuplot likes this) */
      usleep(10000);

      /* Reset plot and vector */
      data_plot.reset_plot();
      scan.clear();
      ranges.clear();
      rangeAngles.clear();

    }

  }
  /* Handle anything else */ catch (...) {
    cerr << "An error occurred!" << endl;
  }

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

void sigintHandler(int signal) {
  running = false;
}
