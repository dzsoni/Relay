#ifndef  RELAY_H
#define  RELAY_H

#include <Arduino.h>
#include "SimpleJsonParser.h"
#include "Medclient.h"


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

    MedClient          mclient;

    Relay(unsigned char pin, bool initstate, bool on_state_level);
    Relay(String pathToJson, String ID_of_relay ,bool initstate, bool on_state_level);
    ~Relay();

    void init(unsigned char pin, bool initstate, bool on_state_level);
    void initMqttClientCallbacks();
    void On();
    void Off();
    void setRelayState(bool state);
    bool getRelayState();
    bool getOnStateLevel();
    bool getInitstate();
    unsigned char getRelayPin();

    void onConnect(bool sessionpresent);
    void onDisconnect(AsyncMqttClientDisconnectReason reason);
    void onSubscribe(uint16_t packetId, uint8_t qos);
    void onUnsubscribe( uint16_t packetid);
    void onMessage(char* topic, char* payload, AsyncMqttClientMessageProperties properties, size_t len, size_t index, size_t total);
    void onPublish(uint16_t packetId);
};

#endif