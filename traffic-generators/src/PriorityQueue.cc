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

#include "PriorityQueue.h"

Define_Module(PriorityQueue)

PriorityQueue::PriorityQueue()
{

}

PriorityQueue::~PriorityQueue()
{

}

struct PacketComparator
{
		bool operator()(Packet *left, Packet *right)
		{
			// Descending, highest priority at front of the queue, use less-than for ascending
			return (left->getPriority() > right->getPriority());
		}
} packetComparator;

void PriorityQueue::initialize()
{
	//Parameters
	priority = par("priority");
	delay = par("delay");
	capacity = par("capacity");

	//gates
	out = gate("out");

	//accumulators
	limitedQueueList = new std::list<Packet*>();

	internalDispatchingMessage = new cMessage("PriorityQueue");

}

void PriorityQueue::handleMessage(cMessage* msg)
{

	EV<< "PriorityQueue::handleMessage called for SenderModuleId " << msg->getSenderModuleId() << "\n";
	if (msg == internalDispatchingMessage)
	{

		Packet* pck = getFromQueue();

		if(pck)
		{

			cChannel* channel = out->getChannel();

			simtime_t sendPostponeTime;
			if(channel)
			{
				simtime_t channelTransmissionFinishTime = channel->getTransmissionFinishTime();

				//Calculate time when channel will be available
				sendPostponeTime = channelTransmissionFinishTime - simTime();

				simtime_t simtimePlusDelay = simTime() + delay;

				if (sendPostponeTime < simtimePlusDelay)
				{
					sendPostponeTime = simtimePlusDelay;
				}

			}
			else
			{
				sendPostponeTime = simTime() + delay;
			}

			sendDelayed(pck, sendPostponeTime, out);

			packetsSentOut++;
		}

	}
	else
	{
		Packet* pck = check_and_cast<Packet*>(msg);

		put2queue(pck);

		packetsReceivedIn++;

		if(!internalDispatchingMessage->isScheduled())
		{
			scheduleAt(simTime() + delay, internalDispatchingMessage);
		}

	}
}

void PriorityQueue::put2queue(Packet* packet)
{
	int currentCapacity = limitedQueueList->size();
	if (currentCapacity < capacity)
	{
		EV<< "PriorityQueue::put2queue: Packet accepted by queue. Used capacity = "<< currentCapacity << " of " << capacity << endl;
		limitedQueueList->push_back(packet);
		limitedQueueList->sort(packetComparator);
	}
	else
	{
		EV<< "PriorityQueue::put2queue: Packet rejected by queue. Used capacity = "<< currentCapacity << " of " << capacity << endl;
		EV<< "PriorityQueue::put2queue: Packet " << *packet << " deleted" << endl;
		delete(packet);
	}

}

Packet* PriorityQueue::getFromQueue()
{
	if (limitedQueueList->size() > 0)
	{
		Packet* packet = limitedQueueList->front();
		limitedQueueList->pop_front();
		return packet;
	}
	else
	{
		return NULL;
	}
}

void PriorityQueue::finish()
{

}

