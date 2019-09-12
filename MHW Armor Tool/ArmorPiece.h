#ifndef ARMORPIECE_H
#define ARMORPIECE_H

#include "json.h"
#include <vector>
#include <string>
#include <map>

class ArmorPiece {
public:
	ArmorPiece();

	~ArmorPiece();

	ArmorPiece(const ArmorPiece& other); // Copy Constructor
	ArmorPiece(ArmorPiece&& other); // Move Constructor
	ArmorPiece& operator=(const ArmorPiece& other); // Copy Assignment
	ArmorPiece& operator=(ArmorPiece&& other); // Move Assignment
	
	void printArmor();

private:
	std::string name;
	std::string gender;
	std::string type;
	int rarity;
	std::vector<int> defenseVals;
	std::vector<int> slots;
	std::map<std::string, int> armorSetSkills;
	std::map<std::string, int> craftingMaterials;
};

#endif