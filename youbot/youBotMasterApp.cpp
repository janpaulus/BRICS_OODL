#include <soem_master.h>
#include <cstdio>
#include <iostream>
//#include <soem_driver_factory.h>

#include <MemoryMappedFiles.h>
#include <SemaphoreLock.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

//#include "EtherCATSlaves/youBotArm.h"
//#include "EtherCATSlaves/youBotGripper.h"
//#include "EtherCATSlaves/youBotPlatform.h"

//Wenn im CMAKE der Inlcude Pfad gesetzt ist, kann man den include so angeben
//SET(locationSlaveFiles ${CMAKE_SOURCE_DIR}/EtherCATSlaves)
//include_directories(${locationSlaveFiles})
//#include <youBotArm.h>
//#include <youBotGripper.h>
//#include <youBotPlatform.h>
//#include <soem_driver.h>
#include "EtherCatSlaves/youBotSlaveComponent.h"
#include "youBotArm.h"

using namespace soem_ethercat_drivers;
using namespace std;

using namespace memmap;
using namespace semlock;

timeval last_time;

int main(int argc, char *argv[]) {

	SoemMaster master = SoemMaster();

	int semaphoreKey = 123456;

	if(argc != 1) {
		semaphoreKey = atoi(argv[1]);
	}

	char * eth = (char*) "eth0";
	
	if(argc == 3) {
		eth = argv[2];
	}

	if(master.init(eth)) {

			// the number of existing slaves
		int nrOfSlaves = master.drivers_.size();
		cout << "Master.drivers_-Grösse " << master.drivers_.size() << endl;
		cout << "Anzahl aller Slaves    " << ec_slavecount			<< endl;
		//create semaphore-objekt and a semaphore
		SemaphoreLock semLock;

		if ( semLock.createLock(semaphoreKey) < 0 ) {
			printf( "createLock failed\n");
			return 1;
		}

		//reserve memory for mapped file
		//MemmoryMappedFiles memMap(DEFAULT_DIR.c_str(), nrOfSlaves * sizeof(YouBotSlaveMsg) );
		MemmoryMappedFiles memMap("/tmp/youBotMemMapFile", sizeof(YouBotHeaderMsg) + 10*sizeof(YouBotSlaveMsg) );

		//create a msg-object-pointer and assign the address of the mapped file 
		//after that use the pointer like an array
		YouBotHeaderMsg * mappedHead = (YouBotHeaderMsg *) memMap.getAddr();
		YouBotSlaveMsg * mappedMsg = (YouBotSlaveMsg *) (memMap.getAddr() + sizeof(YouBotHeaderMsg));
		YouBotSlaveMsg msg;

		//Mailbox-Buffer
		ec_mbxbuft mbx;
//

			msg.stctOutput.positionOrSpeed = 1500;
			msg.stctOutput.controllerMode = 2 ;

		//Initialisierung von dem Arm:

		YouBotArmMsg joint[5];
		int startValue = 0;

		mappedHead->stctInput.slaveCount = 10;
///////////////////////////////////////
// Auf Null kallibrieren
///////////////////////////////////////
		for(int i = 0; i < 5; i++)
		{
//			joint[i].stctOutput.controllerMode = 4;
//			joint[i].stctOutput.positionOrSpeed = startValue;
			mappedMsg[i+4].stctOutput.controllerMode = 4;
			mappedMsg[i+4].stctOutput.positionOrSpeed = startValue;
		}

		for(int i = 0; i < 5; i++)
		{
//			((YouBotArm*)(master.drivers_[i+4]))->update(joint[i]);
			YouBotArmMsg * msg = (YouBotArmMsg*) &mappedMsg[i+4];
			((YouBotArm*)(master.drivers_[i+4]))->update(*msg);
		}

		try
		{
			master.update();
		}
		catch(const std::exception& e) {
			printf("Updating master failed: %s\n",e.what());
		}

/////////////////////////////////////////////////////////////////////////
// Auf Velocity Controll setzen, wegen Aktivierung der Sinus-Kommutierung
/////////////////////////////////////////////////////////////////////////
		for(int i = 0; i < 5; i++){
//			joint[i].stctOutput.controllerMode = 2;
//			joint[i].stctOutput.positionOrSpeed = -1;
			mappedMsg[i+4].stctOutput.controllerMode = 2;
			mappedMsg[i+4].stctOutput.positionOrSpeed = -1;
		}

		for(int i = 0; i < 1000; i++)
		{
			for(int i = 0; i < 5; i++)
			{
				YouBotArmMsg * msg = (YouBotArmMsg*) &mappedMsg[i+4];
				((YouBotArm*)(master.drivers_[i+4]))->update( *msg );
			}
			usleep(4000);
			try {
				master.update();
			}
			catch(const std::exception& e) {
				printf("Updating master failed: %s\n",e.what());
			}
		}

///////////////////////////////////////
// Auf Positionskontrolle setzen und NULLEN
///////////////////////////////////////
		for(int i = 0; i < 5; i++){
//			joint[i].stctOutput.controllerMode = 1;
//			joint[i].stctOutput.positionOrSpeed = 0;
			mappedMsg[i+4].stctOutput.controllerMode = 1;
			if ( i != 4 )
			  mappedMsg[i+4].stctOutput.positionOrSpeed = -2000;
			else
			  mappedMsg[i+4].stctOutput.positionOrSpeed = -6000;
		}

		for(int i = 0; i < 5; i++)
		{
			YouBotArmMsg * msg = (YouBotArmMsg*) &mappedMsg[i+4];
			((YouBotArm*)(master.drivers_[i+4]))->update( *msg );
		}

		for(int i = 0; i < 1000; i++)
		{
			usleep(4000);
			try {
				master.update();
			}
			catch(const std::exception& e) {
				printf("Updating master failed: %s\n",e.what());
			}
		}

//////////////////////////////////
// Greifer initialisieren.
//////////////////////////////////
		mappedMsg[9].stctOutput.positionOrSpeed = 0;
		mappedMsg[9].stctOutput.controllerMode = 0;
////Initialsierung ENDE


		// Initialize odometry
		double xPos = 0, yPos = 0, thetaPos = 0;
		uint32 wheel[4];
		for(int i=0; i<4; i++)
			wheel[i] = mappedMsg[i].stctInput.actualPosition;
		mappedHead->stctInput.thetaPos = thetaPos;
		mappedHead->stctInput.xPos = xPos;
		mappedHead->stctInput.yPos = yPos;

		// Working loop

		int counter = 1;
		while(true) 
		//for(int i = 0; i < 10000; i++)
		{
			usleep(4000);
			// first lock the memory
			// commit message-objects from the memory map to the slaves --> typecast to corresponding slave is neccessary
			// with this update method the input variable of the message-objects is set automatically with the last received data
			semLock.lock();

			for(int i = 0; i < 4; i++ ) {
				static_cast<YouBotSlaveComponent*>(master.drivers_[i])->update(mappedMsg[i]);
			}


			for(int i = 4; i < 9 ; i++)
			{
				YouBotArmMsg * msg = (YouBotArmMsg*) &mappedMsg[i];
				static_cast<YouBotArm*>(master.drivers_[i])->update( *msg );
				int pos = mappedMsg[i].stctInput.actualPosition;
			switch( i - 4 ) 
			{ 	
				case  0:	
				  if(pos < -580000 || pos > -1000) mappedMsg[i].stctOutput.controllerMode = 0;
					break; 
				case  1:	
				  if(pos < -260000 || pos > -1000) mappedMsg[i].stctOutput.controllerMode = 0;
					break; 
				case  2:	
					if(pos < -320000 || pos > -1000) mappedMsg[i].stctOutput.controllerMode = 0;
					break; 
				case  3:
					if(pos < -155000 || pos > -1000) mappedMsg[i].stctOutput.controllerMode = 0;
					break;
				case  4:
					if(pos < -255000 || pos > -5000) mappedMsg[i].stctOutput.controllerMode = 0;
					break;
			}
				//printf("Wert: %i an der Stelle: %i\n", mappedMsg[i].stctOutput.controllerMode, i );
			}
			
			mappedHead->timestamp = last_time;
				
			if(mappedMsg[9].stctOutput.controllerMode == 1)
			{
				mbx[0] = 1;
				mbx[1] = 4;
				mbx[2] = 1;
				mbx[3] = 0;

				if(mappedMsg[9].stctOutput.positionOrSpeed == 1)
				{
					mbx[4] = (char) -1;
					mbx[5] = (char) -1;
					mbx[6] = (char) -255;
					mbx[7] = (char) -255;
				}

				if(mappedMsg[9].stctOutput.positionOrSpeed == 2)
				{
					mbx[4] = (char) 0;
					mbx[5] = (char) 0;
					mbx[6] = (char) 255;
					mbx[7] = (char) 255;
				}

				ec_mbxsend(11, &mbx, 4000);

				mappedMsg[9].stctOutput.positionOrSpeed = 0;
				mappedMsg[9].stctOutput.controllerMode  = 0;

			}


			// update odometry
			int tickDelta[4];
			for(int i=0; i<4; i++) {
				tickDelta[i] = mappedMsg[i].stctInput.actualPosition - wheel[i];
				wheel[i] = mappedMsg[i].stctInput.actualPosition;
			}

//			setMotorPositionOrSpeed(0, (int)(-forwardTicks - rightTicks + yawTicks));
//			setMotorPositionOrSpeed(1, (int)(forwardTicks - rightTicks + yawTicks));
//			setMotorPositionOrSpeed(2, (int)(-forwardTicks + rightTicks + yawTicks));
//			setMotorPositionOrSpeed(3, (int)(forwardTicks + rightTicks + yawTicks));

			double forwardTicksPerM = 330000,
					sidewardsTicksPerM = 346000,
					rotationTicksPerRad = 805000 / 2 / 3.14159265;
			double xDelta = (tickDelta[3]-tickDelta[2])/ 2 / forwardTicksPerM,
					yDelta = (tickDelta[3]- tickDelta[1]) / 2 / sidewardsTicksPerM,
					thetaDelta = (tickDelta[3] + tickDelta[0]) / 2 / rotationTicksPerRad;
			xPos += xDelta * cos(thetaPos) + yDelta * sin(thetaPos);
			yPos += xDelta * -sin(thetaPos) + yDelta * cos(thetaPos);
			thetaPos += thetaDelta;
			mappedHead->stctInput.xPos = xPos;
			mappedHead->stctInput.yPos = yPos;
			mappedHead->stctInput.thetaPos = thetaPos;

			semLock.unlock();
			cout<<xDelta << " / " << yDelta << " / " << thetaDelta << endl;
			// now send output data to slaves; new input data will be received at the same time
			try {
				master.update();
				gettimeofday(&last_time, NULL);
			}
			catch(const std::exception& e) {
				printf("Updating master failed: %s\n",e.what());
			}


			//some inputs
			cout << "--------------------------------" << endl;
			cout << "Base 1 Position :" << mappedMsg[0].stctInput.actualPosition		<< endl;
			cout << "Base 2 Position :" << mappedMsg[1].stctInput.actualPosition		<< endl;
			cout << "Base 3 Position :" << mappedMsg[2].stctInput.actualPosition		<< endl;
			cout << "Base 4 Position :" << mappedMsg[3].stctInput.actualPosition		<< endl;
			cout << "Arm 0 Position :" << mappedMsg[4].stctInput.actualPosition		<< endl;
			cout << "Arm 1 Position :" << mappedMsg[5].stctInput.actualPosition		<< endl;
			cout << "Arm 2 Position :" << mappedMsg[6].stctInput.actualPosition		<< endl;
			cout << "Arm 3 Position :" << mappedMsg[7].stctInput.actualPosition		<< endl;
			cout << "Arm 4 Position :" << mappedMsg[8].stctInput.actualPosition		<< endl;
			
		}
	}

	return 0;
}
