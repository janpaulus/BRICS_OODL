#include <iostream>

#include "generic/Errors.h"
#include "generic/Units.h"
#include "generic/Logger.h"
#include "mesa-swissranger/MesaSwissRanger.h"
#include "generic-tof-camera/ToFCameraConfiguration.h"
#include "generic-tof-camera/ToFCameraData.h"
#include "generic-tof-camera/ToFCamera.h"


using namespace std;




int main(){

  // Initialize logging to std::cout
  logging::init_log_to_console(std::cout);
  // Initialize logging to the "test.log" file
  logging::init_log_to_file("log.txt");

  MesaSwissRanger mesa;
  Errors error;

  ToFCameraConfiguration config;
  ToFCameraData data;
  mesa.getConfiguration(config, error);
  mesa.setConfiguration(config, error);
 // mesa.getData(data, error);

  return 0;
}