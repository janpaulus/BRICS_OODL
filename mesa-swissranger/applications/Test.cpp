#include <iostream>

#include "generic/Errors.hpp"
#include "generic/Units.hpp"
#include "generic/Logger.hpp"
#include "mesa-swissranger/MesaSwissRanger.hpp"
#include "generic-tof-camera/ToFCameraConfiguration.hpp"
#include "generic-tof-camera/ToFCameraData.hpp"
#include "generic-tof-camera/ToFCamera.hpp"


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