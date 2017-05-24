#ifndef INC_METROSTATION_H
#define INC_METROSTATION_H
#pragma once

#include "Station.h"

class MetroStation: public Station {
public:
  // CONSTRUCTORS
  /**
  \n ENSURE(properlyInitialized(), "constructor must end in properlyInitialized state");
  */
  MetroStation(); // default
  /**
  \n REQUIRE(naam != "", "naam must not be empty");
  \n ENSURE(properlyInitialized(), "constructor must end in properlyInitialized state");
  */
  MetroStation(const std::string& naam); // full

  /**
  \n REQUIRE(properlyInitialized(), "MetroStation wasn't initialized when calling albatrosCanStop");
  */
  bool albatrosCanStop() const;
};

#endif /* INC_METROSTATION_H */
