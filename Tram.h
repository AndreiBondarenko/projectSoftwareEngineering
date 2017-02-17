//
//  Tram.h
//  projectSoftwareEngineering
//
//  Created by Andrei Bondarenko on 17/02/2017.
//
//

#ifndef Tram_h
#define Tram_h

#include <string>

class Tram {
private:
  int _lijnNr;
  int _zitplaatsen;
  std::string _beginStation;
  int _snelheid;
public:
  // constructors
  Tram(); // default
  Tram(int lijnNr, int zitplaatsen, std::string beginStation, int snelheid); // full
  // destructor
  ~Tram();
  // getter methods
  int getLijnNr() const;
  int getZitplaatsen() const;
  std::string getBeginStation() const;
  int getSnelheid() const;
  // setter methods
  void setLijnNr(int newLijnNr);
  void setZitplaatsen(int newZitplaatsen);
  void setBeginStation(std::string newBeginStation);
  void setSnelheid(int newSnelheid);

protected:

};


#endif /* Tram_h */
