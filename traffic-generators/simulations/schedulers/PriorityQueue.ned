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

package traffic_generators.simulations.schedulers;

import traffic_generators.schedulers.PriorityQueue;
import traffic_generators.generators.RandomPriorityPacketGenerator;
import traffic_generators.generators.RandomSizePacketGenerator;
import traffic_generators.receivers.Receiver;
import traffic_generators.generators.Source;


//
// TODO auto-generated type
//
network PriorityQueue
{
    @display("bgl=3");
    submodules:
        receiver: Receiver {
            @display("p=347,126");
        }
        randomPriorityPacketGenerator1: RandomPriorityPacketGenerator {
            @display("p=38,57");
        }
        priorityQueue: PriorityQueue {
            @display("p=185,126");
        }
        randomPriorityPacketGenerator2: RandomPriorityPacketGenerator {
            @display("p=38,126");
        }
        randomPriorityPacketGenerator3: RandomPriorityPacketGenerator {
            @display("p=38,192");
        }
    connections:
        randomPriorityPacketGenerator1.out --> priorityQueue.in++;
        randomPriorityPacketGenerator2.out --> priorityQueue.in++;
        randomPriorityPacketGenerator3.out --> priorityQueue.in++;
        priorityQueue.out --> receiver.in;
}
