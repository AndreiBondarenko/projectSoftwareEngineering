#include <iostream>

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
      TiXmlNode *naam, *volgende, *vorige, *spoor, *type;
      naam = element->FirstChild("naam");
      type = element->FirstChild("type");
      volgende = element->FirstChild("volgende");
      vorige = element->FirstChild("vorige");
      spoor = element->FirstChild("spoor");
      if(naam == NULL) {
        errStream << "XML PARTIAL IMPORT: Expected <naam> ... </naam>." << std::endl;
        endResult = PartialImport;
        delete station;
        continue;
      }
      if(type == NULL) {
        errStream << "XML PARTIAL IMPORT: Expected <type> ... </type>." << std::endl;
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
          delete station;
          deleted = true;
        }
        for (TiXmlNode* data = infoElem->FirstChild();
          data != NULL;
          data = data->NextSibling())
        {
          TiXmlText* text = data->ToText();
          if (text != NULL && !deleted) {
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
                endResult = PartialImport;
                errStream << "XML PARTIAL IMPORT: Station not created, negative rail: " << text->Value() << "." << std::endl;
                deleted = true;
                break;
              }
              catch (std::invalid_argument& e) {
                delete station;
                endResult = PartialImport;
                errStream << "XML PARTIAL IMPORT: Station not created, invalid rail: " << text->Value() << "." << std::endl;
                deleted = true;
                break;
              }
            }
            else if (elemName == "type") {
              std::string typeVal = text->Value();
              try {
                if (typeVal == "Metrostation" || typeVal == "Halte") {
                  station->setType(typeVal);
                }
                else throw 0;
              }
              catch (int e) {
                delete station;
                endResult = PartialImport;
                errStream << "XML PARTIAL IMPORT: Station not created, station type \"" << text->Value() << "\" not recognized." << std::endl;
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
                endResult = PartialImport;
                errStream << "XML PARTIAL IMPORT: Station not created, negative opstappen: " << text->Value() << "." << std::endl;
                deleted = true;
                break;
              }
              catch (std::invalid_argument& e) {
                delete station;
                endResult = PartialImport;
                errStream << "XML PARTIAL IMPORT: Station not created, invalid opstappen: " << text->Value() << "." << std::endl;
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
                endResult = PartialImport;
                errStream << "XML PARTIAL IMPORT: Station not created, negative afstappen: " << text->Value() << "." << std::endl;
                deleted = true;
                break;
              }
              catch (std::invalid_argument& e) {
                delete station;
                endResult = PartialImport;
                errStream << "XML PARTIAL IMPORT: Station not created, invalid afstappen: " << text->Value() << "." << std::endl;
                deleted = true;
                break;
              }
            }
            else {
              errStream << "XML PARTIAL IMPORT:" << std::endl << "Expected:" << std::endl << "<naam> ... </naam> or"
              << std::endl << "<volgende> ... </volgende> or" << std::endl << "<vorige> ... </vorige> or" << std::endl <<
              "<type> ... </type> or" << std::endl << "<spoor> ... </spoor> or" << std::endl << "<opstappen> ... </opstappen> or" << std::endl <<
                "<afstappen> ... </afstappen>" << std::endl << "and got: <" << elemName << "> ... </" << elemName << ">." << std::endl;
            }
          }
        }
      }
      if (deleted) continue;
      metronet.addStation(station);
    }
    else if(elementType == "TRAM"){
      Tram* tram = new Tram;
      TiXmlNode *lijnNr, *zitplaatsen, *snelheid, *beginStation, *type, *voertuigNr;
      lijnNr = element->FirstChild("lijnNr");
      zitplaatsen = element->FirstChild("zitplaatsen");
      snelheid = element->FirstChild("snelheid");
      beginStation = element->FirstChild("beginStation");
      type = element->FirstChild("type");
      voertuigNr = element->FirstChild("voertuigNr");
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
      if(type == NULL) {
        errStream << "XML PARTIAL IMPORT: Expected <type> ... </type>." << std::endl;
        endResult = PartialImport;
        delete tram;
        continue;
      }
      if(voertuigNr == NULL) {
        errStream << "XML PARTIAL IMPORT: Expected <voertuigNr> ... </voertuigNr>." << std::endl;
        endResult = PartialImport;
        delete tram;
        continue;
      }
      for(TiXmlElement* infoElem = element->FirstChildElement();
          infoElem != NULL;
          infoElem = infoElem->NextSiblingElement()) {
        std::string elemName = infoElem->Value();
        if(infoElem->FirstChild() == NULL) {
          errStream << "XML PARTIAL IMPORT: <"
    				<< elemName <<  "> ... </" << elemName << "> is empty." << std::endl;
    			endResult = PartialImport;
          delete tram;
          deleted = true;
        }
        for(TiXmlNode* data = infoElem->FirstChild();
            data != NULL;
            data = data->NextSibling())
        {
          TiXmlText* text = data->ToText();
          if(text != NULL && !deleted) {
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
                else {
                  throw 2;
                }
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
              else if (elemName == "type") {
                std::string typeVal = text->Value();
                  if (typeVal == "PCC" || typeVal == "Albatros") {
                    tram->setType(typeVal);
                  }
                  else throw 4;
              }
              else if (elemName == "voertuigNr") {
                int nr = std::stoi(text->Value());
                if (nr >= 0)
                  tram->setVoertuigNr(nr);
                else throw 5;
              }
              else {
                errStream << "XML PARTIAL IMPORT:" << std::endl << "Expected:" << std::endl << "<lijnNr> ... </lijnNr> or" << std::endl <<
                "<zitplaatsen> ... </zitplaatsen> or" << std::endl << "<snelheid> ... </snelheid> or" << std::endl <<
                "<type> ... </type> or" << std::endl << "<voertuigNr> ... </voertuigNr> or" << std::endl << "<beginStation> ... </beginStation>" <<
                std::endl << "and got: <" << elemName << "> ... </" << elemName << ">." << std::endl;
              }
            }
            catch(int e) {
              switch (e) {
              case 0:
                delete tram;
                endResult = PartialImport;
                errStream << "XML PARTIAL IMPORT: Tram not created, negative line number: " << text->Value() << "." << std::endl;
                deleted = true;
                break;
              case 1:
                errStream << "XML PARTIAL IMPORT: Tram not created, negative number of seats: " << text->Value() << "." << std::endl;
                delete tram;
                endResult = PartialImport;
                deleted = true;
                break;
              case 2:
                errStream << "XML PARTIAL IMPORT: Tram not created, negative speed: " << text->Value() << "." << std::endl;
                delete tram;
                endResult = PartialImport;
                deleted = true;
                break;
              case 3:
                errStream << "XML PARTIAL IMPORT: BeginStation not found for tram " << tram->getLijnNr() << std::endl;
                delete tram;
                endResult = PartialImport;
                deleted = true;
                break;
              case 4:
                errStream << "XML PARTIAL IMPORT: Tram not created, tram type \"" << text->Value() << "\" not recognized." << std::endl;
                delete tram;
                endResult = PartialImport;
                deleted = true;
                break;
              case 5:
                errStream << "XML PARTIAL IMPORT: Tram not created, negative voertuigNr: " << text->Value() << "." << std::endl;
                delete tram;
                endResult = PartialImport;
                deleted = true;
                break;
              }
            }
            catch (std::invalid_argument& e) {
              if (elemName == "lijnNr") {
                delete tram;
                endResult = PartialImport;
                errStream << "XML PARTIAL IMPORT: Tram not created, invalid line number: " << text->Value() << "." << std::endl;
                deleted = true;
                break;
              }
              else if (elemName == "zitplaatsen") {
                delete tram;
                endResult = PartialImport;
                errStream << "XML PARTIAL IMPORT: Tram not created, invalid number of seats: " << text->Value() << "." << std::endl;
                deleted = true;
                break;
              }
              else if (elemName == "snelheid") {
                delete tram;
                endResult = PartialImport;
                errStream << "XML PARTIAL IMPORT: Tram not created, invalid speed: " << text->Value() << "." << std::endl;
                deleted = true;
                break;
              }
              else if (elemName == "voertuigNr") {
                delete tram;
                endResult = PartialImport;
                errStream << "XML PARTIAL IMPORT: Tram not created, invalid voertuigNr: " << text->Value() << "." << std::endl;
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

static SuccessEnum importPassengers(const char* inputfilename, std::ostream& errStream, MetroNet& metronet) {
  REQUIRE(metronet.properlyInitialized(), "metronet wasn't initialized when passed to MetroNetImporter::importPassengers");

	TiXmlDocument doc;
  SuccessEnum endResult = Success;

  if(!doc.LoadFile(inputfilename)) {
    errStream << "XML IMPORT ABORTED: " << doc.ErrorDesc() << std::endl;
    return ImportAborted;
  }

  for (TiXmlElement* passenger = doc.FirstChildElement();
  	passenger != NULL;
  	passenger = passenger->NextSiblingElement()) {

  	bool deleted = false;
		std::string rootName = passenger->Value();
  	if (rootName != "PASSAGIER") {
  		errStream << "XML PARTIAL IMPORT: Expected <PASSAGIER> ... </PASSAGIER> and got <"
        << rootName <<  "> ... </" << rootName << ">." << std::endl;
      endResult = PartialImport;
      continue;
  	}

  	Passagier* passagier = new Passagier;
  	TiXmlNode *naam, *beginStation, *eindStation, *hoeveelheid;
  	naam = passenger->FirstChild("naam");
  	beginStation = passenger->FirstChild("beginstation");
  	eindStation = passenger->FirstChild("eindstation");
  	hoeveelheid = passenger->FirstChild("hoeveelheid");
  	if (naam == NULL) {
  		errStream << "XML PARTIAL IMPORT: Expected <naam> ... </naam>." << std::endl;
      endResult = PartialImport;
      delete passagier;
      continue;
  	}
  	if (beginStation == NULL) {
  		errStream << "XML PARTIAL IMPORT: Expected <beginstation> ... </beginstation>." << std::endl;
      endResult = PartialImport;
      delete passagier;
      continue;
  	}
  	if (eindStation == NULL) {
  		errStream << "XML PARTIAL IMPORT: Expected <eindstation> ... </eindstation>." << std::endl;
      endResult = PartialImport;
      delete passagier;
      continue;
  	}
  	if (hoeveelheid == NULL) {
  		errStream << "XML PARTIAL IMPORT: Expected <hoeveelheid> ... </hoeveelheid>." << std::endl;
      endResult = PartialImport;
      delete passagier;
      continue;
  	}

  	for (TiXmlElement* infoElem = passenger->FirstChildElement();
      infoElem != NULL;
      infoElem = infoElem->NextSiblingElement()) {

      std::string elemName = infoElem->Value();
      if(infoElem->FirstChild() == NULL) {
        errStream << "XML PARTIAL IMPORT: <"
          << elemName <<  "> ... </" << elemName << "> is empty." << std::endl;
        endResult = PartialImport;
        delete passagier;
        deleted = true;
      }
      for (TiXmlNode* data = infoElem->FirstChild();
        data != NULL;
        data = data->NextSibling()) {

      	TiXmlText* text = data->ToText();
      	if (text == NULL || deleted)
      		continue;

      	if (elemName == "naam")
      		passagier->setNaam(text->Value());
      	else if (elemName == "beginstation")
      		passagier->setBeginStation(text->Value());
      	else if (elemName == "eindstation")
      		passagier->setEindStation(text->Value());
      	else if (elemName == "hoeveelheid") {
      		try {
      			int aantal = std::stoi(text->Value());
      			if (aantal >= 0)
      				passagier->setHoeveelheid(aantal);
      			else throw 0;
      		}
      		catch(int e) {
      			delete passagier;
            endResult = PartialImport;
            errStream << "XML PARTIAL IMPORT: Passagier not created, negative hoeveelheid: " << text->Value() << "." << std::endl;
            deleted = true;
            break;
      		}
      		catch (std::invalid_argument& e) {
            delete passagier;
            endResult = PartialImport;
            errStream << "XML PARTIAL IMPORT: Passagier not created, invalid hoeveelheid: " << text->Value() << "." << std::endl;
            deleted = true;
            break;
      		}
      	}
      	else {
          errStream << "XML PARTIAL IMPORT:" << std::endl << "Expected:" << std::endl << "<naam> ... </naam> or"
          << std::endl << "<beginstation> ... </beginstation> or" << std::endl << "<eindstation> ... </eindstation> or"
          << std::endl << "<hoeveelheid> ... </hoeveelheid> or" << std::endl << "and got: <"
          << elemName << "> ... </" << elemName << ">." << std::endl;
        }
      }
    }
    if (deleted) continue;
    metronet.addPassagier(passagier);
  }
  doc.Clear();
  ENSURE(metronet.isConsistent(), "MetroNet is not consistent");
  return endResult;
}
