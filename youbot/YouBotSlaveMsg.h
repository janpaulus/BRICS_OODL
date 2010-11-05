
#ifndef _YOUBOT_SLAVE_MESSAGE_H
#define	_YOUBOT_SLAVE_MESSAGE_H

#include <ethercattype.h>
#include <string>
#include <time.h>

class YouBotSlaveMsg {
public:
    //    struct outputbuffer; master view

    struct outputBuffer {
        int32 positionOrSpeed;
        uint8 controllerMode;
    } __attribute__ ((__packed__));

    outputBuffer stctOutput;

    //    struct inputbuffer; master view

    struct inputBuffer {
        int32 actualPosition;
        int32 actualCurrent;
        int32 actualVelocity;
        uint16 errorFlags;
        uint16 driverTemperature;
    } __attribute__ ((__packed__));
    inputBuffer stctInput;

    // Constructor

    YouBotSlaveMsg() {
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

class YouBotHeaderMsg {
public:

    //    struct outputbuffer; master view

    struct headOutputBuffer {
        uint8 cmd;
        uint32 value;
    } stctOutput;

    //    struct inputbuffer; master view

    struct headInputBuffer {
        uint32 slaveCount;
        float xPos;
        float yPos;
        float thetaPos;
    } stctInput;

    timeval timestamp;

    // Constructor

    YouBotHeaderMsg() {
    }

    // Copy-Constructor

    YouBotHeaderMsg(const YouBotHeaderMsg &copy) {
        stctOutput = copy.stctOutput;
        stctInput = copy.stctInput;
    }

    // Destructor

    ~YouBotHeaderMsg() {
    }

    // assignment operator

    YouBotHeaderMsg & operator=(const YouBotHeaderMsg &copy) {
        if (this == &copy)
            return *this;

        stctOutput = copy.stctOutput;
        stctInput = copy.stctInput;

        return *this;
    }
};


#endif	/* _YOUBOT_SLAVE_MESSAGE_H */
