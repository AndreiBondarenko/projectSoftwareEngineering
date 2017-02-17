//
//  MetroNet.h
//  projectSoftwareEngineering
//
//  Created by Andrei Bondarenko on 17/02/2017.
//
//

#ifndef INC_METRONET_H
#define INC_METRONET_H

#include <map>
#include <set>
#include <string>
#include "Tram.h"
#include "Station.h"

class MetroNet {
private:
  MetroNet* initCheck;
  std::map<std::string, Station*> alleStations;
  std::map<int, Station*> alleTrams;
  std::set<int> alleSporen;
public:
  // CONSTRUCTOR
  /**
  \n ENSURE(properlyInitialized(), "constructor must end in properlyInitialized state");
  */
  MetroNet();

  // DESTRUCTOR
  ~MetroNet();

  // INITIALIZATION CHECK
  bool properlyInitialized();

  
protected:

};


#endif /* INC_METRONET_H */
