#include "../headers/caveDB.h"
#include <stdlib.h>
#include "../headers/catch.hpp"
#include <filesystem>

namespace fs = std::filesystem;

TEST_CASE("create a new database", "[createDB]") {
	// should be able to create a new database from scratch

	SECTION("Default settings") {
		std::string dbName("testDB");
		caveDB db = caveDB::createDB(dbName, "C:/dev/cavedb");

		//this should create index and db files
		REQUIRE(fs::is_regular_file(fs::status(db.getIndexFilePath())));
		REQUIRE(fs::is_regular_file(fs::status(db.getDbFilePath())));

		db.destroyDB();
		//now the files must be deleted
		REQUIRE(fs::exists(fs::status(db.getIndexFilePath())));
		REQUIRE(fs::exists(fs::status(db.getDbFilePath())));
	}
}

TEST_CASE("read existing database", "[createDB]") {
	// should be able to create a new database from scratch

	SECTION("Default settings") {
		std::string dbName("testDB");
		caveDB db = caveDB::createDB(dbName, "C:/dev/cavedb");

		caveDB db2 = caveDB::loadDB(dbName, "C:/dev/cavedb");

		//this should create index and db files
		REQUIRE(fs::is_regular_file(fs::status(db.getIndexFilePath())));
		REQUIRE(fs::is_regular_file(fs::status(db.getDbFilePath())));

		db2.destroyDB();
		//now the files must be deleted
		REQUIRE(fs::exists(fs::status(db.getIndexFilePath())));
		REQUIRE(fs::exists(fs::status(db.getDbFilePath())));
	}
}
