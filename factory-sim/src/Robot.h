/*
 * Robot.h
 *
 *  Created on: Nov 18, 2025
 *      Author: erni
 */

#ifndef ROBOT_H_
#define ROBOT_H_

#include <omnetpp.h>
#include "Item_m.h"

using namespace omnetpp;
using namespace std;

/**
 * TODO - Generated class
 */
class Robot : public cSimpleModule
{
    private:
        int N;
        std::vector<double> p;
    protected:
        virtual void initialize() override;
        virtual void handleMessage(cMessage *msg) override;
        std::vector<double> getBernoulliValues(cModule *factory);
};


#endif /* ROBOT_H_ */
