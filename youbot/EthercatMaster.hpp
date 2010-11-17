/*
 * This is the Ethercat master class based on the SOEM package
 *
 * @author: Koen Buys, Ruben Smits, Jan Paulus
 *
 *
 *
 */
#ifndef ETHERCAT_MASTER_H
#define ETHERCAT_MASTER_H

extern "C" {
#include <ethercattype.h>
#include <ethercatmain.h>
}
#include <vector>
#include "generic/ExceptionOODL.hpp"
#include "generic/Logger.hpp"

namespace brics_oodl {

    class EthercatMaster {
        int nr_slaves_; //contains the number of found slave on the EC bus
        char IOmap_[4096];

    public:

        EthercatMaster();
        ~EthercatMaster();
        /**
         * Initialise the master and bind the socket to ifname
         *
         * @param ifname ethernet interface used to connect to ethercat slaves
         *
         * @return error code
         */
        bool init(const char *ifname);
        /**
         * send updated data from all drivers to the slaves
         *
         */
        bool send();
        /**
         * receive data from slaves and update drivers data
         *
         * @param waiting_time maximal time to wait for data
         */
        void receive();
        void update();
        void close();

    };

} // namespace brics_oodl
#endif
