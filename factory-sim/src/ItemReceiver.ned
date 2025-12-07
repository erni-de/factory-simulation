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

//Statistica per tempo di produzione di item non difettosi
//Definisco R = ProductionTime - generationTime
//(Poi ci sarà da considerare il warmup period)

simple ItemReceiver
{
    parameters:
        int N = default(0);

        @signal[itemResponseTime](type = double);
        @statistic[itemResponseTime](source = "itemResponseTime"; record = mean,vector; unit = "s");

        @signal[goodItem](type = long); //Lo useremo anche per la percentuale dei difettosi
    	@statistic[goodItem](source="goodItem"; record=count;);
    	
    	@signal[defectiveItem](type=long);	//Anche questo serve per la percentuale dei difettosi
    	@statistic[defectiveItem](source = "defectiveItem"; record = count;);
    	
   	gates:
        input in[N];
}
