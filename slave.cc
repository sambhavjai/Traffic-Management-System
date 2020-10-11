#include <omnetpp.h>
#include <outgoing_m.h>
#include <bits/stdc++.h>
#include <incoming_m.h>

using namespace omnetpp;

class outgoing_message:public Outgoing_Base
{
    virtual outgoing_message *dup() const override {return new outgoing_message(*this);}
};
class incoming_message:public Incoming_Base
{
    virtual incoming_message *dup() const override {return new incoming_message(*this);}
};
Register_Class(incoming_message);
class slave: public cSimpleModule
{
public:
    //int count_of_cars=5;
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
};
Define_Module(slave);
void slave::initialize()
{
}
void slave::handleMessage(cMessage *msg)
{
    outgoing_message *imsg = check_and_cast<outgoing_message *>(msg);
    if(imsg->getRequest())
    {
        EV<<"Message received at node "<<getName()<<" with request value true";
        incoming_message *omsg=new incoming_message();
        omsg->setNode(getName());
        omsg->setCount_of_cars(par("count_of_cars").intValue());
        send(omsg,"gate$o");
    }
    else
    {
        EV<<"Message received at node "<<getName()<<"with green light time"<<imsg->getGreen_light_time();
//        if(strcmp(imsg->getNode(),getName())==0)
//        {
//            int green_light=imsg->getGreen_light_time();
//        }
    }
}
