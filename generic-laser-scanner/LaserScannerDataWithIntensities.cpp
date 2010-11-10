
#include "generic-laser-scanner/LaserScannerDataWithIntensities.hpp"
namespace brics_oodl {

LaserScannerDataWithIntensities::LaserScannerDataWithIntensities() {
  // Bouml preserved body begin 00024C71


  // Bouml preserved body end 00024C71
}

LaserScannerDataWithIntensities::~LaserScannerDataWithIntensities() {
  // Bouml preserved body begin 00024CF1

  // Bouml preserved body end 00024CF1
}

void LaserScannerDataWithIntensities::getMesasurementIterator(std::vector< quantity<length> >::iterator& rangesIterator, std::vector< quantity<plane_angle> >::iterator& rangeAnglesIterator, std::vector< double >::iterator& intensitieIterator) {
  // Bouml preserved body begin 0002A4F1
  rangesIterator = this->ranges.begin();
  rangeAnglesIterator = this->rangeAngles.begin();
  intensitieIterator = this->intensities.begin();
  // Bouml preserved body end 0002A4F1
}

void LaserScannerDataWithIntensities::getMeasurements(std::vector< quantity<length> >& ranges, std::vector< quantity<plane_angle> >& rangeAngles, std::vector< double >& intensities) const {
  // Bouml preserved body begin 0002A371
  ranges = this->ranges;
  rangeAngles = this->rangeAngles;
  intensities = this->intensities;
  // Bouml preserved body end 0002A371
}

void LaserScannerDataWithIntensities::setMeasurements(const std::vector< quantity<length> >& ranges, const std::vector< quantity<plane_angle> >& rangeAngles, const std::vector< double >& intensities) {
  // Bouml preserved body begin 0002A2F1
  this->ranges = ranges;
  this->rangeAngles = rangeAngles;
  this->intensities = intensities;
  // Bouml preserved body end 0002A2F1
}

void LaserScannerDataWithIntensities::setMeasurements(double* ranges, double* rangeAngles, unsigned int* intensities, const unsigned int& numMeasurements, const boost::units::si::length& rangeUnit, const boost::units::si::plane_angle& angleUnit, const boost::units::si::length& intensitieUnit) {
  // Bouml preserved body begin 0002A571
  this->ranges.reserve(numMeasurements);
  this->rangeAngles.reserve(numMeasurements);
  this->intensities.reserve(numMeasurements);
  
  for(unsigned int i=0; i< numMeasurements; i++){
      this->ranges[i] = ranges[i] * rangeUnit;
      this->rangeAngles[i] =  rangeAngles[i] * angleUnit;
      this->intensities[i] =  ((double)intensities[i]);// * intensitieUnit;
  }
  // Bouml preserved body end 0002A571
}

void LaserScannerDataWithIntensities::setMeasurements(unsigned int* ranges, double* rangeAngles, unsigned int* intensities, const unsigned int& numMeasurements, const boost::units::si::length& rangeUnit, const boost::units::si::plane_angle& angleUnit, const boost::units::si::length& intensitieUnit) {
  // Bouml preserved body begin 0002A671
  this->ranges.reserve(numMeasurements);
  this->rangeAngles.reserve(numMeasurements);
  this->intensities.reserve(numMeasurements);
  
  for(unsigned int i=0; i< numMeasurements; i++){
      this->ranges[i] = ((double)ranges[i]) * rangeUnit;
      this->rangeAngles[i] =  rangeAngles[i] * angleUnit;
      this->intensities[i] =  ((double)intensities[i]);// * intensitieUnit;
  }
  // Bouml preserved body end 0002A671
}

void LaserScannerDataWithIntensities::setMeasurements(const std::vector<double>& ranges, const std::vector<double>& rangeAngles, const std::vector<double>& intensities, const boost::units::si::length& rangeUnit, const boost::units::si::plane_angle& angleUnit, const boost::units::si::length& intensitieUnit) {
  // Bouml preserved body begin 0002C071
  if(ranges.size() != rangeAngles.size() || ranges.size() != intensities.size()){
    
    return;
  }
  this->ranges.reserve(ranges.size());
  this->rangeAngles.reserve(ranges.size());
  this->intensities.reserve(ranges.size());
  
  for(unsigned int i=0; i< ranges.size(); i++){
      this->ranges[i] = ((double)ranges[i]) * rangeUnit;
      this->rangeAngles[i] =  rangeAngles[i] * angleUnit;
      this->intensities[i] =  ((double)intensities[i]);// * intensitieUnit;
  }
  // Bouml preserved body end 0002C071
}


} // namespace brics_oodl
