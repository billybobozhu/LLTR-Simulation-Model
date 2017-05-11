// LLTRSuperApp.cc : Defines LLTR Application.
//

#include "inet/common/INETDefs.h"
#include "inet/transportlayer/contract/udp/UDPSocket.h"

namespace inet {

class INET_API LLTRApp: public cSimpleModule
{
	UDPSocket socket;

	/*=================================================================================*/

	int numInitStages() const
	{
		return NUM_INIT_STAGES;
	}

	void initialize(int stage)
	{
		cSimpleModule::initialize(stage);

		switch(stage){
		case INITSTAGE_APPLICATION_LAYER:
			socket.setOutputGate(gate("udpOut"));
			socket.bind(1100);

			break;
		}
	}

	void handleMessage(cMessage *msg)
	{
		switch(msg->getKind()){
		case UDP_I_DATA:{
			EV << "Arrived: " << msg->getName() << endl;
			delete msg;

		}break;
		case UDP_I_ERROR:{
			EV_WARN << "Ignoring UDP error report" << endl;
			delete msg;

		}break;
		default: throw cRuntimeError("Unrecognized message (%s)%s", msg->getClassName(), msg->getName());
		}
	}

	void finish()
	{
		socket.close();

		cSimpleModule::finish();
	}

	~LLTRApp()
	{
		//TODO: write here
	}
};

Define_Module(LLTRApp);
}
