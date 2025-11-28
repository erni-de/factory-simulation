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

}

void ItemReceiver::finish() {
    if (csvFile.is_open()) {
        csvFile.close();
        EV_INFO << "CSV file closed.\n";
    }
}

