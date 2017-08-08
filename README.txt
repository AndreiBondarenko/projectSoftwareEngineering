This reposityory was used for development of our project for the course "Project Software Engineering", during our second semester at the University of Antwerp.
The course is taught by: Prof. Dr. Serge Demeyer and Brent van Bladel
During this course we learned the following:
-important aspects of object oriented programming and good design
-developing software that is easy to adapt to future additions and changes to the specifiaction
-estimating the amount of work we could finish within the given timeframe
-an introduction on using the Google Test Framework

A .pdf-file of the final specification (dutch) can be found in the root of this repository

Project Software Engineering 2.1 - Final
door Andrei Bondarenko en Igor Schittekat

Klassendocumentatie te vinden in de 'documentation'-map

GEBRUIKSAANWIJZINGEN:

(0. Voer make uit in huidige map)
1. Plaats alle .xml-files van het metronet dat u wilt simuleren in de '_input'-map

2. Het programma kan 'live' en 'non-live' worden uitgevoerd:
- 'live': Alle output wordt naar de terminal geschreven, deze modus biedt ook enkel interactiemogelijkheden
- 'non-live': Het programma wordt zonder onderbrekingen uitgevoerd en alle output wordt naar de juiste bestanden in de '_output'-map geschreven

3. Men roept het programma aan door in de huidige map './MetroNetMain' uit te voeren met:
- als eerste argument het .xml-bestand van het metronet
- als tweede argument het .xml-bestand met de passagiers
e.g. ./MetroNetMain demoMetronet.xml demoPassagiers.xml
Indien men de simulatie live wilt uitvoeren moet men enkel een '-l'-tag aan het einde van het commando toevoegen.
e.g. ./MetroNetMain demoMetronet.xml demoPassagiers.xml -l

4. Indien men de testen wilt laten uitvoeren, moet men volgend commando uitvoeren:
./MetroNetTests
