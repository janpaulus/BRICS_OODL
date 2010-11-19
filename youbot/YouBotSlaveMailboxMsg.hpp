
#ifndef _YOUBOT_SLAVE_MAILBOX_MESSAGE_H
#define	_YOUBOT_SLAVE_MAILBOX_MESSAGE_H

#include <ethercattype.h>
#include <string>
#include <time.h>

namespace brics_oodl {

    class YouBotSlaveMailboxMsg {
    public:

        struct mailboxOutputBuffer {
            uint8 moduleAddress; //0 = Drive  1 = Gripper
            uint8 commandNumber;
            uint8 typeNumber;
            uint8 motorNumber; //always zero
            uint32 value; //MSB first!
        } __attribute__((__packed__));

        struct mailboxInputBuffer {
            uint8 replyAddress;
            uint8 moduleAddress;
            uint8 status; //(e.g. 100 means “no error”)
            uint8 commandNumber;
            uint32 value; //MSB first!
        } __attribute__((__packed__));

        mailboxOutputBuffer stctOutput;
        mailboxInputBuffer stctInput;

        // Constructor

        YouBotSlaveMailboxMsg() {
            stctOutput.moduleAddress = 0;
            stctOutput.commandNumber = 0;
            stctOutput.typeNumber = 0;
            stctOutput.motorNumber = 0;
            stctOutput.value = 0;

            stctInput.replyAddress = 0;
            stctInput.moduleAddress = 0;
            stctInput.status = 0;
            stctInput.commandNumber = 0;
            stctInput.value = 0;
            slaveNumber = 1000;
        }

        // Constructor

        YouBotSlaveMailboxMsg(unsigned int slaveNo) {
            stctOutput.moduleAddress = 0;
            stctOutput.commandNumber = 0;
            stctOutput.typeNumber = 0;
            stctOutput.motorNumber = 0;
            stctOutput.value = 0;

            stctInput.replyAddress = 0;
            stctInput.moduleAddress = 0;
            stctInput.status = 0;
            stctInput.commandNumber = 0;
            stctInput.value = 0;
            slaveNumber = slaveNo;
        }



        // Copy-Constructor

        YouBotSlaveMailboxMsg(const YouBotSlaveMailboxMsg& copy) {
            stctOutput = copy.stctOutput;
            stctInput = copy.stctInput;
            slaveNumber = copy.slaveNumber;
        }

        // Destructor

        ~YouBotSlaveMailboxMsg() {
        }

        // assignment operator

        YouBotSlaveMailboxMsg & operator=(const YouBotSlaveMailboxMsg& copy) {
            stctOutput = copy.stctOutput;
            stctInput = copy.stctInput;
            slaveNumber = copy.slaveNumber;

            return *this;
        }

        unsigned int getSlaveNo() const {
            return slaveNumber;
        }
    private:
        unsigned int slaveNumber;
    };

} // namespace brics_oodl

#endif	/* _YOUBOT_SLAVE_MESSAGE_H */
