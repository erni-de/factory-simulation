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
        @display("bgb=321,384");
    gates:
        input in[N];
        output out[N];
        output hail_out[N];
    submodules:
        useless: UselessModule;
        robot[N]: Robot {
            @display("p=124,253;is=vl");
        }
    connections:
        in[0] --> robot[0].instart;
        useless.out --> robot[0].in_internal;
        robot[N-1].out_internal --> useless.in[0];
        for i=0..N-1 {
            robot[i].outend --> out[i]; //every robot can send directly to out (used to manage discarded items)
            robot[i].out_hail --> hail_out[i]; //used from robot to signal to the generator that another item can be sent
        }

        for i=0..N-2 {
            robot[i].out_internal --> robot[i+1].in_internal; //connect stage[i] --> stage[i+1]
        }

        for i=1..N-1 {
            in[i] --> useless.in[i];
            useless.out2[i - 1] --> robot[i].instart;
        }
}
