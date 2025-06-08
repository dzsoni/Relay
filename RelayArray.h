#ifndef RELAYARRAY_H
#define RELAYARRAY_H

#include <Arduino.h>
#include <vector>
#include "SimpleJsonParser.h"
#include "SimpleJsonWriter.h"
#include "FS.h"
#include "Relay.h"

//#define DEBUG_RELAYARRAY 1 //set to 1 to enable debug messages
#ifdef DEBUG_RELAYARRAY
#define DEBUG_RELAYARRAY_PP(a) Serial.print(a);
#define DEBUG_RELAYARRAY_PL(a) Serial.println(a);
#else
#define DEBUG_RELAYARRAY_PP(a)
#define DEBUG_RELAYARRAY_PL(a)
#endif




class RelayArray 
{
    private:
        std::vector<std::shared_ptr<Relay>> _relayarray;
                
    public:
        RelayArray(unsigned char reserve_size = 2);
        ~RelayArray();

        bool addRelay(String relayid, unsigned char pin, bool initstate, bool on_state_level);

        bool removeRelayByPin(unsigned char pin);
        bool removeRelayById(String relayid);
        bool removeRelayByIndex(unsigned char index);

        bool changeIdByPin(unsigned char pin, String newid);
        bool changeIdById(String oldid,String newid);
        bool changeIdByIndex(unsigned char index, String newid);

        bool initByPin(unsigned char pin, bool initstate, bool on_state_level);
        bool initById(String relayid, bool initstate, bool on_state_level);
        bool initByIndex(unsigned char index, bool initstate, bool on_state_level);

        void OnByPin(unsigned char pin);
        void OnById(String relayid);
        void OnByIndex(unsigned char index);

        void OffByPin(unsigned char pin);        
        void OffById(String relayid);
        void OffByIndex(unsigned char index);

        void setStateByPin(unsigned char pin, bool state);        
        void setStateById(String relayid, bool state);
        void setStateByIndex(unsigned char index, bool state);

        bool getStateByPin(unsigned char pin);
        bool getStateById(String relayid);
        bool getStateByIndex(unsigned char index);

        bool getInitStateByPin(unsigned char pin);
        bool getInitStateById(String relayid);
        bool getInitStateByIndex(unsigned char index);

        bool getOnStateLevelByPin(unsigned char pin);
        bool getOnStateLevelById(String relayid);
        bool getOnStateLevelByIndex(unsigned char index);
        
        int getRelayPinById(String relayid);//-1 if not found, otherwise pin number of relay with id relayid
        int getRelayPinByIndex(unsigned char index);//-1 if not found, otherwise pin number of relay with index index

        int getRelayIndexByPin(unsigned char pin);//-1 if not found, otherwise index of relay with pin pin
        int getRelayIndexById(String relayid);//-1 if not found, otherwise index of relay with id relayid

        String getRelayIdByPin(unsigned char pin);
        String getRelayIdByIndex(unsigned char index);

        int getRelayCount() { return _relayarray.size(); };
        bool isIdExist(String relayid);

        void loadRelays(String pathtoJsonfile);
        void saveRelays(String pathtoJsonfile);

        void shrinkToFit() { _relayarray.shrink_to_fit(); };
        void clearArray() { _relayarray.clear(); };
        
};





#endif /* RELAYARRAY_H */
