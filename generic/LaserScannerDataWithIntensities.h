#ifndef _LASERSCANNERDATAWITHINTENSITIES_H
#define _LASERSCANNERDATAWITHINTENSITIES_H


#include "LaserScannerData.h"

/**
 * \brief 
 *
 */
class LaserScannerDataWithIntensities : public LaserScannerData {
  public:
    LaserScannerDataWithIntensities();

    virtual ~LaserScannerDataWithIntensities();

    void getMesasurementIterator(std::vector< quantity<length> >::iterator rangesIterator, std::vector< quantity<plane_angle> >::iterator rangeAnglesIterator, const std::vector< double >::iterator intensitieIterator);

    void getsMeasurements(std::vector< quantity<length> >& ranges, std::vector< quantity<plane_angle> >& rangeAngles, std::vector< double >& intensities) const;

    void setMeasurements(const std::vector< quantity<length> >& ranges, const std::vector< quantity<plane_angle> >& rangeAngles, const std::vector< double >& intensities);


  protected:
    std::vector< double > intensities;

};
#endif
