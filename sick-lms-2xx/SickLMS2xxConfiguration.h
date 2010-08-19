#ifndef _SICKLMS2XXCONFIGURATION_H
#define _SICKLMS2XXCONFIGURATION_H


#include "LaserScannerConfiguration.h"

#include "sicklms-1.0/SickLMS.hh"
using namespace SickToolbox;
class SickLMS2xxConfiguration : public LaserScannerConfiguration {
  public:
    SickLMS2xxConfiguration();

    virtual ~SickLMS2xxConfiguration();

    SickLMS2xxConfiguration(const SickLMS2xxConfiguration & source);

    virtual SickLMS2xxConfiguration & operator=(const SickLMS2xxConfiguration & source);

    sick_lms_measuring_mode_t measuring_mode;

    uint8_t availability_level;

    sick_lms_sensitivity_t sensitivity;

    sick_lms_peak_threshold_t peak_threshold;

    sick_lms_operating_mode_t operating_mode;

    bool is_sick_lms_fast;

    sick_lms_measuring_units_t measuring_units;

};
#endif
