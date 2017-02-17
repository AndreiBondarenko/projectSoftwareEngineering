//
//  Station.h
//  projectSoftwareEngineering
//
//  Created by Andrei Bondarenko on 17/02/2017.
//
//

#ifndef Station_h
#define Station_h

#include <string>

class Station {
private:
  std::string _naam;
  std::string _vorige;
  std::string _volgende;
  int _spoor;
// int _opstappen;
// int _afstappen;
public:
  // constructors
  Station(); // default
  Station(std::string naam, std::string vorige, std::string volgende, int spoor); // full
  // destructor
  ~Station();
  // getter methods
  std::string getNaam() const;
  std::string getVorige() const;
  std::string getVolgende() const;
  int getSpoor() const;
// int getOpstappen() const;
// int getAfstappen() const;
  // setter methods
  void setNaam(std::string newNaam);
  void setVorige(std::string newVorige);
  void setVolgende(std::string newVolgende);
  void setSpoor(int newSpoor);
// void setOpstappen(int newOpstappen);
// void setAfstappen(int newAfstappen);


protected:

};


#endif /* Station_h */
