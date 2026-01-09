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

package factory_sim.simulations;

import factory_sim.AssemblyLine;
import factory_sim.ItemGenerator;
import factory_sim.ItemReceiver;

//
// TODO auto-generated type
//
network Factory
{
    parameters:
        int N = default(0);
        double p = default(0);
        string mode = default("parallelized");
        @display("bgb=367,332");
    submodules:
        assemblyLine: AssemblyLine{
            mode = parent.mode;
            N = parent.N;
            @display("p=151,158;is=vl");
        }
        generator: ItemGenerator{
            @display("p=266,245;is=vl");
        }
        receiver: ItemReceiver;
    connections allowunconnected:
        generator.out[0] --> assemblyLine.in[0] if mode != "parallelized";
        for i=0..N-1 {
            generator.out[i] --> assemblyLine.in[i] if mode  == "parallelized";
            assemblyLine.out[i] --> receiver.in[i];
            assemblyLine.hail_out[i] --> generator.hail_in[i];
        }

}