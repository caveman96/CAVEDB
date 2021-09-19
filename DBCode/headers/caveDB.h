#pragma once
#include <string>
#include <unordered_map>

class caveDB {
	std::unordered_map < std::string, long> index;
	std::string dbName;
	std::string dbFolderPath;
	std::string dbFilePath;
	std::string indexFilePath;

public:
	static caveDB createDB(std::string dbName, std::string dbPath);
	static caveDB loadDB(std::string dbName, std::string dbPath);
	static caveDB loadOrCreateDB(std::string dbName, std::string dbPath);

	caveDB(std::string dbName, std::string dbFolderPath, std::string dbFilePath, std::string indexFilePath);

	std::string getIndexFilePath();
	std::string getDbFilePath();

	std::string getRecord(std::string id);
	std::unordered_map<std::string, std::string> getAllRecords();
	void putRecord(std::string id, std::string record);

	void destroyDB();

};
