/*
 * Robot.cc
 *
 *  Created on: Nov 18, 2025
 *      Author: erni
 */

#include "Robot.h"
#include "Item_m.h"

Define_Module(Robot);


void Robot::initialize(){
    cModule *assemblyLine = getParentModule();
    cModule *factory = assemblyLine->getParentModule();
    int N = factory->par("N");
    std::vector<double> p = getBernoulliValues(factory);

    //make it so we can take parameters from INI file
}

void Robot::handleMessage(cMessage *msg){
    if(msg->isSelfMessage()){
        Item *item = check_and_cast<Item*>(msg); //casts generic cMessage into Item_m
        int counterValue = item->getCounter();
        int defect = bernoulli(p[counterValue]);
        if (defect == 0){ //p = 0 means no defect is produced; process goes on
            item->increaseCounter();
            if (counterValue == N) //handle last stage
            {
                item->setProductionTime(simTime().dbl());
                send(item, "outend");
            } else {               //handle midst of process
                send(item, "out_internal");
            }
        } else {
            item->setIsDiscarded(true); //item is discarded
            send(item, "outend"); //sent directly to receiver for registration
        }
    } else {
        Item *item = check_and_cast<Item*>(msg); //casts generic cMessage into Item_m
        if (item->getCounter() == 0){
            item->setStartTime(simTime().dbl());
        }
        double t = uniform(0,1); //change it to make it parameterizable
        scheduleAt(simTime() + t, item);
    }
}

std::vector<double> Robot::getBernoulliValues(cModule *factory){ //parses p (factory parameters) that is a string into a vector of doubles
    std::vector<std::string> pStr = cStringTokenizer(factory->par("p")).asVector();
    std::vector<double> pVec;
    for (auto i : pStr) {
        pVec.push_back(std::stod(i));
    }
    return pVec;
}


