#include "Relay.h"


Relay::Relay(unsigned char  pin, bool initstate, bool on_state_level)
{
    init( pin,  initstate,  on_state_level);
}

Relay::Relay(String pathToJson , String ID_of_relay , bool initstate, bool on_state_level)
{
    if(_sjsonp.getJSONValueByKeyFromFile(pathToJson, ID_of_relay)=="")
    {
        Serial.println(F("Relay init not succesful. No such relay ID."));
        return;
    }
    init( _sjsonp.getJSONValueByKeyFromFile(pathToJson, ID_of_relay).toInt(), initstate,  on_state_level);
}

Relay::~Relay()
{
}

void Relay::On()
{
    _state=_onstatelevel;
    _controlRelay();
    Serial.println("RELAY IS ON");
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
    _state          = initstate;
    _initstate      = initstate;
    _onstatelevel   = on_state_level;
    pinMode(_pin, OUTPUT);
    _controlRelay();
}
void Relay::initMqttClientCallbacks()
{
    //mclient.setOnConnect([this](bool sessionpresent){this->onConnect(sessionpresent);});
    //mclient.setOnDisconnect([this](AsyncMqttClientDisconnectReason reason){this->onDisconnect(reason);});
    mclient.setOnSubscribe([this](uint16_t packetId, uint8_t qos){this->onSubscribe(packetId,qos);});
    mclient.setOnUnsubscribe([this](uint16_t packetid){this->onUnsubscribe(packetid);});
    mclient.setOnMessage([this](char* topic, char* payload, AsyncMqttClientMessageProperties properties, size_t len, size_t index, size_t total){this->onMessage(topic,payload,properties,len,index,total);});
    mclient.setOnPublish([this](uint16_t packetId){this->onPublish(packetId);});
}

unsigned char Relay::getRelayPin()
{
    return _pin;
}
bool Relay::getOnStateLevel()
{
    return _onstatelevel;
}
bool Relay::getInitstate()
{
    return _initstate;
}

//MQTT CALLBACKS
void Relay::onConnect(bool sessionpresent)
{
Serial.println("RELAY ONCONNECT.");
}
void Relay::onDisconnect(AsyncMqttClientDisconnectReason reason)
{
Serial.println("RELAY ONDISCONNECT");
}
void Relay::onSubscribe( uint16_t packetId, uint8_t qos)
{
Serial.println("RELAY SUBSCRIBE");
Serial.println("Subscribe acknowledged.");
Serial.print("  packetId: ");
Serial.println(packetId);
Serial.print("  qos: ");
Serial.println(qos);
}
void Relay::onUnsubscribe(uint16_t packetid)
{
Serial.println("RELAY ONUNSUBSCRIBE");
}
void Relay::onMessage(char* topic, char* payload, AsyncMqttClientMessageProperties properties, size_t len, size_t index, size_t total)
{
Serial.println("RELAY ONMESSAGE");
 Serial.println("Publish received.");
  Serial.print("  topic: ");
  Serial.print(topic);
  Serial.print("  qos: ");
  Serial.print(properties.qos);
  Serial.print("  dup: ");
  Serial.print(properties.dup);
  Serial.print("  retain: ");
  Serial.print(properties.retain);
  Serial.print("  len: ");
  Serial.print(len);
  Serial.print("  index: ");
  Serial.print(index);
  Serial.print("  total: ");
  Serial.print(total);
  Serial.println("");
}
void Relay::onPublish(uint16_t packetId)
{
Serial.println("RELAY ONPUBLISH");
}