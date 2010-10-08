
#include "sick-s300/SickS300.h"
SickS300::SickS300() {
  // Bouml preserved body begin 00020E67

  this->sickS300 = NULL;
  this->config = NULL;
  this->isConnected = false;
  this->newData1 = false;
  this->newData2 = false;


  distance1.assign(numberOfScanPoints, 0);
  angle1.assign(numberOfScanPoints, 0);
  intensity1.assign(numberOfScanPoints, 0);

  distance2.assign(numberOfScanPoints, 0);
  angle2.assign(numberOfScanPoints, 0);
  intensity2.assign(numberOfScanPoints, 0);
  /*
  {
    boost::mutex::scoped_lock vecLock(mutex);
    pDistance = &distance1;
    pAngle = &angle1;
    pIntensity = &intensity1;
  }*/
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
  /*
  if (this->config != NULL) {
    delete this->config;
  }
  this->config = new SickS300Configuration;
  *(this->config) = configuration;

  if (!this->open(error)) {
    return false;
  }
  */
  error.addError("configuration_not_possible", "the configuration is not possible.");
  return false;
  // Bouml preserved body end 00020FE7
}

bool SickS300::getConfiguration(LaserScannerConfiguration& configuration, Errors& error) {
  // Bouml preserved body begin 000210E7
  if (!this->open(error)) {
    return false;
  }
  try {
    configuration.vendor = "SICK";
    configuration.product = "S300";

    configuration.scanAngleStart = -135.0/180.0*M_PI * radian;
    configuration.scanAngleStop = 135.0/180.0*M_PI * radian;
    configuration.scanResolution = ((-configuration.scanAngleStart) + configuration.scanAngleStop)/(double)numberOfScanPoints;


    LOG( trace) << "read Sick LMS configuration";

  } catch (...) {
    error.addError("unable_to_read_configuration", "could not get the configuration from the Sick S300");
    return false;
  }

  return true;
  
  // set of parameters which are specific to the SickS300
	/*

  struct ParamType
	{
		int iDataLength;	// length of data telegram
		int iHeaderLength;	// length of telegram header
		int iNumScanPoints;	// number of measurements in the scan
		double dScale;		// scaling of the scan (multiply with to get scan in meters)
		double dStartAngle;	// scan start angle
		double dStopAngle;	// scan stop angle
	};
  */

  // Bouml preserved body end 000210E7
}

bool SickS300::getData(LaserScannerData& data, Errors& error) {
  // Bouml preserved body begin 000211E7
  if (!this->open(error)) {
    return false;
  }
  try {

    if (newData1 == true) {
      {
        boost::mutex::scoped_lock dataMutex1(mutexData1);
        data.setMeasurements(distance1, angle1, si::meter, radian); //TODO dictance in centimeter
      }
      newData1 = false;

    } else if (newData2 == true) {
      {
        boost::mutex::scoped_lock dataMutex2(mutexData2);
        data.setMeasurements(distance2, angle2, meter, radian); //TODO dictance in centimeter
      }
      newData2 = false;
    } else {
      //   error.addError("unable_to_get_data", "could not get data from the Sick S300");
      return false;
    }

    //  LOG(trace) << "receiving range scan from Sick S300";
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

    if (newData1 == true) {
      {
        boost::mutex::scoped_lock dataMutex1(mutexData1);
        data.setMeasurements(distance1, angle1, intensity1, meter, radian, meter); //TODO dictance in centimeter
      }
      newData1 = false;

    } else if (newData2 == true) {
      {
        boost::mutex::scoped_lock dataMutex2(mutexData2);
        data.setMeasurements(distance2, angle2, intensity2, meter, radian, meter); //TODO dictance in centimeter
      }
      newData2 = false;
    } else {
      //  error.addError("unable_to_get_data", "could not get data from the Sick S300");
      return false;
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

void SickS300::receiveScan() {
  // Bouml preserved body begin 000371F1

  bool returnValue = false;

  {
    boost::mutex::scoped_lock lock_it(mutexSickS300);


    while (!stopThread) {

      if (newData1 == false) {
        {
          boost::mutex::scoped_lock dataMutex1(mutexData1);
          returnValue = sickS300->getScan(distance1, angle1, intensity1);
        }
        //      printf("data 1\n");
        if (returnValue) {
          newData1 = true;
          newData2 = false;
          //        printf("Scan found\n");


        }

      } else if (newData2 == false) {
        {
          boost::mutex::scoped_lock dataMutex2(mutexData2);
          returnValue = sickS300->getScan(distance2, angle2, intensity2);
        }
        //     printf("data 2\n");
        if (returnValue) {

          newData2 = true;
          newData1 = false;
          //      printf("Scan found\n");

        }
      }
      boost::this_thread::sleep(boost::posix_time::milliseconds(20));
    }
  }
  // Bouml preserved body end 000371F1
}

