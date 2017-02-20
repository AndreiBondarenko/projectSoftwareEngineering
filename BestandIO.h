//
//  BestandIO.h
//  projectSoftwareEngineering
//
//  Created by Andrei Bondarenko on 19/02/2017.
//
//

#ifndef BESTANDIO_H
#define BESTANDIO_H

#include <string>
#include "MetroNet.h"

class BestandIO {
private:
public:
  static MetroNet* input(std::string file);
  static void output(MetroNet* net);
protected:

};


#endif /* BESTANDIO_H */
