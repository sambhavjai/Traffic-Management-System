#include <omnetpp.h>
#include <outgoing_m.h>

using namespace omnetpp;
class outgoing_message:public Outgoing_Base
{
    virtual outgoing_message *dup() const override {return new outgoing_message(*this);}
};
Register_Class(outgoing_message);
class master: public cSimpleModule
{
protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
};
Define_Module(master);
void master::initialize()
{
    outgoing_message *init_message = new outgoing_message();
    init_message->setNode_id(1);
    init_message->setGreen_light_time(10);
   // EV<<"Sending initial message to gate "<<init_message->getNode_id()<<"with green light time "<<init_message->getGreen_light_time();
    send(init_message,"gate1$o");
}
void master::handleMessage(cMessage *msg)
{

}
