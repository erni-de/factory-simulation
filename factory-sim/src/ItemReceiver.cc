/*
 * ItemReceiver.cc
 *
 *  Created on: Nov 18, 2025
 *      Author: erni
 */

#include <fstream>
#include "ItemReceiver.h"
#include "Item_m.h"
#include <iomanip>

Define_Module(ItemReceiver);

std::ofstream csvFile;

void ItemReceiver::initialize(){

    cModule *factory = getParentModule();

    mode = factory->par("mode").stringValue();
    N = factory->par("N");
    p = factory->par("p");


    //Registro i segnali per le statistiche
    responseTimeSignal   = registerSignal("itemResponseTime");
    goodItemSignal       = registerSignal("goodItem");
    defectiveItemSignal  = registerSignal("defectiveItem");
    waitingTimeSignal    = registerSignal("itemWaitingTime");
    completedItemSignal  = registerSignal("completedItem");
    defectiveLifetimeSignal = registerSignal("defectiveLifetime");

    frequency_histogram.setName("Stages Passed");
    frequency_histogram.setRange(0,(int)par("N")+1);
    frequency_histogram.setNumBinsHint((int)par("N") + 1);
    frequency_histogram.setMode(cHistogram::MODE_INTEGERS);



    csvFile.open("output.csv", std::ios::app);
    csvFile << std::setprecision(15) << std::fixed;

    if (!csvFile.is_open()) {
        EV_INFO << "Error opening CSV file!\n";
    } else {
        EV_INFO << "CSV file opened successfully.\n";
        csvFile << "counter,discarded,gen_time,arrival_time,discard_time,prod_time,mode,N,p\n";
    }
}

void ItemReceiver::handleMessage(cMessage *msg){
    Item *item = check_and_cast<Item*>(msg);

    //Ogni item che arriva qui è completato
    emit(completedItemSignal, 1);
    frequency_histogram.collect(item->getCounter());

    if (!item->isDiscarded()) {
        simtime_t rt = item->getProductionTime() - item->getGenerationTime();

        //NB --> Le statistiche le ho fatte per gli item buoni
        //Se vogliamo considerare tutti basta spostare le emit fuori dall'if
        emit(responseTimeSignal, rt);   //tempo di produzione item buoni
        emit(goodItemSignal, 1);        //conta buoni
        emit(waitingTimeSignal, item->getTotalWaitingTime()); //Tempo totale in coda

    } else {
        simtime_t life = item->getDiscardTime() - item->getGenerationTime();
        emit(defectiveLifetimeSignal, life); //Salvo il tempo per capire quanto ci metto a scartarlo
        emit(defectiveItemSignal, 1);   //conta difettosi
    }

    EV_INFO << "Item arrived!";
    csvFile << item->getCounter() << ","
            << item->isDiscarded() << ","
            << item->getGenerationTime() << ","
            << item->getStartTime() << ","
            << item->getDiscardTime() << ","
            << item->getProductionTime() << ","
            << mode << ","
            << N << ","
            << p << "\n";

    //Dealloco non avrà più owner
    delete item;
}



void ItemReceiver::finish() {
    if (csvFile.is_open()) {
        csvFile.close();
        EV_INFO << "CSV file closed.\n";
    }
    recordStatistic(&frequency_histogram);
}

