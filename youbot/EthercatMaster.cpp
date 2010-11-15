/*
 * This is the Ethercat master class based on the SOEM package
 *
 * @author: Koen Buys, Ruben Smits
 *
 *
 *
 */

extern "C" {
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
#include <stdexcept>
#include <iostream>
#include "youbot/EthercatMaster.hpp"

EthercatMaster::EthercatMaster() {
}

EthercatMaster::~EthercatMaster() {
  this->close();
}

bool EthercatMaster::init(const char *ifname) {

  /* initialise SOEM, bind socket to ifname */
  if (ec_init(ifname)) {
    LOG(trace) << "Initializing EtherCAT on " << ifname;
    /* find and auto-config slaves */
    if (ec_config(TRUE, &IOmap_) > 0)
      //if( ec_config(FALSE, &IOmap_) > 0 )
      //if ( ec_config_init(FALSE) > 0 )
    {

      //ec_config_map(&IOmap_);
      //copy nr of slaves to class variable
      nr_slaves_ = ec_slavecount;
      LOG(trace) << ec_slavecount << " slaves found and configured.";

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
      ec_statecheck(0, EC_STATE_SAFE_OP, EC_TIMEOUTSTATE);
      if (ec_slave[0].state != EC_STATE_SAFE_OP) {
        LOG(info) << "Not all slaves reached safe operational state.";
        ec_readstate();
        //If not all slaves operational find out which one
        for (int i = 1; i <= ec_slavecount; i++) {
          if (ec_slave[i].state != EC_STATE_SAFE_OP) {
            LOG(info) << "Slave " << i << " State=" << ec_slave[i].state << " StatusCode=" << ec_slave[i].ALstatuscode << " : " << ec_ALstatuscode2string(ec_slave[i].ALstatuscode);

          }
        }
      }

      //Configure distributed clock
      //ec_configdc();
      //Read the state of all slaves
      //ec_readstate();

      LOG(trace) << "Request operational state for all slaves";

      ec_slave[0].state = EC_STATE_OPERATIONAL;
      // request OP state for all slaves
      /* send one valid process data to make outputs in slaves happy*/
      ec_send_processdata();
      ec_receive_processdata(EC_TIMEOUTRET);
      /* request OP state for all slaves */
      ec_writestate(0);
      // wait for all slaves to reach OP state

      ec_statecheck(0, EC_STATE_OPERATIONAL, EC_TIMEOUTSTATE);
      if (ec_slave[0].state == EC_STATE_OPERATIONAL) {
        LOG(trace) << "Operational state reached for all slaves.";
      } else {
        LOG(info) << "Not all slaves reached operational state.";
        return false;
      }
    } else {
      LOG(error) << "No slaves found!";
      return false;
    }
    return true;
  } else {
    LOG(error) << "No socket connection on " << ifname << "\nExcecute as root";
    return false;
  }
}

void EthercatMaster::close() {

  //stop SOEM, close socket
  ec_close();
}

bool EthercatMaster::send() {
  return ec_send_processdata();
}

void EthercatMaster::update() {
  if (ec_send_processdata() == 0)
    throw ExceptionOODL("Sending process data failed");
  if (ec_receive_processdata(EC_TIMEOUTRET) == 0)
    throw ExceptionOODL("Receiving data failed");
}

