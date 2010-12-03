#include "youbot/YouBotBase.hpp"

using namespace brics_oodl;

int main() {
   try {
      YouBotBase myYouBotBase("youbot-base");
      std::cout << "Test" << std::endl;
   } catch (std::exception& e) {
      std::cout << e.what() << std::endl;
   } catch (...) {
      std::cout << "Unhandled exception. Aborting!" << std::endl;   
   }
   return 0;
}

