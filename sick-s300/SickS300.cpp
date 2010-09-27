
#include "sick-s300/SickS300.h"
SickS300::SickS300() {
  // Bouml preserved body begin 00020E67
  this->sickS300 = NULL;
  this->config = NULL;
  this->isConnected = false;
  src::severity_logger< severity_level > lg;


  // Bouml preserved body end 00020E67
}

SickS300::~SickS300() {
  // Bouml preserved body begin 00020EE7
  Errors er;
  this->close(er);
  if (this->config != NULL) {
    delete this->config;
  }
  // Bouml preserved body end 00020EE7
}

bool SickS300::close(Errors& error) {
  // Bouml preserved body begin 00020F67
  if (this->sickS300 != NULL) {
    try {
      this->sickS300->stopScanner();
       BOOST_LOG_SEV(lg, trace) << "connection to Sick S300 closed";
    } catch (...) {
      error.addError("unable_to_uninitialize", "could not uninitialize the Sick S300");
      return false;
    }
    delete sickS300;
    this->sickS300 = NULL;
  }
  this->isConnected = false;
  return true;
  // Bouml preserved body end 00020F67
}

bool SickS300::setConfiguration(const LaserScannerConfiguration& configuration, Errors& error) {
  // Bouml preserved body begin 00020FE7
  error.addError("configuration_not_possible", "the configuration is not possible.");
  return false;
  // Bouml preserved body end 00020FE7
}

bool SickS300::setConfiguration(const SickS300Configuration& configuration, Errors& error) {
  // Bouml preserved body begin 00021067
  error.addError("configuration_not_possible", "the configuration is not possible.");
  return false;
  // Bouml preserved body end 00021067
}

bool SickS300::getConfiguration(LaserScannerConfiguration& configuration, Errors& error) {
  // Bouml preserved body begin 000210E7
    error.addError("unable_to_read_configuration", "could not get the configuration from the Sick S300");
    return false;
  // Bouml preserved body end 000210E7
}

bool SickS300::getConfiguration(SickS300Configuration& configuration, Errors& error) {
  // Bouml preserved body begin 00021167
  error.addError("unable_to_read_configuration", "could not get the configuration from the Sick S300");
    return false;
  // Bouml preserved body end 00021167
}

bool SickS300::getData(LaserScannerData& data, Errors& error) {
  // Bouml preserved body begin 000211E7
  if (!this->open(error)) {
    return false;
  }
  try {
    std::vector<double> intput_ranges; //meter
    std::vector<double> intput_range_angles; //rad
    std::vector<double> intput_intensity; //?

    intput_ranges.assign(541, 110);
    intput_range_angles.assign(541, 0);
    intput_intensity.assign(541, 0);
    

    this->sickS300->getScan(intput_ranges, intput_range_angles, intput_intensity);

    if (intput_ranges.size() != intput_range_angles.size()) {
      error.addError("unable_to_get_data", "ranges vector and range_angles vector have to have the same size");
      return false;
    }
/*    std::vector< quantity<length> > output_ranges;
    std::vector< quantity<plane_angle> > output_range_angles;
    for (unsigned int i = 0; i < intput_ranges.size(); i++) {
      output_ranges[i] = intput_ranges[i] * meter;
      output_range_angles[i] = intput_range_angles[i] * radian;
    }
*/
    data.setMeasurements(intput_ranges, intput_range_angles, meter, radian);

    BOOST_LOG_SEV(lg, trace) << "receiving range scan from Sick S300" ;

  } catch (...) {
    error.addError("unable_to_get_data", "could not get data from the Sick S300");
    return false;
  }

  return true;
  // Bouml preserved body end 000211E7
}

bool SickS300::getData(LaserScannerDataWithIntensities& data, Errors& error) {
  // Bouml preserved body begin 00021267
  if (!this->open(error)) {
    return false;
  }
  try {

    std::vector<double> vdDistanceM;
    std::vector<double> vdAngleRAD;
    std::vector<double> vdIntensityAU;

    this->sickS300->getScan(vdDistanceM, vdAngleRAD, vdIntensityAU);

    data.setMeasurements(vdDistanceM, vdAngleRAD, vdIntensityAU, meter, radian, meter);

    BOOST_LOG_SEV(lg, trace) << "receiving range and intensity scan from Sick S300";

  } catch (...) {
    error.addError("unable_to_get_data", "could not get data from the Sick S300");
    return false;
  }

  return true;
  // Bouml preserved body end 00021267
}

bool SickS300::resetDevice(Errors& error) {
  // Bouml preserved body begin 000212E7
  error.addError("unable_to_reset_sick_s300", "could not reset the Sick S300");
  return false;
  // Bouml preserved body end 000212E7
}

bool SickS300::open(Errors& error) {
  // Bouml preserved body begin 00021367
  if (this->isConnected) {
    return true;
  }

  if (this->config->devicePath == "") {
    error.addError("no_DevicePath", "the device path is not specified in the configuration");
    this->isConnected = false;
    return false;
  }

  if (this->sickS300 != NULL) {
    error.addError("still_Connected", "a previous connection was not closed correctly please close it again.");
    this->isConnected = false;
    return false;
  }

  this->sickS300 = new ScannerSickS300();

  int desired_baud = 500000;

  switch (this->config->baud) {
    case BAUD_9600:
      desired_baud = 9600;
      BOOST_LOG_SEV(lg, trace) << "using 9600 baut to comunicate to Sick S300";
      break;
    case BAUD_19200:
      desired_baud = 19200;
      BOOST_LOG_SEV(lg, trace) << "using 19200 baut to comunicate to Sick S300";
      break;
    case BAUD_38400:
      desired_baud = 38400;
      BOOST_LOG_SEV(lg, trace) << "using 38400 baut to comunicate to Sick S300";
      break;
    case BAUD_500K:
      desired_baud = 500000;
      BOOST_LOG_SEV(lg, trace) << "using 500000 baut to comunicate to Sick S300";
      break;
    case BAUD_UNKNOWN:
      desired_baud = 0;
      break;
  }

  //Initialize the Sick S300
  try {
    if(!this->sickS300->open(this->config->devicePath.c_str(), desired_baud)){
      throw "could not initilize Sick S300";
    }
    this->isConnected = true;
    BOOST_LOG_SEV(lg, trace) << "connection to Sick S300 initialized";
  } catch (...) {
    error.addError("Initialize_failed", "could not initilize Sick S300");
    this->isConnected = false;
    delete this->sickS300;
    this->sickS300 = NULL;
    return false;
  }
  return true;
  // Bouml preserved body end 00021367
}

