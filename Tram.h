//
//  Tram.h
//  projectSoftwareEngineering
//
//  Created by Andrei Bondarenko on 17/02/2017.
//
//

#ifndef INC_TRAM_H
#define INC_TRAM_H

#include <string>

class Tram {
private:
  Tram* fInitCheck;
  int fLijnNr;
  int fZitplaatsen;
  std::string fBeginStation;
  int fSnelheid;
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


#endif /* INC_TRAM_H */
