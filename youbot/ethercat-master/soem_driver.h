#ifndef SOEM_DRIVER_H
#define SOEM_DRIVER_H

extern "C"{
#include <ethercattype.h>
#include <ethercatmain.h>
}

//#include <boost/shared_ptr.hpp>

namespace soem_ethercat_drivers{
  
  class SoemDriver
  {
  public:
    ~SoemDriver(){};
    template <typename MsgType>
      bool update(MsgType& data);
    const char* getName() const{
      return datap->name;
    }
    const uint16& getAddress() const{
      return datap->configadr;
    }
    ec_slavet* datap;

  protected:
    SoemDriver(ec_slavet* mem_loc)
      {
	datap = mem_loc;
      };
  };
}
#endif
