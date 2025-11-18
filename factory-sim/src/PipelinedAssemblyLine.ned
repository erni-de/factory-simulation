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
module PipelinedAssemblyLine like AssemblyLine
{
    parameters:
        int N = default(0);
    gates:
        input in[N];
        output out;
    submodules:
        robot[N]: Robot;
    connections:
        for i=0..N-1 {
        	in[i] --> robot[0].instart;
        }

        for i=0..N-2 {
            robot[i].out_internal --> robot[i+1].in_internal; //connect stage[i] --> stage[i+1]
        }

        robot[N-1].outend --> out; //connect last stage to compound output
}
