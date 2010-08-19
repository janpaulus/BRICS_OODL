#ifndef _SICKLDCONFIGURATION_H
#define _SICKLDCONFIGURATION_H


#include "LaserScannerConfiguration.h"

class SickLDConfiguration : public LaserScannerConfiguration {
  public:
    SickLDConfiguration();

    virtual ~SickLDConfiguration();

    SickLDConfiguration(const SickLDConfiguration & source);

    virtual SickLDConfiguration & operator=(const SickLDConfiguration & source);

    sick_lms_measuring_mode_t measuring_mode;

    uint8_t availability_level;

    sick_lms_sensitivity_t sensitivity;

    sick_lms_peak_threshold_t peak_threshold;

    sick_lms_operating_mode_t operating_mode;

    bool is_sick_lms_fast;

    sick_lms_measuring_units_t measuring_units;

};
#endif
