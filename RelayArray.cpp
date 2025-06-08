#include "RelayArray.h"



RelayArray::RelayArray(unsigned char reserve_size)
{
    _relayarray.reserve(reserve_size);
    _relayarray.shrink_to_fit();
}
    

RelayArray::~RelayArray()
{
    _relayarray.clear();
    _relayarray.resize(0);
    _relayarray.shrink_to_fit();
    
}

bool RelayArray::addRelay(String relayid, unsigned char pin, bool initstate, bool on_state_level)
{
    for(size_t i=0;i<_relayarray.size();i++)
    {
        if(_relayarray.at(i)->getRelayPin() == pin || _relayarray.at(i)->getId() == relayid)
        {
            DEBUG_RELAYARRAY_PL(F("Relay with pin ") + String(pin) + F(" or id ") + relayid + F(" already exists."));
            return false;
        }
    }
    _relayarray.emplace_back(std::make_shared<Relay>(relayid, pin, initstate, on_state_level));
    return true;
}

bool RelayArray::removeRelayByPin(unsigned char pin)
{
    for(size_t i=0;i<_relayarray.size();i++)
    {
        if(_relayarray.at(i)->getRelayPin() == pin)
        {
            _relayarray.erase(_relayarray.begin()+i);
            return true;
        }
    }
    return false;
}

bool RelayArray::removeRelayById(String relayid)
{
    for(size_t i=0;i<_relayarray.size();i++)
    {
        if(_relayarray.at(i)->getId() == relayid)
        {
            _relayarray.erase(_relayarray.begin()+i);
            return true;
        }
    }
    return false;
}
bool RelayArray::removeRelayByIndex(unsigned char index)
{
    if (index >= _relayarray.size())
    {
        DEBUG_RELAYARRAY_PL(F("Index out of range"));
        return false;
    }

    _relayarray.erase(_relayarray.begin() + index);
    return true;
}

bool RelayArray::changeIdByPin(unsigned char pin, String newid)
{
    for(size_t i=0;i<_relayarray.size();i++)
    {
        if(_relayarray.at(i)->getRelayPin() == pin)
        {
            if(newid == "" || isIdExist(newid))
            {
                DEBUG_RELAYARRAY_PL(F("Id already exists or is empty."));
                return false;
            }
            _relayarray.at(i)->changeId(newid);
            DEBUG_RELAYARRAY_PL(F("Relay with pin ") + String(pin) + F(" changed to ") + newid);
            if(newid == "" || isIdExist(newid))
           
            return true;
        }
    }
    return false;
}

bool RelayArray::changeIdById(String oldid, String newid)
{
    for(size_t i=0;i<_relayarray.size();i++)
    {
        if(_relayarray.at(i)->getId() == oldid)
        {
            if(newid == "" || isIdExist(newid))
            {
                DEBUG_RELAYARRAY_PL(F("Id already exists or is empty."));
                return false;
            }
            _relayarray.at(i)->changeId(newid);
            DEBUG_RELAYARRAY_PL(F("Relay with id ") + oldid + F(" changed to ") + newid);
            return true;
        }
    }
    return false;
}

bool RelayArray::changeIdByIndex(unsigned char index, String newid)
{
    if (index >= _relayarray.size())
    {
        DEBUG_RELAYARRAY_PL(F("Index out of range"));
        return false;
    }
    if(newid == "" || isIdExist(newid))
    {
        DEBUG_RELAYARRAY_PL(F("Id already exists or is empty."));
        return false;
    }
    _relayarray.at(index)->changeId(newid);
    DEBUG_RELAYARRAY_PL(F("Relay with id ") + _relayarray.at(index)->getId() + F(" changed to ") + newid);
    return true;
}

bool RelayArray::initByPin(unsigned char pin, bool initstate, bool on_state_level)
{
    for(size_t i=0;i<_relayarray.size();i++)
    {
        if(_relayarray.at(i)->getRelayPin() == pin)
        {
            _relayarray.at(i)->init(pin, initstate, on_state_level);
            DEBUG_RELAYARRAY_PL(F("Relay with id ") + _relayarray.at(i)->getId() + F(" initialized."));
            return true;
        }
    }
    return false;
}

bool RelayArray::initById(String relayid, bool initstate, bool on_state_level)
{
    for(size_t i=0;i<_relayarray.size();i++)
    {
        if(_relayarray.at(i)->getId() == relayid)
        {
            _relayarray.at(i)->init(_relayarray.at(i)->getRelayPin(), initstate, on_state_level);
            DEBUG_RELAYARRAY_PL(F("Relay with id ") + _relayarray.at(i)->getId() + F(" initialized."));
            return true;
        }
    }
    return false;
}

bool RelayArray::initByIndex(unsigned char index, bool initstate, bool on_state_level)
{
    if (index >= _relayarray.size())
    {
        DEBUG_RELAYARRAY_PL(F("Index out of range."));
        return false;
    }
    _relayarray.at(index)->init(_relayarray.at(index)->getRelayPin(), initstate, on_state_level);
    DEBUG_RELAYARRAY_PL(F("Relay with id ") + _relayarray.at(index)->getId() + F(" initialized."));
    return true;
}

void RelayArray::OnByPin(unsigned char pin)
{
    for(size_t i=0;i<_relayarray.size();i++)
    {
        if(_relayarray.at(i)->getRelayPin() == pin)
        {
            _relayarray.at(i)->On();
            DEBUG_RELAYARRAY_PL(F("Relay with id ") + _relayarray.at(i)->getId() + F(" turned on."));
            return;
        }
    }
}

void RelayArray::OnById(String relayid)
{
    for(size_t i=0;i<_relayarray.size();i++)
    {
        if(_relayarray.at(i)->getId() == relayid)
        {
            _relayarray.at(i)->On();
            DEBUG_RELAYARRAY_PL(F("Relay with id ") + _relayarray.at(i)->getId() + F(" turned on."));
            return;
        }
    }
    DEBUG_RELAYARRAY_PL(F("Relay with id ") + relayid + F(" not found."));
}

void RelayArray::OnByIndex(unsigned char index)
{
    if (index >= _relayarray.size())
    {
        DEBUG_RELAYARRAY_PL(F("Index out of range."));
        return;
    }
    _relayarray.at(index)->On();
    DEBUG_RELAYARRAY_PL(F("Relay with id ") + _relayarray.at(index)->getId() + F(" turned on."));
}

void RelayArray::OffByPin(unsigned char pin)
{
    for(size_t i=0;i<_relayarray.size();i++)
    {
        if(_relayarray.at(i)->getRelayPin() == pin)
        {
            _relayarray.at(i)->Off();
            DEBUG_RELAYARRAY_PL(F("Relay with id ") + _relayarray.at(i)->getId() + F(" turned off."));
            return;
        }
    }
    DEBUG_RELAYARRAY_PL(F("Relay with pin ") + String(pin) + F(" not found."));
}

void RelayArray::OffById(String relayid)
{
    for(size_t i=0;i<_relayarray.size();i++)
    {
        if(_relayarray.at(i)->getId() == relayid)
        {
            _relayarray.at(i)->Off();
            DEBUG_RELAYARRAY_PL(F("Relay with id ") + _relayarray.at(i)->getId() + F(" turned off."));
            return;
        }
    }
    DEBUG_RELAYARRAY_PL(F("Relay with id ") + relayid + F(" not found."));
}

void RelayArray::OffByIndex(unsigned char index)
{
    if (index >= _relayarray.size())
    {
        DEBUG_RELAYARRAY_PL(F("Index out of range."));
        return;
    }
    _relayarray.at(index)->Off();
    DEBUG_RELAYARRAY_PL(F("Relay with id ") + _relayarray.at(index)->getId() + F(" turned off."));
}

void RelayArray::setStateByPin(unsigned char pin, bool state)
{
    for(size_t i=0;i<_relayarray.size();i++)
    {
        if(_relayarray.at(i)->getRelayPin() == pin)
        {
            _relayarray.at(i)->setRelayState(state);
            DEBUG_RELAYARRAY_PL(F("Relay with id ") + _relayarray.at(i)->getId() + F(" set to ") + String(state));
            return;
        }
    }
    DEBUG_RELAYARRAY_PL(F("Relay with pin ") + String(pin) + F(" not found."));
}

void RelayArray::setStateById(String relayid, bool state)
{
    for(size_t i=0;i<_relayarray.size();i++)
    {
        if(_relayarray.at(i)->getId() == relayid)
        {
            _relayarray.at(i)->setRelayState(state);
            DEBUG_RELAYARRAY_PL(F("Relay with id ") + _relayarray.at(i)->getId() + F(" set to ") + String(state));
            return;
        }
    }
    DEBUG_RELAYARRAY_PL(F("Relay with id ") + relayid + F(" not found."));
}

void RelayArray::setStateByIndex(unsigned char index, bool state)
{
    if (index >= _relayarray.size())
    {
        DEBUG_RELAYARRAY_PL(F("Index out of range."));
        return;
    }
    _relayarray.at(index)->setRelayState(state);
    DEBUG_RELAYARRAY_PL(F("Relay with id ") + _relayarray.at(index)->getId() + F(" set to ") + String(state));
}

bool RelayArray::getStateByPin(unsigned char pin)
{
    for(size_t i=0;i<_relayarray.size();i++)
    {
        if(_relayarray.at(i)->getRelayPin() == pin)
        {           
            return _relayarray.at(i)->getRelayState();
        }
    }
    DEBUG_RELAYARRAY_PL(F("Relay with pin ") + String(pin) + F(" not found."));
    return false;
}

bool RelayArray::getStateById(String relayid)
{
    for(size_t i=0;i<_relayarray.size();i++)
    {
        if(_relayarray.at(i)->getId() == relayid)
        {           
            return _relayarray.at(i)->getRelayState();
        }
    }
    DEBUG_RELAYARRAY_PL(F("Relay with id ") + relayid + F(" not found."));
    return false;
}

bool RelayArray::getStateByIndex(unsigned char index)
{
    if (index >= _relayarray.size())
    {
        DEBUG_RELAYARRAY_PL(F("Index out of range."));
        return false;
    }
    return _relayarray.at(index)->getRelayState();
}

bool RelayArray::getInitStateByPin(unsigned char pin)
{
    for(size_t i=0;i<_relayarray.size();i++)
    {
        if(_relayarray.at(i)->getRelayPin() == pin)
        {           
            
            return _relayarray.at(i)->getInitState();
        }
    }
    DEBUG_RELAYARRAY_PL(F("Relay with pin ") + String(pin) + F(" not found."));
    return false;
}

/**
 * @brief Retrieves the initial state of a relay by its ID.
 *
 * @param relayid The ID of the relay to retrieve the initial state for.
 *
 * @return The initial state of the relay, or false if the relay with the given ID is not found.
 */
bool RelayArray::getInitStateById(String relayid)
{
    for(size_t i=0;i<_relayarray.size();i++)
    {
        if(_relayarray.at(i)->getId() == relayid)
        {           
            return _relayarray.at(i)->getInitState();
        }
    }
    DEBUG_RELAYARRAY_PL(F("Relay with id ") + relayid + F(" not found."));
    return false;
}
/**
 * @brief Retrieves the initial state of the relay at the specified index.
 *
 * @param index The index of the relay to retrieve the initial state for.
 *
 * @return The initial state of the relay. If the index is out of range,
 *   the function will return false.
 */
bool RelayArray::getInitStateByIndex(unsigned char index)
{
    if (index >= _relayarray.size())
    {
        DEBUG_RELAYARRAY_PL(F("Index out of range."));
        return false;
    }
    return _relayarray.at(index)->getInitState();
}

/**
 * @brief Retrieves the physical voltage level of a relay when it is turned on, by its GPIO pin.
 *
 * @param pin The GPIO pin of the relay.
 *
 * @return The physical voltage level of the relay when it is turned on, or false if the relay with the given pin is not found.
 */
bool RelayArray::getOnStateLevelByPin(unsigned char pin)
{
    
    for(size_t i=0;i<_relayarray.size();i++)
    {
        if(_relayarray.at(i)->getRelayPin() == pin)
        {           
            return _relayarray.at(i)->getOnStateLevel();
        }
    }
    DEBUG_RELAYARRAY_PL(F("Relay with pin ") + String(pin) + F(" not found."));
    return false;
}

/**
 * @brief Retrieves the physical voltage level of a relay when it is turned on, by its ID.
 *
 * @param relayid The ID of the relay to retrieve the physical voltage level for.
 *
 * @return The physical voltage level of the relay when it is turned on, or false if the relay with the given ID is not found.
 */
bool RelayArray::getOnStateLevelById(String relayid)
{
    for(size_t i=0;i<_relayarray.size();i++)
    {
        if(_relayarray.at(i)->getId() == relayid)
        {           
            return _relayarray.at(i)->getOnStateLevel();
        }
    }
    DEBUG_RELAYARRAY_PL(F("Relay with id ") + relayid + F(" not found."));
    return false;
}

/**
 * @brief Retrieves the physical voltage level of a relay when it is turned on, by its index in the relay array.
 *
 * @param index The index of the relay in the relay array.
 *
 * @return The physical voltage level of the relay when it is turned on, or false if the index is out of range.
 */
bool RelayArray::getOnStateLevelByIndex(unsigned char index)
{
    if (index >= _relayarray.size())
    {
        DEBUG_RELAYARRAY_PL(F("Index out of range."));
        return false;
    }
    return _relayarray.at(index)->getOnStateLevel();
}

/**
 * @brief Retrieves the GPIO pin number of a relay by its ID.
 *
 * @param relayid The ID of the relay to retrieve the GPIO pin number for.
 *
 * @return The GPIO pin number of the relay, or 0 if the relay with the given ID is not found.
 */
int RelayArray::getRelayPinById(String relayid)
{
    for(size_t i=0;i<_relayarray.size();i++)
    {
        if(_relayarray.at(i)->getId() == relayid)
        {           
            return (int)_relayarray.at(i)->getRelayPin();
        }
    }
    DEBUG_RELAYARRAY_PL(F("Relay with id ") + relayid + F(" not found."));
    return -1;
}

/**
 * @brief Retrieves the GPIO pin number of the relay at the specified index.
 *
 * @param index The index of the relay in the relay array.
 *
 * @return The GPIO pin number of the relay. If the index is out of range,
 *   the function will return 0.
 */
int RelayArray::getRelayPinByIndex(unsigned char index)
{
    if (index >= _relayarray.size())
    {
        DEBUG_RELAYARRAY_PL(F("Index out of range."));
        return -1;
    }
    return (int)_relayarray.at(index)->getRelayPin();
}

int RelayArray::getRelayIndexByPin(unsigned char pin)
{
    for(size_t i=0;i<_relayarray.size();i++)
    {
        if(_relayarray.at(i)->getRelayPin() == pin)
        {           
            return (int)i;
        }
    }
    DEBUG_RELAYARRAY_PL(F("Relay with pin ") + String(pin) + F(" not found."));
    return -1;
}

int RelayArray::getRelayIndexById(String relayid)
{
    for(size_t i=0;i<_relayarray.size();i++)
    {
        if(_relayarray.at(i)->getId() == relayid)
        {           
            return (int)i;
        }
    }
    DEBUG_RELAYARRAY_PL(F("Relay with id ") + relayid + F(" not found."));
    return -1;
}

String RelayArray::getRelayIdByPin(unsigned char pin)
{
    for(size_t i=0;i<_relayarray.size();i++)
    {
        if(_relayarray.at(i)->getRelayPin() == pin)
        {           
            return _relayarray.at(i)->getId();
        }
    }
    DEBUG_RELAYARRAY_PL(F("Relay with pin ") + String(pin) + F(" not found."));
    return String("");
}

String RelayArray::getRelayIdByIndex(unsigned char index)
{
    if (index >= _relayarray.size())
    {
        DEBUG_RELAYARRAY_PL(F("Index out of range."));
        return String("");
    }
    return _relayarray.at(index)->getId();
}

bool RelayArray::isIdExist(String relayid)
{
    for(size_t i=0;i<_relayarray.size();i++)
    {
        if(_relayarray.at(i)->getId() == relayid)
        {           
            return true;
        }
    }
    return false;
}
void RelayArray::loadRelays(String pathtoJsonfile)
{
  SimpleJsonParser sjp;
  std::vector<std::pair<String, String>> vec;
  vec = sjp.extractKeysandValuesFromFile(pathtoJsonfile);
  
  for (std::pair a : vec)
  {
    if (a.first.indexOf(":id") > 0)
    {
      int ai = a.first.substring(0, a.first.indexOf(":id")).toInt();
      for (std::pair b : vec)
      {
        if (b.first.indexOf(":pin") > 0)
        {
          int bi = b.first.substring(0, b.first.indexOf(":pin")).toInt();
          if (ai == bi)
          {
            for (std::pair c : vec)
            {
              if (c.first.indexOf(":initstate") > 0)
              {
                int ci = c.first.substring(0, c.first.indexOf(":initstate")).toInt();
                if (ai == ci)
                {
                  for (std::pair d : vec)
                  {
                    if (d.first.indexOf(":onstate") > 0)
                    {
                      int di = d.first.substring(0, d.first.indexOf(":onstate")).toInt();
                      if (ai == di)
                      {
                        if (!addRelay(a.second, (uint8_t)b.second.toInt(), (bool)c.second.toInt(),
                                                (bool)d.second.toInt()))
                        {
                          Serial.println(F("Relay with id ") + a.second + F(" and pin ") + b.second + F(" not added."));
                        }
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
  }
  shrinkToFit();
}

void RelayArray::saveRelays(String pathtoJsonfile) 
{
  SimpleJsonWriter sjw;
  for(int i=0;i<getRelayCount();i++)
  {
    sjw.addKeyValue(String(i)+":id",getRelayIdByIndex(i).c_str());
    sjw.addKeyValue(String(i)+":pin",String(getRelayPinByIndex(i)));
    sjw.addKeyValue(String(i)+":initstate",String(getInitStateByIndex(i)));
    sjw.addKeyValue(String(i)+":onstate",String(getOnStateLevelByIndex(i)));
  }
  File file = SPIFFS.open(pathtoJsonfile, "w");
  if (!file)
  {
    Serial.println(F("Error opening file for writing."));
    return;
  }
  file.print(sjw.getJsonString());
  file.flush();
  file.close();
  sjw.clear();
}