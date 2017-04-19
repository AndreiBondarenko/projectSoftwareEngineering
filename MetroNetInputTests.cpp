#include <iostream>
#include <fstream>
#include <sys/stat.h>
#include <gtest/gtest.h>

#include "MetroNet.h"
#include "MetroNetUtils.h"
#include "MetroNetImporter.h"

class MetroNetInputTests: public ::testing::Test {
protected:
	friend class MetroNet;

	MetroNet metronet;	
};
/*
TEST_F(MetroNetInputTests, correctInput) {
	ASSERT_TRUE(DirectoryExists("_testOutput"));
	ASSERT_TRUE(DirectoryExists("_testInput"));
	ASSERT_TRUE(DirectoryExists("_testOutput/expected"));

	std::ofstream ofile, error;
	SuccessEnum importResult;

	ofile.open("_testInput/Input01.xml");
	ofile << "<?xml version=\"1.0\" ?>" << std::endl
		<< "<METRONET>\n\t<STATION>\n"
		<< "\t\t<naam>A</naam>\n\t\t<volgende>B</volgende>\n"
		<< "<vorige>C</vorige>\n\t\t<spoor>12</spoor>\n"
		<< "\t\t<opstappen>7</opstappen>\n"
		<< "\t</STATION>\n\t<STATION>\n"
		<< "\t\t<naam>B</naam>\n\t\t<volgende>C</volgende>\n"
		<< "<vorige>A</vorige>\n\t\t<spoor>12</spoor>\n"
		<< "\t\t<opstappen>10</opstappen>\n\t\t<afstappen>5</afstappen>\n"
		<< "\t</STATION>\n\t<STATION>\n"
		<< "\t\t<naam>C</naam>\n\t\t<volgende>A</volgende>\n"
		<< "<vorige>B</vorige>\n\t\t<spoor>12</spoor>\n"
		<< "\t</STATION>\n\t<TRAM>\n"
		<< "\t\t<lijnNr>12</lijnNr>\n\t\t<zitplaatsen>32</zitplaatsen>\n"
		<< "\t\t<snelheid>60</snelheid>\n\t\t<beginStation>A</beginStation>\n"
		<< "\t</TRAM>\n</METRONET>" << std::endl;
	ofile.close();
	ofile.open("_testOutput/Error01.txt");
	importResult = MetroNetImporter::importMetroNet("_testInput/Input01.xml", ofile, metronet);
	ofile.close();
	EXPECT_TRUE(importResult == Success);

	ofile.open("_testOutput/test01.txt");
	error.open("_testOutput//Error01.txt");
	metronet.movePassengers("A", 12, ofile, error);
	metronet.moveTram("B", 12, ofile);
	metronet.movePassengers("B", 12, ofile, error);
	metronet.moveTram("C", 12, ofile);
	ofile.close();
	error.close();
	EXPECT_TRUE(FileCompare("_testOutput/test01.txt", "_testOutput/expected/test01Expected.txt"));
	std::map<int, Tram*>* trams = metronet.getAlleTrams();
	Tram* tram = trams->find(12)->second;
	EXPECT_TRUE(tram->getPassagiers() == 12);
	EXPECT_TRUE(tram->getCurrentStation() == "C");
}

TEST_F(MetroNetInputTests, correctInput2) {
	ASSERT_TRUE(DirectoryExists("_testOutput"));
	ASSERT_TRUE(DirectoryExists("_testInput"));
	ASSERT_TRUE(DirectoryExists("_testOutput/expected"));

	std::ofstream ofile, error;
	SuccessEnum importResult;

	ofile.open("_testInput/Input07.xml");
	ofile << "<?xml version=\"1.0\" ?>" << std::endl
		<< "<METRONET>\n\t<STATION>\n"
		<< "\t\t<naam>A</naam>\n\t\t<volgende>B</volgende>\n"
		<< "<vorige>C</vorige>\n\t\t<spoor>12</spoor>\n"
		<< "\t\t<opstappen>7</opstappen>\n"
		<< "\t</STATION>\n\t<STATION>\n"
		<< "\t\t<naam>B</naam>\n\t\t<volgende>C</volgende>\n"
		<< "<vorige>A</vorige>\n\t\t<spoor>12</spoor>\n"
		<< "\t\t<opstappen>10</opstappen>\n\t\t<afstappen>5</afstappen>\n"
		<< "\t</STATION>\n\t<STATION>\n"
		<< "\t\t<naam>C</naam>\n\t\t<volgende>A</volgende>\n"
		<< "<vorige>B</vorige>\n\t\t<spoor>12</spoor>\n"
		<< "\t</STATION>\n\t<TRAM>\n"
		<< "\t\t<lijnNr>12</lijnNr>\n\t\t<zitplaatsen>32</zitplaatsen>\n"
		<< "\t\t<snelheid>60</snelheid>\n\t\t<beginStation>A</beginStation>\n"
		<< "\t</TRAM>\n</METRONET>" << std::endl;
	ofile.close();
	ofile.open("_testOutput/Error07.txt");
	importResult = MetroNetImporter::importMetroNet("_testInput/Input07.xml", ofile, metronet);
	ofile.close();
	EXPECT_TRUE(importResult == Success);

	ofile.open("_testOutput/test07.txt");
	error.open("_testOutput//Error07.txt");
	metronet.moveAllePassengers(ofile, error);
	metronet.moveAlleTrams(ofile);
	metronet.moveAllePassengers(ofile, error);
	metronet.moveAlleTrams(ofile);
	ofile.close();
	error.close();
	EXPECT_TRUE(FileCompare("_testOutput/test07.txt", "_testOutput/expected/test07Expected.txt"));
	std::map<int, Tram*>* trams = metronet.getAlleTrams();
	Tram* tram = trams->find(12)->second;
	EXPECT_TRUE(tram->getPassagiers() == 12);
	EXPECT_TRUE(tram->getCurrentStation() == "C");
}

// error : MERONET ipv METRONET
TEST_F(MetroNetInputTests, wrongSyntax) {
	ASSERT_TRUE(DirectoryExists("_testOutput"));
	ASSERT_TRUE(DirectoryExists("_testInput"));
	ASSERT_TRUE(DirectoryExists("_testOutput/expected"));

	std::ofstream ofile;
	SuccessEnum importResult;

	ofile.open("_testInput/Input02.xml");
	ofile << "<?xml version=\"1.0\" ?>" << std::endl
		<< "<MERONET>\n\t<STATION>\n"
		<< "\t\t<naam>A</naam>\n\t\t<volgende>B</volgende>\n"
		<< "\t\t<vorige>C</vorige>\n\t\t<spoor>12</spoor>\n"
		<< "\t\t<opstappen>7</opstappen>\n"
		<< "\t</STATION>\n\t<STATION>\n"
		<< "\t\t<naam>B</naam>\n\t\t<volgende>C</volgende>\n"
		<< "\t\t<vorige>A</vorige>\n\t\t<spoor>12</spoor>\n"
		<< "\t\t<opstappen>10</opstappen>\n\t\t<afstappen>5</afstappen>\n"
		<< "\t</STATION>\n\t<STATION>\n"
		<< "\t\t<naam>C</naam>\n\t\t<volgende>A</volgende>\n"
		<< "\t\t<vorige>B</vorige>\n\t\t<spoor>12</spoor>\n"
		<< "\t</STATION>\n\t<TRAM>\n"
		<< "\t\t<lijnNr>12</lijnNr>\n\t\t<zitplaatsen>32</zitplaatsen>\n"
		<< "\t\t<snelheid>60</snelheid>\n\t\t<beginStation>A</beginStation>\n"
		<< "\t</TRAM>\n</METRONET>" << std::endl;
	ofile.close();
	ofile.open("_testOutput/Error02.txt");
	importResult = MetroNetImporter::importMetroNet("_testInput/Input02.xml", ofile, metronet);
	ofile.close();
	EXPECT_TRUE(importResult == ImportAborted);
	EXPECT_TRUE(FileCompare("_testOutput/Error02.txt", "_testOutput/expected/Error02Expected.txt"));
}

// error : name is missing in station A, vorige is missing in station B
TEST_F(MetroNetInputTests, invalidInput) {
	ASSERT_TRUE(DirectoryExists("_testOutput"));
	ASSERT_TRUE(DirectoryExists("_testInput"));
	ASSERT_TRUE(DirectoryExists("_testOutput/expected"));

	std::ofstream ofile;

	ofile.open("_testInput/Input03.xml");
	ofile << "<?xml version=\"1.0\" ?>" << std::endl
		<< "<METRONET>\n\t<STATION>\n"
		<< "\t\t<volgende>B</volgende>\n"
		<< "\t\t<vorige>C</vorige>\n\t\t<spoor>12</spoor>\n"
		<< "\t\t<opstappen>7</opstappen>\n"
		<< "\t</STATION>\n\t<STATION>\n"
		<< "\t\t<naam>B</naam>\n\t\t<volgende>C</volgende>\n"
		<< "\t\t<spoor>12</spoor>\n"
		<< "\t\t<opstappen>10</opstappen>\n\t\t<afstappen>5</afstappen>\n"
		<< "\t</STATION>\n\t<STATION>\n"
		<< "\t\t<naam>C</naam>\n\t\t<volgende>A</volgende>\n"
		<< "\t\t<vorige>B</vorige>\n\t\t<spoor>12</spoor>\n"
		<< "\t</STATION>\n\t<TRAM>\n"
		<< "\t\t<lijnNr>12</lijnNr>\n\t\t<zitplaatsen>32</zitplaatsen>\n"
		<< "\t\t<snelheid>60</snelheid>\n\t\t<beginStation>A</beginStation>\n"
		<< "\t</TRAM>\n</METRONET>" << std::endl;
	ofile.close();
	ofile.open("_testOutput/Error03.txt");
	EXPECT_DEATH(MetroNetImporter::importMetroNet("_testInput/Input03.xml", ofile, metronet), 
		"MetroNet is inconsistent");
	ofile.close();
	EXPECT_TRUE(FileCompare("_testOutput/Error03.txt", "_testOutput/expected/Error03Expected.txt"));
}

// error : spoor missing in station D, still consistent metronet
TEST_F(MetroNetInputTests, invalidInput2) {
	ASSERT_TRUE(DirectoryExists("_testOutput"));
	ASSERT_TRUE(DirectoryExists("_testInput"));
	ASSERT_TRUE(DirectoryExists("_testOutput/expected"));

	std::ofstream ofile;
	SuccessEnum importResult;

	ofile.open("_testInput/Input04.xml");
	ofile << "<?xml version=\"1.0\" ?>" << std::endl
		<< "<METRONET>\n\t<STATION>\n"
		<< "\t\t<naam>A</naam>\n\t\t<volgende>B</volgende>\n"
		<< "\t\t<vorige>C</vorige>\n\t\t<spoor>12</spoor>\n"
		<< "\t\t<opstappen>7</opstappen>\n"
		<< "\t</STATION>\n\t<STATION>\n"
		<< "\t\t<naam>B</naam>\n\t\t<volgende>C</volgende>\n"
		<< "\t\t<vorige>A</vorige>\n\t\t<spoor>12</spoor>\n"
		<< "\t\t<opstappen>10</opstappen>\n\t\t<afstappen>5</afstappen>\n"
		<< "\t</STATION>\n\t<STATION>\n"
		<< "\t\t<naam>C</naam>\n\t\t<volgende>A</volgende>\n"
		<< "\t\t<vorige>B</vorige>\n\t\t<spoor>12</spoor>\n"
		<< "\t</STATION>\n\t<STATION>\n"
		<< "\t\t<naam>D</naam>\n\t\t<volgende>E</volgende>\n"
		<< "\t\t<vorige>F</vorige>\n"
		<< "\t</STATION>\n\t<TRAM>\n"
		<< "\t\t<lijnNr>12</lijnNr>\n\t\t<zitplaatsen>32</zitplaatsen>\n"
		<< "\t\t<snelheid>60</snelheid>\n\t\t<beginStation>A</beginStation>\n"
		<< "\t</TRAM>\n</METRONET>" << std::endl;
	ofile.close();
	ofile.open("_testOutput/Error04.txt");
	importResult = MetroNetImporter::importMetroNet("_testInput/Input04.xml", ofile, metronet);
	ofile.close();
	EXPECT_TRUE(importResult == PartialImport);
	EXPECT_TRUE(FileCompare("_testOutput/Error04.txt", "_testOutput/expected/Error04Expected.txt"));
}

// error : Tram 13 missing zitplaatsen
TEST_F(MetroNetInputTests, invalidInput3) {
	ASSERT_TRUE(DirectoryExists("_testOutput"));
	ASSERT_TRUE(DirectoryExists("_testInput"));
	ASSERT_TRUE(DirectoryExists("_testOutput/expected"));

	std::ofstream ofile;
	SuccessEnum importResult;

	ofile.open("_testInput/Input05.xml");
	ofile << "<?xml version=\"1.0\" ?>" << std::endl
		<< "<METRONET>\n\t<STATION>\n"
		<< "\t\t<naam>A</naam>\n\t\t<volgende>B</volgende>\n"
		<< "\t\t<vorige>C</vorige>\n\t\t<spoor>12</spoor>\n"
		<< "\t\t<opstappen>7</opstappen>\n"
		<< "\t</STATION>\n\t<STATION>\n"
		<< "\t\t<naam>B</naam>\n\t\t<volgende>C</volgende>\n"
		<< "\t\t<vorige>A</vorige>\n\t\t<spoor>12</spoor>\n"
		<< "\t\t<opstappen>10</opstappen>\n\t\t<afstappen>5</afstappen>\n"
		<< "\t</STATION>\n\t<STATION>\n"
		<< "\t\t<naam>C</naam>\n\t\t<volgende>A</volgende>\n"
		<< "\t\t<vorige>B</vorige>\n\t\t<spoor>12</spoor>\n"
		<< "\t</STATION>\n\t<TRAM>\n"
		<< "\t\t<lijnNr>12</lijnNr>\n\t\t<zitplaatsen>32</zitplaatsen>\n"
		<< "\t\t<snelheid>60</snelheid>\n\t\t<beginStation>A</beginStation>\n"
		<< "\t</TRAM>\n\t<TRAM>\n"
		<< "\t\t<lijnNr>13</lijnNr>\n"
		<< "\t\t<snelheid>60</snelheid>\n\t\t<beginStation>A</beginStation>\n"
		<< "\t</TRAM>\n</METRONET>" << std::endl;
	ofile.close();
	ofile.open("_testOutput/Error05.txt");
	importResult = MetroNetImporter::importMetroNet("_testInput/Input05.xml", ofile, metronet);
	ofile.close();
	EXPECT_TRUE(importResult == PartialImport);
	EXPECT_TRUE(FileCompare("_testOutput/Error05.txt", "_testOutput/expected/Error05Expected.txt"));
}

// error : Tram 13 missing negative snelheid
TEST_F(MetroNetInputTests, invalidInput4) {
	ASSERT_TRUE(DirectoryExists("_testOutput"));
	ASSERT_TRUE(DirectoryExists("_testInput"));
	ASSERT_TRUE(DirectoryExists("_testOutput/expected"));

	std::ofstream ofile;
	SuccessEnum importResult;

	ofile.open("_testInput/Input06.xml");
	ofile << "<?xml version=\"1.0\" ?>" << std::endl
		<< "<METRONET>\n\t<STATION>\n"
		<< "\t\t<naam>A</naam>\n\t\t<volgende>B</volgende>\n"
		<< "\t\t<vorige>C</vorige>\n\t\t<spoor>12</spoor>\n"
		<< "\t\t<opstappen>7</opstappen>\n"
		<< "\t</STATION>\n\t<STATION>\n"
		<< "\t\t<naam>B</naam>\n\t\t<volgende>C</volgende>\n"
		<< "\t\t<vorige>A</vorige>\n\t\t<spoor>12</spoor>\n"
		<< "\t\t<opstappen>10</opstappen>\n\t\t<afstappen>5</afstappen>\n"
		<< "\t</STATION>\n\t<STATION>\n"
		<< "\t\t<naam>C</naam>\n\t\t<volgende>A</volgende>\n"
		<< "\t\t<vorige>B</vorige>\n\t\t<spoor>12</spoor>\n"
		<< "\t</STATION>\n\t<TRAM>\n"
		<< "\t\t<lijnNr>12</lijnNr>\n\t\t<zitplaatsen>32</zitplaatsen>\n"
		<< "\t\t<snelheid>60</snelheid>\n\t\t<beginStation>A</beginStation>\n"
		<< "\t</TRAM>\n\t<TRAM>\n"
		<< "\t\t<lijnNr>13</lijnNr>\n\t\t<zitplaatsen>32</zitplaatsen>\n"
		<< "\t\t<snelheid>-60</snelheid>\n\t\t<beginStation>A</beginStation>\n"
		<< "\t</TRAM>\n</METRONET>" << std::endl;
	ofile.close();
	ofile.open("_testOutput/Error06.txt");
	importResult = MetroNetImporter::importMetroNet("_testInput/Input06.xml", ofile, metronet);
	ofile.close();
	EXPECT_TRUE(importResult == PartialImport);
	EXPECT_TRUE(FileCompare("_testOutput/Error06.txt", "_testOutput/expected/Error06Expected.txt"));
}
*/