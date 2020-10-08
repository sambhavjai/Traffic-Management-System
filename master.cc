#include <omnetpp.h>

using namespace omnetpp;

class master: public cSimpleModule
{
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
};

Define_Module(master);

void Txc1::initialize()
{

}

void Txc1::handleMessage(cMessage *msg)
{

}
