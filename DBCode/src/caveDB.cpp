
#include "../headers/caveDB.h"
#include "../headers/storage.h"
#include <iostream>
#include <map>
#include <cstdlib>
#include <direct.h>
#include <string.h>
#include <filesystem>
#include <fstream>

#pragma warning(disable: 4996)

namespace fs = std::filesystem;

caveDB caveDB::loadOrCreateDB(std::string dbName, std::string dbPath) {
	try {
		return caveDB::loadDB(dbName, dbPath);
	}
	catch (...) {
		return caveDB::createDB(dbName, dbPath);
	}
};


caveDB caveDB::createDB(std::string dbName, std::string dbPath) {

	//get root directory path from env and create folder
	std::string folderPath = dbPath + "/" + dbName;
	store::makeDir(folderPath);
	//create filenames for db and index file
	std::string dbFilePath = folderPath +"/"+ dbName + ".db";
	std::string indexFilePath = folderPath + "/" + dbName + ".index";
	//make the two files by opening and closing filestreams
	std::ofstream fil(indexFilePath.c_str());
	fil.close();
	fil.open(dbFilePath.c_str());
	fil.close();
	//create and return instance of the DB setting the created strings 
	return caveDB(dbName, folderPath, dbFilePath, indexFilePath);
};

caveDB caveDB::loadDB(std::string dbName, std::string dbPath) {

	std::string folderPath = dbPath + "/" + dbName;
	if (fs::is_directory(folderPath)) {
		std::string dbFilePath = folderPath + "/" + dbName + ".db";
		std::string indexFilePath = folderPath + "/" + dbName + ".index";
		if (fs::exists(dbFilePath) && fs::exists(indexFilePath)) {
			return caveDB(dbName, folderPath, dbFilePath, indexFilePath);
		}
	}
	throw std::runtime_error("Loading DB failed");

};

std::string caveDB::getRecord(std::string id) {
	if (index.find(id) == index.end()) {
		throw std::runtime_error("no value found");
	}
	return store::readfromDB(this->dbFilePath, index[id]);
};

void caveDB::putRecord(std::string id, std::string record) {
	long pos = store::writeToDB(this->dbFilePath, record);
	index[id] = pos;
	store::writeToIndex(this->indexFilePath, id, pos);
};

std::string caveDB::getIndexFilePath() {
	return this->indexFilePath;
}

std::string caveDB::getDbFilePath() {
	return this->dbFilePath;
};

caveDB::caveDB(std::string dbName, std::string dbFolderPath, std::string dbFilePath, std::string indexFilePath) {
	this->dbFolderPath = dbFolderPath;
	this->dbName = dbName;
	this->dbFilePath = dbFilePath;
	this->indexFilePath = indexFilePath;
	store::loadIndex(indexFilePath, this->index);
};

std::unordered_map<std::string, std::string> caveDB::getAllRecords() {
	std::unordered_map<std::string, std::string> output;
	for (auto kv : this->index) {
		output[kv.first] = store::readfromDB(this->dbFilePath,kv.second);
	}
	return output;
}

void caveDB::destroyDB() {
	store::deleteFolder(this->dbFolderPath);
}
