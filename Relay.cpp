#include "Relay.h"


Relay::Relay(unsigned char  pin, bool initstate, bool on_state_level)
{
    init( pin,  initstate,  on_state_level);
}

Relay::Relay(String pathToJson , String ID_of_relay , bool initstate, bool on_state_level)
{
    if(_sjsonp.getValueByKeyFromFile(pathToJson, ID_of_relay)=="")
    {
        Serial.println(F("Relay init not succesful. No such relay ID."));
        return;
    }
    init( _sjsonp.getValueByKeyFromFile(pathToJson, ID_of_relay).toInt(), initstate,  on_state_level);
}

Relay::~Relay()
{
}

void Relay::On()
{
    _state=_onstatelevel;
    _controlRelay();
}

void Relay::Off()
{
    _state=!_onstatelevel;
    _controlRelay();
}
//Set the state on the pin
void Relay::_controlRelay()
{
   digitalWrite(_pin,_state);
}
void Relay::setRelayState(bool state)
{
    if(state){_state=_onstatelevel;}
    else{_state=!_onstatelevel;}
    _controlRelay();
}
bool Relay::getRelayState()
{
    if(_onstatelevel==_state) return 1;
    return 0;
}
void Relay::init(unsigned char  pin, bool initstate, bool on_state_level)
{
    _pin            = pin;
    _onstatelevel   = on_state_level;
    _initstate      = (initstate==on_state_level)?on_state_level:!on_state_level;
    _state          = _initstate;
    
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