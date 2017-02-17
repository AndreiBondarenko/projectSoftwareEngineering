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
  std::string naam;
  std::string vorige;
  std::string volgende;
  int spoor;
  // int opstappen;
  // int afstappen;
public:
    Station();
    ~Station();
protected:

};


#endif /* Station_h */
