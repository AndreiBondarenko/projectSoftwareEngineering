#ifndef INC_HALTE_H
#define INC_HALTE_H
#pragma once

#include "Station.h"

class Halte: public Station {
public:
  // CONSTRUCTORS
  /**
  \n ENSURE(properlyInitialized(), "constructor must end in properlyInitialized state");
  */
  Halte(); // default
  /**
  \n REQUIRE(naam != "", "naam must not be empty");
  \n ENSURE(properlyInitialized(), "constructor must end in properlyInitialized state");
  */
  Halte(const std::string& naam); // full

  /**
  \n REQUIRE(properlyInitialized(), "Halte wasn't initialized when calling albatrosCanStop");
  */
  bool albatrosCanStop() const;
};

#endif /* INC_HALTE_H */
