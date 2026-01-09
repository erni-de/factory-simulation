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
    cModule *factory = assemblyLine->getParentModule();
    mode = factory->par("mode").stringValue();
    EV_INFO << "Mode: " << mode << "!" <<  endl;
    N = factory->par("N");
    p = factory->par("p");
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

    cModule *assemblyLine = getParentModule();
    cModule *factory = assemblyLine->getParentModule();

    if (msg->isSelfMessage()) { //end of production stage
        Item *item = check_and_cast<Item*>(msg);
        int counterValue = item->getCounter();
        int defect = bernoulli(p);

        if (defect == 1) { //nessun difetto
            item->setCounter(item->getCounter() + 1);

            if (counterValue == N - 1) { //ultimo stage per questo item
                item->setProductionTime(simTime().dbl());

                //chiudo periodo busy
                simtime_t dur = simTime() - busyStart;
                emit(busyPeriodSignal, dur);
                busy = false;

                send(item, "outend");
                if (strcmp(mode, "parallelized") == 0)
                    sendHail();
            } else { //stage intermedio
                //chiudo periodo busy di questo stage
                simtime_t dur = simTime() - busyStart;
                emit(busyPeriodSignal, dur);
                busy = false;

                send(item, "out_internal");
                if (strcmp(mode, "pipelined") == 0 && index == 0)
                {
                    sendHail();
                }
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
            if (strcmp(mode, "parallelized") == 0 ||
                (strcmp(mode, "pipelined") == 0 && index == 0))
            {
                sendHail();
            }
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



void Robot::finish(){
    if(busy){
        simtime_t dur = simTime() - busyStart;
        emit(busyPeriodSignal, dur);
        busy = false;
    }
    while(!msgQueue.isEmpty()){
        cMessage* msg = (cMessage *)msgQueue.pop();
        delete msg;
    }
}


