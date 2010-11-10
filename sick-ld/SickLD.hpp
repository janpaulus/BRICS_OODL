#ifndef BRICS_OODL_SICKLD_H
#define BRICS_OODL_SICKLD_H

/**
 * \file 
 *
 * \author
 * \date
 */
#include <vector>
#include "generic/Logger.hpp"
#include "generic/Units.hpp"
#include "generic/Errors.hpp"
#include "generic-laser-scanner/LaserScanner.hpp"
#include "generic-laser-scanner/LaserScannerData.hpp"
#include "generic-laser-scanner/LaserScannerDataWithIntensities.hpp"
#include "generic-laser-scanner/LaserScannerConfiguration.hpp"
#include "sick-ld/SickLDConfiguration.hpp"

#include <sickld-1.0/SickLD.hh>
namespace brics_oodl { class Errors; } 
namespace brics_oodl { class LaserScannerConfiguration; } 
namespace brics_oodl { class SickLDConfiguration; } 
namespace brics_oodl { class LaserScannerData; } 
namespace brics_oodl { class LaserScannerDataWithIntensities; } 

namespace brics_oodl {

/**
 * \brief 
 *
 */
class SickLD : public LaserScanner {
  public:
    SickLD();

    virtual ~SickLD();

    bool open(Errors& error);

    bool close(Errors& error);

    bool setConfiguration(const LaserScannerConfiguration& configuration, Errors& error);

    bool setConfiguration(const SickLDConfiguration& configuration, Errors& error);

    bool getConfiguration(LaserScannerConfiguration& configuration, Errors& error);

    bool getConfiguration(SickLDConfiguration& configuration, Errors& error);

    bool getData(LaserScannerData& data, Errors& error);

    bool getData(LaserScannerDataWithIntensities& data, Errors& error);

    bool resetDevice(Errors& error);


  private:
    LaserScannerConfiguration* config;

    bool isConnected;

    SickToolbox::SickLD* sickLD;

    double* ranges;

    double* rangeAngles;

    unsigned int* intensities;

};

} // namespace brics_oodl
#endif
