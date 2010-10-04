#include "LaserScannerTools.h"


bool LaserScannerTools::plot_laserscanner_values(LaserScanner& scanner,Errors& errors){
/* Define the plot */
  Gnuplot data_plot("points");
  string plot_label("Range");

  LaserScannerData scanData;

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
    for (unsigned int i = 0; i < 10; i++) {

      /* Acquire the most recent scan from the Sick */
      if (!scanner.getData(scanData, errors))
        return -1;

      scanData.getMeasurements(ranges, rangeAngles);

 //     std::cout << ranges.size() << " "<< rangeAngles.size()<< std::endl;

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
  return true;
}