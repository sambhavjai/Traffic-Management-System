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
    int red_light_time=0;
    int starvation_limit=104;
    bool starvation=false;
    // Alpha calculation
    cLongHistogram GreenLightStats;
    cLongHistogram countStats;
    long sum_count_of_car=0;
    //
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
    virtual void handleParameterChange(const char *parname) override;
    virtual void finish() override;
    void reset_para();
    void update_para(int green_light_time);
};
Define_Module(slave);
void slave::initialize()
{}
void slave::handleParameterChange(const char *parname)
{}
void slave::finish()
{
    EV<<getName()<<" "<<sum_count_of_car<<"    ";
}
void slave::reset_para()
{
    double meanOfCountofcars= 24.546;
    double stdDevofCountofcars= 15.072620342860098;
    int setCountofcars= (int)(poisson(meanOfCountofcars));
    par("count_of_cars").setIntValue(setCountofcars);
    int flag=intuniform(1,100);
    if(flag<=5)
    {
        par("emergency").setBoolValue(true);
    }
    else
        par("emergency").setBoolValue(false);
    starvation=false;
}
void slave::update_para(int green_light_time)
{
    int count=par("count_of_cars").intValue();
    int update_value=(count*green_light_time)/100;
    if(update_value>50)
        update_value=50;
    par("count_of_cars").setIntValue(count+update_value);
    int flag=intuniform(1,100);
    if(flag<=5)
    {
       par("emergency").setBoolValue(true);
    }
    else
       par("emergency").setBoolValue(false);
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
        omsg->setEmergency(par("emergency").boolValue());
        omsg->setStarvation(this->starvation);
        send(omsg,"gate$o");
    }
    else
    {
        if(strcmp(imsg->getNode(),getName())==0)
        {
            EV<<"Message received at node "<<imsg->getNode()<<"with green light time "<<imsg->getGreen_light_time();
            //Alpha calculation
            GreenLightStats.collect(imsg->getGreen_light_time());
            countStats.collect(par("count_of_cars").intValue());
            sum_count_of_car=sum_count_of_car+par("count_of_cars").intValue();
            //
            this->red_light_time=0;
            reset_para();
        }
        else
        {
            this->red_light_time=this->red_light_time+imsg->getGreen_light_time();
            if(this->red_light_time >= this->starvation_limit)
            {
                this->starvation=true;
            }
            else
                this->starvation=false;
            update_para(imsg->getGreen_light_time());
        }
    }
}
