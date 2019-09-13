// MHW Armor Tool.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <fstream>
#include <typeinfo>

#include "ArmorSearch.h"

using jsonVector = std::vector<Json::Value>;

Json::Value armorJson;

int main()
{
	std::ifstream file("armors.json", std::ifstream::binary);

	file >> armorJson;

	ArmorSearch seeker(armorJson);

	jsonVector armorList;

	string type = "arms";

	seeker.searchByType(armorList, type);

	Json::Value leatherHelmDef = armorJson["armors"][0]["defense_values"];

	// Use idea here for adding skills and materials to list
	for (Json::Value::iterator it = leatherHelmDef.begin(); it != leatherHelmDef.end(); ++it) {
		std::cout << it.key() << std::endl;
	}

	seeker.~ArmorSearch();
	file.close();

	return 0;
}
