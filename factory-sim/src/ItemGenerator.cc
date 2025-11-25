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
    scheduleAt(simTime() + 0.5, new cMessage());
}

void ItemGenerator::handleMessage(cMessage *msg)
{
    if (msg->isSelfMessage()){
        sendItems();
    }
    scheduleAt(simTime() + 0.5, new cMessage());
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

