
#include "SickLMS2xx.h"

SickLMS2xx::SickLMS2xx() {
  // Bouml preserved body begin 0001F471
  this->sickLMS = NULL;
  this->config = NULL;
  this->isConnected = false;
  this->ranges = NULL;
  this->rangeAngles = NULL;
  this->intensities = NULL;
  this->numMeasurements = 0;
  // Bouml preserved body end 0001F471
}

SickLMS2xx::~SickLMS2xx() {
  // Bouml preserved body begin 0001F4F1
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
  // Bouml preserved body end 0001F4F1
}

bool SickLMS2xx::close(Errors& error) {
  // Bouml preserved body begin 00021071
  if (this->sickLMS != NULL) {
    try {
      this->sickLMS->Uninitialize();
    } catch (SickToolbox::SickException &e){
      error.addError("unable_to_uninitialize", e.what());
    } catch (...) {
      error.addError("unable_to_uninitialize", "could not uninitialize the Sick LMS");
      return false;
    }
    delete sickLMS;
    this->sickLMS = NULL;
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

    if (configuration.availabilityLevel != currentConfig.availabilityLevel) {
      this->sickLMS->SetSickAvailability(configuration.availabilityLevel);
    }
    if (configuration.measuringMode != currentConfig.measuringMode) {
      this->sickLMS->SetSickMeasuringMode(configuration.measuringMode);
    }
    if (configuration.sensitivity != currentConfig.sensitivity) {
      this->sickLMS->SetSickSensitivity(configuration.sensitivity);
    }
    if (configuration.peakThreshold != currentConfig.peakThreshold) {
      this->sickLMS->SetSickPeakThreshold(configuration.peakThreshold);
    }
    if (configuration.measuringUnits != currentConfig.measuringUnits) {
      this->sickLMS->SetSickMeasuringUnits(configuration.measuringUnits);
    }
    if ((configuration.scanAngle != currentConfig.scanAngle) || (configuration.scanResolution != currentConfig.scanResolution)) {

      sick_lms_scan_angle_t desired_scan_angle;
      sick_lms_scan_resolution_t desired_scan_resolution;

      double angle = configuration.scanAngle.value()*180.0 / M_PI;
      double resolution = configuration.scanResolution.value()*180.0 / M_PI;
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

      this->sickLMS->SetSickVariant(desired_scan_angle, desired_scan_resolution);
    }
  } catch (SickToolbox::SickException &e){
    error.addError("unable_to_set_configuration", e.what());
  } catch (...) {
    error.addError("unable_to_set_configuration", "could not set the configuration to the Sick LMS");
    return false;
  }

  // configuration.operating_mode = this->sickLMS->GetSickOperatingMode();
  // configuration.model = this->sickLMS->SickTypeToString(this->sickLMS->GetSickType());
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
    configuration.measuringMode = this->sickLMS->SickMeasuringModeToString(this->sickLMS->GetSickMeasuringMode());
    configuration.sensitivity = this->sickLMS->SickSensitivityToString(this->sickLMS->GetSickSensitivity());
    configuration.peakThreshold = this->sickLMS->SickPeakThresholdToString(this->sickLMS->GetSickPeakThreshold());
    configuration.scanAngle = this->sickLMS->GetSickScanAngle() * M_PI / 180.0 * radian;
    configuration.scanResolution = this->sickLMS->GetSickScanResolution() * M_PI / 180.0 * radian;
    configuration.firmware = this->sickLMS->GetSickSoftwareVersionAsString();
    // this->sickLMS->GetSickStatusAsString();
    configuration.operatingMode = this->sickLMS->SickOperatingModeToString(this->sickLMS->GetSickOperatingMode());
    configuration.model = this->sickLMS->SickTypeToString(this->sickLMS->GetSickType());

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
    configuration.availabilityLevel = this->sickLMS->GetSickAvailability();
    configuration.measuringMode = this->sickLMS->GetSickMeasuringMode();
    configuration.sensitivity = this->sickLMS->GetSickSensitivity();
    configuration.peakThreshold = this->sickLMS->GetSickPeakThreshold();
    configuration.scanAngle = this->sickLMS->GetSickScanAngle() * M_PI / 180.0 * radian;
    configuration.scanResolution = this->sickLMS->GetSickScanResolution() * M_PI / 180.0 * radian;
    configuration.firmware = this->sickLMS->GetSickSoftwareVersionAsString();
    // this->sickLMS->GetSickStatusAsString();
    configuration.operatingMode = this->sickLMS->GetSickOperatingMode();
    configuration.measuringUnits = this->sickLMS->GetSickMeasuringUnits();
    configuration.model = this->sickLMS->SickTypeToString(this->sickLMS->GetSickType());
    configuration.isSickLMSFast = this->sickLMS->IsSickLMSFast();

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

    // derive num_measurements from configuration
    if(this->config->scanResolution.value() == 0.0){
      error.addError("unable_to_get_data", "the scan resolution can not be zero");
      return false;
    }

    unsigned int newNumMeasurements = ((1.0/this->config->scanResolution) * this->config->scanAngle).value();;

    if(this->numMeasurements != newNumMeasurements){
      this->numMeasurements  = newNumMeasurements;
      delete this->ranges;
      delete this->rangeAngles;
      this->ranges = new unsigned int[this->numMeasurements];
      this->rangeAngles = new double[this->numMeasurements];
    }

    this->sickLMS->GetSickScan(ranges, this->numMeasurements);


    for(unsigned int i=0; i< this->numMeasurements; i++){
      rangeAngles[i] =  this->config->scanResolution.value() * (i + this->config->scanAngle.value()/2 * (-1)) ;
    }

    data.setMeasurements(ranges, rangeAngles, this->numMeasurements, meter, radian); //TODO find out right units


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

    // derive num_measurements from configuration
    if(this->config->scanResolution.value() == 0.0){
      error.addError("unable_to_get_data", "the scan resolution can not be zero");
      return false;
    }

    unsigned int newNumMeasurements = ((1.0/this->config->scanResolution) * this->config->scanAngle).value();;

    if(this->numMeasurements != newNumMeasurements){
      this->numMeasurements  = newNumMeasurements;
      delete this->ranges;
      delete this->rangeAngles;
      delete this->intensities;
      this->ranges = new unsigned int[this->numMeasurements];
      this->rangeAngles = new double[this->numMeasurements];
      this->intensities = new unsigned int[this->numMeasurements];
    }

    this->sickLMS->GetSickScan(ranges, intensities, this->numMeasurements, this->numMeasurements);


    for(unsigned int i=0; i< this->numMeasurements; i++){
      rangeAngles[i] =  this->config->scanResolution.value() * (i + this->config->scanAngle.value()/2 * (-1)) ;
    }

    data.setMeasurements(ranges, rangeAngles, intensities, this->numMeasurements, meter, radian, meter); //TODO find out right units

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
    this->sickLMS->ResetSick();
  } catch (SickToolbox::SickException &e){
    error.addError("unable_to_reset_sickLMS", e.what());
  } catch (...) {
    error.addError("unable_to_reset_sickLMS", "could not reset the Sick LMS");
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

  if (this->config->devicePath == "") {
    error.addError("no_DevicePath", "the device path is not specified in the configuration");
    this->isConnected = false;
    return false;
  }

  if (this->sickLMS != NULL) {
    error.addError("still_Connected", "a previous connection was not closed correctly please close it again.");
    this->isConnected = false;
    return false;
  }

  this->sickLMS = new SickToolbox::SickLMS(this->config->devicePath);

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
    this->sickLMS->Initialize(desired_baud);
    this->getConfiguration(*(this->config), error);
    this->isConnected = true;
  } catch (SickToolbox::SickException &e){
    error.addError("Initialize_failed", e.what());
  } catch (...) {
    error.addError("Initialize_failed", "Initialize failed! Are you using the correct device path?");
    this->isConnected = false;
    delete this->sickLMS;
    this->sickLMS = NULL;
    return false;
  }
  return true;
  // Bouml preserved body end 00020FF1
}

