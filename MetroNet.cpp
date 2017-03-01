//
//  MetroNet.cpp
//  projectSoftwareEngineering
//
//  Created by Andrei Bondarenko on 17/02/2017.
//
//

#include "MetroNet.h"
#include "tinyxml.h"
#include "DesignByContract.h"
#include <iostream>
#include <fstream>
#include <stdexcept>

MetroNet::MetroNet()  {
  initCheck = this;
  ENSURE(properlyInitialized(),
    "constructor must end in properlyInitialized state");
}
MetroNet::~MetroNet() {
  for(auto it = alleStations.begin(); it != alleStations.end(); ++it) {
      delete it->second;
  }
  for(auto it = alleTrams.begin(); it != alleTrams.end(); ++it) {
      delete it->second;
  }
  alleStations.clear();
  alleTrams.clear();
  alleSporen.clear();
}

bool MetroNet::properlyInitialized() const {
  return initCheck == this;
}

bool MetroNet::isConsistent() const {
  REQUIRE(properlyInitialized(),
    "MetroNet wasn't initialized when calling isConsistent");
  // elk station is verbonden met een voorgaand en een volgend station
  // voor elk spoor
  for(auto mapIt = alleStations.begin(); mapIt != alleStations.end(); ++mapIt) {
    std::string vorige = mapIt->second->getVorige();
    std::string volgende = mapIt->second->getVolgende();
    if (alleStations.find(vorige) == alleStations.end() ||
        alleStations.find(volgende) == alleStations.end()) {
      return false;
    }
  }
  // er bestaan geen trams met een lijn nummer dat niet overeenkomt met een
  // spoor in een station
  // het beginstation van een tram een geldig station in het metronet is
  for(auto mapIt = alleTrams.begin(); mapIt != alleTrams.end(); ++mapIt) {
    unsigned int lijnNr = mapIt->second->getLijnNr();
    std::string beginStation = mapIt->second->getBeginStation();
    if (alleSporen.find(lijnNr) == alleSporen.end()) {
      return false;
    }
    if (alleStations.find(beginStation) == alleStations.end()) {
      return false;
    }
  }
  // er geen sporen zijn waarvoor geen tram bestaat
  for(auto setIt = alleSporen.begin(); setIt != alleSporen.end(); ++setIt) {
    unsigned int spoor = *setIt;
    if (alleTrams.find(spoor) == alleTrams.end()) {
      return false;
    }
  }
  // elk spoor maximaal een keer door elk station komt ???????????????????????
  return true;
}

std::map<std::string, Station*>* MetroNet::getAlleStations() {
  REQUIRE(properlyInitialized(),
    "MetroNet wasn't initialized when calling getAlleStations");
  return &alleStations;
}

std::map<int, Tram*>* MetroNet::getAlleTrams() {
  REQUIRE(properlyInitialized(),
    "MetroNet wasn't initialized when calling getAlleTrams");
  return &alleTrams;
}

std::set<unsigned int>* MetroNet::getAlleSporen() {
  REQUIRE(properlyInitialized(),
    "MetroNet wasn't initialized when calling getAlleSporen");
  return &alleSporen;
}

void MetroNet::setAlleStations(std::map<std::string, Station*>& newAlleStations) {
  REQUIRE(properlyInitialized(),
    "MetroNet wasn't initialized when calling setAlleStations");
  alleStations = newAlleStations;
  ENSURE(*getAlleStations() == newAlleStations,
    "setAlleStations post condition failure");
}

void MetroNet::setAlleTrams(std::map<int, Tram*>& newAlleTrams) {
  REQUIRE(properlyInitialized(),
    "MetroNet wasn't initialized when calling setAlleTrams");
  alleTrams = newAlleTrams;
  ENSURE(*getAlleTrams() == newAlleTrams,
    "setAlleTrams post condition failure");
}

void MetroNet::setAlleSporen(std::set<unsigned int>& newAlleSporen) {
  REQUIRE(properlyInitialized(),
    "MetroNet wasn't initialized when calling setAlleSporen");
  alleSporen = newAlleSporen;
  ENSURE(*getAlleSporen() == newAlleSporen,
    "setAlleSporen post condition failure");
}

void MetroNet::addStation(Station* newStation) {
  REQUIRE(properlyInitialized(),
    "MetroNet wasn't initialized when calling addStation");
  REQUIRE(getAlleStations()->count(newStation->getNaam()) == 0,
    "This MetroNet already contains a station with this name");
  alleSporen.insert(newStation->getSpoor());
  alleStations[newStation->getNaam()] = newStation;
  ENSURE(getAlleStations()->at(newStation->getNaam()) == newStation,
    "addStation post condition failure");
}

void MetroNet::removeStation(const std::string& stationName) {
  REQUIRE(properlyInitialized(),
    "MetroNet wasn't initialized when calling removeStation");
  REQUIRE(getAlleStations()->count(stationName) == 1,
    "This MetroNet doesn't contain a station with this name");
  alleStations.erase(stationName);
  ENSURE(getAlleStations()->count(stationName) == 0,
    "removeStation post condition failure");
}

void MetroNet::addTram(Tram* newTram) {
  REQUIRE(properlyInitialized(),
    "MetroNet wasn't initialized when calling addTram");
  REQUIRE(getAlleTrams()->count(newTram->getLijnNr()) == 0,
    "This MetroNet already contains a Tram with this lijnNr");
  alleTrams[newTram->getLijnNr()] = newTram;
  ENSURE(getAlleTrams()->at(newTram->getLijnNr()) == newTram,
    "addTram post condition failure");
}

void MetroNet::removeTram(const unsigned int lijnNr) {
  REQUIRE(properlyInitialized(),
    "MetroNet wasn't initialized when calling removeTram");
  REQUIRE(getAlleTrams()->count(lijnNr) == 1,
    "This MetroNet doesn't contain a tram with this lijnNr");
  alleTrams.erase(lijnNr);
  ENSURE(getAlleTrams()->count(lijnNr) == 0,
    "removeTram post condition failure");
}

void MetroNet::moveTrams() {
  REQUIRE(properlyInitialized(),
    "MetroNet wasn't initialized when calling moveTrams");
  for(auto mapIt = getAlleTrams()->begin(); mapIt != getAlleTrams()->end(); ++mapIt) {
    std::string previousStation = mapIt->second->getCurrentStation();
    std::string nextStation = getAlleStations()->at(previousStation)->getVolgende();
    unsigned int lijnNr = mapIt->second->getLijnNr();
    mapIt->second->setCurrentStation(nextStation);
    getAlleStations()->at(nextStation)->setTramInStation(lijnNr);
    ENSURE(mapIt->second->getCurrentStation() != previousStation,
      "moveTrams post condition failure");
    ENSURE(lijnNr == getAlleStations()->at(nextStation)->getTramInStation(),
      "moveTrams post condition failure");
    std::cout << "Tram " << mapIt->second->getLijnNr() << " reed van station "
              << previousStation << " naar station " << nextStation << ".\n";
  }
}

MetroNet* MetroNet::initializeFromFile(const char* file) {

  TiXmlDocument doc;
  if(!doc.LoadFile(file)) {
    std::cerr << doc.ErrorDesc() << std::endl;
  }

  TiXmlElement* net = doc.FirstChildElement();
  if(net == NULL) {
    std::cerr << "Failed to load file: No root element." << std::endl;
    doc.Clear();
  }

  MetroNet* result = new MetroNet;
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
                std::cerr << "\nStation not created, negative rail: " << text->Value() << ".\n" << std::endl;
                deleted = true;
                break;
              }
              catch (std::invalid_argument& e) {
                delete station;
                std::cerr << "\nStation not created, invalid rail: " << text->Value() << ".\n" << std::endl;
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
                std::cerr << "\nStation not created, negative opstappen: " << text->Value() << ".\n" << std::endl;
                deleted = true;
                break;
              }
              catch (std::invalid_argument& e) {
                delete station;
                std::cerr << "\nStation not created, invalid opstappen: " << text->Value() << ".\n" << std::endl;
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
                std::cerr << "\nStation not created, negative afstappen: " << text->Value() << ".\n" << std::endl;
                deleted = true;
                break;
              }
              catch (std::invalid_argument& e) {
                delete station;
                std::cerr << "\nStation not created, invalid afstappen: " << text->Value() << ".\n" << std::endl;
                deleted = true;
                break;
              }
            }
          }
        }
      }
      if (deleted) break;
      result->addStation(station);
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
                result->getAlleStations()->at(value)
                                          ->setTramInStation(tram->getLijnNr());
              }
            }
            catch(int e) {
              switch (e) {
              case 0:
                delete tram;
                std::cerr << "\nTram not created, negative line number: " << text->Value() << ".\n" << std::endl;
                deleted = true;
                break;
              case 1:
                delete tram;
                std::cerr << "\nTram not created, negative number of seats: " << text->Value() << ".\n" << std::endl;
                deleted = true;
                break;
              case 2:
                delete tram;
                std::cerr << "\nTram not created, negative speed: " << text->Value() << ".\n" << std::endl;
                deleted = true;
                break;
              }
              break;
            }
            catch (std::invalid_argument& e) {
              if (elemName == "lijnNr") {
                delete tram;
                std::cerr << "\nTram not created, invalid line number: " << text->Value() << ".\n" << std::endl;
                deleted = true;
                break;
              }
              else if (elemName == "zitplaatsen") {
                delete tram;
                std::cerr << "\nTram not created, invalid number of seats: " << text->Value() << ".\n" << std::endl;
                deleted = true;
                break;
              }
              else if (elemName == "snelheid") {
                delete tram;
                std::cerr << "\nTram not created, invalid speed: " << text->Value() << ".\n" << std::endl;
                deleted = true;
                break;
              }
            }
          }
        }
      }
      if (deleted) break;
      result->addTram(tram);
    }
    else {
      std::cout << "Element of type: " << elementType << " unsupported\n";
    }
  }
  doc.Clear();
  ENSURE(result->isConsistent(), "MetroNet is inconsistent");
  return result;
}

void MetroNet::writeToFile() {
  std::ofstream metroNetTXT;
  metroNetTXT.open ("_output/MetroNet.txt");
  for(auto mapIt = getAlleStations()->begin();
      mapIt != getAlleStations()->end();
      ++mapIt)
  {
    metroNetTXT << "Station " << mapIt->second->getNaam() << std::endl;
    metroNetTXT << "<- Station " << mapIt->second->getVorige() << std::endl;
    metroNetTXT << "-> Station " << mapIt->second->getVolgende() << std::endl;

    unsigned int spoor = mapIt->second->getSpoor();
    metroNetTXT << "Spoor " << spoor
                << ", "     << (getAlleTrams()->at(spoor))->getZitplaatsen()
                << " zitplaatsen\n\n";
  }
  metroNetTXT.close();
}
