/*
 * Robot.cc
 *
 *  Created on: Nov 18, 2025
 *      Author: erni
 */

#include "Robot.h"
#include "Item_m.h"
#include <omnetpp.h>

using namespace omnetpp;

Define_Module(Robot);


void Robot::initialize(){
    index = getIndex();
    cModule *assemblyLine = getParentModule();
    parentType = assemblyLine->getNedTypeName();
    cModule *factory = assemblyLine->getParentModule();
    EV_INFO << "Parent module type: " << parentType << endl;
    N = factory->par("N");
    p = getBernoulliValues(factory);
    busy = false;


    //make it so we can take parameters from INI file
}

void Robot::handleMessage(cMessage *msg){
    if (msg->isSelfMessage()){
        if (busy == true){
            processMessage(msg);
            if (!msgQueue.isEmpty()){
                busy = true;
                processMessage((cMessage *)msgQueue.pop());
            }
        }
    } else {
        if (busy == false){
            busy = true;
            processMessage(msg);
        } else {
            msgQueue.insert(msg);
        }
    }
}


void Robot::sendHail(){
    EV_INFO << "Robot " << index << " sent hail" << endl;

    cMessage *hail = new cMessage("hail");
    hail->addPar("index") = index;
    send(hail, "out_hail");
}

void Robot::sendHail(int index_){
    EV_INFO << "Robot " << index_ << " sent hail" << endl;

    cMessage *hail = new cMessage("hail");
    hail->addPar("index") = index_;
    send(hail, "out_hail");
}

void Robot::processMessage(cMessage *msg){
    if(msg->isSelfMessage()){ //end of procudtion stage
            Item *item = check_and_cast<Item*>(msg); //casts generic cMessage into Item_m
            int counterValue = item->getCounter();
            int defect = bernoulli(p[counterValue]);
            if (defect == 1){ //p = 1 means no defect is produced; process goes on
                item->increaseCounter();
                if (counterValue == N - 1) //handles end of last production stage
                {
                    item->setProductionTime(simTime().dbl());
                    busy = false;
                    send(item, "outend");
                    if (strcmp(parentType, "factory_sim.PipelinedAssemblyLine") == 0){
                        sendHail(0);
                    } else {
                        sendHail();
                    }
                } else {               //handle midst of process
                    busy = false;
                    send(item, "out_internal");
                    if (strcmp(parentType, "factory_sim.PipelinedAssemblyLine") == 0 && index == 0){
                        sendHail();
                    }
                }
            } else {
                item->setIsDiscarded(true); //item is discarded
                item->setDiscardTime(simTime().dbl());
                busy = false;
                send(item, "outend"); //sent directly to receiver for registration
                if (!(strcmp(parentType, "factory_sim.PipelinedAssemblyLine") == 0 && index != 0)){
                    sendHail();
                }
            }
        } else { //begin of production stage
                Item *item = check_and_cast<Item*>(msg); //casts generic cMessage into Item_m
                if (item->getCounter() == 0){
                    item->setStartTime(simTime().dbl());
                }
                double t = uniform(0,1); //change it to make it parameterizable
                scheduleAt(simTime() + t, item); //models production time}
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


