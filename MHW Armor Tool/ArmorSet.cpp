#include "ArmorSet.h"

// Constructor
ArmorSet::ArmorSet() {
	armorSetPieces.reserve(5);
	armorSetGender = "both";
	armorSetName = "New Armor Set";
	totalDefenseVals.resize(8, 0);
}

/**
* Private helper function for addArmor - checks if new armor piece's gender is compatible with current set
*
* @param newArmorGender - Gender of new armor piece to be added to current set
* @return true if compatible with current armor, false if incompatible
*/
bool ArmorSet::checkGender(std::string newArmorGender) {
	if (armorSetGender == newArmorGender) {
		return true;
	}
	else {
		if (armorSetGender == "both") { // newArmorGender is male or female - armorSetGender must change
			armorSetGender = newArmorGender;
			return true;
		}
		else if (newArmorGender == "both") { // "both" can fit with male or female set
			return true;
		}
	}

	std::cout << "Armor gender is " + newArmorGender << std::endl;
	return false; // armorSetGender and newArmorGender are opposite and cannot be in same set
}

/**
* Private helper function for addArmor - checks if new armor piece's type is already present in current set
*
* @param newArmorType - Type of new armor piece to be added to current set
* @return true if compatible with current armor, false if incompatible
*/
bool ArmorSet::checkType(std::string newArmorType) {
	for (Json::Value armor : armorSetPieces) {
		if (armor["type"] == newArmorType) { 
			return false;
		}
	}
	return true;
}

/**
* Private helper function for addArmor - updates defense values, skills, and materials for armor set
*
* @param addedArmor - Armor to be added to set, containing defense, skills, and materials information
*/
void ArmorSet::updateArmorSet(Json::Value& const addedArmor) { // only handles added armor for now
	// For loop that updates defense values of armor set
	int defValIndex = 0;
	for (Json::Value::iterator it = addedArmor["defense_values"].begin(); it != addedArmor["defense_values"].end(); ++it) {

		totalDefenseVals[defValIndex] += (*it).asInt();
		defValIndex++;
	}
	// For loop that updates skills of armor set (must check if skill is already present in set and add points)
	std::map<std::string, int>::iterator mapIt; // Used for skills and materials
	for (Json::Value::iterator it = addedArmor["skills"].begin(); it != addedArmor["skills"].end(); ++it) {
		mapIt = armorSetSkills.find(it.key().asString());

		if (mapIt != armorSetSkills.end()) { // If present in skill list, adds points to sills
			armorSetSkills[it.key().asString()] += (*it).asInt();
		}
		else { // If not present in skill list, adds skill and points to list
			armorSetSkills[it.key().asString()] = (*it).asInt();
		}
	}
	// Fro loop that updates materials needed to craft armor set (must check if material is already present in list and add amount)
	for (Json::Value::iterator it = addedArmor["materials"].begin(); it != addedArmor["materials"].end(); ++it) {
		mapIt = craftingMaterials.find(it.key().asString());

		if (mapIt != craftingMaterials.end()) { // If present in material list, adds to required material
			craftingMaterials[it.key().asString()] += (*it).asInt();
		}
		else { // If not present in material list, adds material and quantity to list
			craftingMaterials[it.key().asString()] = (*it).asInt();
		}
	}
}

/**
* Private helper function for addArmor - checks if new armor piece's type is already present in current set
*
* @param newArmorType - Type of new armor piece to be added to current set
* @return true if compatible with current armor, false if incompatible
*/
void ArmorSet::replaceArmorPiece(Json::Value& const armorToReplace) {

}

/**
* Adds armor to current set if compatible with other armor pieces and updates member variables
*
* @param armorToAdd - Armor piece to add to set
* @return true if armor was added, false if not
*/
bool ArmorSet::addArmor(Json::Value& const armorToAdd) {
	if (checkGender(armorToAdd["gender"].asString())) {
		for (Json::Value armor : armorSetPieces) {
			if (armor["type"] == armorToAdd["type"]) { // Should ask user if they want to replace conflicting armor with new armor piece (replaceArmorPiece)
				return false;
			}
		}
		updateArmorSet(armorToAdd);
		armorSetPieces.push_back(armorToAdd);

		return true;
	}

	return false;
}


void ArmorSet::printArmorSet() {
	/*
	for (Json::Value armor : armorSetPieces) {
		std::cout << armor["type"] << ": " << armor["name_en"] << std::endl;
		std::cout << "	Rarity: " << armor["rarity"] << std::endl;
		std::cout << "	Slots: ";
		for (Json::Value::iterator it = armor["slots"].begin(); it != armor["slots"].end(); ++it) {
			std::cout << (*it).asInt() << " ";
		}
		std::cout << "\n" << "	Defense Values:" << std::endl;
	}
	*/

	// Very Crude implementation for now
	std::cout << "Set Name: " << armorSetName << std::endl;
	std::cout << "Set Gender: " << armorSetGender << std::endl;

	std::cout << "Defense Values: " << std::endl;
	std::cout << std::setw(10) << "Base";
	std::cout << std::setw(10) << "Max";
	std::cout << std::setw(10) << "AugMax";
	std::cout << std::setw(10) << "Fire";
	std::cout << std::setw(10) << "Water";
	std::cout << std::setw(10) << "Thunder";
	std::cout << std::setw(10) << "Ice";
	std::cout << std::setw(10) << "Dragon" << std::endl;
	
	for (int i = 0; i < totalDefenseVals.size(); i++) {
		std::cout << std::setw(10) << totalDefenseVals[i];
	}
	std::cout << "\n";

	std::cout << "Skills: " << std::endl;
	for (auto const& skill: armorSetSkills) {
		std::cout << skill.first << ": " << skill.second << std::endl;
	}
	std::cout << "\n";

	std::cout << "Crafting Materials: " << std::endl;
	for (auto const& material : craftingMaterials) {
		std::cout << material.first << ": " << material.second << std::endl;
	}
}