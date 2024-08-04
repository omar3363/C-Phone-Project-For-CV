#include <iostream>
#include <string>
#include <fstream>
using namespace std;

const int max_number = 50;

// Function prototypes
string lowercase(string name);
bool Valid_input(string input, bool isName);
void add_contact(string array[][2], int& LastIndex);
void retrieve(string array[][2], int LastIndex);
void update_contact(string array[][2], int& LastIndex);
void show_all(string array[][2], int LastIndex);
void delete_contact(string array[][2], int& LastIndex);
void save_file(string contact[][2], int& LastIndex);

int main()
{
    string contact[max_number][2];
    int LastIndex = 0;
    string Operation;

    ifstream inFile("contact_list.txt");
    if (inFile.is_open()) {
        while (LastIndex < max_number && inFile >> contact[LastIndex][0] >> contact[LastIndex][1]) {
            LastIndex++;
        }
        inFile.close();
    } else {
        cout << "Unable to open the file. Starting with an empty contact list.\n";
    }

    do {
        cout << "Choose an Operation" << endl <<
                "[1] ADD a new contact." << endl <<
                "[2] UPDATE a specific contact." << endl <<
                "[3] RETRIEVE a specific contact." << endl <<
                "[4] DELETE a specific contact." << endl <<
                "[5] SHOW ALL DATA." << endl <<
                "[6] EXIT" << endl;
        cin >> Operation;
        Operation = lowercase(Operation);
        if (Operation == "add")
            add_contact(contact, LastIndex);
        else if (Operation == "update")
            update_contact(contact, LastIndex);
        else if (Operation == "retrieve")
            retrieve(contact, LastIndex);
        else if (Operation == "delete")
            delete_contact(contact, LastIndex);
        else if (Operation == "show")
            show_all(contact, LastIndex);
        else if (Operation == "exit") {
            save_file(contact, LastIndex);
            return 0;
        } else
            cout << "Unidentified operation. Please enter a valid operation.\n";

    } while (true);

    return 0;
}

string lowercase(string name) // to make sure all input is lowercase
{
    for (int i = 0; i < name.length(); i++) {
        if (name[i] >= 'A' && name[i] <= 'Z') {
            name[i] = name[i] + ('a' - 'A');
        }
    }
    return name;
}

bool Valid_input(string input, bool isName) {
    const int maximum_namelength = 50;
    const int maximum_numlength = 15;

    if (isName) {
        if (input.length() == 0 || input.length() > maximum_namelength) {
            cout << "Wrong Input" << endl;
            return false;
        }
    } else {
        if (input.length() == 0 || input.length() > maximum_numlength) {
            cout << "Wrong Input" << endl;
            return false;
        }
        for (int i = 0; i < input.length(); i++) {
            if (input[i] < '0' || input[i] > '9') {
                cout << "Wrong Input" << endl;
                return false;
            }
        }
    }
    return true;
}

void add_contact(string array[][2], int& LastIndex)
{
    if (LastIndex >= max_number) {
        cout << "The contact list is full. Cannot add more contacts.\n";
        return;
    }

    string name, phone_number;
    cin.ignore(); // To ignore any leftover newline characters in the input buffer
    cout << "Enter the name: ";
    getline(cin, name); // Allow names with spaces
    cout << "Enter the phone number: ";
    getline(cin, phone_number); // Allow phone numbers with spaces

    if (Valid_input(name, true) && Valid_input(phone_number, false)) {
        array[LastIndex][0] = name;
        array[LastIndex][1] = phone_number;
        LastIndex++;
    } else {
        cout << "Invalid input. Contact not added.\n";
    }
}

void retrieve(string array[][2], int LastIndex)
{
    string choice, search;
    cout << "Do you want to retrieve by name or number? (Enter 'name' or 'number'): ";
    cin >> choice;
    choice = lowercase(choice);

    cin.ignore(); // To ignore any leftover newline characters in the input buffer

    if (choice == "name") {
        cout << "Enter the name to search: ";
        getline(cin, search);
        if (!Valid_input(search, true)) {
            return;
        }
    } else if (choice == "number") {
        cout << "Enter the phone number to search: ";
        getline(cin, search);
        if (!Valid_input(search, false)) {
            return;
        }
    } else {
        cout << "Invalid choice." << endl;
        return;
    }

    bool found = false;
    for (int i = 0; i < LastIndex; i++) {
        if (choice == "name" && array[i][0] == search) {
            cout << array[i][0] << " " << array[i][1] << endl;
            found = true;
        }
        if (choice == "number" && array[i][1] == search) {
            cout << array[i][0] << " " << array[i][1] << endl;
            found = true;
        }
    }
    if (!found) {
        cout << "Contact not found in the system." << endl;
    }
}

void update_contact(string array[][2], int& LastIndex)
{
    string name, updated_number;
    cin.ignore(); // To ignore any leftover newline characters in the input buffer
    cout << "Enter the name of the contact to update: ";
    getline(cin, name);
    bool Found = false;
    for (int i = 0; i < LastIndex; i++) {
        if (array[i][0] == name) {
            cout << "Enter the new phone number: ";
            getline(cin, updated_number);
            if (Valid_input(updated_number, false)) { // Only validate the number here
                array[i][1] = updated_number;
                Found = true;
                return;
            }
        }
    }

    if (!Found) {
        cout << "Contact not found. Adding as a new contact.\n";
        if (LastIndex < max_number) {
            cout << "Enter the phone number: ";
            getline(cin, updated_number);
            if (Valid_input(name, true) && Valid_input(updated_number, false)) {
                array[LastIndex][0] = name;
                array[LastIndex][1] = updated_number;
                LastIndex++;
            } else {
                cout << "Invalid input. Contact not added.\n";
            }
        } else {
            cout << "The contact list is full. Cannot add more contacts.\n";
        }
    }
}

void delete_contact(string array[][2], int& LastIndex)
{
    string name;
    cin.ignore(); // To ignore any leftover newline characters in the input buffer
    cout << "Enter the name of the contact to delete: ";
    getline(cin, name);
    bool Found = false;
    for (int i = 0; i < LastIndex; i++) {
        if (array[i][0] == name) {
            Found = true;
            for (int j = i; j < LastIndex - 1; j++) {
                array[j][0] = array[j + 1][0];
                array[j][1] = array[j + 1][1];
            }
            LastIndex--;
            return;
        }
    }
    if (!Found)
        cout << "Contact name is not on the system" << endl;
}

void show_all(string array[][2], int LastIndex)
{
    if (LastIndex == 0) {
        cout << "Phonebook is empty" << endl;
        return;
    }
    for (int i = 0; i < LastIndex; i++) {
        cout << array[i][0] << " " << array[i][1] << endl; // print all the contacts
    }
}

void save_file(string contact[][2], int& LastIndex)
{
    ofstream MyFile("contact_list.txt");
    if (MyFile.is_open()) {
        for (int i = 0; i < LastIndex; i++) {
            MyFile << contact[i][0] << " " << contact[i][1] << endl;
        }
        MyFile.close();
    } else {
        cout << "Unable to open the file to save contacts.\n";
    }
}
