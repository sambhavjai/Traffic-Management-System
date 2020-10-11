#include <omnetpp.h>
#include <outgoing_m.h>

using namespace omnetpp;

class outgoing_message:public Outgoing_Base
{
    virtual outgoing_message *dup() const override {return new outgoing_message(*this);}
};
class slave: public cSimpleModule
{
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
    //void handleMessage(outgoing_message *msg);
};
Define_Module(slave);

void slave::initialize()
{

}
void slave::handleMessage(cMessage *msg)
{
    outgoing_message *ttmsg = check_and_cast<outgoing_message *>(msg);
    EV<<"Message recieved with node id "<<ttmsg->getNode_id()<<"and green light time"<<ttmsg->getGreen_light_time();
}
