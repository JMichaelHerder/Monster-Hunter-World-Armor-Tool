#ifndef ARMORSET_H
#define ARMORSET_H

#include "json.h"
#include <vector>
#include <string>
#include <map>
#include <iostream>
#include <iomanip>

class ArmorSet {
public:
	ArmorSet();

	bool addArmor(Json::Value& const armorToAdd); // Adds armor piece to set and updates member variables; checks type and gender
	
	//bool removeArmor();

	void printArmorSet();
	//void saveSet(); // We'll see about this
	

private: // Possibly add int cost variable if data is updated
	std::vector<Json::Value> armorSetPieces;
	std::string armorSetGender;
	std::string armorSetName;
	std::vector<int> totalDefenseVals;
	std::map<std::string, int> armorSetSkills;
	std::map<std::string, int> craftingMaterials;

	bool checkGender(std::string gender); // Helper for addArmor function
	bool checkType(std::string type); // Helper for addArmor function
	void updateArmorSet(Json::Value& const addedArmor);
	void replaceArmorPiece(Json::Value& const armorToReplace);
};

#endif