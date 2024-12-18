#ifndef RELAY_H
#define RELAY_H

#include <Arduino.h>
#include "SimpleJsonParser.h"
#include "Medclient.h"


class Relay
{
    private:

    bool            _state; //logical state of the relay
    bool            _initstate;
    unsigned char   _pin;
    bool            _onstatelevel;// physical voltage level when relay is ON
    void            _controlRelay();//set the state on pin
    SimpleJsonParser  _sjsonp;

    public:

    Relay(unsigned char pin, bool initstate, bool on_state_level);
    Relay(String pathToJson, String ID_of_relay ,bool initstate, bool on_state_level);
    ~Relay();

    void init(unsigned char pin, bool initstate, bool on_state_level);
    void On();
    void Off();
    void setRelayState(bool state);
    bool getRelayState();
    bool getOnStateLevel();
    bool getInitState();
    unsigned char getRelayPin();
};

#endif /* RELAY_H */
