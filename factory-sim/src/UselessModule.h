/*
 * UselessModule.h
 *
 *  Created on: Nov 27, 2025
 *      Author: erni
 */

#ifndef USELESSMODULE_H_
#define USELESSMODULE_H_


#include <omnetpp.h>
using namespace omnetpp;


class UselessModule : public cSimpleModule
{
protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *) override;
    virtual void finish() override;

};



#endif /* USELESSMODULE_H_ */
