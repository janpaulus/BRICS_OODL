
#ifndef _YOUBOT_SLAVE_MESSAGE_H
#define	_YOUBOT_SLAVE_MESSAGE_H

#include <ethercattype.h>
#include <string>
#include <time.h>

struct outputBuffer {
    int32 positionOrSpeed;
    uint8 controllerMode;
} __attribute__((__packed__));

//    struct inputbuffer; master view

struct inputBuffer {
    int32 actualPosition;
    int32 actualCurrent;
    int32 actualVelocity;
    uint16 errorFlags;
    uint16 driverTemperature;
} __attribute__((__packed__));


class YouBotSlaveMsg {
public:
    //    struct outputbuffer; master view

    outputBuffer stctOutput;
    inputBuffer stctInput;
    // Constructor

    YouBotSlaveMsg() {
        stctOutput.controllerMode = 0;
        stctOutput.positionOrSpeed = 0;
        stctInput.actualCurrent = 0;
        stctInput.actualPosition = 0;
        stctInput.actualVelocity = 0;
        stctInput.driverTemperature = 0;
        stctInput.errorFlags = 0;
    }

    // Copy-Constructor

    YouBotSlaveMsg(const YouBotSlaveMsg &copy) {
        stctOutput = copy.stctOutput;
        stctInput = copy.stctInput;
    }

    // Destructor

    ~YouBotSlaveMsg() {
    }

    // assignment operator

    YouBotSlaveMsg & operator=(const YouBotSlaveMsg &copy) {
        if (this == &copy)
            return *this;

        stctOutput = copy.stctOutput;
        stctInput = copy.stctInput;

        return *this;
    }
};



#endif	/* _YOUBOT_SLAVE_MESSAGE_H */
