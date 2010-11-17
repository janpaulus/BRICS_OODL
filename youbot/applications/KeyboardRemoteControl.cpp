#include <iostream>
#include <vector>
#include <signal.h>
#include <ncurses.h>

#include "youbot/YouBot.hpp"


using namespace std;
using namespace brics_oodl;

bool running = true;

void sigintHandler(int signal) {
  running = false;
  std::cout << " Interrupt!" << std::endl;
}

int main() {

  signal(SIGINT, sigintHandler);

  try {

    YouBot& myYouBot = YouBot::getInstance();

    int ch = 0;
    double linearVel = -0.05; //meter_per_second
    double angularVel = -0.2; //radian_per_second

    JointVelocitySetpoint setVel;
    quantity<si::velocity> longitudinalVelocity = 0 * meter_per_second;
    quantity<si::velocity> transversalVelocity = 0 * meter_per_second;
    quantity<si::angular_velocity> angularVelocity = 0 * radian_per_second;
    quantity<si::length> sensedLongitudinalPos;
    quantity<si::length> sensedTransversalPos;
    quantity<si::plane_angle> sensedAngularPos;

    (void) initscr(); /* initialize the curses library */
    keypad(stdscr, TRUE); /* enable keyboard mapping */
    (void) nonl(); /* tell curses not to do NL->CR/NL on output */
    (void) cbreak(); /* take input chars one at a time, no wait for \n */
   // (void) echo(); /* echo input - in color */

    def_prog_mode();

    while (running) {

      ch = getch();

      switch (ch) {
        case KEY_DOWN:
          longitudinalVelocity = -linearVel * meter_per_second;
          transversalVelocity = 0 * meter_per_second;
          angularVelocity = 0 * radian_per_second;
          LOG(info) << "drive backward";
          printf("\r");
          break;
        case KEY_UP:
          longitudinalVelocity = linearVel * meter_per_second;
          transversalVelocity = 0 * meter_per_second;
          angularVelocity = 0 * radian_per_second;
          LOG(info) << "drive forward";
          printf("\r");
          break;
        case KEY_LEFT:
          transversalVelocity = linearVel * meter_per_second;
          longitudinalVelocity = 0 * meter_per_second;
          angularVelocity = 0 * radian_per_second;
          LOG(info) << "drive left";
          printf("\r");
          break;
        case KEY_RIGHT:
          transversalVelocity = -linearVel * meter_per_second;
          longitudinalVelocity = 0 * meter_per_second;
          angularVelocity = 0 * radian_per_second;
          LOG(info) << "drive right";
          printf("\r");
          break;
        case 'y':
          angularVelocity = -angularVel * radian_per_second;
          transversalVelocity = 0 * meter_per_second;
          longitudinalVelocity = 0 * meter_per_second;
          LOG(info) << "turn right";
          printf("\r");
          break;
        case 'x':
          angularVelocity = angularVel * radian_per_second;
          transversalVelocity = 0 * meter_per_second;
          longitudinalVelocity = 0 * meter_per_second;
          LOG(info) << "turn left";
          printf("\r");
          break;

        default:
          longitudinalVelocity = 0 * meter_per_second;
          transversalVelocity = 0 * meter_per_second;
          angularVelocity = 0 * radian_per_second;
          LOG(info) << "stop";
          printf("\r");
          break;
      }


      myYouBot.setBaseVelocity(longitudinalVelocity, transversalVelocity, angularVelocity);

      refresh();
      SLEEP_MILLISEC(100);
    }

    setVel.angularVelocity = 0 * radian_per_second;
    myYouBot.getJoint(1).setData(setVel);
    myYouBot.getJoint(2).setData(setVel);
    myYouBot.getJoint(3).setData(setVel);
    myYouBot.getJoint(4).setData(setVel);

    endwin();
    SLEEP_MILLISEC(500);

  } catch (std::exception& e) {
    std::cout << e.what() << std::endl;
  } catch (...) {
    std::cout << "unhandled exception" << std::endl;
  }

  return 0;
}