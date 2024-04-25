#include "Tracking.h"
#include <fstream>
#include <iomanip>

// Displays each menu option when called
void DisplayMenu() {
	cout << "\nPlease select an option by tpying in the corresponding number below:\n" << endl;
	cout << "Option:" << endl;
	cout << "   [1] Find quantity by item lookup." << endl;
	cout << "   [2] Print list of items with total number sold." << endl;
	cout << "   [3] Display a histograph of quantities sold per item." << endl;
	cout << "   [4] Quit." << endl;
}

// Formats the histograph
static string nCharString(size_t n, char c)
{
	return string(n, c);
}

// Creates the output data file for back up as well as places each item read in from the input
// file into a map as the key and counts the times it appears as the value
map<string, int> CreateDataFile(string& file)
{
	ifstream inputFile;
	ofstream outputFile;
	string itemName;
	int itemQuant = 1; // starts the count at one since the first appearance of an item is one
	map<string, int> frequencyData;

	inputFile.open(file);
	outputFile.open("frequency.dat");

	if (!inputFile.is_open()) // checks the input file opens correctly reading
	{
		cout << "Could not open input file." << endl;
		exit(EXIT_FAILURE); // exits program if failed to open
	}

	if (!outputFile.is_open()) // checks the output file opens correctly for writing
	{
		cout << "Could not create data file." << endl;
		exit(EXIT_FAILURE); // exits program if failed to open
	}
	 // for each item name that is read, the item quantity increments
	while (inputFile >> itemName)
	{
		outputFile << itemName << " " << itemQuant << endl;
		frequencyData[itemName] += itemQuant;
	}

	// closes both files
	inputFile.close();
	outputFile.close();

	return frequencyData; //return the map for use in main
}

int main() {
	
	int menuOption;
	bool exit = false;
	string itemName;
	int itemQuant;
	
	// calls the function for backup data and map
	string file = "CS210_Project_Three_Input_File.txt";
	map<string, int> inventory = CreateDataFile(file);


	// loop will continue until exit is true (option 4 changes exit to true)
	while (!exit) {
		
		DisplayMenu();
		cin >> menuOption;

		
		if (menuOption == 1)
		{
			cout << "\nEnter the item you wish to look up:" << endl;
			cin >> itemName; // reads input from user for item they want

			// tries to find the item the user is looking for in the map and assigns the value of that 
			// item(key) to itemQuant, instantiates the object option1 and returns the quantity of item
			try 
			{
				itemQuant = inventory.at(itemName);
				GroceryTracking option1(itemName, itemQuant);
				cout << "\n   There were " << option1.GetQuant() << " " << option1.GetName() << " sold." << endl;
			}
			// handles exception if item can't be found
			catch (const out_of_range& e) 
			{
				cout << "Item not found. Check the spelling and try again." << endl;
			}
			
		}

		// loops through the map assigning the item name and quantity to each pair to allow instantiation
		// of object option2 and will print each key and value pair
		else if (menuOption == 2) 
		{
			cout << "\n...Today's inventory includes...\n" << endl;

			for (const auto& pair : inventory) 
			{
				itemName = pair.first;
				itemQuant = pair.second;

				GroceryTracking option2(itemName, itemQuant);

				cout << setw(12) << setfill(' ') << left << option2.GetName();
				cout << setw(4) << setfill(' ') << right << option2.GetQuant() << endl;
			}
			
		}

		// loops through the map assigning the item name and quantity to each pair to allow instantiation
		// of object option3 and will print each key and value pair
		else if (menuOption == 3) 
		{

			cout << "\n...Printing histograph...\n" << endl;

			for (const auto& pair : inventory) 
			{
				itemName = pair.first;
				itemQuant = pair.second;
				
				GroceryTracking option3(itemName, itemQuant);

				// assigns "|" the amount of itemQuant to print in the form of graph per each item
				string bar = nCharString(option3.GetQuant(), '|');
				cout << left << setw(12) << setfill(' ') << option3.GetName();
				cout << left << bar << endl;
			}
		}

		// exits the program
		else if (menuOption == 4) 
		{
			exit = true;
			cout << "\n...Exiting program..." << endl;
		}

		// input validation for menu and redisplays
		else 
		{
			cout << "Invalid menu option.\n" << endl;
			DisplayMenu();
			cin >> menuOption;
		}
	}
}
