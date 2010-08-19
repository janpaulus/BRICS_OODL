#ifndef _LASERSCANNERDATAWITHINTENSITIES_H
#define _LASERSCANNERDATAWITHINTENSITIES_H


#include "LaserScannerData.h"

/**
 * \brief 
 *
 */
class LaserScannerDataWithIntensities : public LaserScannerData {
  public:
    LaserScannerDataWithIntensities(unsigned int num_intensities_measurements);

    virtual ~LaserScannerDataWithIntensities();

    uint* getIntensitiesPointer();

    void setNumIntensitiesValues(unsigned int num_intensities_measurements);

    unsigned int getNumIntensitiesValues();


  protected:
    unsigned int* intensities;

    unsigned int num_intensities_measurements;

};
#endif
