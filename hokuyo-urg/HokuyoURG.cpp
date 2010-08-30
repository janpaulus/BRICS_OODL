
#include "HokuyoURG.h"

HokuyoURG::HokuyoURG() {
  // Bouml preserved body begin 0002DBF1
  this->config = NULL;
  this->isConnected = false;
  // Bouml preserved body end 0002DBF1
}

HokuyoURG::~HokuyoURG() {
  // Bouml preserved body begin 0002DC71
  Errors er;
  this->close(er);
  if (this->config != NULL) {
    delete this->config;
  }
  // Bouml preserved body end 0002DC71
}

bool HokuyoURG::close(Errors& error) {
  // Bouml preserved body begin 0002DCF1

    try {
      this->hokuyo.disconnect();

    } catch (...) {
      error.addError("unable_to_uninitialize", "could not uninitialize the Hokuyo URG");
      return false;
    }

  this->isConnected = false;
  return true;
  // Bouml preserved body end 0002DCF1
}

bool HokuyoURG::setConfiguration(const LaserScannerConfiguration& configuration, Errors& error) {
  // Bouml preserved body begin 0002DD71
  if (this->config != NULL) {
    delete this->config;
  }
  this->config = new HokuyoURGConfiguration;
  *(this->config) = configuration;

  if (!this->open(error)) {
    return false;
  }
   try{

     qrk::RangeSensorParameter parameters;
     parameters.area_front = 0;   //!< Front direction index
     parameters.area_max = config->scanAngleStop.value();        //!< Maximum possible measurement direction in terms of angle
     parameters.area_min = config->scanAngleStart.value();        //!< Least possible measurement direction in terms of angle
     parameters.area_total = config->scanResolution.value() *180.0/M_PI;      //!< Angular resolution(Number of partitions in 360 degree)
     parameters.distance_max = config->maxRangeDistance.value();    //!< Maximum possible measurement range [mm]
     parameters.distance_min = config->minRangeDistance.value();    //!< Least possible measurement range [mm]
     parameters.model =   config->model;           //!< Sensor model information
     parameters.scan_rpm = 600;  //!< Standard angular velocity [rpm]

     this->hokuyo.setParameter(parameters);

   } catch (...) {
     error.addError("unable_to_set_configuration", "could not set the configuration to the Hokuyo URG");
     return false;
   }

  return true;
  // Bouml preserved body end 0002DD71
}

bool HokuyoURG::setConfiguration(const HokuyoURGConfiguration& configuration, Errors& error) {
  // Bouml preserved body begin 0002DDF1
  if (this->config != NULL) {
    delete this->config;
  }
  this->config = new HokuyoURGConfiguration;
  *(this->config) = configuration;

  if (!this->open(error)) {
    return false;
  }
   try{

     qrk::RangeSensorParameter parameters;
     parameters.area_front = 0;   //!< Front direction index
     parameters.area_max = config->scanAngleStop.value() *180.0/M_PI;        //!< Maximum possible measurement direction in terms of angle
     parameters.area_min = config->scanAngleStart.value() *180.0/M_PI;        //!< Least possible measurement direction in terms of angle
     parameters.area_total = config->scanResolution.value() *180.0/M_PI;      //!< Angular resolution(Number of partitions in 360 degree)
     parameters.distance_max = config->maxRangeDistance.value() *1000;    //!< Maximum possible measurement range [mm]
     parameters.distance_min = config->minRangeDistance.value() *1000;    //!< Least possible measurement range [mm]
     parameters.model =   config->model;           //!< Sensor model information
     parameters.scan_rpm = 600;  //!< Standard angular velocity [rpm]

     this->hokuyo.setParameter(parameters);
    
   } catch (...) {
     error.addError("unable_to_set_configuration", "could not set the configuration to the Hokuyo URG");
     return false;
   }

  return true;
  // Bouml preserved body end 0002DDF1
}

bool HokuyoURG::getConfiguration(LaserScannerConfiguration& configuration, Errors& error) {
  // Bouml preserved body begin 0002DE71
  if (!this->open(error)) {
    return false;
  }
  try {
  qrk::RangeSensorParameter parameters;
  parameters = this->hokuyo.parameter();

     config->scanAngleStop =  parameters.area_max * M_PI/180.0 *radian ;        //!< Maximum possible measurement direction in terms of angle
     config->scanAngleStart = parameters.area_min * M_PI/180.0 * radian;        //!< Least possible measurement direction in terms of angle
     config->scanResolution = parameters.area_total * M_PI/180.0 * radian;      //!< Angular resolution(Number of partitions in 360 degree)
     config->maxRangeDistance = parameters.distance_max /1000.0 *meter;    //!< Maximum possible measurement range [mm]
     config->minRangeDistance = parameters.distance_min /1000.0 * meter;    //!< Least possible measurement range [mm]
     config->model = parameters.model;           //!< Sensor model information

  } catch (...) {
    error.addError("unable_to_read_configuration", "could not get the configuration from the Hokuyo URG");
    return false;
  }

  return true;
  // Bouml preserved body end 0002DE71
}

bool HokuyoURG::getConfiguration(HokuyoURGConfiguration& configuration, Errors& error) {
  // Bouml preserved body begin 0002DEF1
if (!this->open(error)) {
    return false;
  }
  try {
  qrk::RangeSensorParameter parameters;
  parameters = this->hokuyo.parameter();

     config->scanAngleStop =  parameters.area_max * M_PI/180.0 *radian ;        //!< Maximum possible measurement direction in terms of angle
     config->scanAngleStart = parameters.area_min * M_PI/180.0 * radian;        //!< Least possible measurement direction in terms of angle
     config->scanResolution = parameters.area_total * M_PI/180.0 * radian;      //!< Angular resolution(Number of partitions in 360 degree)
     config->maxRangeDistance = parameters.distance_max /1000.0 *meter;    //!< Maximum possible measurement range [mm]
     config->minRangeDistance = parameters.distance_min /1000.0 * meter;    //!< Least possible measurement range [mm]
     config->model = parameters.model;           //!< Sensor model information

  } catch (...) {
    error.addError("unable_to_read_configuration", "could not get the configuration from the Hokuyo URG");
    return false;
  }

  return true;
  // Bouml preserved body end 0002DEF1
}

bool HokuyoURG::getData(LaserScannerData& data, Errors& error) {
  // Bouml preserved body begin 0002DF71
  if (!this->open(error)) {
    return false;
  }
  try {
    std::vector<long> intput_ranges; //meter
    long timestamp;

    this->hokuyo.capture(intput_ranges, &timestamp);

    std::vector< quantity<length> > output_ranges;
    std::vector< quantity<plane_angle> > output_range_angles;
    
    for (unsigned int i = 0; i < intput_ranges.size(); i++) {
      output_ranges.push_back(intput_ranges[i] * meter);
      output_range_angles.push_back((this->config->scanResolution * (double)i) + this->config->scanAngleStart) ;
    }

    data.setMeasurements(output_ranges, output_range_angles);

  } catch (...) {
    error.addError("unable_to_get_data", "could not get data from the Hokuyo URG");
    return false;
  }

  return true;
  // Bouml preserved body end 0002DF71
}

bool HokuyoURG::getData(LaserScannerDataWithIntensities& data, Errors& error) {
  // Bouml preserved body begin 0002DFF1
  if (!this->open(error)) {
    return false;
  }
  try {
    std::vector<long> intput_ranges; //meter
    std::vector<long> intput_intensity; //?
    long timestamp;

  //  this->hokuyo->getScan(intput_ranges, intput_range_angles, intput_intensity);
    this->hokuyo.captureWithIntensity(intput_ranges, intput_intensity, &timestamp);

    if (intput_ranges.size() != intput_intensity.size()) {
      error.addError("unable_to_get_data", "ranges vector and intensity vector have to have the same size");
      return false;
    }
    std::vector< quantity<length> > output_ranges;
    std::vector< double > output_intensity;
    std::vector< quantity<plane_angle> > output_range_angles;


    for (unsigned int i = 0; i < intput_ranges.size(); i++) {
      output_ranges.push_back(intput_ranges[i] * meter);
      output_intensity.push_back(intput_intensity[i]);
      output_range_angles.push_back((this->config->scanResolution * (double)i) + this->config->scanAngleStart) ;
    }

    data.setMeasurements(output_ranges, output_range_angles, output_intensity);

  } catch (...) {
    error.addError("unable_to_get_data", "could not get data from the Hokuyo URG");
    return false;
  }

  return true;
  // Bouml preserved body end 0002DFF1
}

bool HokuyoURG::resetDevice() {
  // Bouml preserved body begin 0002E071
  Errors error;

  if(!this->hokuyo.reboot()){
    error.addError("unable_to_reset_hokuyo_urg", "could not reset the Hokuyo URG");
    return false;
  }
  return true;
  // Bouml preserved body end 0002E071
}

bool HokuyoURG::open(Errors& error) {
  // Bouml preserved body begin 0002E0F1
  if (this->hokuyo.isConnected()) {
    return true;
  }

  if (this->config->devicePath == "") {
    error.addError("no_DevicePath", "the device path is not specified in the configuration");
    this->isConnected = false;
    return false;
  }


  int desired_baud = 115200;

  switch (this->config->baud) {
    case BAUD_9600:
      desired_baud = 9600;
      break;
    case BAUD_19200:
      desired_baud = 19200;
      break;
    case BAUD_38400:
      desired_baud = 38400;
      break;
    case BAUD_115200:
      desired_baud = 115200;
      break;
    case BAUD_500K:
      desired_baud = 500000;
      break;
    case BAUD_UNKNOWN:
      desired_baud = 0;
      break;
  }


  try {
    this->hokuyo.connect(this->config->devicePath.c_str(), desired_baud);
    this->isConnected = true;
  } catch (...) {
    error.addError("Initialize_failed", "Initialize failed! Are you using the correct device path?");
    this->isConnected = false;
    return false;
  }
  return true;
  // Bouml preserved body end 0002E0F1
}

