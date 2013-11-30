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

#ifndef RANDOMSIZEPACKETGENERATOR_H_
#define RANDOMSIZEPACKETGENERATOR_H_


#include "Packet_m.h"
#include "Source.h"

class RandomSizePacketGenerator: public Source{
    public:
        RandomSizePacketGenerator();
        virtual ~RandomSizePacketGenerator();
    protected:
        virtual Packet* generatePacket();
        virtual void handleMessage(cMessage *msg);
        virtual void initialize();

        //Parameters
        int minPacketSize;
        int maxPacketSize;
};

#endif /* RANDOMSIZEPACKETGENERATOR_H_ */
