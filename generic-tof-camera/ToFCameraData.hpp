#ifndef BRICS_OODL_TOFCAMERADATA_H
#define BRICS_OODL_TOFCAMERADATA_H


#include "generic/Logger.hpp"
#include "generic/Units.hpp"
namespace brics_oodl {

/**
 * \brief 
 *
 */
class ToFCameraData {
  public:
    ToFCameraData();

    ~ToFCameraData();

    void getMeasurements(std::vector< quantity<length> >& ranges, std::vector< quantity<plane_angle> >& rangeAngles) const;

    void setMeasurements(const std::vector< quantity<length> >& ranges, const std::vector< quantity<plane_angle> >& rangeAngles);

    quantity<si::time> getTimeStamp() const;


  protected:
    quantity<si::time> timestamp;

};

} // namespace brics_oodl
#endif
