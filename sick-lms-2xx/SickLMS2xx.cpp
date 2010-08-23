
#include "SickLMS2xx.h"

SickLMS2xx::SickLMS2xx() {
  // Bouml preserved body begin 0001F471
  this->sick_lms = NULL;
  this->config = NULL;
  this->isConnected = false;
  // Bouml preserved body end 0001F471
}

SickLMS2xx::~SickLMS2xx() {
  // Bouml preserved body begin 0001F4F1
  Errors er;
  this->close(er);
  if (this->config != NULL) {
    delete this->config;
  }
  // Bouml preserved body end 0001F4F1
}

bool SickLMS2xx::close(Errors& error) {
  // Bouml preserved body begin 00021071
  if (this->sick_lms != NULL) {
    try {
      this->sick_lms->Uninitialize();
    } catch (SickToolbox::SickException &e){
      error.addError("unable_to_uninitialize", e.what());
    } catch (...) {
      error.addError("unable_to_uninitialize", "could not uninitialize the Sick LMS");
      return false;
    }
    delete sick_lms;
    this->sick_lms = NULL;
  }
  this->isConnected = false;
  return true;
  // Bouml preserved body end 00021071
}

bool SickLMS2xx::setConfiguration(const LaserScannerConfiguration& configuration, Errors& error) {
  // Bouml preserved body begin 00020E71
  error.addError("configuration_not_possible", "the configuration is not possible. Please configurate with SickLMS2xxConfiguration.");
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
  // Bouml preserved body end 00020E71
}

bool SickLMS2xx::setConfiguration(const SickLMS2xxConfiguration& configuration, Errors& error) {
  // Bouml preserved body begin 000213F1
  if (this->config != NULL) {
    delete this->config;
  }
  this->config = new SickLMS2xxConfiguration;
  *(this->config) = configuration;

  if (!this->open(error)) {
    return false;
  }

  SickLMS2xxConfiguration currentConfig;
  if (!this->getConfiguration(currentConfig, error)) {
    return false;
  }

  try {

    if (configuration.availability_level != currentConfig.availability_level) {
      this->sick_lms->SetSickAvailability(configuration.availability_level);
    }
    if (configuration.measuring_mode != currentConfig.measuring_mode) {
      this->sick_lms->SetSickMeasuringMode(configuration.measuring_mode);
    }
    if (configuration.sensitivity != currentConfig.sensitivity) {
      this->sick_lms->SetSickSensitivity(configuration.sensitivity);
    }
    if (configuration.peak_threshold != currentConfig.peak_threshold) {
      this->sick_lms->SetSickPeakThreshold(configuration.peak_threshold);
    }
    if (configuration.measuring_units != currentConfig.measuring_units) {
      this->sick_lms->SetSickMeasuringUnits(configuration.measuring_units);
    }
    if ((configuration.scan_angle != currentConfig.scan_angle) || (configuration.scan_resolution != currentConfig.scan_resolution)) {

      sick_lms_scan_angle_t desired_scan_angle;
      sick_lms_scan_resolution_t desired_scan_resolution;

      double angle = configuration.scan_angle.value()*180.0 / M_PI;
      double resolution = configuration.scan_resolution.value()*180.0 / M_PI;
      double offset = 1;

      if (90 > angle - offset && 90 < angle + offset) {
        desired_scan_angle = SickLMS::SICK_SCAN_ANGLE_90;

      } else if (100 > angle - offset && 100 < angle + offset) {
        desired_scan_angle = SickLMS::SICK_SCAN_ANGLE_100;

      } else if (180 > angle - offset && 180 < angle + offset) {
        desired_scan_angle = SickLMS::SICK_SCAN_ANGLE_180;

      } else {
        desired_scan_angle = SickLMS::SICK_SCAN_ANGLE_UNKNOWN;
        error.addError("unknown_scan_angle", "the scan angle is unknown. Please select one of 90°, 100° or 180°");
      }


      if (25 > resolution - offset && 25 < resolution + offset) {
        desired_scan_resolution = SickLMS::SICK_SCAN_RESOLUTION_25;

      } else if (50 > resolution - offset && 50 < resolution + offset) {
        desired_scan_resolution = SickLMS::SICK_SCAN_RESOLUTION_50;

      } else if (100 > resolution - offset && 100 < resolution + offset) {
        desired_scan_resolution = SickLMS::SICK_SCAN_RESOLUTION_100;

      } else {
        desired_scan_resolution = SickLMS::SICK_SCAN_RESOLUTION_UNKNOWN;
        error.addError("unknown_scan_resolution", "the scan resolution is unknown. Please select one of 0.25°, 0.5° or 1°");
      }

      this->sick_lms->SetSickVariant(desired_scan_angle, desired_scan_resolution);
    }
  } catch (SickToolbox::SickException &e){
    error.addError("unable_to_set_configuration", e.what());
  } catch (...) {
    error.addError("unable_to_set_configuration", "could not set the configuration to the Sick LMS");
    return false;
  }

  // configuration.operating_mode = this->sick_lms->GetSickOperatingMode();
  // configuration.model = this->sick_lms->SickTypeToString(this->sick_lms->GetSickType());
  return true;
  // Bouml preserved body end 000213F1
}

bool SickLMS2xx::getConfiguration(LaserScannerConfiguration& configuration, Errors& error) {
  // Bouml preserved body begin 00020EF1
  if (!this->open(error)) {
    return false;
  }
  try {
    configuration.vendor = "SICK";
    configuration.product = "LMS";
    configuration.measuring_mode = this->sick_lms->SickMeasuringModeToString(this->sick_lms->GetSickMeasuringMode());
    configuration.sensitivity = this->sick_lms->SickSensitivityToString(this->sick_lms->GetSickSensitivity());
    configuration.peak_threshold = this->sick_lms->SickPeakThresholdToString(this->sick_lms->GetSickPeakThreshold());
    configuration.scan_angle = this->sick_lms->GetSickScanAngle() * M_PI / 180.0 * radian;
    configuration.scan_resolution = this->sick_lms->GetSickScanResolution() * M_PI / 180.0 * radian;
    configuration.firmware = this->sick_lms->GetSickSoftwareVersionAsString();
    // this->sick_lms->GetSickStatusAsString();
    configuration.operating_mode = this->sick_lms->SickOperatingModeToString(this->sick_lms->GetSickOperatingMode());
    configuration.model = this->sick_lms->SickTypeToString(this->sick_lms->GetSickType());

  } catch (SickToolbox::SickException &e){
    error.addError("unable_to_read_configuration", e.what());
  } catch (...) {
    error.addError("unable_to_read_configuration", "could not get the configuration from the Sick LMS");
    return false;
  }

  return true;
  // Bouml preserved body end 00020EF1
}

bool SickLMS2xx::getConfiguration(SickLMS2xxConfiguration& configuration, Errors& error) {
  // Bouml preserved body begin 00021471
  if (!this->open(error)) {
    return false;
  }

  try {
    configuration.vendor = "SICK";
    configuration.product = "LMS";
    configuration.availability_level = this->sick_lms->GetSickAvailability();
    configuration.measuring_mode = this->sick_lms->GetSickMeasuringMode();
    configuration.sensitivity = this->sick_lms->GetSickSensitivity();
    configuration.peak_threshold = this->sick_lms->GetSickPeakThreshold();
    configuration.scan_angle = this->sick_lms->GetSickScanAngle() * M_PI / 180.0 * radian;
    configuration.scan_resolution = this->sick_lms->GetSickScanResolution() * M_PI / 180.0 * radian;
    configuration.firmware = this->sick_lms->GetSickSoftwareVersionAsString();
    // this->sick_lms->GetSickStatusAsString();
    configuration.operating_mode = this->sick_lms->GetSickOperatingMode();
    configuration.measuring_units = this->sick_lms->GetSickMeasuringUnits();
    configuration.model = this->sick_lms->SickTypeToString(this->sick_lms->GetSickType());
    configuration.is_sick_lms_fast = this->sick_lms->IsSickLMSFast();

  } catch (SickToolbox::SickException &e){
    error.addError("unable_to_read_configuration", e.what());
  } catch (...) {
    error.addError("unable_to_read_configuration", "could not get the configuration from the Sick LMS");
    return false;
  }

  return true;
  // Bouml preserved body end 00021471
}

bool SickLMS2xx::getData(LaserScannerData& data, Errors& error) {
  // Bouml preserved body begin 00020F71
  if (!this->open(error)) {
    return false;
  }
  try {

    unsigned int num_measurements = 0;
    //TODO derive num_measurements from configuration
    unsigned int* intput_ranges = new unsigned int[num_measurements];


    //Gets measurement data from the Sick. NOTE: Data can be either range or reflectivity given the Sick mode.
    this->sick_lms->GetSickScan(intput_ranges, num_measurements); 


    std::vector< quantity<length> > output_ranges;
    std::vector< quantity<plane_angle> > output_range_angles;

    for(unsigned int i=0; i< num_measurements; i++){
      output_ranges[i] = intput_ranges[i] * meter;
      output_range_angles[i] =  this->config->scan_resolution.value() * (i + this->config->scan_angle.value()/2 * (-1)) *radian ;
    }
    data.setNumMeasurementValues(num_measurements);
    data.setRanges(output_ranges, output_range_angles);


  } catch (SickToolbox::SickException &e){
    error.addError("unable_to_get_data", e.what());
  } catch (...) {
    error.addError("unable_to_get_data", "could not get data from the Sick LMS");
    return false;
  }

  return true;
  // Bouml preserved body end 00020F71
}

bool SickLMS2xx::getData(LaserScannerDataWithIntensities& data, Errors& error) {
  // Bouml preserved body begin 00024B71
   if (!this->open(error)) {
    return false;
  }
  try {
    unsigned int ranges_size = data.getNumMeasurementValues();
    unsigned int intensities_size = data.getNumIntensitiesValues();

    //Gets range and reflectivity data from the Sick. NOTE: This only applies to Sick LMS 211/221/291-S14!
//    this->sick_lms->GetSickScan(data.getRangesPointer(), data.getIntensitiesPointer(), ranges_size, intensities_size);


    unsigned int num_measurements = 0;
    //TODO derive num_measurements from configuration
    unsigned int* intput_ranges = new unsigned int[num_measurements];
    unsigned int* intput_intensities = new unsigned int[num_measurements];

    this->sick_lms->GetSickScan(intput_ranges, intput_intensities, num_measurements, num_measurements);


    std::vector< quantity<length> > output_ranges;
    std::vector< quantity<plane_angle> > output_range_angles;
    std::vector< double > output_intensities;

    for(unsigned int i=0; i< num_measurements; i++){
      output_ranges[i] = intput_ranges[i] * meter; //TODO use mesurment unit to derive right unit
      output_range_angles[i] =  this->config->scan_resolution.value() * (i + this->config->scan_angle.value()/2 * (-1)) *radian ;
      output_intensities[i] = intput_intensities[i];
    }
    data.setNumMeasurementValues(num_measurements);
    data.setRanges(output_ranges, output_range_angles);
    // TODO set intensities

  } catch (SickToolbox::SickException &e){
    error.addError("unable_to_get_data", e.what());
  } catch (...) {
    error.addError("unable_to_get_data", "could not get data from the Sick LMS");
    return false;
  }

  return true;
  // Bouml preserved body end 00024B71
}

bool SickLMS2xx::resetDevice() {
  // Bouml preserved body begin 00023071
  Errors error;
  if (!this->open(error)) {
    return false;
  }
  try {
    this->sick_lms->ResetSick();
  } catch (SickToolbox::SickException &e){
    error.addError("unable_to_reset_Sick_LMS", e.what());
  } catch (...) {
    error.addError("unable_to_reset_Sick_LMS", "could not reset the Sick LMS");
    return false;
  }
  return true;
  // Bouml preserved body end 00023071
}

bool SickLMS2xx::open(Errors& error) {
  // Bouml preserved body begin 00020FF1
  if (this->isConnected) {
    return true;
  }

  if (this->config->device_path == "") {
    error.addError("no_DevicePath", "the device path is not specified in the configuration");
    this->isConnected = false;
    return false;
  }

  if (this->sick_lms != NULL) {
    error.addError("still_Connected", "a previous connection was not closed correctly please close it again.");
    this->isConnected = false;
    return false;
  }

  this->sick_lms = new SickToolbox::SickLMS(this->config->device_path);

  SickToolbox::SickLMS::sick_lms_baud_t desired_baud = SickToolbox::SickLMS::SICK_BAUD_38400;

  switch (this->config->boud) {
    case BAUD_9600:
      desired_baud = SickToolbox::SickLMS::SICK_BAUD_9600;
      break;
    case BAUD_19200:
      desired_baud = SickToolbox::SickLMS::SICK_BAUD_19200;
      break;
    case BAUD_38400:
      desired_baud = SickToolbox::SickLMS::SICK_BAUD_38400;
      break;
    case BAUD_500K:
      desired_baud = SickToolbox::SickLMS::SICK_BAUD_500K;
      break;
    case BAUD_UNKNOWN:
      desired_baud = SickToolbox::SickLMS::SICK_BAUD_UNKNOWN;
      break;
  }

  //Initialize the Sick LMS 2xx
  try {
    this->sick_lms->Initialize(desired_baud);
    this->isConnected = true;
  } catch (SickToolbox::SickException &e){
    error.addError("Initialize_failed", e.what());
  } catch (...) {
    error.addError("Initialize_failed", "Initialize failed! Are you using the correct device path?");
    this->isConnected = false;
    delete this->sick_lms;
    this->sick_lms = NULL;
    return false;
  }
  return true;
  // Bouml preserved body end 00020FF1
}

