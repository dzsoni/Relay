#ifndef RELAY_H
#define RELAY_H

#include <Arduino.h>
#include "SimpleJsonParser.h"


class Relay
{
    private:

    bool            _state;
    bool            _initstate;
    unsigned char   _pin;
    bool            _onstatelevel;
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
    bool getInitstate();
    unsigned char getRelayPin();
};

#endif /* RELAY_H */
