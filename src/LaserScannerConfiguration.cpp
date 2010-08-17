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
  this->device_path = source.device_path;
  this->firmware = source.firmware;
  this->measuring_mode = source.measuring_mode;
  this->model = source.model;
  this->operating_mode = source.operating_mode;
  this->peak_threshold = source.peak_threshold;
  this->product = source.product;
  this->protocol = source.protocol;
  this->scan_angle = source.scan_angle;
  this->scan_resolution = source.scan_resolution;
  this->sensitivity = source.sensitivity;
  this->serialnumber = source.serialnumber;
  this->vendor = source.vendor;

  return *this;

  // Bouml preserved body end 00021571
}

