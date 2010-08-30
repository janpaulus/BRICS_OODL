
#include <stdlib.h>
#include <string>
#include <vector>
#include <signal.h>
#include <iostream>

#include "LaserScannerConfiguration.h"
#include "SickS300Configuration.h"
#include "LaserScannerData.h"
#include "LaserScannerDataWithIntensities.h"
#include "LaserScanner.h"
#include "SickS300.h"
#include "Errors.h"



#include <boost/units/systems/si.hpp>
#include <boost/units/make_scaled_unit.hpp>
#include <boost/units/systems/si/prefixes.hpp>


using namespace std;
using namespace boost::units;
using namespace boost::units::si;
using namespace boost::units::angle;


#include "gnuplot_i.h"

using namespace std;

bool running = true;
void sigintHandler(int signal);

int main(int argc, char * argv[]) {
  
   SickS300Configuration config;
  config.devicePath = "/dev/ttyUSB0"; // Device path of the Sick LMS 2xx
  config.baud = BAUD_500K;

  SickS300 scanner;

  Errors errors;

  LaserScannerData scanData;

  /* Signal handler */
  signal(SIGINT,sigintHandler);
  
  /* Define the plot */
  Gnuplot data_plot("points");
  string plot_label("Range");

  try {

    /*
     * Check whether the device is returning reflectivity
     */
      plot_label = "Reflectivity";
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
      if(!scanner.getData(scanData, errors))
        return -1;

      scanData.getMeasurements(ranges, rangeAngles);



      for ( rangesIterator=ranges.begin() ; rangesIterator < ranges.end(); rangesIterator++ ){
        scan.push_back(rangesIterator->value());
      }

      
      /* Plot the values */
      data_plot.plot_x(scan,plot_label.c_str());
      
      /* Sleep a bit (gnuplot likes this) */
      usleep(10000);
      
      /* Reset plot and vector */
      data_plot.reset_plot();
      
    }

  }

  /* Handle anything else */
  catch(...) {
    cerr << "An error occurred!"  << endl;
  }

  /*
   * Uninitialize the device
   */
  try {
    scanner.close(errors);
  }
  
  catch(...) {
    cerr << "Uninitialize failed!" << endl;
    return -1;
  }
  
  /* Success! */
  return 0;

}

void sigintHandler(int signal){  running = false;  }
