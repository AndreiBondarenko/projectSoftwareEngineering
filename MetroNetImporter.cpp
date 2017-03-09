//
//  MetroNetImporter.cpp
//  projectSoftwareEngineering
//
//  Created by Andrei Bondarenko on 09/03/2017.
//
//

#include "MetroNetImporter.h"
#include "tinyxml.h"
#include "DesignByContract.h"

SuccessEnum MetroNetImporter::importMetroNet(const char *inputfilename, std::ostream &errStream, MetroNet &metronet) {

  REQUIRE(metronet.properlyInitialized(), "metronet wasn't initialized when passed to MetroNetImporter::importMetroNet");

  TiXmlDocument doc;
  SuccessEnum endResult = Success;

  if(!doc.LoadFile(inputfilename)) {
    errStream << "XML IMPORT ABORTED: " << doc.ErrorDesc() << std::endl;
		return ImportAborted;
  }

  TiXmlElement* net = doc.FirstChildElement();
  if(net == NULL) {
    errStream << "XML PARTIAL IMPORT: " << "Failed to load file: No root element." << std::endl;
    doc.Clear();
		return PartialImport;
  }
  std::string rootName = net->Value();
  if(rootName != "METRONET") {
    errStream << "XML PARTIAL IMPORT: Expected <METRONET> ... </METRONET> and got <"
				<< rootName <<  "> ... </" << rootName << ">." << std::endl;
			endResult = PartialImport;
  }
  for (TiXmlElement* element = net->FirstChildElement();
    element != NULL;
    element = element->NextSiblingElement())
  {
    bool deleted = false;
    std::string elementType = element->Value();
    if (elementType == "STATION") {
      Station* station = new Station;
      for (TiXmlElement* infoElem = element->FirstChildElement();
        infoElem != NULL;
        infoElem = infoElem->NextSiblingElement())
      {
        std::string elemName = infoElem->Value();
        for (TiXmlNode* data = infoElem->FirstChild();
          data != NULL;
          data = data->NextSibling())
        {
          TiXmlText* text = data->ToText();
          if (text != NULL) {
            if (elemName == "naam")
              station->setNaam(text->Value());
            else if (elemName == "vorige")
              station->setVorige(text->Value());
            else if (elemName == "volgende")
              station->setVolgende(text->Value());
            else if (elemName == "spoor") {
              try {
                int spoor = std::stoi(text->Value());
                if (spoor >= 0)
                  station->setSpoor(spoor);
                else throw 0;
              }
              catch (int e) {
                delete station;
                errStream << "\nStation not created, negative rail: " << text->Value() << ".\n" << std::endl;
                deleted = true;
                break;
              }
              catch (std::invalid_argument& e) {
                delete station;
                errStream << "\nStation not created, invalid rail: " << text->Value() << ".\n" << std::endl;
                deleted = true;
                break;
              }
            }
            else if (elemName == "opstappen") {
              try {
                int opstappen = std::stoi(text->Value());
                if (opstappen >= 0)
                  station->setOpstappen(opstappen);
                else throw 0;
              }
              catch (int e) {
                delete station;
                errStream << "\nStation not created, negative opstappen: " << text->Value() << ".\n" << std::endl;
                deleted = true;
                break;
              }
              catch (std::invalid_argument& e) {
                delete station;
                errStream << "\nStation not created, invalid opstappen: " << text->Value() << ".\n" << std::endl;
                deleted = true;
                break;
              }
            }
            else if (elemName == "afstappen") {
              try {
                int afstappen = std::stoi(text->Value());
                if (afstappen >= 0)
                  station->setAfstappen(afstappen);
                else throw 0;
              }
              catch (int e) {
                delete station;
                errStream << "\nStation not created, negative afstappen: " << text->Value() << ".\n" << std::endl;
                deleted = true;
                break;
              }
              catch (std::invalid_argument& e) {
                delete station;
                errStream << "\nStation not created, invalid afstappen: " << text->Value() << ".\n" << std::endl;
                deleted = true;
                break;
              }
            }
          }
        }
      }
      if (deleted) break;
      metronet.addStation(station);
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
            try {
              if (elemName == "lijnNr") {
                int nummer = std::stoi(text->Value());
                if (nummer >= 0)
                  tram->setLijnNr(nummer);
                else throw 0;
              }
              else if (elemName == "zitplaatsen") {
                int plaatsen = std::stoi(text->Value());
                if (plaatsen >= 0)
                  tram->setZitplaatsen(plaatsen);
                else throw 1;
              }
              else if (elemName == "snelheid") {
                int snelheid = std::stoi(text->Value());
                if (snelheid > 0)
                  tram->setSnelheid(snelheid);
                else throw 2;
              }
              else if (elemName == "beginStation") {
                std::string value = text->Value();
                tram->setBeginStation(value);
                tram->setCurrentStation(value);
                metronet.getAlleStations()->at(value)
                                          ->setTramInStation(true);
              }
            }
            catch(int e) {
              switch (e) {
              case 0:
                delete tram;
                errStream << "\nTram not created, negative line number: " << text->Value() << ".\n" << std::endl;
                deleted = true;
                break;
              case 1:
                delete tram;
                errStream << "\nTram not created, negative number of seats: " << text->Value() << ".\n" << std::endl;
                deleted = true;
                break;
              case 2:
                delete tram;
                errStream << "\nTram not created, negative speed: " << text->Value() << ".\n" << std::endl;
                deleted = true;
                break;
              }
              break;
            }
            catch (std::invalid_argument& e) {
              if (elemName == "lijnNr") {
                delete tram;
                errStream << "\nTram not created, invalid line number: " << text->Value() << ".\n" << std::endl;
                deleted = true;
                break;
              }
              else if (elemName == "zitplaatsen") {
                delete tram;
                errStream << "\nTram not created, invalid number of seats: " << text->Value() << ".\n" << std::endl;
                deleted = true;
                break;
              }
              else if (elemName == "snelheid") {
                delete tram;
                errStream << "\nTram not created, invalid speed: " << text->Value() << ".\n" << std::endl;
                deleted = true;
                break;
              }
            }
          }
        }
      }
      if (deleted) break;
      metronet.addTram(tram);
    }
    else {
      std::cout << "Element of type: " << elementType << " unsupported\n";
    }
  }
  doc.Clear();
  ENSURE(metronet.isConsistent(), "MetroNet is inconsistent");
}
