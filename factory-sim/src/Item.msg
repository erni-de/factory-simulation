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

//
// TODO generated message class
//
packet Item {
    int counter = 0;
    bool isDiscarded = false; //Is item discarded?
    double generationTime = -1.0; //Time at which item is generated
    double arrivalTime = -1.0; //Time at which item arrives at factory (is stored in input array)
    double startTime = -1.0; //Time at which first production stage starts
    double productionTime = -1.0; //Time at which item is finished (last production stage ends)
}
