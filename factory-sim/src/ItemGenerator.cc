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
        cModule *factory = getParentModule();
        const char* mode = factory->par("mode").stringValue();
        item->setGenerationTime(simTime().dbl());
        if(strcmp(mode, "parallelized") == 0)
            send(item, "out", msg->par("index").longValue());
        else
            send(item, "out",0);

    }

    delete msg;
}


void ItemGenerator::sendItems()
{
    cModule *factory = getParentModule();
    const char* mode = factory->par("mode").stringValue();
    int N = factory->par("N");
    if(strcmp(mode, "parallelized") == 0)
        for (int i = 0; i < N; i++){
            Item *item = new Item();
            item->setGenerationTime(simTime().dbl());
            send(item, "out", i);
        }
    else{
        Item *item = new Item();
        item->setGenerationTime(simTime().dbl());
        send(item, "out", 0);
    }

}


