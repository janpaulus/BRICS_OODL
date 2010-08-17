
#include "LaserScannerDataWithIntensities.h"

LaserScannerDataWithIntensities::LaserScannerDataWithIntensities(unsigned int num_intensities_measurements)
: LaserScannerData(num_intensities_measurements) {
  // Bouml preserved body begin 00024C71
  this->intensities = NULL;
  this->setNumIntensitiesValues(num_intensities_measurements);
  // Bouml preserved body end 00024C71
}

LaserScannerDataWithIntensities::~LaserScannerDataWithIntensities() {
  // Bouml preserved body begin 00024CF1
  if (this->intensities != NULL) {
    delete this->intensities;
  }
  // Bouml preserved body end 00024CF1
}

uint* LaserScannerDataWithIntensities::getIntensitiesPointer() {
  // Bouml preserved body begin 00024BF1
  return this->intensities;
  // Bouml preserved body end 00024BF1
}

void LaserScannerDataWithIntensities::setNumIntensitiesValues(unsigned int num_intensities_measurements) {
  // Bouml preserved body begin 00024D71
  if (this->intensities != NULL) {
    delete this->intensities;
  }
  this->intensities = new unsigned int[num_intensities_measurements];
  this->num_intensities_measurements = num_intensities_measurements;
  // Bouml preserved body end 00024D71
}

unsigned int LaserScannerDataWithIntensities::getNumIntensitiesValues() {
  // Bouml preserved body begin 00024DF1
  return this->num_intensities_measurements;
  // Bouml preserved body end 00024DF1
}

