#ifndef BRICS_OODL_ONEDOFGRIPPERDATA_H
#define BRICS_OODL_ONEDOFGRIPPERDATA_H


#include "generic/Units.hpp"
#include "generic-gripper/GripperData.hpp"
namespace brics_oodl {

class OneDOFGripperData : public GripperData {
};
class GripperBarSpacingSetPoint : public OneDOFGripperData {
  public:
    quantity<si::length> barSpacing;

};

} // namespace brics_oodl
#endif
