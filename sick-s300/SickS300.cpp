
#include "sick-s300/SickS300.h"

void SickS300::receiveScan() {
  // Bouml preserved body begin 000371F1

  std::vector<double> DistanceM;
  std::vector<double> AngleRAD;
  std::vector<double> IntensityAU;


  DistanceM.assign(541, 0);
  AngleRAD.assign(541, 0);
  IntensityAU.assign(541, 0);
  bool returnValue = false;

  {
    boost::mutex::scoped_lock lock_it(mutexSickS300);


    while (!stopThread) {
      
      returnValue = sickS300->getScan(DistanceM, AngleRAD, IntensityAU);

      if (returnValue) {
        {
          boost::mutex::scoped_lock vecLock(mutex);

          this->vdDistanceM = DistanceM;
          this->vdAngleRAD = AngleRAD;
          this->vdIntensityAU = IntensityAU;
          printf("Scan found\n");
      //    LOG(trace) << "get Scan";

        }
      }else{
      boost::this_thread::sleep(boost::posix_time::milliseconds(100));
   //   usleep(100000);
      }
    }

  }

  //   LOG( trace) << "receiving range and intensity scan from Sick S300";
  // Bouml preserved body end 000371F1
}

SickS300::SickS300() {
  // Bouml preserved body begin 00020E67

  this->sickS300 = NULL;
  this->config = NULL;
  this->isConnected = false;


  vdDistanceM.assign(541, 0);
  vdAngleRAD.assign(541, 0);
  vdIntensityAU.assign(541, 0);

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
  void *status;


  stopThread = true;

  threads.join_all();


  {
    boost::mutex::scoped_lock lock_it(mutexSickS300);
    if (sickS300 != NULL) {
      try {

        LOG(trace) << "connection to Sick S300 closed";
      } catch (...) {
        error.addError("unable_to_uninitialize", "could not uninitialize the Sick S300");
        return false;
      }
      delete sickS300;
      sickS300 = NULL;
    }
    this->isConnected = false;
  }
  return true;
  // Bouml preserved body end 00020F67
}

bool SickS300::setConfiguration(const LaserScannerConfiguration& configuration, Errors& error) {
  // Bouml preserved body begin 00020FE7
  if (this->config != NULL) {
    delete this->config;
  }
  this->config = new SickS300Configuration;
  *(this->config) = configuration;

  if (!this->open(error)) {
    return false;
  }

  //  error.addError("configuration_not_possible", "the configuration is not possible.");
  return true;
  // Bouml preserved body end 00020FE7
}

bool SickS300::setConfiguration(const SickS300Configuration& configuration, Errors& error) {
  // Bouml preserved body begin 00021067
  if (this->config != NULL) {
    delete this->config;
  }
  this->config = new SickS300Configuration;
  *(this->config) = configuration;

  if (!this->open(error)) {
    return false;
  }
  //  error.addError("configuration_not_possible", "the configuration is not possible.");
  return true;
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

    {
      boost::mutex::scoped_lock vecLock(mutex);

      data.setMeasurements(vdDistanceM, vdAngleRAD, meter, radian);

    }

  //  LOG(trace) << "receiving range scan from Sick S300";
    printf("SickS300::getData\n");
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

    {
      boost::mutex::scoped_lock vecLock(mutex);

      data.setMeasurements(vdDistanceM, vdAngleRAD, vdIntensityAU, meter, radian, meter);

    }

    
   // LOG(trace) << "receiving range and intensity scan from Sick S300";

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

  {
    boost::mutex::scoped_lock lock_it(mutexSickS300);

    if (sickS300 != NULL) {
      error.addError("still_Connected", "a previous connection was not closed correctly please close it again.");
      this->isConnected = false;
      return false;
    }

    sickS300 = new ScannerSickS300();

  }

  int desired_baud = 500000;

  switch (this->config->baud) {
    case BAUD_9600:
      desired_baud = 9600;
      LOG(trace) << "using 9600 baut to comunicate to Sick S300";
      break;
    case BAUD_19200:
      desired_baud = 19200;
      LOG(trace) << "using 19200 baut to comunicate to Sick S300";
      break;
    case BAUD_38400:
      desired_baud = 38400;
      LOG(trace) << "using 38400 baut to comunicate to Sick S300";
      break;
    case BAUD_500K:
      desired_baud = 500000;
      LOG(trace) << "using 500000 baut to comunicate to Sick S300";
      break;
    case BAUD_UNKNOWN:
      desired_baud = 0;
      break;
  }

  //Initialize the Sick S300
  try {
    {
      boost::mutex::scoped_lock lock_it(mutexSickS300);
      if (!sickS300->open(this->config->devicePath.c_str(), desired_baud)) {
        throw "could not initilize Sick S300";
      }
      this->isConnected = true;
    }
    LOG(trace) << "connection to Sick S300 initialized";

    stopThread = false;

    threads.create_thread(boost::bind(&SickS300::receiveScan, this));

  } catch (...) {
    error.addError("Initialize_failed", "could not initilize Sick S300");
    {
      boost::mutex::scoped_lock lock_it(mutexSickS300);
      this->isConnected = false;
      delete sickS300;
      sickS300 = NULL;
    }
    return false;
  }
  return true;
  // Bouml preserved body end 00021367
}

