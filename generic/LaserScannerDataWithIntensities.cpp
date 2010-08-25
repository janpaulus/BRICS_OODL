
#include "LaserScannerDataWithIntensities.h"

LaserScannerDataWithIntensities::LaserScannerDataWithIntensities() {
  // Bouml preserved body begin 00024C71


  // Bouml preserved body end 00024C71
}

LaserScannerDataWithIntensities::~LaserScannerDataWithIntensities() {
  // Bouml preserved body begin 00024CF1

  // Bouml preserved body end 00024CF1
}

void LaserScannerDataWithIntensities::getMesasurementIterator(std::vector< quantity<length> >::iterator rangesIterator, std::vector< quantity<plane_angle> >::iterator rangeAnglesIterator, const std::vector< double >::iterator intensitieIterator) {
  // Bouml preserved body begin 0002A4F1
  ranges = this->ranges;
  rangeAngles = this->rangeAngles;
  // Bouml preserved body end 0002A4F1
}

void LaserScannerDataWithIntensities::getsMeasurements(std::vector< quantity<length> >& ranges, std::vector< quantity<plane_angle> >& rangeAngles, std::vector< double >& intensities) const {
  // Bouml preserved body begin 0002A371
  ranges = this->ranges;
  rangeAngles = this->rangeAngles;
  // Bouml preserved body end 0002A371
}

void LaserScannerDataWithIntensities::setMeasurements(const std::vector< quantity<length> >& ranges, const std::vector< quantity<plane_angle> >& rangeAngles, const std::vector< double >& intensities) {
  // Bouml preserved body begin 0002A2F1
  this->ranges = ranges;
  // Bouml preserved body end 0002A2F1
}

