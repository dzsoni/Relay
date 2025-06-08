#ifndef RELAY_H
#define RELAY_H


#include <Arduino.h>
#include <WString.h>

#ifdef DEBUG_RELAY
#define _RELAYARRAY_PP(a) Serial.print(a);
#define _RELAYARRAY_PL(a) Serial.println(a);
#else
#define _RELAY_PP(a)
#define _RELAY_PL(a)
#endif


class Relay
{
    private:

    String          _relayid;     //ID of the relay
    bool            _state;       //logical state of the relay
    bool            _initstate;   //initial state of the relay
    unsigned char   _pin;         //GPIO pin number of the relay
    bool            _onstatelevel;// physical voltage level when relay is on state (HIGH or LOW,0V or 5V,3.3V stb)
    void            _controlRelay();//set the state on pin

    public:

    
    Relay(String relayid, unsigned char pin, bool initstate, bool on_state_level);
    ~Relay();

    void init(unsigned char pin, bool initstate, bool on_state_level);
    void On();
    void Off();
    void setRelayState(bool state);
    bool getRelayState();
    bool getOnStateLevel();
    bool getInitState();
    
    bool changeId(String newid) { _relayid = newid; return true; };
    String getId() { return _relayid; };

    unsigned char getRelayPin();
};

#endif /* RELAY_H */
