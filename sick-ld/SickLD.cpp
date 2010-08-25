/**
 * \file 
 *
 * \author
 * \date
 */
#include "SickLD.h"

SickLD::SickLD() {
  // Bouml preserved body begin 00026771
  this->sickLD = NULL;
  this->config = NULL;
  this->isConnected = false;
  // Bouml preserved body end 00026771
}

SickLD::~SickLD() {
  // Bouml preserved body begin 000267F1
  Errors er;
  this->close(er);
  if (this->config != NULL) {
    delete this->config;
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
  start_angs[0] = 180.0 - ((configuration.scanAngle.value()*180.0/M_PI)/2);
  stop_angs[0]  = 180.0 + ((configuration.scanAngle.value()*180.0/M_PI)/2);
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
    configuration.serialnumber = this->sickLD->GetSickSerialNumber();
    configuration.devicePath = this->sickLD->GetSickIPAddress();
    configuration.scanResolution = (this->sickLD->GetSickScanResolution()*M_PI/180.0) *radian;
    configuration.motorSpeed = this->sickLD->GetSickMotorSpeed() * hertz;
    configuration.numSectors = this->sickLD->GetSickNumActiveSectors();
    configuration.scanAngle = (this->sickLD->GetSickScanArea()*M_PI/180.0) *radian;

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

    unsigned int num_measurements = 0;
    //TODO derive num_measurements from configuration
    double* intput_ranges = new double[num_measurements];

    this->sickLD->GetSickMeasurements(intput_ranges, NULL, &num_measurements);


    std::vector< quantity<length> > output_ranges;
    std::vector< quantity<plane_angle> > output_range_angles;

    for(unsigned int i=0; i< num_measurements; i++){
      output_ranges[i] = intput_ranges[i] * meter;
      output_range_angles[i] =  this->config->scanResolution * (i + this->config->scanAngle.value()/2 * (-1));
    }
//    data.setNumMeasurementValues(num_measurements);
 //   data.setMeasurements(output_ranges, output_range_angles);


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
    unsigned int num_measurements = 0;
    //TODO derive num_measurements from configuration
    double* intput_ranges = new double[num_measurements];
    unsigned int* intput_intensities = new unsigned int[num_measurements];

    this->sickLD->GetSickMeasurements(intput_ranges, intput_intensities, &num_measurements);


    std::vector< quantity<length> > output_ranges;
    std::vector< quantity<plane_angle> > output_range_angles;
    std::vector< double > output_intensities;

    for(unsigned int i=0; i< num_measurements; i++){
      output_ranges[i] = intput_ranges[i] * meter;
      output_range_angles[i] =  this->config->scanResolution.value() * (i + this->config->scanAngle.value()/2 * (-1)) *radian ;
      output_intensities[i] = intput_intensities[i];
    }
//    data.setNumMeasurementValues(num_measurements);
//    data.setMeasurements(output_ranges, output_range_angles);
    // TODO set intensities

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

