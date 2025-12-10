/*
 * ItemReceiver.h
 *
 *  Created on: Nov 18, 2025
 *      Author: erni
 */

#ifndef ITEMRECEIVER_H_
#define ITEMRECEIVER_H_


#include <omnetpp.h>
#include "Item_m.h"

using namespace omnetpp;


class ItemReceiver : public cSimpleModule
{
protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *) override;
    virtual void finish() override;

private:
    simsignal_t responseTimeSignal;
    simsignal_t goodItemSignal;
    simsignal_t defectiveItemSignal;
    simsignal_t waitingTimeSignal;
    simsignal_t completedItemSignal;
    simsignal_t defectiveLifetimeSignal;
};


#endif /* ITEMRECEIVER_H_ */
