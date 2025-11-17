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
module ParallelizedAssemblyLine like AssemblyLine
{
    parameters:
        int N;
    gates:
        input in;
        output out;
    submodules:
        robot[N]: Robot;
    connections:
        // connect each submodule to compound gates
        for i=0..N-1 {
            in --> robot[i].in;
            robot[i].out --> out;
        }
}
