/*
 * ItemGenerator.cc
 *
 *  Created on: Nov 18, 2025
 *      Author: erni
 */


#include "ItemGenerator.h"
#include "Item_m.h"
#include <omnetpp.h>

using namespace omnetpp;

Define_Module(ItemGenerator);

void ItemGenerator::initialize()
{
    sendItems();
}

void ItemGenerator::handleMessage(cMessage *msg)
{
    if (strcmp(msg->getName(), "hail") == 0){
        Item *item = new Item();
        item->setGenerationTime(simTime().dbl());
        send(item, "out", msg->par("index").longValue());
    }
}


void ItemGenerator::sendItems()
{
    cModule *factory = getParentModule();
    int N = factory->par("N");
    for (int i = 0; i < N; i++){
            Item *item = new Item();
            item->setGenerationTime(simTime().dbl());
            send(item, "out", i);
        }
}

