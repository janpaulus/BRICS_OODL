
#include "HokuyoURG.h"
#include "LaserScannerDataWithIntensities.h"

HokuyoURG::HokuyoURG() {
  // Bouml preserved body begin 00020E67
  //this->sick_s300 = NULL;
  //this->config = NULL;
  //this->isConnected = false;
  // Bouml preserved body end 00020E67
}

HokuyoURG::~HokuyoURG() {
  // Bouml preserved body begin 00020EE7
  Errors er;
  this->close(er);
  if (this->config != NULL) {
    delete this->config;
  }
  // Bouml preserved body end 00020EE7
}

bool HokuyoURG::close(Errors& error) {
  // Bouml preserved body begin 00020F67
  try {
    this->urgDevice.disconnect();
  } catch (...) {
    error.addError("unable_to_uninitialize", "could not uninitialize the Sick LMS");
    return false;
  }
  this->isConnected = false;
  // Bouml preserved body end 00020F67
}

bool HokuyoURG::setConfiguration(const LaserScannerConfiguration& configuration, Errors& error) {
  // Bouml preserved body begin 00020FE7
  error.addError("configuration_not_possible", "the configuration is not possible. Please configurate with SickLMS2xxConfiguration.");
  /*
  if (this->config != NULL) {
    delete this->config;
  }
  this->config = new LaserScannerConfiguration;
   *(this->config) = configuration;
  
  if (!this->open(error)) {
    return false;
  }
   */
  // Bouml preserved body end 00020FE7
}

bool HokuyoURG::setConfiguration(const HokuyoURGConfiguration& configuration, Errors& error) {
  // Bouml preserved body begin 00021067
 /* if (this->config != NULL) {
    delete this->config;
  }
*/
  if (!this->open(error)) {
    return false;
  }
  try{
  
    
  } catch (...) {
    error.addError("unable_to_set_configuration", "could not set the configuration to the Sick LMS");
    return false;
  }

  // configuration.operating_mode = this->sick_s300->GetSickOperatingMode();
  // configuration.model = this->sick_s300->SickTypeToString(this->sick_s300->GetSickType());

  // Bouml preserved body end 00021067
}

bool HokuyoURG::getConfiguration(LaserScannerConfiguration& configuration, Errors& error) {
  // Bouml preserved body begin 000210E7
  if (!this->open(error)) {
    return false;
  }
  try {
   

  } catch (...) {
    error.addError("unable_to_read_configuration", "could not get the configuration from the Sick LMS");
    return false;
  }

  return true;
  // Bouml preserved body end 000210E7
}

bool HokuyoURG::getConfiguration(HokuyoURGConfiguration& configuration, Errors& error) {
  // Bouml preserved body begin 00021167
  if (!this->open(error)) {
    return false;
  }

  try {
   

  } catch (...) {
    error.addError("unable_to_read_configuration", "could not get the configuration from the Sick LMS");
    return false;
  }

  return true;
  // Bouml preserved body end 00021167
}

bool HokuyoURG::getData(LaserScannerData& data, Errors& error) {
  // Bouml preserved body begin 000211E7
  if (!this->open(error)) {
    return false;
  }
  try {
//    unsigned int size = data.getNumMeasurementValues();
    
    //getScan(std::vector<double> &vdDistanceM, std::vector<double> &vdAngleRAD, std::vector<double> &vdIntensityAU);
 //   this->sick_s300->GetSickScan(data.getRangesPointer(), size);

  } catch (...) {
    error.addError("unable_to_get_data", "could not get data from the Sick LMS");
    return false;
  }

  return true;
  // Bouml preserved body end 000211E7
}

bool HokuyoURG::getData(LaserScannerDataWithIntensities& data, Errors& error) {
  // Bouml preserved body begin 00021267
  /* if (!this->open(error)) {
    return false;
  }
  try {
    unsigned int ranges_size = data.getNumMeasurementValues();
    unsigned int intensities_size = data.getNumIntensitiesValues();


//    getScan(std::vector<double> &vdDistanceM, std::vector<double> &vdAngleRAD, std::vector<double> &vdIntensityAU);
 //   this->sick_s300->GetSickScan(data.getRangesPointer(), data.getIntensitiesPointer(), ranges_size, intensities_size);

  } catch (...) {
    error.addError("unable_to_get_data", "could not get data from the Sick LMS");
    return false;
  }
*/
  return true;
  // Bouml preserved body end 00021267
}

bool HokuyoURG::resetDevice() {
  // Bouml preserved body begin 000212E7
  Errors error;

  error.addError("unable_to_reset_sick_s300", "could not reset the Sick LMS");

  return false;
  // Bouml preserved body end 000212E7
}

bool HokuyoURG::open(Errors& error) {
  // Bouml preserved body begin 00021367
  if (this->isConnected) {
    return true;
  }

  if (this->config->devicePath == "") {
    error.addError("no_DevicePath", "the device path is not specified in the configuration");
    this->isConnected = false;
    return false;
  }

  if (this->urgDevice.isConnected()){
    error.addError("still_Connected", "a previous connection was not closed correctly please close it again.");
    this->isConnected = false;
    return false;
  }

 // this->urgDevice = new UrgCtrl(void);
/*
  //Initialize the Sick LMS 2xx
  try {
    this->urgDevice->connect(this->config->devicePath.c_str());
    this->isConnected = true;
  } catch (...) {
    error.addError("Initialize_failed", "Initialize failed! Are you using the correct device path?");
    this->isConnected = false;
    delete this->urgDevice;
    this->urgDevice = NULL;
    return false;
  }*/
  return true;
  // Bouml preserved body end 00021367
}

