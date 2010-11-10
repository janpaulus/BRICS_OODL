
#ifndef _YOUBOT_SLAVE_MAILBOX_MESSAGE_H
#define	_YOUBOT_SLAVE_MAILBOX_MESSAGE_H

#include <ethercattype.h>
#include <string>
#include <time.h>

struct mailboxOutputBuffer {
    uint8 moduleAddress; //0 = Drive  1 = Gripper
    uint8 commandNumber;
    uint8 typeNumber;
    uint8 motorNumber; //always zero
    int32 value; //MSB first!
} __attribute__((__packed__));

//    struct inputbuffer; master view

struct mailboxInputBuffer {
    uint8 replyAddress;
    uint8 moduleAddress;
    uint8 status; //(e.g. 100 means “no error”)
    uint8 commandNumber;
    int32 value; //MSB first!
} __attribute__((__packed__));

class YouBotSlaveMailboxMsg {
public:
    //    struct outputbuffer; master view

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
    }

    // Copy-Constructor

    YouBotSlaveMailboxMsg(const YouBotSlaveMailboxMsg &copy) {
        stctOutput = copy.stctOutput;
        stctInput = copy.stctInput;
    }

    // Destructor

    ~YouBotSlaveMailboxMsg() {
    }

    // assignment operator

    YouBotSlaveMailboxMsg & operator=(const YouBotSlaveMailboxMsg &copy) {
        if (this == &copy)
            return *this;

        stctOutput = copy.stctOutput;
        stctInput = copy.stctInput;

        return *this;
    }
};


#endif	/* _YOUBOT_SLAVE_MESSAGE_H */
