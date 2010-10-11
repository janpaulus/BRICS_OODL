#include "LaserScannerTools.h"
  #include "boost/date_time/posix_time/posix_time.hpp"

  using namespace boost::posix_time;


bool running = true;
void sigintHandler(int signal){  running = false;  }

bool LaserScannerTools::plot_laserscanner_values(LaserScanner& scanner, Errors& errors) {
  /* Define the plot */
  Gnuplot data_plot("points");
  string plot_label("Range");

  ptime t1;
  time_duration td;
  ptime t2;
  double cycaltime1 = 0.0;
  double cycaltimesum = 0.0;
  int cycals = 0.0;


  LaserScannerData scanData;

  signal(SIGINT,sigintHandler);

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
    t2 = microsec_clock::local_time();
    cout << "\tGrabbing 100 measurements..." << endl << endl;
    while(running) {

      /* Acquire the most recent scan from the Sick */
      if (scanner.getData(scanData, errors)) {

        scanData.getMeasurements(ranges, rangeAngles);

        //     std::cout << ranges.size() << " "<< rangeAngles.size()<< std::endl;

        for (rangesIterator = ranges.begin(); rangesIterator != ranges.end(); rangesIterator++) {
          scan.push_back(rangesIterator->value());
        }


        /* Plot the values */
        data_plot.plot_x(scan, plot_label.c_str());

        /* Sleep a bit (gnuplot likes this) */
        boost::this_thread::sleep(boost::posix_time::milliseconds(10));

        /* Reset plot and vector */
        data_plot.reset_plot();
        scan.clear();
        ranges.clear();
        rangeAngles.clear();

        

        t1 = microsec_clock::local_time();
        td = t1 - t2;
        t2 = microsec_clock::local_time();
        cycaltime1 = ((double)td.total_milliseconds()/1000.0);
        cycaltimesum = cycaltimesum + cycaltime1;
        cycals++;
        std::cout << 1.0/(cycaltimesum/cycals)  <<" Hz"<<  std::endl;

      } else {
        boost::this_thread::sleep(boost::posix_time::milliseconds(10));

      }


    }

  }  /* Handle anything else */ catch (...) {
    cerr << "An error occurred!" << endl;
  }
  return true;
}