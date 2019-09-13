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
* Private helper function for addArmor - checks if new armor piece's type is already present in current set
*
* @param newArmorType - Type of new armor piece to be added to current set
* @return true if compatible with current armor, false if incompatible
*/
void ArmorSet::replaceArmorPiece(Json::Value& const armorToReplace) {
	
}

void ArmorSet::updateArmorSet(Json::Value& const addedArmor) { // only handles added armor for now
	
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
				
			}
		}


		return true;
	}

	return false;
}
