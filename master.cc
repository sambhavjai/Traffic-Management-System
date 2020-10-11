#include <omnetpp.h>
#include <outgoing_m.h>
#include <incoming_m.h>
#include <queue>

using namespace omnetpp;
using namespace std;
class outgoing_message:public Outgoing_Base
{
public:
    virtual outgoing_message *dup() const override {return new outgoing_message(*this);}
};
Register_Class(outgoing_message);
class incoming_message:public Incoming_Base
{
    virtual incoming_message *dup() const override {return new incoming_message(*this);}
};
class Compare
{
public:
    bool operator() (incoming_message* a, incoming_message* b)
    {
        return a->getCount_of_cars()-b->getCount_of_cars();
    }
};
class master: public cSimpleModule
{
public:
    int green_light;
    void send_request();
    priority_queue<incoming_message*,vector<incoming_message*>,Compare> pq;
protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
};
Define_Module(master);
void master::send_request()
{
        outgoing_message *init_request=new outgoing_message();
        init_request->setRequest(true);
        sendDelayed(init_request,this->green_light,"gate1$o");
        sendDelayed(init_request->dup(),this->green_light,"gate2$o");
        sendDelayed(init_request->dup(),this->green_light,"gate3$o");
        sendDelayed(init_request->dup(),this->green_light,"gate4$o");
}
void master::initialize()
{
    outgoing_message *init_message = new outgoing_message();
    init_message->setRequest(false);
    init_message->setNode("traffic_light_1");
    init_message->setGreen_light_time(10);
    init_message->setRed_light_time(0);
    this->green_light=10;
    send(init_message,"gate1$o");
    this->send_request();
}

void master::handleMessage(cMessage *msg)
{
    incoming_message *imsg = check_and_cast<incoming_message *>(msg);
    pq.push(imsg);
    if(pq.size()==4)
    {
        while(pq.size()>0)
        {
            incoming_message *a=pq.top();
            pq.pop();
            EV<<"Count of "<<a->getCount_of_cars()<<" cars received from node "<<a->getNode();
        }
    }
}
