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
        int index;
        int N;
        std::vector<double> p;
        const char *parentType;
        bool busy;
        cQueue msgQueue;

        //Statistica utilizzo tempo medio robot
        simsignal_t busyPeriodSignal;
        simtime_t busyStart;

    protected:
        virtual void initialize() override;
        virtual void handleMessage(cMessage *msg) override;
        std::vector<double> getBernoulliValues(cModule *factory);
        void sendHail();
        void sendHail(int index_);
        void processMessage(cMessage *msg);
};


#endif /* ROBOT_H_ */
