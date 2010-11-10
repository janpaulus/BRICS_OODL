#ifndef BRICS_OODL_LASERSCANNERDATA_H
#define BRICS_OODL_LASERSCANNERDATA_H


#include <vector>
#include "generic/Units.hpp"
namespace brics_oodl {

/**
 * \brief 
 *
 */
class LaserScannerData {
  public:
    LaserScannerData();

    ~LaserScannerData();

    void getMesasurementIterator(std::vector< quantity<length> >::iterator& rangesIterator, std::vector< quantity<plane_angle> >::iterator& rangeAnglesIterator);

    void getMeasurements(std::vector< quantity<length> >& ranges, std::vector< quantity<plane_angle> >& rangeAngles) const;

    void setMeasurements(const std::vector< quantity<length> >& ranges, const std::vector< quantity<plane_angle> >& rangeAngles);

    void setMeasurements(double* ranges, double* rangeAngles, const unsigned int& numRanges, const boost::units::si::length& rangeUnit, const boost::units::si::plane_angle& angleUnit);

    void setMeasurements(unsigned int* ranges, double* rangeAngles, const unsigned int& numRanges, const boost::units::si::length& rangeUnit, const boost::units::si::plane_angle& angleUnit);

    void setMeasurements(const std::vector<double>& ranges, const std::vector<double>& rangeAngles, const boost::units::si::length& rangeUnit, const boost::units::si::plane_angle& angleUnit);

    quantity<si::time> getTimeStamp() const;


  protected:
    std::vector< quantity<length> > ranges;

    std::vector< quantity<plane_angle> > rangeAngles;

    quantity<si::time> timestamp;

};

} // namespace brics_oodl
#endif
