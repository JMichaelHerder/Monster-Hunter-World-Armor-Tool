#include "ArmorSearch.h"

// Constructor
ArmorSearch::ArmorSearch(Json::Value& const root) {
	armorJson = new Json::Value;
	this->armorJson = &root;
}

// Copy Constructor
ArmorSearch::ArmorSearch(const ArmorSearch& other) {
	armorJson = new Json::Value;
	*armorJson = *other.armorJson;
}

// Move Constructor
ArmorSearch::ArmorSearch(ArmorSearch&& other) : armorJson(other.armorJson) {
	other.armorJson = nullptr;
}

// Copy Assignment
ArmorSearch& ArmorSearch::operator=(const ArmorSearch& other) {
	if (&other == this) {
		return *this;
	}

	delete armorJson;

	armorJson = new Json::Value;
	*armorJson = *other.armorJson;

	return *this;
}

// Move Assignment
ArmorSearch& ArmorSearch::operator=(ArmorSearch&& other) {
	if (&other == this) {
		return *this;
	}

	delete armorJson;

	armorJson = other.armorJson;
	other.armorJson = nullptr;

	return *this;
}

//Destructor
ArmorSearch::~ArmorSearch(){
	armorJson->~Value();
}

/**
* Searches JSON for armors matching provided skill. (use DDL with text input to find skill)
*
* TODO: Change so that skill is found in menu rather than searched for
*
* @param resultList - List to populate with matching armors
* @param skillName - Name of skill to check against skills in JSON
*/
void ArmorSearch::searchBySkill(std::vector<Json::Value>& resultList, string& skillName) {
	// Checks if skillName is correct format:
	//		- Hyphens, forward-slashes, and spaces only allowed between strings of alphabetic characters
	//		- Disallows multiple spaces, hyphens, and forward-slashes
	if (std::regex_match(skillName, std::regex("^[[:alpha:]]([-/ ]?[[:alpha:]]+)*"))) {
		resultList.clear();

		// Reformats skill name to enable case-insensitive search
		for (int i = 0; i < skillName.length(); i++) {
			if (i == 0 || !isalpha(skillName.at(i - 1))) {
				skillName[i] = toupper(skillName.at(i)); // Capitalizes first letter of each word
			}
			else if (isalpha(skillName.at(i))) {
				skillName[i] = tolower(skillName.at(i)); // Makes all other characters lowercase, ignoring special characters
			}
		}

		// Use reformatted skill name to find matching armors
		for (auto const& armor : (*armorJson)["armors"]) {
			if (armor["skills"].isMember(skillName)) {
				resultList.push_back(armor);
			}
		}
	}
	else {
		std::cout << "Incorrect skill name format." << std::endl;
	}
}

/**
* Searches JSON for armors matching provided name. 
*
* TODO: Change so that name is searched using "string contains" function rather than specific regex_match
*
* @param resultList - List to populate with matching armors
* @param armorName - Name of armor to check against "name_en" field in JSON
*/
void ArmorSearch::searchByName(std::vector<Json::Value>& resultList, string& armorName) {
	// Checks if skillName is correct format:
	//		- Apostrophes and spaces only allowed between strings of alphabetic characters
	//		- Disallows multiple spaces and apostrophes
	if (std::regex_match(armorName, std::regex("^[[:alpha:]]([' ]?[[:alpha:]]+)*"))) {
		resultList.clear();

		// Reformats armor name to enable case-insensitive search
		for (int i = 0; i < armorName.length(); i++) {
			if (i == 0 || (armorName.at(i - 1) == ' ')) {
				armorName[i] = toupper(armorName.at(i)); // Capitalizes first letter of each word
			}
			else if (isalpha(armorName.at(i))) {
				armorName[i] = tolower(armorName.at(i)); // Makes all other characters lowercase, ignoring special characters
			}
		}

		// Use reformatted armor name to find matching armors
		for (auto const& armor : (*armorJson)["armors"]) {
			if (armor["name_en"] == armorName) {
				resultList.push_back(armor);
			}
		}
	}
	else {
		std::cout << "Incorrect armor name format." << std::endl;
	}
}


/**
* Searches JSON for armors matching provided rank. (use DDL to choose rank)
*		-Low Rank: Rarity 1 - 4
*		-High Rank: Rarity 5 - 8
*		-Master Rank: Rarity 9 - 12
*
* @param resultList - List to populate with matching armors
* @param rankName - Name of rank to check against "rarity" field in JSON
*/
void ArmorSearch::searchByRank(std::vector<Json::Value>& resultList, string& const rankName) {
	resultList.clear();

	if (rankName == "Low") { // Low Rank: Finds armors of Rarity 1 - 4
		for (auto const& armor : (*armorJson)["armors"]) {
			if (armor["rarity"] >= 1 && (armor["rarity"] <= 4)) {
				resultList.push_back(armor);
			}
		}
	}
	else if (rankName == "High") { // High Rank: Finds armors of Rarity 5 - 8
		for (auto const& armor : (*armorJson)["armors"]) {
			if (armor["rarity"] >= 5 && (armor["rarity"] <= 8)) {
				resultList.push_back(armor);
			}
		}
	}
	else { // Master Rank: Finds armors of Rarity 9 - 12
		for (auto const& armor : (*armorJson)["armors"]) {
			if (armor["rarity"] <= 9) {
				resultList.push_back(armor);
			}
		}
	}
}

/**
* Searches JSON for armors matching provided rarity. (use DDL to choose rank)
*		-Low Rank: Rarity 1 - 4
*		-High Rank: Rarity 5 - 8
*		-Master Rank: Rarity 9 - 12
*
* @param resultList - List to populate with matching armors
* @param rarityVal - Rarity value to check against "rarity" field in JSON
*/
void ArmorSearch::searchByRarity(std::vector<Json::Value>& resultList, int& const rarityVal) {
	resultList.clear();

	for (auto const& armor : (*armorJson)["armors"]) {
		if (armor["rarity"] == rarityVal) {
			resultList.push_back(armor);
		}
	}
}

/**
* Searches JSON for armors matching provided type. (use DDL to choose rank)
*		Possible Types: head, chest, arms, waist, legs
*
* @param resultList - List to populate with matching armors
* @param typeName - Name of type to check against "type" field in JSON
*/
void ArmorSearch::searchByType(std::vector<Json::Value>& resultList, string& const typeName) {
	resultList.clear();

	for (auto const& armor : (*armorJson)["armors"]) {
		if (armor["type"] == typeName) {
			resultList.push_back(armor);
		}
	}
}