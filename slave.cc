#include <omnetpp.h>

using namespace omnetpp;

class slave: public cSimpleModule
{
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
};
Define_Module(slave);

void slave::initialize()
{

}

void slave::handleMessage(cMessage *msg)
{
    if(msg);
}
