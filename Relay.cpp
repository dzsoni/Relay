#include "Relay.h"


Relay::Relay(String relayid, unsigned char pin, bool initstate, bool on_state_level)
{
    _relayid = relayid;
    if(relayid=="")
    {
        _relayid = String("RELAY")+String(pin);
    }
    init(pin, initstate, on_state_level);
}

Relay::~Relay()
{
}

void Relay::On()
{
    _state=true;
    _controlRelay();
}

void Relay::Off()
{
    _state=false;
    _controlRelay();
}
//Set the state on the pin
void Relay::_controlRelay()
{
   digitalWrite(_pin,(_state) ? _onstatelevel : !_onstatelevel);
}
void Relay::setRelayState(bool newstate)
{
    _state= newstate;
    _controlRelay();
}
bool Relay::getRelayState()
{
    return _state;
}

void Relay::init(unsigned char  pin, bool initstate, bool on_state_level)
{
    _pin            = pin;
    _onstatelevel   = on_state_level;
    _initstate      = initstate;
    _state          = initstate;
    
    pinMode(_pin, OUTPUT);
    _controlRelay();
}


unsigned char Relay::getRelayPin()
{
    return _pin;
}
bool Relay::getOnStateLevel()
{
    return _onstatelevel;
}
bool Relay::getInitState()
{
    return _initstate;
}