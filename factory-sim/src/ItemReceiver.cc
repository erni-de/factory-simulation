/*
 * ItemReceiver.cc
 *
 *  Created on: Nov 18, 2025
 *      Author: erni
 */

#include <fstream>
#include "ItemReceiver.h"
#include "Item_m.h"


Define_Module(ItemReceiver);

std::ofstream csvFile;

void ItemReceiver::initialize(){

    //Registro i segnali per le statistiche
    responseTimeSignal = registerSignal("itemResponseTime");
    goodItemSignal = registerSignal("goodItem");
    defectiveItemSignal = registerSignal("defectiveItem");

    csvFile.open("output.csv", std::ios::out);
    if (!csvFile.is_open()) {
            EV_INFO << "Error opening CSV file!\n";
        } else {
            EV_INFO << "CSV file opened successfully.\n";
            csvFile << "counter,discarded,gen_time,arrival_time,discard_time,prod_time\n";  // CSV header
    }
}

void ItemReceiver::handleMessage(cMessage *msg){
    Item *item = check_and_cast<Item*>(msg); //casts generic cMessage into Item_m
    EV_INFO << "Item arrived!";
        // Write data
    csvFile << item->getCounter() << "," << item->isDiscarded() << "," << item->getGenerationTime() << "," << item->getStartTime() << ","  << item->getDiscardTime()  << ","  << item->getProductionTime() << "\n";

    //Aggiungo la roba delle statistiche

    //L'item è buono salvo responseTime
    if(!item->isDiscarde()){
        simtime_t rt = item->getProductionTime() - item->getGenerationTime();
        emit(responseTimeSignal, rt);

        //Casto perché l'ho salvato come long
        emit(goodItemSignal, (long)1);

    }else{

        //Conta item difettosi
        emit(defectiveItemSignal, (long)1);

    }
}

void ItemReceiver::finish() {
    if (csvFile.is_open()) {
        csvFile.close();
        EV_INFO << "CSV file closed.\n";
    }
}

