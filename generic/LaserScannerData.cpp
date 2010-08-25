
#include "LaserScannerData.h"

LaserScannerData::LaserScannerData() {
  // Bouml preserved body begin 0001F67C

  
  // Bouml preserved body end 0001F67C
}

LaserScannerData::~LaserScannerData(){
  // Bouml preserved body begin 0001F6FC

  // Bouml preserved body end 0001F6FC
}

void LaserScannerData::getMesasurementIterator(std::vector< quantity<length> >::iterator rangesIterator) {
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
  // Bouml preserved body end 000287F1
}

quantity<si::time> LaserScannerData::getTimeStamp() const {
  // Bouml preserved body begin 0001F9FC
  // Bouml preserved body end 0001F9FC
}

