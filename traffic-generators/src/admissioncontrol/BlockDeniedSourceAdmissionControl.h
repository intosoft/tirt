//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

#ifndef BLOCKDENIEDSOURCEADMISSIONCONTROL_H_
#define BLOCKDENIEDSOURCEADMISSIONCONTROL_H_

#include "Packet_m.h"

/**
 * Block Denied Source Admission Control
 * @author Tomasz Obszarny
 * @date 2013
 * @copyright GNU Public License.
 */
class BlockDeniedSourceAdmissionControl : public cSimpleModule
{
	public:
		BlockDeniedSourceAdmissionControl();
		virtual ~BlockDeniedSourceAdmissionControl();

	protected:

		//Parameters
		double delay;
		std::string blockedPar;
		std::list<int>* blackList;

		//Infrastructure
		cGate* out;

		//Accumulators
		simtime_t lastPacketProcessTime;

		// Statistics
	 	int32 rejected;
	 	int32 accepted;

		int32 packetsReceivedIn;
		int32 packetsSentOut;

		cDoubleHistogram histogram;

		// Methods

		virtual void initialize();
		virtual bool accept(Packet* packet);
		virtual void handleMessage(cMessage* msg);
		virtual void finish();
		virtual void parseSources(std::string blockedSources, std::list<int>* blockedList) throw ();
		virtual bool isInTheList(int item, std::list<int>* list);
		virtual void printList(std::list<int>* list);

	private:
		simsignal_t signalAccepted;
		simsignal_t signalRejected;
};

#endif /* SIZEBASEDADMISSIONCONTROL_H_ */
