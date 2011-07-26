
#include "LaserScannerData.hpp"
namespace brics_oodl {

LaserScannerData::LaserScannerData() {
  // Bouml preserved body begin 0001F67C

  
  // Bouml preserved body end 0001F67C
}

LaserScannerData::~LaserScannerData(){
  // Bouml preserved body begin 0001F6FC

  // Bouml preserved body end 0001F6FC
}

void LaserScannerData::getMesasurementIterator(std::vector< quantity<length> >::iterator& rangesIterator, std::vector< quantity<plane_angle> >::iterator& rangeAnglesIterator) {
  // Bouml preserved body begin 0002A471

  // Bouml preserved body end 0002A471
}

void LaserScannerData::getMeasurements(std::vector< quantity<length> >& ranges, std::vector< quantity<plane_angle> >& rangeAngles) const {
  // Bouml preserved body begin 0001F77C
  ranges = this->ranges;
  rangeAngles = this->rangeAngles;
  // Bouml preserved body end 0001F77C
}

void LaserScannerData::setMeasurements(const std::vector< quantity<length> >& ranges, const std::vector< quantity<plane_angle> >& rangeAngles) {
  // Bouml preserved body begin 000287F1
  this->ranges = ranges;
  this->rangeAngles = rangeAngles;
  // Bouml preserved body end 000287F1
}

void LaserScannerData::setMeasurements(double* ranges, double* rangeAngles, const unsigned int& numRanges, const boost::units::si::length& rangeUnit, const boost::units::si::plane_angle& angleUnit) {
  // Bouml preserved body begin 00028871
  this->ranges.clear();
  this->rangeAngles.clear();
  
  for(unsigned int i=0; i< numRanges; i++){
      this->ranges.push_back(ranges[i] * rangeUnit);
      this->rangeAngles.push_back(rangeAngles[i] * angleUnit);
  }

  // Bouml preserved body end 00028871
}

void LaserScannerData::setMeasurements(unsigned int* ranges, double* rangeAngles, const unsigned int& numRanges, const boost::units::si::length& rangeUnit, const boost::units::si::plane_angle& angleUnit) {
  // Bouml preserved body begin 0002A5F1
  this->ranges.clear();
  this->rangeAngles.clear();
  
  for(unsigned int i=0; i< numRanges; i++){
      this->ranges.push_back(((double)ranges[i]) * rangeUnit);
      this->rangeAngles.push_back(rangeAngles[i] * angleUnit);
  }

  // Bouml preserved body end 0002A5F1
}

void LaserScannerData::setMeasurements(const std::vector<double>& ranges, const std::vector<double>& rangeAngles, const boost::units::si::length& rangeUnit, const boost::units::si::plane_angle& angleUnit) {
  // Bouml preserved body begin 0002BFF1
  if(ranges.size() != rangeAngles.size()){
    return;
  }
  this->ranges.clear();
  this->rangeAngles.clear();
  
  for(unsigned int i=0; i< ranges.size(); i++){
      this->ranges.push_back((ranges[i]) * rangeUnit);
      this->rangeAngles.push_back(rangeAngles[i] * angleUnit);
  }

  // Bouml preserved body end 0002BFF1
}

quantity<si::time> LaserScannerData::getTimeStamp() const {
  // Bouml preserved body begin 0001F9FC
  // Bouml preserved body end 0001F9FC
}


} // namespace brics_oodl
