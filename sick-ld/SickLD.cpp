/**
 * \file 
 *
 * \author
 * \date
 */
#include "sick-ld/SickLD.h"
SickLD::SickLD() {
  // Bouml preserved body begin 00026771
  this->sickLD = NULL;
  this->config = NULL;
  this->isConnected = false;
  this->ranges = NULL;
  this->rangeAngles = NULL;
  this->intensities = NULL;
  this->ranges = new double[SickToolbox::SickLD::SICK_MAX_NUM_MEASUREMENTS];
  this->rangeAngles = new double[SickToolbox::SickLD::SICK_MAX_NUM_MEASUREMENTS];
  this->intensities = new unsigned int[SickToolbox::SickLD::SICK_MAX_NUM_MEASUREMENTS];
  // Bouml preserved body end 00026771
}

SickLD::~SickLD() {
  // Bouml preserved body begin 000267F1
  Errors er;
  this->close(er);
  if (this->config != NULL) {
    delete this->config;
  }
  if (this->ranges != NULL) {
    delete this->ranges;
  }
  if (this->rangeAngles != NULL) {
    delete this->rangeAngles;
  }
  if (this->intensities != NULL) {
    delete this->intensities;
  }
  // Bouml preserved body end 000267F1
}

bool SickLD::close(Errors& error) {
  // Bouml preserved body begin 00026871
  if (this->sickLD != NULL) {
    try {
      this->sickLD->Uninitialize();
    } catch (SickToolbox::SickException &e){
      error.addError("unable_to_uninitialize", e.what());
    } catch (...) {
      error.addError("unable_to_uninitialize", "could not uninitialize the Sick LD");
      return false;
    }
    delete sickLD;
    this->sickLD = NULL;
  }
  this->isConnected = false;
  return true;
  // Bouml preserved body end 00026871
}

bool SickLD::setConfiguration(const LaserScannerConfiguration& configuration, Errors& error) {
  // Bouml preserved body begin 000268F1
  error.addError("configuration_not_possible", "the configuration is not possible. Please configurate with SickLDConfiguration.");
  return false;
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
  // Bouml preserved body end 000268F1
}

bool SickLD::setConfiguration(const SickLDConfiguration& configuration, Errors& error) {
  // Bouml preserved body begin 00026971
  if (this->config != NULL) {
    delete this->config;
  }
  this->config = new SickLDConfiguration;
  *(this->config) = configuration;

  if (!this->open(error)) {
    return false;
  }


  double start_angs[SickToolbox::SickLD::SICK_MAX_NUM_MEASURING_SECTORS] = {0};
  double stop_angs[SickToolbox::SickLD::SICK_MAX_NUM_MEASURING_SECTORS] = {0};
  start_angs[0] = configuration.scanAngleStart.value()*180.0/M_PI;
  stop_angs[0]  = configuration.scanAngleStop.value()*180.0/M_PI;
  try {

    this->sickLD->SetSickGlobalParamsAndScanAreas(configuration.motorSpeed.value(),
                                                   configuration.scanResolution.value(),
                                                   start_angs,
                                                   stop_angs,
                                                   configuration.numSectors);
    
  } catch (SickToolbox::SickException &e){
    error.addError("unable_to_set_configuration", e.what());
  } catch (...) {
    error.addError("unable_to_set_configuration", "could not set the configuration to the Sick LD");
    return false;
  }

  // configuration.operating_mode = this->sickLD->GetSickOperatingMode();
  // configuration.model = this->sickLD->SickTypeToString(this->sickLD->GetSickType());
  return true;
  // Bouml preserved body end 00026971
}

bool SickLD::getConfiguration(LaserScannerConfiguration& configuration, Errors& error) {
  // Bouml preserved body begin 000269F1
  if (!this->open(error)) {
    return false;
  }
  try {
   

  } catch (SickToolbox::SickException &e){
    error.addError("unable_to_read_configuration", e.what());
  } catch (...) {
    error.addError("unable_to_read_configuration", "could not get the configuration from the Sick LD");
    return false;
  }

  return true;
  // Bouml preserved body end 000269F1
}

bool SickLD::getConfiguration(SickLDConfiguration& configuration, Errors& error) {
  // Bouml preserved body begin 00026A71
  if (!this->open(error)) {
    return false;
  }

  try {
    configuration.vendor = "SICK";
    configuration.product = "LD";
    configuration.firmware = this->sickLD->GetSickFirmwareName()+ this->sickLD->GetSickFirmwareVersion();
  //  configuration.model
  //  configuration.protocol
    configuration.serialNumber = this->sickLD->GetSickSerialNumber();
    configuration.devicePath = this->sickLD->GetSickIPAddress();
    configuration.scanResolution = (this->sickLD->GetSickScanResolution()*M_PI/180.0) *radian;
    configuration.motorSpeed = this->sickLD->GetSickMotorSpeed() * hertz;
    configuration.numSectors = this->sickLD->GetSickNumActiveSectors();
    configuration.scanAngleStart = (this->sickLD->GetSickScanArea()*M_PI/180.0)/-2.0 *radian;

  } catch (SickToolbox::SickException &e){
    error.addError("unable_to_read_configuration", e.what());
  } catch (...) {
    error.addError("unable_to_read_configuration", "could not get the configuration from the Sick LD");
    return false;
  }

  return true;
  // Bouml preserved body end 00026A71
}

bool SickLD::getData(LaserScannerData& data, Errors& error) {
  // Bouml preserved body begin 00026AF1
  if (!this->open(error)) {
    return false;
  }
  try {

    unsigned int NumMeasurements = 0;

    this->sickLD->GetSickMeasurements(ranges, NULL, &NumMeasurements);

    for(unsigned int i=0; i< NumMeasurements; i++){
      rangeAngles[i] =  (this->config->scanResolution.value() * i) + this->config->scanAngleStart.value() ;
    }

    data.setMeasurements(ranges, rangeAngles, NumMeasurements, meter, radian); //TODO find out right units


  } catch (SickToolbox::SickException &e){
    error.addError("unable_to_get_data", e.what());
  } catch (...) {
    error.addError("unable_to_get_data", "could not get data from the Sick LD");
    return false;
  }

  return true;
  // Bouml preserved body end 00026AF1
}

bool SickLD::getData(LaserScannerDataWithIntensities& data, Errors& error) {
  // Bouml preserved body begin 00026B71
      if (!this->open(error)) {
    return false;
  }
  try {

   unsigned int NumMeasurements = 0;


    this->sickLD->GetSickMeasurements(this->ranges, this->intensities, &NumMeasurements);



    for(unsigned int i=0; i< NumMeasurements; i++){
      this->rangeAngles[i] =  (this->config->scanResolution.value() * i) + this->config->scanAngleStart.value() ;
    }

    data.setMeasurements(this->ranges, this->rangeAngles, this->intensities, NumMeasurements, meter, radian, meter); //TODO find out right units

  } catch (SickToolbox::SickException &e){
    error.addError("unable_to_get_data", e.what());
  } catch (...) {
    error.addError("unable_to_get_data", "could not get data from the Sick LD");
    return false;
  }

  return true;
  // Bouml preserved body end 00026B71
}

bool SickLD::resetDevice() {
  // Bouml preserved body begin 00026BF1
  Errors error;
  if (!this->open(error)) {
    return false;
  }
  try {
    this->sickLD->ResetSick();
  } catch (SickToolbox::SickException &e){
    error.addError("unable_to_reset_sickLD", e.what());
  } catch (...) {
    error.addError("unable_to_reset_sickLD", "could not reset the Sick LD");
    return false;
  }
  return true;
  // Bouml preserved body end 00026BF1
}

bool SickLD::open(Errors& error) {
  // Bouml preserved body begin 00026C71
  if (this->isConnected) {
    return true;
  }

  if (this->config->devicePath == "") {
    error.addError("no_DevicePath", "the device path is not specified in the configuration");
    this->isConnected = false;
    return false;
  }

  if (this->sickLD != NULL) {
    error.addError("still_Connected", "a previous connection was not closed correctly please close it again.");
    this->isConnected = false;
    return false;
  }

  this->sickLD = new SickToolbox::SickLD(this->config->devicePath);

 

  //Initialize the Sick LD
  try {
    this->sickLD->Initialize();
    this->isConnected = true;
  } catch (SickToolbox::SickException &e){
    error.addError("Initialize_failed", e.what());
  } catch (...) {
    error.addError("Initialize_failed", "Initialize failed! Are you using the correct device path?");
    this->isConnected = false;
    delete this->sickLD;
    this->sickLD = NULL;
    return false;
  }
  return true;
  // Bouml preserved body end 00026C71
}

