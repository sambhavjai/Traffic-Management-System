//
// Generated file, do not edit! Created by nedtool 5.6 from incoming.msg.
//

#ifndef __INCOMING_M_H
#define __INCOMING_M_H

#if defined(__clang__)
#  pragma clang diagnostic ignored "-Wreserved-id-macro"
#endif
#include <omnetpp.h>

// nedtool version check
#define MSGC_VERSION 0x0506
#if (MSGC_VERSION!=OMNETPP_VERSION)
#    error Version mismatch! Probably this file was generated by an earlier version of nedtool: 'make clean' should help.
#endif



/**
 * Class generated from <tt>incoming.msg:19</tt> by nedtool.
 * <pre>
 * //
 * // TODO generated message class
 * //
 * packet Incoming
 * {
 *     \@customize(true);  // see the generated C++ header for more info
 *     string node;
 *     int count_of_cars;
 * }
 * </pre>
 *
 * Incoming_Base is only useful if it gets subclassed, and Incoming is derived from it.
 * The minimum code to be written for Incoming is the following:
 *
 * <pre>
 * class Incoming : public Incoming_Base
 * {
 *   private:
 *     void copy(const Incoming& other) { ... }

 *   public:
 *     Incoming(const char *name=nullptr, short kind=0) : Incoming_Base(name,kind) {}
 *     Incoming(const Incoming& other) : Incoming_Base(other) {copy(other);}
 *     Incoming& operator=(const Incoming& other) {if (this==&other) return *this; Incoming_Base::operator=(other); copy(other); return *this;}
 *     virtual Incoming *dup() const override {return new Incoming(*this);}
 *     // ADD CODE HERE to redefine and implement pure virtual functions from Incoming_Base
 * };
 * </pre>
 *
 * The following should go into a .cc (.cpp) file:
 *
 * <pre>
 * Register_Class(Incoming)
 * </pre>
 */
class Incoming_Base : public ::omnetpp::cPacket
{
  protected:
    ::omnetpp::opp_string node;
    int count_of_cars;

  private:
    void copy(const Incoming_Base& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const Incoming_Base&);
    // make constructors protected to avoid instantiation
    Incoming_Base(const char *name=nullptr, short kind=0);
    Incoming_Base(const Incoming_Base& other);
    // make assignment operator protected to force the user override it
    Incoming_Base& operator=(const Incoming_Base& other);

  public:
    virtual ~Incoming_Base();
    virtual Incoming_Base *dup() const override {throw omnetpp::cRuntimeError("You forgot to manually add a dup() function to class Incoming");}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
    virtual const char * getNode() const;
    virtual void setNode(const char * node);
    virtual int getCount_of_cars() const;
    virtual void setCount_of_cars(int count_of_cars);
};


#endif // ifndef __INCOMING_M_H

