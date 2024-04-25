#pragma once
#include <iostream>
#include <set>
#include <map>

using namespace std;

#ifndef TRACKING_H
#define TRACKING_H

class GroceryTracking {
public:

	// default contructor to mutate private members
	GroceryTracking(string& itemName, int itemQuant);

	// getters to show private members
	string GetName();
	int GetQuant() const;

private:
	string itemName;
	int itemQuant = 0;

};

#endif