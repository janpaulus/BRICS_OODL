
#include "youbot/YouBotGripper.hpp"
namespace brics_oodl {

void YouBotGripper::setConfiguration(const OneDOFGripperConfiguration& configuration) {
  // Bouml preserved body begin 00048271
  // Bouml preserved body end 00048271
}

void YouBotGripper::getConfiguration(OneDOFGripperConfiguration& configuration) {
  // Bouml preserved body begin 000482F1
  // Bouml preserved body end 000482F1
}

void YouBotGripper::setData(const OneDOFGripperData& data) {
  // Bouml preserved body begin 00048371
  	//! To open or close the gripper
	//! input:
	//!		action: 0 = do nothing; 1 = open ; 2 = close;
	//!	return:
	//!		errorCode: 0  OK
	//!		errorCode: -1 error
  /*
	int setGripper(int action) {
		mappedMsg[9].stctOutput.positionOrSpeed = action;
		mappedMsg[9].stctOutput.controllerMode = 1;
		return 0;
	}
   * */
  // Bouml preserved body end 00048371
}

void YouBotGripper::getData(OneDOFGripperData& data) {
  // Bouml preserved body begin 000483F1
  // Bouml preserved body end 000483F1
}


} // namespace brics_oodl
