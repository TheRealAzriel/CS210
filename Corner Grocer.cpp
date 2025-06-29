// Project: Corner Grocer Item Tracker
// Developer: Chad Cattell
// Date: 2025-06-20
// Purpose: Track and analyze frequency of grocery items from a daily input file

#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <iomanip>
#include <algorithm>
#include <limits>
using namespace std;

// Class to handle item tracking functionality
class ItemTracker {
private:
    map<string, int> itemFrequency;  // Stores item and its frequency
    string inputFileName = "CS210_Project_Three_Input_File.txt";
    string outputFileName = "frequency.dat";

    // Reads data from the input file and populates itemFrequency map
    void readInputFile() {
        ifstream inputFile(inputFileName);
        string item;
        
        if (!inputFile) {
            cerr << "Error: Unable to open input file." << endl;
            return;
        }

        while (getline(inputFile, item)) {
            itemFrequency[item]++;
        }

        inputFile.close();
    }

    // Writes frequency data to a backup file
    void writeFrequencyToFile() {
        ofstream outputFile(outputFileName);

        for (const auto& pair : itemFrequency) {
            outputFile << pair.first << " " << pair.second << endl;
        }

        outputFile.close();
    }

public:
    ItemTracker() {
        readInputFile();
        writeFrequencyToFile();
    }

    // Returns the frequency of a specific item
    void searchItem(const string& item) const {
        auto it = itemFrequency.find(item);
        if (it != itemFrequency.end()) {
            cout << item << " was purchased " << it->second << " times.\n";
        } else {
            cout << item << " was not found in today's purchases.\n";
        }
    }

    // Prints all items and their frequencies
    void printAllFrequencies() const {
        cout << "\nItem Frequency List:\n";
        for (const auto& pair : itemFrequency) {
            cout << left << setw(15) << pair.first << " " << pair.second << endl;
        }
    }

    // Prints histogram of items based on their frequencies
    void printHistogram() const {
        cout << "\nItem Frequency Histogram:\n";
        for (const auto& pair : itemFrequency) {
            cout << left << setw(15) << pair.first << " ";
            for (int i = 0; i < pair.second; ++i) {
                cout << "*";
            }
            cout << endl;
        }
    }
};

// Menu interface for user interaction
void displayMenu() {
    cout << "\n===== Corner Grocer Menu =====" << endl;
    cout << "1. Search for item frequency" << endl;
    cout << "2. Print all item frequencies" << endl;
    cout << "3. Print histogram of item frequencies" << endl;
    cout << "4. Exit" << endl;
    cout << "Enter your choice: ";
}

int main() {
    ItemTracker tracker;
    int choice;
    string item;

    do {
        displayMenu();
        
        // Check for valid integer input
        while (!(cin >> choice) || choice < 1 || choice > 4) {
            cout << "Invalid option. Please enter a number between 1 and 4: ";
            cin.clear(); // Clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
        }
        cin.ignore(); // Clear newline from input buffer after valid input

        switch (choice) {
            case 1:
                cout << "Enter item name: ";
                getline(cin, item);
                tracker.searchItem(item);
                break;
            case 2:
                tracker.printAllFrequencies();
                break;
            case 3:
                tracker.printHistogram();
                break;
            case 4:
                cout << "Exiting program. Goodbye!\n";
                break;
            // No default case needed since the validation loop ensures choice is valid
        }
    } while (choice != 4);

    return 0;
}


