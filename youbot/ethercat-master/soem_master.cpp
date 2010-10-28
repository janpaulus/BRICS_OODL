/*
* This is the Ethercat master class based on the SOEM package
*
* @author: Koen Buys, Ruben Smits
*
*
*
*/

extern "C"{
#include "ethercattype.h"
#include "nicdrv.h"
#include "ethercatbase.h"
#include "ethercatmain.h"
#include "ethercatconfig.h"
#include "ethercatcoe.h"
#include "ethercatdc.h"
#include "ethercatprint.h"
}

#include <cstdio>
#include "soem_master.h"
#include "soem_driver_factory.h"
#include <stdexcept>

#include <iostream>

namespace soem_ethercat_drivers{
  
  SoemMaster::SoemMaster(){
  }
  
  SoemMaster::~SoemMaster(){
    this->close();
  }
  
  int SoemMaster::init(const char *ifname){
    
    /* initialise SOEM, bind socket to ifname */
    if (ec_init(ifname))
	{	
      printf("ec_init on %s succeeded.\n",ifname);
		/* find and auto-config slaves */
		if ( ec_config(TRUE, &IOmap_) > 0 )
		//if( ec_config(FALSE, &IOmap_) > 0 )
		//if ( ec_config_init(FALSE) > 0 )
		{
			
		//ec_config_map(&IOmap_);
		//copy nr of slaves to class variable
		nr_slaves_=ec_slavecount;
		printf("%d slaves found and configured.\n",ec_slavecount);
		
			/* wait for all slaves to reach Pre OP state */
			/*ec_statecheck(0, EC_STATE_PRE_OP,  EC_TIMEOUTSTATE);
			if (ec_slave[0].state != EC_STATE_PRE_OP )
			{
			printf("Not all slaves reached prae operational state.\n");
			ec_readstate();
			//If not all slaves operational find out which one
				for(int i = 1; i<=ec_slavecount ; i++)
				{
					if(ec_slave[i].state != EC_STATE_PRE_OP)
					{
						printf("Slave %d State=%2x StatusCode=%4x : %s\n",
						i, ec_slave[i].state, ec_slave[i].ALstatuscode, ec_ALstatuscode2string(ec_slave[i].ALstatuscode));
					}
				}
			}*/
		
		
			/* wait for all slaves to reach SAFE_OP state */
			ec_statecheck(0, EC_STATE_SAFE_OP,  EC_TIMEOUTSTATE);
			if (ec_slave[0].state != EC_STATE_SAFE_OP )
			{
			printf("Not all slaves reached safe operational state.\n");
			ec_readstate();
			//If not all slaves operational find out which one
				for(int i = 1; i<=ec_slavecount ; i++)
				{
					if(ec_slave[i].state != EC_STATE_SAFE_OP)
					{
						printf("Slave %d State=%2x StatusCode=%4x : %s\n",
						i, ec_slave[i].state, ec_slave[i].ALstatuscode, ec_ALstatuscode2string(ec_slave[i].ALstatuscode));
					}
				}
			}
			
		//Configure distributed clock
		//ec_configdc();
		//Read the state of all slaves
		//ec_readstate();
		
		printf("Request operational state for all slaves\n");
		
		ec_slave[0].state = EC_STATE_OPERATIONAL;
		// request OP state for all slaves
		/* send one valid process data to make outputs in slaves happy*/
		ec_send_processdata();
		ec_receive_processdata(EC_TIMEOUTRET);
		/* request OP state for all slaves */
		ec_writestate(0);
		// wait for all slaves to reach OP state 
		
		ec_statecheck(0, EC_STATE_OPERATIONAL,  EC_TIMEOUTSTATE);
		if (ec_slave[0].state == EC_STATE_OPERATIONAL )
			{
			printf("Operational state reached for all slaves.\n");
			}
		else{
			printf("Not all slaves reached operational state. \n");
			return false;
		}
		
		this->createDrivers();
	//Erweiterung START
	//          this->setComponentsState();
	//Erweiterung STOP
		}
		else
		{
		printf("No slaves found!\n");
		return false;
		}
      return true;
    }
    else
      {
	printf("No socket connection on %s\nExcecute as root\n",ifname);
	return false;
      }	
  }
  
  void SoemMaster::close(){   
    //delete all drivers
    for (unsigned int i=0;i<drivers_.size();i++)
      delete drivers_[i];

    //stop SOEM, close socket
    ec_close();
  }	
  
  
  bool SoemMaster::send(){
    return ec_send_processdata();
  }
  
  void SoemMaster::update(){
    if(ec_send_processdata()==0)
      throw std::runtime_error("sending process data failed");
    if(ec_receive_processdata(EC_TIMEOUTRET)==0)
      throw std::runtime_error("receiving data failed");
  }
  
  void SoemMaster::createDrivers()
  {
    for(int i=1;i<=nr_slaves_;i++){
      try{
	drivers_.push_back(SoemDriverFactory::Instance().createDriver(&ec_slave[i]));
	printf("Created driver for %s, with address %x\n",ec_slave[i].name,ec_slave[i].configadr);
      }catch(const std::exception& ex){
	printf("Could not create driver for %s: %s\n",ec_slave[i].name,ex.what());
      }
    }
  }
}//namespace soem_ethercat_drivers
