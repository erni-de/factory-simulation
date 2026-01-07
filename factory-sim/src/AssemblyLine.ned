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

package factory_sim;

//
// TODO auto-generated type
//
module AssemblyLine
{
    parameters:
        int N = default(0);
        string mode = default("parallelized");
    gates:
        input in[N];
        output out[N];
        output hail_out[N];
   	submodules:
   	    robot[N]: Robot;
   	connections allowunconnected:
   	    in[0] --> robot[0].instart if mode != "parallelized";
   	    for i=0..N-1 {
   	        robot[i].out_hail --> hail_out[i];
        	in[i] --> robot[i].instart if mode =="parallelized";
            robot[i].outend --> out[i];
            robot[i].out_internal --> robot[i].in_internal if mode == "parallelized";
		}
		
		for i=0..N-2 {
			robot[i].out_internal --> robot[i+1].in_internal if mode != "parallelized";
		}
}
