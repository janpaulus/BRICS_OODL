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

#include "generic-laser-scanner/LaserScannerConfiguration.h"
#include "generic-laser-scanner/LaserScannerData.h"
#include "generic-laser-scanner/LaserScannerDataWithIntensities.h"
#include "generic-laser-scanner/LaserScanner.h"
#include "generic/Errors.h"
#include "generic/Logger.h"
#include "generic/Units.h"
#include "generic-laser-scanner/applications/gnuplot_i.h"


using namespace std;

class LaserScannerTools {
  public:
    bool plot_laserscanner_values(LaserScanner& scanner, Errors& errors);

};

#endif	/* LASERSCANNERTOOLS_H */

