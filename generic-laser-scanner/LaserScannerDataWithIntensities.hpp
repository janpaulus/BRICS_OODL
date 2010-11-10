#ifndef _LASERSCANNERDATAWITHINTENSITIES_H
#define _LASERSCANNERDATAWITHINTENSITIES_H


#include "LaserScannerData.hpp"

#include "generic-laser-scanner/LaserScannerData.hpp"
/**
 * \brief 
 *
 */
class LaserScannerDataWithIntensities : public LaserScannerData {
  public:
    LaserScannerDataWithIntensities();

    virtual ~LaserScannerDataWithIntensities();

    void getMesasurementIterator(std::vector< quantity<length> >::iterator& rangesIterator, std::vector< quantity<plane_angle> >::iterator& rangeAnglesIterator, std::vector< double >::iterator& intensitieIterator);

    void getMeasurements(std::vector< quantity<length> >& ranges, std::vector< quantity<plane_angle> >& rangeAngles, std::vector< double >& intensities) const;

    void setMeasurements(const std::vector< quantity<length> >& ranges, const std::vector< quantity<plane_angle> >& rangeAngles, const std::vector< double >& intensities);

    void setMeasurements(double* ranges, double* rangeAngles, unsigned int* intensities, const unsigned int& numMeasurements, const boost::units::si::length& rangeUnit, const boost::units::si::plane_angle& angleUnit, const boost::units::si::length& intensitieUnit);

    void setMeasurements(unsigned int* ranges, double* rangeAngles, unsigned int* intensities, const unsigned int& numMeasurements, const boost::units::si::length& rangeUnit, const boost::units::si::plane_angle& angleUnit, const boost::units::si::length& intensitieUnit);

    void setMeasurements(const std::vector<double>& ranges, const std::vector<double>& rangeAngles, const std::vector<double>& intensities, const boost::units::si::length& rangeUnit, const boost::units::si::plane_angle& angleUnit, const boost::units::si::length& intensitieUnit);


  protected:
    std::vector< double > intensities;

};
#endif
