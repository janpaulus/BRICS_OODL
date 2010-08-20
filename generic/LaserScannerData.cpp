
#include "LaserScannerData.h"

LaserScannerData::LaserScannerData(const unsigned int& num_range_measurements_values){
  // Bouml preserved body begin 0001F67C
  this->ranges = NULL;
  this->setNumMeasurementValues(num_range_measurements_values);
  
  // Bouml preserved body end 0001F67C
}

LaserScannerData::~LaserScannerData(){
  // Bouml preserved body begin 0001F6FC
  if(this->ranges != NULL){
    delete this->ranges;
  }

  // Bouml preserved body end 0001F6FC
}

quantity<length> LaserScannerData::getRanges() const {
  // Bouml preserved body begin 0001F77C
  // Bouml preserved body end 0001F77C
}

double* LaserScannerData::getRangesPointer() {
  // Bouml preserved body begin 000249F1
  return this->ranges;
  // Bouml preserved body end 000249F1
}

quantity<si::time> LaserScannerData::getTimeStamp() const {
  // Bouml preserved body begin 0001F9FC
  // Bouml preserved body end 0001F9FC
}

void LaserScannerData::setNumMeasurementValues(const unsigned int& num_range_measurements_values) {
  // Bouml preserved body begin 00024A71
  if(this->ranges != NULL){
    delete this->ranges;
  }
  this->ranges = new double[num_range_measurements_values];
  this->num_range_measurements = num_range_measurements_values;
  // Bouml preserved body end 00024A71
}

unsigned int LaserScannerData::getNumMeasurementValues() {
  // Bouml preserved body begin 00024AF1
  return this->num_range_measurements;
  // Bouml preserved body end 00024AF1
}

