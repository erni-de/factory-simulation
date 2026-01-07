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

    //registro i segnali
    busyPeriodSignal = registerSignal("busyPeriod");
    busyStart = SIMTIME_ZERO;
}

void Robot::handleMessage(cMessage *msg){
    if (msg->isSelfMessage()) {
        if (busy == true) {
            //fine di un periodo di servizio (vedi processMessage)
            processMessage(msg);

            //se c'è qualcosa in coda, parte subito un nuovo periodo busy
            if (!msgQueue.isEmpty()) {
                busy = true;
                busyStart = simTime();
                processMessage((cMessage *)msgQueue.pop());
            }
        }
    } else {

        Item *item = check_and_cast<Item*>(msg);
        //Salvo il tempo di arrivo a questo robot
        item->setTimestamp(simTime());

        if (busy == false) {
            busy = true;
            busyStart = simTime();   //inizio periodo busy
            processMessage(msg);
        } else {
            msgQueue.insert(msg);    //va in coda locale del robot
        }
    }
}

void Robot::sendHail(){
    EV_INFO << "Robot " << index << " sent hail" << endl;

    cMessage *hail = new cMessage("hail");
    hail->addPar("index") = index;
    send(hail, "out_hail");
}



void Robot::processMessage(cMessage *msg){
    if (msg->isSelfMessage()) { //end of production stage
        Item *item = check_and_cast<Item*>(msg);
        int counterValue = item->getCounter();
        int defect = bernoulli(p[counterValue]);

        if (defect == 1) { //nessun difetto
            item->setCounter(item->getCounter() + 1);

            if (counterValue == N - 1) { //ultimo stage per questo item
                item->setProductionTime(simTime().dbl());

                //chiudo periodo busy
                simtime_t dur = simTime() - busyStart;
                emit(busyPeriodSignal, dur);
                busy = false;

                send(item, "outend");
                sendHail();
            } else { //stage intermedio
                //chiudo periodo busy di questo stage
                simtime_t dur = simTime() - busyStart;
                emit(busyPeriodSignal, dur);
                busy = false;

                send(item, "out_internal");
                sendHail();
            }
        }
        else { //difettoso
            item->setIsDiscarded(true);
            item->setDiscardTime(simTime().dbl());

            //anche qui chiudo un periodo busy
            simtime_t dur = simTime() - busyStart;
            emit(busyPeriodSignal, dur);
            busy = false;

            send(item, "outend");
            sendHail();
        }
    }
    else { //begin of production stage
        Item *item = check_and_cast<Item*>(msg);

        simtime_t w = simTime() - item->getTimestamp();
        double newTotalW = item->getTotalWaitingTime() + w.dbl();
        item->setTotalWaitingTime(newTotalW);

        if (item->getCounter() == 0) {
            item->setStartTime(simTime().dbl());
        }

        double t = uniform(0,1);
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


