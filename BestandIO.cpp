//
//  BestandIO.cpp
//  projectSoftwareEngineering
//
//  Created by Andrei Bondarenko on 19/02/2017.
//
//

#include "BestandIO.h"
#include "tinyxml.h"
#include <iostream>

MetroNet* BestandIO::input(std::string file) {

  TiXmlDocument doc;
  if(!doc.LoadFile("input/cdCatalog.xml")) {
    std::cerr << doc.ErrorDesc() << std::endl;
  }

  TiXmlElement* net = doc.FirstChildElement();
  if(net == NULL) {
    std::cerr << "Failed to load file: No root element." << std::endl;
    doc.Clear();
  }

  MetroNet* metroNet = new MetroNet;
  for(TiXmlElement* element = net->FirstChildElement();
      element != NULL;
      element = element->NextSiblingElement())
  {
    std::string elementType = element->Value();
    if(elementType == "STATION"){
      Station* station = new Station;
      for(TiXmlElement* infoElem = element->FirstChildElement();
          infoElem != NULL;
          infoElem = infoElem->NextSiblingElement())
      {
        std::string elemName = infoElem->Value();
        for(TiXmlNode* data = infoElem->FirstChild();
            data != NULL;
            data = data->NextSibling())
        {
          TiXmlText* text = data->ToText();
          if(text != NULL){
            if (elemName == "naam")
              station->setNaam(text->Value());
            else if (elemName == "vorige")
              station->setVorige(text->Value());
            else if (elemName == "volgende")
              station->setVolgende(text->Value());
            else if (elemName == "spoor")
              station->setSpoor(std::stoi(text->Value()));
          }
        }
      }
    metroNet->addStation(station);
    }
    else if(elementType == "TRAM"){
      Tram* tram = new Tram;
      for(TiXmlElement* infoElem = element->FirstChildElement();
          infoElem != NULL;
          infoElem = infoElem->NextSiblingElement()){
        std::string elemName = infoElem->Value();
        for(TiXmlNode* data = infoElem->FirstChild();
            data != NULL;
            data = data->NextSibling())
        {
          TiXmlText* text = data->ToText();
          if(text != NULL){
            if (elemName == "lijnNr")
              tram->setLijnNr(std::stoi(text->Value()));
            else if (elemName == "zitplaatsen")
              tram->setZitplaatsen(std::stoi(text->Value()));
            else if (elemName == "snelheid")
              tram->setSnelheid(std::stoi(text->Value()));
            else if (elemName == "beginStation")
              tram->setBeginStation(text->Value());
          }
        }
      }
      metroNet->addTram(tram);
    }
  }
  doc.Clear();
  return metroNet;
}
