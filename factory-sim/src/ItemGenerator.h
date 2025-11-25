/*
 * ItemGenerator.h
 *
 *  Created on: Nov 18, 2025
 *      Author: erni
 */

#ifndef ITEMGENERATOR_H_
#define ITEMGENERATOR_H_

#include <omnetpp.h>
#include "Item_m.h"

using namespace omnetpp;


class ItemGenerator : public cSimpleModule
{
    protected:
        virtual void initialize() override;
        virtual void handleMessage(cMessage *msg) override;
        void sendItems();
};


#endif /* ITEMGENERATOR_H_ */
