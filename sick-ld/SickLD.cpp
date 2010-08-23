/**
 * \file 
 *
 * \author
 * \date
 */
#include "SickLD.h"

SickLD::SickLD() {
  // Bouml preserved body begin 00026771
  this->sick_ld = NULL;
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
  if (this->sick_ld != NULL) {
    try {
      this->sick_ld->Uninitialize();
    } catch (SickToolbox::SickException &e){
      error.addError("unable_to_uninitialize", e.what());
    } catch (...) {
      error.addError("unable_to_uninitialize", "could not uninitialize the Sick LD");
      return false;
    }
    delete sick_ld;
    this->sick_ld = NULL;
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
  start_angs[0] = 180.0 - ((configuration.scan_angle.value()*180.0/M_PI)/2);
  stop_angs[0]  = 180.0 + ((configuration.scan_angle.value()*180.0/M_PI)/2);
  try {

    this->sick_ld->SetSickGlobalParamsAndScanAreas(configuration.motor_speed.value(),
                                                   configuration.scan_resolution.value(),
                                                   start_angs,
                                                   stop_angs,
                                                   configuration.num_sectors);
    
  } catch (SickToolbox::SickException &e){
    error.addError("unable_to_set_configuration", e.what());
  } catch (...) {
    error.addError("unable_to_set_configuration", "could not set the configuration to the Sick LD");
    return false;
  }

  // configuration.operating_mode = this->sick_ld->GetSickOperatingMode();
  // configuration.model = this->sick_ld->SickTypeToString(this->sick_ld->GetSickType());
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
    configuration.firmware = this->sick_ld->GetSickFirmwareName()+ this->sick_ld->GetSickFirmwareVersion();
  //  configuration.model
  //  configuration.protocol
    configuration.serialnumber = this->sick_ld->GetSickSerialNumber();
    configuration.device_path = this->sick_ld->GetSickIPAddress();
    configuration.scan_resolution = (this->sick_ld->GetSickScanResolution()*M_PI/180.0) *radian;
    configuration.motor_speed = this->sick_ld->GetSickMotorSpeed() * hertz;
    configuration.num_sectors = this->sick_ld->GetSickNumActiveSectors();
    configuration.scan_angle = (this->sick_ld->GetSickScanArea()*M_PI/180.0) *radian;

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

    this->sick_ld->GetSickMeasurements(intput_ranges, NULL, &num_measurements);


    std::vector< quantity<length> > output_ranges;
    std::vector< quantity<plane_angle> > output_range_angles;

    for(unsigned int i=0; i< num_measurements; i++){
      output_ranges[i] = intput_ranges[i] * meter;
      output_range_angles[i] =  this->config->scan_resolution * i + this->config->scan_angle.value()/2 * (-1) ;
    }
    data.setNumMeasurementValues(num_measurements);
    data.setRanges(output_ranges, output_range_angles);


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

    this->sick_ld->GetSickMeasurements(intput_ranges, intput_intensities, &num_measurements);


    std::vector< quantity<length> > output_ranges;
    std::vector< quantity<plane_angle> > output_range_angles;
    std::vector< double > output_intensities;

    for(unsigned int i=0; i< num_measurements; i++){
      output_ranges[i] = intput_ranges[i] * meter;
      output_range_angles[i] =  this->config->scan_resolution.value() * (i + this->config->scan_angle.value()/2 * (-1)) *radian ;
      output_intensities[i] = intput_intensities[i];
    }
    data.setNumMeasurementValues(num_measurements);
    data.setRanges(output_ranges, output_range_angles);
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
    this->sick_ld->ResetSick();
  } catch (SickToolbox::SickException &e){
    error.addError("unable_to_reset_sick_ld", e.what());
  } catch (...) {
    error.addError("unable_to_reset_sick_ld", "could not reset the Sick LD");
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

  if (this->config->device_path == "") {
    error.addError("no_DevicePath", "the device path is not specified in the configuration");
    this->isConnected = false;
    return false;
  }

  if (this->sick_ld != NULL) {
    error.addError("still_Connected", "a previous connection was not closed correctly please close it again.");
    this->isConnected = false;
    return false;
  }

  this->sick_ld = new SickToolbox::SickLD(this->config->device_path);

 

  //Initialize the Sick LD
  try {
    this->sick_ld->Initialize();
    this->isConnected = true;
  } catch (SickToolbox::SickException &e){
    error.addError("Initialize_failed", e.what());
  } catch (...) {
    error.addError("Initialize_failed", "Initialize failed! Are you using the correct device path?");
    this->isConnected = false;
    delete this->sick_ld;
    this->sick_ld = NULL;
    return false;
  }
  return true;
  // Bouml preserved body end 00026C71
}

