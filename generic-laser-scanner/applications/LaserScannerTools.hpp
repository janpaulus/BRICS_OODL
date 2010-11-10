/* 
 * File:   tools.h
 * Author: jan
 *
 * Created on September 7, 2010, 12:43 PM
 */

#ifndef LASERSCANNERTOOLS_H
#define	LASERSCANNERTOOLS_H


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
#include "generic-laser-scanner/applications/gnuplot_i.hpp"


using namespace std;

class LaserScannerTools {
  public:
    bool plot_laserscanner_values(LaserScanner& scanner, Errors& errors);

};

#endif	/* LASERSCANNERTOOLS_H */

