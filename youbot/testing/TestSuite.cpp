#include "YouBotBaseTest.hpp"

#include <cppunit/CompilerOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/extensions/HelperMacros.h>

CPPUNIT_TEST_SUITE_REGISTRATION( YouBotBaseTest );

int main(int argc, char* argv[]) {
  CppUnit::Test *suite = CppUnit::TestFactoryRegistry::getRegistry().makeTest();
  CppUnit::TextUi::TestRunner runner;
  runner.addTest( suite );
  runner.setOutputter( new CppUnit::CompilerOutputter( &runner.result(),
                                                       std::cerr ) );
  /** let the test run */
  bool wasSucessful = runner.run();
  
  /** check whether it was sucessfull or not */
  return wasSucessful ? 0 : 1;
}


/*
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

*/

