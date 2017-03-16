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

TEST_F(MetroNetInputTests, correctInput) {
	ASSERT_TRUE(DirectoryExists("_testOutput"));
	ASSERT_TRUE(DirectoryExists("_testInput"));

	std::ofstream ofile;
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
	metronet.movePassengers("A", 12, ofile);
	metronet.moveTram("B", 12, ofile);
	metronet.movePassengers("B", 12, ofile);
	metronet.moveTram("C", 12, ofile);
	ofile.close();
	EXPECT_TRUE(FileCompare("_testOutput/test01.txt", "_testOutput/test01Expected.txt"));
	std::map<int, Tram*>* trams = metronet.getAlleTrams();
	Tram* tram = trams->find(12)->second;
	EXPECT_TRUE(tram->getPassagiers() == 12);
}