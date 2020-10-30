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
      if(a1->getEmergency()==1 && b1->getEmergency()==1)
          return b1->getCount_of_cars() - a1->getCount_of_cars();
      if(a1->getEmergency()==1)
          return -1;
      else if(b1->getEmergency()==1)
          return 1;
      else if(a1->getStarvation()==1 && b1->getStarvation()==1)
          return b1->getCount_of_cars() - a1->getCount_of_cars();
      else if(a1->getStarvation()==1)
          return -1;
      else if(b1->getStarvation()==1)
          return 1;
      else
      return b1->getCount_of_cars()-a1->getCount_of_cars();
}
class master: public cSimpleModule
{
public:
    int green_light;
    double timeForavehicle=0.776;
    void send_request();
    int (*fun_ptr)(cObject *,cObject *) = &fun;
    cQueue *q=new cQueue("queue",fun_ptr);
    cModule *light1;
    cModule *light2;
    cModule *light3;
    cModule *light4;
protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
};
Define_Module(master);
void master::send_request()
{
        outgoing_message *init_request=new outgoing_message();
        init_request->setRequest(true);
        sendDirect(init_request,this->green_light,0,light1->gate("gate"));
        sendDirect(init_request->dup(),this->green_light,0,light2->gate("gate"));
        sendDirect(init_request->dup(),this->green_light,0,light3->gate("gate"));
        sendDirect(init_request->dup(),this->green_light,0,light4->gate("gate"));
}
void master::initialize()
{
    light1=getModuleByPath("traffic_light1");
    light2=getModuleByPath("traffic_light2");
    light3=getModuleByPath("traffic_light3");
    light4=getModuleByPath("traffic_light4");
    outgoing_message *init_message = new outgoing_message();
    init_message->setRequest(false);
    init_message->setNode("traffic_light1");
    init_message->setGreen_light_time(10);
    init_message->setRed_light_time(0);
    this->green_light=10;
    sendDirect(init_message,light1->gate("gate"));
    this->send_request();
}
void master::handleMessage(cMessage *msg)
{
    incoming_message *imsg = check_and_cast<incoming_message *>(msg);
    q->insert(imsg);
    EV<<"Count of "<<imsg->getCount_of_cars()<<" cars received from node "<<imsg->getNode()<<" with emergency value "<<imsg->getEmergency()<<" and starvation value "<<imsg->getStarvation()<<"\n";
    if(q->getLength()==4)
    {
            incoming_message *a=(incoming_message*)q->pop();
            outgoing_message *omsg=new outgoing_message();
            omsg->setRequest(false);
            omsg->setNode(a->getNode());
            omsg->setGreen_light_time((int)(a->getCount_of_cars()*this->timeForavehicle));
            this->green_light=omsg->getGreen_light_time();
            sendDirect(omsg,light1->gate("gate"));
            sendDirect(omsg->dup(),light2->gate("gate"));
            sendDirect(omsg->dup(),light3->gate("gate"));
            sendDirect(omsg->dup(),light4->gate("gate"));
            q->clear();
            this->send_request();
    }
}
