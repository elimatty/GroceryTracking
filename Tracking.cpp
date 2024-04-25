#include "Tracking.h"

// constructor and getter definitions

GroceryTracking::GroceryTracking(string& itemName, int itemQuant)
{
	this->itemName = itemName;
	this->itemQuant = itemQuant;
}

string GroceryTracking::GetName() { return itemName; }
int GroceryTracking::GetQuant() const { return itemQuant; }



