#include <iostream>
#include <sstream>  
#include <fstream>  
#include <string> 
#include <cstdlib>

using namespace std;

struct Contact {
    string firstName;
    string lastName;
    string phoneNumber;
    string address;
};
bool contactExists(const string& phoneNumber) {
    ifstream file("contacts.txt");
    string line;

    while (getline(file, line)) {
        Contact contact;
        stringstream ss(line);
        ss >> contact.firstName >> contact.lastName >> contact.phoneNumber >> contact.address;

        if (contact.phoneNumber == phoneNumber) {
            file.close();
            return true;
        }
    }

    file.close();
    return false;
}
void addContact() {
    Contact newContact;

    cout << "\nEnter first name: ";
    cin >> newContact.firstName;
    cout << "Enter last name: ";
    cin >> newContact.lastName;
    cout << "Enter phone number: ";
    cin >> newContact.phoneNumber;
    cout << "Enter address: ";
    cin >> newContact.address;

    if (contactExists(newContact.phoneNumber)) {

        cout << "\n*************************************************\n";
        cout << "************Contact already exists!**************" << endl;
        cout << "*************************************************\n";
        return;
    }
    ofstream file("contacts.txt", ios::app);
    file << newContact.firstName << " " << newContact.lastName << " " << newContact.phoneNumber << " " << newContact.address << endl;
    file.close();

    cout << "\n*************************************************\n";
    cout << "**********Contact added successfully!************" << endl;
    cout << "*************************************************\n";
}
void editContact() {
    string phoneNumber;

    cout << "\nEnter the phone number of the contact you want to edit: ";
    cin >> phoneNumber;

    ifstream file("contacts.txt");
    ofstream tempFile("temp.txt");

    bool found = false;
    string line;

    while (getline(file, line)) {
        Contact contact;
        stringstream str(line);
        str >> contact.firstName >> contact.lastName >> contact.phoneNumber >> contact.address;

        if (contact.phoneNumber == phoneNumber) {
            found = true;
            string newFirstName, newLastName, newAddress, newPhoneNumber;

            cout << "\nEnter new first name: ";
            cin >> newFirstName;
            cout << "Enter new last name: ";
            cin >> newLastName;
            cout << "Enter new address: ";
            cin >> newAddress;
            cout << "Enter new phone number: ";
            cin >> newPhoneNumber;

            tempFile << newFirstName << " " << newLastName << " " << newPhoneNumber << " " << newAddress << endl;
            cout << "\n*************************************************\n";
			cout << "********Contact updated successfully!************" << endl;
            cout << "*************************************************\n";
        } else {
            tempFile << line << endl;
        }
    }
    file.close();
    tempFile.close();

    if (!found) {
    	cout << "\n*************************************************\n";
        cout << "*************Contact Does not exist**************" << endl;
        cout << "*************************************************\n";
    } else {
        remove("contacts.txt");
        rename("temp.txt", "contacts.txt");
    }
}
void searchContact() {
    cout <<"\n*************************************************\n";
    cout << "\t\tSearch contact by:" << endl;
    cout << "\t\t1. First Name" << endl;
    cout << "\t\t2. Last Name" << endl;
    cout << "\t\t3. Phone Number" << endl;
    cout << "\t\t4. Address" << endl;
    cout <<"*************************************************\n";

    int searchOption;
    cout << "\t\nEnter your choice: ";
    cin >> searchOption;

    string searchString;
    cout << "\nEnter the search term: ";
    cin >> searchString;

    ifstream file("contacts.txt");

    bool found = false;
    string line;

    while (getline(file, line)) {
        Contact contact;
        stringstream ss(line);
        ss >> contact.firstName >> contact.lastName >> contact.phoneNumber >> contact.address;

        if ((searchOption == 1 && contact.firstName == searchString) ||
            (searchOption == 2 && contact.lastName == searchString) ||
            (searchOption == 3 && contact.phoneNumber == searchString) ||
            (searchOption == 4 && contact.address == searchString)) {
            found = true;
            cout << "\nFirst Name: " << contact.firstName << endl;
            cout << "Last Name: " << contact.lastName << endl;
            cout << "Phone Number: " << contact.phoneNumber << endl;
            cout << "Address: " << contact.address << endl;
            //break;
        }
    }
    file.close();

    if (!found) {
        cout << "\n*************************************************\n";
        cout << "*************Contact Does not exist**************" << endl;
        cout << "*************************************************\n";
    }
}
void viewContacts() {
    ifstream file("contacts.txt");

    if (file.is_open()) {
        string line;

        while (getline(file, line)) {
            Contact contact;
            stringstream str(line);
            str >> contact.firstName >> contact.lastName >> contact.phoneNumber >> contact.address;

            cout << "\nFirst Name: " << contact.firstName << endl;
            cout << "Last Name: " << contact.lastName << endl;
            cout << "Phone Number: " << contact.phoneNumber << endl;
            cout << "Address: " << contact.address <<endl;
            cout << endl;
        }
        file.close();
    } else
    	cout << endl << endl;
    	cout << "\n*************************************************\n";
        cout << "**********Add some contacts to display***********" << endl;
        cout << "*************************************************\n";	
}
void deleteContact() {
    string phoneNumber;

    cout << "\nEnter the phone number of the contact you want to delete: ";
    cin >> phoneNumber;

    ifstream file("contacts.txt");
    ofstream tempFile("temp.txt");

    bool found = false;
    string line;

    while (getline(file, line)) {
        Contact contact;
        stringstream str(line);
        str >> contact.firstName >> contact.lastName >> contact.phoneNumber >> contact.address;

        if (contact.phoneNumber == phoneNumber) {
            found = true;
            cout << "\n*************************************************\n";
			cout << "***********Contact deleted successfully!*********" << endl;
			cout << "*************************************************\n";
        } else {
            tempFile << line << endl;
        }
    }
    file.close();
    tempFile.close();

    if (!found) {
    	cout << "\n*************************************************\n";
        cout << "*************Contact Does not exist**************" << endl;
        cout << "*************************************************\n";
    } else {
        remove("contacts.txt");
        rename("temp.txt", "contacts.txt");
    }
}
int main() {
	system("color 0a");
    int choice;
	cout << "*************************************************\n";
	cout << "*******Welcome To Contact Managment System*******\n";
	cout << "*************************************************\n";
	
    do {
    	cout <<"\n*************************************************\n";
    	cout << "\t\t1. Add contact\n";
    	cout << "\t\t2. Edit contact\n";
    	cout << "\t\t3. Search contact\n";
    	cout << "\t\t4. View contacts\n";
    	cout << "\t\t5. Delete contact\n";
    	cout << "\t\t6. Exit\n";
    	cout <<"*************************************************\n";
        cout << "\t\nEnter your choice: ";
        cin >> choice;
        
        switch(choice) {
            case 1:
                system("cls");
            	cout <<"\n*************************************************\n";
            	cout << "**************Add Option Selected****************\n";
            	cout <<"*************************************************\n";
                addContact();
                break;
            case 2:
                system("cls");
            	cout <<"\n*************************************************\n";
            	cout << "************Editing Option Selected**************\n";
            	cout <<"*************************************************\n";
                editContact();
                break;
            case 3:
                system("cls");
            	cout <<"\n*************************************************\n";
            	cout << "*************Search Option Selected**************\n";
            	cout <<"*************************************************\n";
                searchContact();
                break;
            case 4:
                system("cls");
            	cout <<"\n*************************************************\n";
            	cout << "**************View Option Selected***************\n";
            	cout <<"*************************************************\n";
                viewContacts();
                break;
            case 5:
                system("cls");
            	cout <<"\n*************************************************\n";
            	cout << "*************Delete Option Selected**************\n";
            	cout <<"*************************************************\n";
                deleteContact();
                break;
            case 6:
                system("cls");
            	cout << "\n*************************************************\n";
                cout << "******************Bye! See you*******************\n";
                cout << "*************************************************\n";
                break;
            default:
            	cout << "\n*************************************************\n";
                cout << "************Wrong input dumbass!!****************\n";
                cout << "*************************************************\n";
                break;
        }
    } while (choice != 6);
    return 0;
}

