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

	virtual void SetUp() {
		metronet = new MetroNet();
	}

	MetroNet* metronet;	
};

TEST_F(MetroNetInputTests, InputHappyDay) {
	ASSERT_TRUE(DirectoryExists("_testInput"));

	std::ofstream ofile;
	SuccessEnum importResult;

	ofile.open("_testInput/correctInput.xml");
	ofile << "<?xml version=\"1.0\" ?>" << std::endl
		<< "<METRONET>\n\t<STATION>\n"
		<< "\t\t<naam>A</naam>\n\t\t<type>Metrostation</type>\n"
		<< "\t\t<SPOOR>\n\t\t\t<spoor>12</spoor>\n"
		<< "\t\t\t<volgende>B</volgende>\n\t\t\t<vorige>B</vorige>\n"
		<< "\t\t</SPOOR>\n\t</STATION>\n\t<STATION>\n"
		<< "\t\t<naam>B</naam>\n\t\t<type>Halte</type>\n"
		<< "\t\t<SPOOR>\n\t\t\t<spoor>12</spoor>\n"
		<< "\t\t\t<volgende>A</volgende>\n\t\t\t<vorige>A</vorige>\n"
		<< "\t\t</SPOOR>\n\t</STATION>\n\t<TRAM>\n"
		<< "\t\t<lijnNr>12</lijnNr>\n\t\t<zitplaatsen>32</zitplaatsen>\n"
		<< "\t\t<snelheid>60</snelheid>\n\t\t<beginStation>A</beginStation>\n"
		<< "\t\t<type>PCC</type>\n\t\t<voertuigNr>1</voertuigNr>\n"
		<< "\t</TRAM>\n</METRONET>" << std::endl;
	ofile.close();
	ofile.open("_testInput/zzzError.txt");
	importResult = MetroNetImporter::importMetroNet("_testInput/correctInput.xml", ofile, *metronet);
	ofile.close();
	EXPECT_TRUE(importResult == Success);
	EXPECT_TRUE(FileIsEmpty("_testInput/zzzError.txt"));
}

TEST_F(MetroNetInputTests, correctInput) {
	ASSERT_TRUE(DirectoryExists("_testInput"));

	std::ofstream ofile;
	SuccessEnum importResult;
	int fileCounter = 1;
	std::string fileName = "_testInput/correctInput" + std::to_string(fileCounter) + ".xml";

	while (FileExists(fileName)) {
		ofile.open("_testInput/zzzError.txt");
		importResult = MetroNetImporter::importMetroNet(fileName.c_str(), ofile, *metronet);
		ofile.close();
		EXPECT_TRUE(importResult == Success);
		EXPECT_TRUE(FileIsEmpty("_testInput/zzzError.txt"));

		fileCounter++;
		fileName = "_testInput/correctInput" + std::to_string(fileCounter) + ".xml";
	}
	EXPECT_TRUE(fileCounter == 2);
}

TEST_F(MetroNetInputTests, wrongInputSyntaxError) {
	ASSERT_TRUE(DirectoryExists("_testInput"));
	ASSERT_TRUE(DirectoryExists("_testInput/expected"));

	std::ofstream ofile;
	SuccessEnum importResult;
	int fileCounter = 1;
	std::string fileName = "_testInput/syntaxErrorInput" + std::to_string(fileCounter) + ".xml";

	while (FileExists(fileName)) {
		ofile.open("_testInput/zzzError.txt");
		importResult = MetroNetImporter::importMetroNet(fileName.c_str(), ofile, *metronet);
		ofile.close();
		EXPECT_TRUE(importResult == ImportAborted);
		std::string expectedFileName = "_testInput/expected/syntaxError" + std::to_string(fileCounter) + ".txt";
		EXPECT_TRUE(FileCompare("_testInput/zzzError.txt", expectedFileName));

		fileCounter++;
		fileName = "_testInput/syntaxErrorInput" + std::to_string(fileCounter) + ".xml";
	}
	EXPECT_TRUE(fileCounter == 6);
}

TEST_F(MetroNetInputTests, wrongInput) {
	ASSERT_TRUE(DirectoryExists("_testInput"));
	ASSERT_TRUE(DirectoryExists("_testInput/expected"));

	std::ofstream ofile;
	SuccessEnum importResult;
	int fileCounter = 1;
	std::string fileName = "_testInput/wrongInput" + std::to_string(fileCounter) + ".xml";

	while (FileExists(fileName)) {
		SetUp();
		ofile.open("_testInput/zzzError.txt");
		importResult = MetroNetImporter::importMetroNet(fileName.c_str(), ofile, *metronet);
		ofile.close();
		EXPECT_TRUE(importResult == PartialImport);
		std::string expectedFileName = "_testInput/expected/wrongInput" + std::to_string(fileCounter) + ".txt";
		EXPECT_TRUE(FileCompare("_testInput/zzzError.txt", expectedFileName));

		fileCounter++;
		fileName = "_testInput/wrongInput" + std::to_string(fileCounter) + ".xml";
	}
	// EXPECT_TRUE(fileCounter == 6);
}

