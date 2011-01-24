#ifndef BRICS_OODL_YOUBOTJOINTSTORAGE_H
#define BRICS_OODL_YOUBOTJOINTSTORAGE_H


namespace brics_oodl {

class YouBotJointStorage {
  public:
    unsigned int encoderTicksPerRound;

    double gearRatio;

    bool inverseMovementDirection;

    int upperLimit;

    int lowerLimit;

};

} // namespace brics_oodl
#endif
