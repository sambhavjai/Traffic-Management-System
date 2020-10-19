#include <omnetpp.h>
#include <outgoing_m.h>
#include <incoming_m.h>

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
int fun(cObject *a,cObject *b)
{
      incoming_message *a1=(incoming_message*)a;
      incoming_message *b1=(incoming_message*)b;
      if(a1->getEmergency()==1&&b1->getEmergency()==1)
          return b1->getCount_of_cars()-a1->getCount_of_cars();
      if(a1->getEmergency()==1)
          return -1;
      else if(b1->getEmergency()==1)
          return 1;
      else
      return b1->getCount_of_cars()-a1->getCount_of_cars();
}
class master: public cSimpleModule
{
public:
    int green_light;
    void send_request();
    int (*fun_ptr)(cObject *,cObject *) = &fun;
    cQueue *q=new cQueue("queue",fun_ptr);
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
    init_message->setNode("traffic_light1");
    init_message->setGreen_light_time(10);
    init_message->setRed_light_time(0);
    this->green_light=10;
    send(init_message,"gate1$o");
    this->send_request();
}
void master::handleMessage(cMessage *msg)
{
    incoming_message *imsg = check_and_cast<incoming_message *>(msg);
    q->insert(imsg);
    EV<<"Count of "<<imsg->getCount_of_cars()<<" cars received from node "<<imsg->getNode()<<" with emergency value "<<imsg->getEmergency()<<"\n";
    if(q->getLength()==4)
    {
            incoming_message *a=(incoming_message*)q->pop();
            outgoing_message *omsg=new outgoing_message();
            omsg->setRequest(false);
            omsg->setNode(a->getNode());
            omsg->setGreen_light_time(a->getCount_of_cars());
            this->green_light=omsg->getGreen_light_time();
            send(omsg,"gate1$o");
            send(omsg->dup(),"gate2$o");
            send(omsg->dup(),"gate3$o");
            send(omsg->dup(),"gate4$o");
            q->clear();
            this->send_request();
    }
}
