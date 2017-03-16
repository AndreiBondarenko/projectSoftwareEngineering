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
	ASSERT_TRUE(DirectoryExists("_tests"));

	std::ofstream ofile;
	SuccessEnum importResult;

	ofile.open("_tests/Input01.xml");
	ofile << "<?xml version=\"1.0\" ?>" << std::endl
		<< "<METRONET>" << std::endl
		<< "\t<STATION>" << std::endl
		<< "\t\t<naam>A</naam>" << std::endl
		<< "\t</STATION>" << std::endl
		<< "</METRONET>" << std::endl;
	ofile.close();
	ofile.open("_tests/Error01.txt");
	importResult = MetroNetImporter::importMetroNet("_tests/Input01.xml", ofile, metronet);
	ofile.close();
	EXPECT_TRUE(importResult == PartialImport);

}