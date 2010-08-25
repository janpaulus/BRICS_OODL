/**
 * \file 
 *
 * \author
 * \date
 */
#include "LaserScannerConfiguration.h"

LaserScannerConfiguration::LaserScannerConfiguration(){
  // Bouml preserved body begin 0001F47C
  // Bouml preserved body end 0001F47C
}

LaserScannerConfiguration::~LaserScannerConfiguration(){
  // Bouml preserved body begin 0001F4FC
  // Bouml preserved body end 0001F4FC
}

LaserScannerConfiguration::LaserScannerConfiguration(const LaserScannerConfiguration & source) {
  // Bouml preserved body begin 000214F1
  *this = source;
  // Bouml preserved body end 000214F1
}

LaserScannerConfiguration & LaserScannerConfiguration::operator=(const LaserScannerConfiguration & source) {
  // Bouml preserved body begin 00021571

  this->boud = source.boud;
  this->devicePath = source.devicePath;
  this->firmware = source.firmware;
  this->measuringMode = source.measuringMode;
  this->model = source.model;
  this->operatingMode = source.operatingMode;
  this->peakThreshold = source.peakThreshold;
  this->product = source.product;
  this->protocol = source.protocol;
  this->scanAngle = source.scanAngle;
  this->scanResolution = source.scanResolution;
  this->sensitivity = source.sensitivity;
  this->serialnumber = source.serialnumber;
  this->vendor = source.vendor;

  return *this;

  // Bouml preserved body end 00021571
}

