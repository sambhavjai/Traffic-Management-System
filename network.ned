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

simple master
{
    parameters:

        @display("i=abstract/multicast");
    gates:
        input gate1 @directIn;
}
simple slave
{
    parameters:
		int count_of_cars;
		bool emergency=default(false);
    gates:
        input gate @directIn;
}
channel data_flow extends ned.DelayChannel
{
    delay=100ms;
}
network traffic_management
{
    submodules:
        master: master {
            @display("p=287,198");
        }
        traffic_light1: slave {
            @display("p=42,189");
        }
        traffic_light2: slave {
            @display("p=287,38");
        }
        traffic_light3: slave {
            @display("p=558,189");
        }
        traffic_light4: slave {
            @display("p=287,353");
        }
    connections:
}


