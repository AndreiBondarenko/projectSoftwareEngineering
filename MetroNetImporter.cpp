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
    errStream << "XML IMPORT ABORTED: " << "Failed to load file: No root element." << std::endl;
    doc.Clear();
        return ImportAborted;
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
      TiXmlNode *naam, *volgende, *vorige, *spoor;
      naam = element->FirstChild("naam");
      volgende = element->FirstChild("volgende");
      vorige = element->FirstChild("vorige");
      spoor = element->FirstChild("spoor");
      if(naam == NULL) {
        errStream << "XML PARTIAL IMPORT: Expected <naam> ... </naam>." << std::endl;
        endResult = PartialImport;
        delete station;
        continue;
      }
      if(volgende == NULL) {
        errStream << "XML PARTIAL IMPORT: Expected <volgende> ... </volgende>." << std::endl;
        endResult = PartialImport;
        delete station;
        continue;
      }
      if(vorige == NULL) {
        errStream << "XML PARTIAL IMPORT: Expected <vorige> ... </vorige>." << std::endl;
        endResult = PartialImport;
        delete station;
        continue;
      }
      if(spoor == NULL) {
        errStream << "XML PARTIAL IMPORT: Expected <spoor> ... </spoor>." << std::endl;
        endResult = PartialImport;
        delete station;
        continue;
      }

      for (TiXmlElement* infoElem = element->FirstChildElement();
        infoElem != NULL;
        infoElem = infoElem->NextSiblingElement())
      {
        std::string elemName = infoElem->Value();
        if(infoElem->FirstChild() == NULL) {
          errStream << "XML PARTIAL IMPORT: <"
    				<< elemName <<  "> ... </" << elemName << "> is empty." << std::endl;
    			endResult = PartialImport;
        }
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
                errStream << "XML PARTIAL IMPORT: Station not created, negative rail: " << text->Value() << ".\n" << std::endl;
                deleted = true;
                break;
              }
              catch (std::invalid_argument& e) {
                delete station;
                errStream << "XML PARTIAL IMPORT: Station not created, invalid rail: " << text->Value() << ".\n" << std::endl;
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
                errStream << "XML PARTIAL IMPORT: Station not created, negative opstappen: " << text->Value() << ".\n";
                deleted = true;
                break;
              }
              catch (std::invalid_argument& e) {
                delete station;
                errStream << "XML PARTIAL IMPORT: Station not created, invalid opstappen: " << text->Value() << ".\n";
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
                errStream << "XML PARTIAL IMPORT: Station not created, negative afstappen: " << text->Value() << ".\n";
                deleted = true;
                break;
              }
              catch (std::invalid_argument& e) {
                delete station;
                errStream << "XML PARTIAL IMPORT: Station not created, invalid afstappen: " << text->Value() << ".\n";
                deleted = true;
                break;
              }
            }
            else {
              errStream << "XML PARTIAL IMPORT:\nExpected:\n<naam> ... </naam> or\n<volgende> ... </volgende> or\n<vorige> ... </vorige> or\n<spoor> ... </spoor> or\n<opstappen> ... </opstappen> or\n<afstappen> ... </afstappen>\nand got: <"
				            << elemName <<  "> ... </" << elemName << ">." << std::endl;
            }
          }
        }
      }
      if (deleted) continue;
      metronet.addStation(station);
    }
    else if(elementType == "TRAM"){
      Tram* tram = new Tram;
      TiXmlNode *lijnNr, *zitplaatsen, *snelheid, *beginStation;
      lijnNr = element->FirstChild("lijnNr");
      zitplaatsen = element->FirstChild("zitplaatsen");
      snelheid = element->FirstChild("snelheid");
      beginStation = element->FirstChild("beginStation");
      if(lijnNr == NULL) {
        errStream << "XML PARTIAL IMPORT: Expected <lijnNr> ... </lijnNr>." << std::endl;
        endResult = PartialImport;
        delete tram;
        continue;
      }
      if(zitplaatsen == NULL) {
        errStream << "XML PARTIAL IMPORT: Expected <zitplaatsen> ... </zitplaatsen>." << std::endl;
        endResult = PartialImport;
        delete tram;
        continue;
      }
      if(snelheid == NULL) {
        errStream << "XML PARTIAL IMPORT: Expected <snelheid> ... </snelheid>." << std::endl;
        endResult = PartialImport;
        delete tram;
        continue;
      }
      if(beginStation == NULL) {
        errStream << "XML PARTIAL IMPORT: Expected <beginStation> ... </beginStation>." << std::endl;
        endResult = PartialImport;
        delete tram;
        continue;
      }
      for(TiXmlElement* infoElem = element->FirstChildElement();
          infoElem != NULL;
          infoElem = infoElem->NextSiblingElement()){
        std::string elemName = infoElem->Value();
        if(infoElem->FirstChild() == NULL) {
          errStream << "XML PARTIAL IMPORT: <"
    				<< elemName <<  "> ... </" << elemName << "> is empty." << std::endl;
    			endResult = PartialImport;
        }
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
                if (metronet.getAlleStations()->find(value) == metronet.getAlleStations()->end()) {
                  throw 3;
                }
                else
                  metronet.getAlleStations()->find(value)->second->setTramInStation(true);
              }
              else {
                errStream << "XML PARTIAL IMPORT:\nExpected:\n<lijnNr> ... </lijnNr> or\n<zitplaatsen> ... </zitplaatsen> or\n<snelheid> ... </snelheid> or\n<beginStation> ... </beginStation>\nand got: <"
  				            << elemName <<  "> ... </" << elemName << ">." << std::endl;
              }
            }
            catch(int e) {
              switch (e) {
              case 0:
                delete tram;
                errStream << "XML PARTIAL IMPORT: Tram not created, negative line number: " << text->Value() << ".\n";
                deleted = true;
                break;
              case 1:
                delete tram;
                errStream << "XML PARTIAL IMPORT: Tram not created, negative number of seats: " << text->Value() << ".\n";
                deleted = true;
                break;
              case 2:
                delete tram;
                errStream << "XML PARTIAL IMPORT: Tram not created, negative speed: " << text->Value() << ".\n";
                deleted = true;
                break;
              case 3:
                errStream << "XML PARTIAL IMPORT: BeginStation not found for tram " << tram->getLijnNr() << std::endl;
                delete tram;
                deleted = true;
                break;
              }
              break;
            }
            catch (std::invalid_argument& e) {
              if (elemName == "lijnNr") {
                delete tram;
                errStream << "XML PARTIAL IMPORT: Tram not created, invalid line number: " << text->Value() << ".\n";
                deleted = true;
                break;
              }
              else if (elemName == "zitplaatsen") {
                delete tram;
                errStream << "XML PARTIAL IMPORT: Tram not created, invalid number of seats: " << text->Value() << ".\n";
                deleted = true;
                break;
              }
              else if (elemName == "snelheid") {
                delete tram;
                errStream << "XML PARTIAL IMPORT: Tram not created, invalid speed: " << text->Value() << ".\n";
                deleted = true;
                break;
              }
            }
          }
        }
      }
      if (deleted) continue;
      metronet.addTram(tram);
    }
    else {
      errStream << "XML PARTIAL IMPORT: Expected <STATION> ... </STATION> or <TRAM> ... </TRAM> and got <"
				<< elementType <<  "> ... </" << elementType << ">." << std::endl;
      endResult = PartialImport;
    }
  }
  doc.Clear();
  ENSURE(metronet.isConsistent(), "MetroNet is inconsistent");
  return endResult;
}
