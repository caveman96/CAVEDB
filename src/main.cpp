#include "../headers/caveDB.h"

#include <iostream>


void printMap(std::unordered_map <std::string, std::string> const& a) {
	std::cout << "The DB elements are : ";

	for (auto kv: a)
		std::cout <<std::endl<< kv.first << " - " << kv.second<<std::endl;
}

int main() {
	std::string dbname, dbPath;
	std::cout << "Enter the DB name: ";
	std::cin >> dbname;
	std::cout << "Enter the root location: ";
	std::cin >> dbPath;
	caveDB db = caveDB::loadOrCreateDB(dbname, dbPath);
	short choice;
	bool keepgoing = true;
	while (keepgoing) {

		std::cout << "\nSelect operation" << std::endl;
		std::cout << "1. Read all from DB\n2. Read one from DB\n3. Insert into DB\n4. Exit\n";
		std::cin>>choice;

		switch (choice) {
		case 1: {
			std::vector<std::string> records;
			printMap(db.getAllRecords());
			break;
		}
		case 2: {
			std::string id;
			std::cout << "enter the id: ";
			std::cin >> id;
			try {
				std::cout << "Data- " << db.getRecord(id);
			}
			catch (...) {
				std::cout << "No Value found";
			}
			break;
		}
		case 3: {
			std::string id, data;
			std::cout << "enter the id: ";
			std::cin >> id;
			std::cout << "enter the data: ";
			std::cin.ignore(256, '\n');
			std::getline(std::cin, data, '\n');
			db.putRecord(id, data);
			std::cout << "Done" << std::endl;
			break;
		}
		case 4: {
			keepgoing = false;
			break;
		}
		default: std::cout << "Invalid input, try again";
		}
	}
}

