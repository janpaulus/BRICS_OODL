
#include "LaserScannerData.h"

LaserScannerData::LaserScannerData(const unsigned int& num_range_measurements_values){
  // Bouml preserved body begin 0001F67C
  this->setNumMeasurementValues(num_range_measurements_values);
  
  // Bouml preserved body end 0001F67C
}

LaserScannerData::~LaserScannerData(){
  // Bouml preserved body begin 0001F6FC

  // Bouml preserved body end 0001F6FC
}

void LaserScannerData::getRanges(std::vector< quantity<length> >& ranges, std::vector< quantity<plane_angle> >& range_angles) const {
  // Bouml preserved body begin 0001F77C
  ranges = this->_ranges;
  range_angles = this->_range_angles;
  // Bouml preserved body end 0001F77C
}

void LaserScannerData::setRanges(const std::vector< quantity<length> >& ranges, const std::vector< quantity<plane_angle> >& range_angles) {
  // Bouml preserved body begin 000287F1
  this->_ranges = ranges;
  // Bouml preserved body end 000287F1
}

void LaserScannerData::setRanges(double* ranges, unsigned int num_ranges, const boost::units::si::length& unit) {
  // Bouml preserved body begin 00028871
  this->_ranges.clear();
  for(unsigned int i = 0; i<num_ranges; i++){
    this->_ranges.push_back(ranges[i] * unit);
  }
  // Bouml preserved body end 00028871
}

void LaserScannerData::setRanges(unsigned int* ranges, unsigned int num_ranges, const boost::units::si::length& unit) {
  // Bouml preserved body begin 000288F1
  // Bouml preserved body end 000288F1
}

quantity<si::time> LaserScannerData::getTimeStamp() const {
  // Bouml preserved body begin 0001F9FC
  // Bouml preserved body end 0001F9FC
}

void LaserScannerData::setNumMeasurementValues(const unsigned int& num_range_measurements_values) {
  // Bouml preserved body begin 00024A71
  this->_ranges.reserve(num_range_measurements_values);
  this->num_range_measurements = num_range_measurements_values;
  // Bouml preserved body end 00024A71
}

unsigned int LaserScannerData::getNumMeasurementValues() {
  // Bouml preserved body begin 00024AF1
  return this->num_range_measurements;
  // Bouml preserved body end 00024AF1
}

