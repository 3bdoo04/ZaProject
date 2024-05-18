#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<ctime>
#include "FileHandler.h"

using namespace std;

    class PatientRecordManager
    {

    protected:

        tm recordDate;  // Stores the date the record was created.
        vector <PatientRecord> records;  // Vector to store patient records.
	    FileHandler fileHandler;

    public:
        struct PatientRecord {
            string name;
            string address;
            int age;
            char gender;
            string diseaseDescription;
            int specialistRoomNumber;
        };

        void exprotToFile() {
            fileHandler.saveToFile(records);
        }

        void importFromFile() {
            fileHandler.readFromFile(records);
        }

    PatientRecordManager()
    {
        nextRecordNumber = 1;

        time_t now = time(0);
        recordDate = *localtime(&now);
    }
    void addNewPatient(string serviceType) {

        PatientRecordManager record;  // Create a new patient record.

        cin.ignore(); // Clear any leftover input from previous operations.
        cout << "Patient Name: ";
        getline(cin, record.name);

        cin.ignore();
        cout << "Address: ";
        getline(cin, record.address);
        cin.ignore();

        bool validAge = false;
        while (!validAge) {
            cout << "Age: ";
            cin >> record.age;
            if (record.age >= 0 && record.age <= 120) {
                validAge = true;
            }
            else {
                cout << "Invalid age. Please enter a value between 0 and 120." << endl;
            }
        }
        cin.ignore();

        bool validGender = false;
        while (!validGender) {
            cout << "M for Male & F for Female" << endl;
            cout << "Gender: ";
            cin >> record.gender;
            validGender = record.gender == 'M' || record.gender == 'F';
            if (!validGender) {
                cout << "Invalid gender. Please enter 'M' or 'F'." << endl;
            }
        }
        cin.ignore();

        cout << "Disease description: ";
        getline(cin, record.diseaseDescription);
        cin.ignore();

        bool validRoomNumber = false;
        while (!validRoomNumber) {
            cout << "Specialist room number: ";
            cin >> record.specialistRoomNumber;
            if (record.specialistRoomNumber >= 0) {
                validRoomNumber = true;
            }
            else {
                cout << "Invalid room number. Please enter a non-negative value." << endl;
            }
        }
        cin.ignore();

        record.name += " (" + serviceType + ") ";  // Add service type information to the name (if provided).

        records.push_back(record);
        cout << "Record " << nextRecordNumber << " have been added successfully";
        nextRecordNumber++;

    }
    void searchOrEditPatientRecord(int recordNumber) {
        int index = findRecordIndex(recordNumber);
        if (index == -1) {
            cout << "Record not found." << endl;
            return;
        }

        displayRecordDetails(records[index]);

        char choice;
        cout << "Edit record (Y/N)? ";
        cin >> choice;
        cin.ignore();

        if (choice == 'Y' || choice == 'y') {
            editPatientRecord(records[index]);
        }
    }
    void searchOrEditPatientRecord(string fullName) {
        int index = findRecordIndexByName(fullName);
        if (index == -1) {
            cout << "Record not found." << endl;
            return;
        }

        char choice;
        cout << "Display or edit record (D/E)? "; //D is for displaying and E is for editing the record.
        cin >> choice;
        cin.ignore();

        if (choice == 'D' || choice == 'd') {
            displayRecordDetails(records[index]);
        }
        else if (choice == 'E' || choice == 'e') {
            editPatientRecord(records[index]);
        }
        else {
            cout << "Invalid choice." << endl;
        }
    }
    void listPatientRecords(string option) {
        if (option == "alphabetical") {

            sort(records.begin(), records.end(), [](const PatientRecordManager& a, const PatientRecordManager& b) {
                return a.name < b.name;
                });

            cout << "Listing patients alphabetically:" << endl;
            for (const PatientRecordManager& record : records) {
                displayRecordDetails(record);
            }
        }
        else if (option == "emergency") {
            cout << "Listing emergency patients:" << endl;

            for (const PatientRecordManager& record : records) {
                if (record.name.find("Emergency") != string::npos) {
                    displayRecordDetails(record);
                }
            }
        }
        else if (option == "outpatient") {
            cout << "Listing outpatient patients:" << endl;

            for (const PatientRecordManager& record : records) {
                if (record.name.find("Outpatient") != string::npos) {
                    displayRecordDetails(record);
                }
            }
        }
        else if (option == "date") {
            tm userDate;


            bool validDate = false;
            while (!validDate) {
                cout << "Enter date (YYYY MM DD): ";
                cin >> userDate.tm_year >> userDate.tm_mon >> userDate.tm_mday;
                userDate.tm_isdst = -1;


                if (userDate.tm_year >= 1900 && userDate.tm_mon >= 0 && userDate.tm_mon <= 11 && userDate.tm_mday >= 1 && userDate.tm_mday <= 31) {
                    validDate = true;
                }
                else {
                    cout << "Invalid date format. Please try again." << endl;
                }
            }

            cout << "Listing patients with records on " << userDate.tm_year + 1900 << "-" << userDate.tm_mon + 1 << "-" << userDate.tm_mday << ":" << endl;


            for (const PatientRecordManager& record : records) {
                if (record.recordDate.tm_year == userDate.tm_year && record.recordDate.tm_mon == userDate.tm_mon && record.recordDate.tm_mday == userDate.tm_mday) {
                    displayRecordDetails(record);
                }
            }
        }
        else {
            cout << "Invalid option." << endl;
        }
    }
    void deletePatientRecord(int recordNumber) {
        int index = findRecordIndex(recordNumber);
        if (index == -1) {
            cout << "Record not found." << endl;
            return;
        }

        char choice;
        cout << "Are you sure you want to delete record " << recordNumber << " (Y/N)? ";
        cin >> choice;
        cin.ignore();

        if (choice == 'Y' || choice == 'y') {
            records.erase(records.begin() + index);
            cout << "Record deleted successfully." << endl;
        }
    }
    int findRecordIndex(int recordNumber) {  // Function to find record index by record number.
        for (int i = 0; i < records.size(); i++) {
            if (records[i].nextRecordNumber == recordNumber) {
                return i;
            }
        }
        return -1;
    }


    int findRecordIndexByName(string fullName) {  // Function to find record index by full name.
        for (int i = 0; i < records.size(); i++) {
            if (records[i].name.find(fullName) != string::npos) {
                return i;
            }
        }

        return -1;
    }


    void displayRecordDetails(const PatientRecordManager& record) {
        cout << "Record Number: " << record.nextRecordNumber << endl;
        cout << "Name: " << record.name << endl;
        cout << "Address: " << record.address << endl;

    }
    void editPatientRecord(PatientRecordManager& record) {

        cout << "Current Name: " << record.name << endl;
        cout << "Current Address: " << record.address << endl;
        cout << "Current Age: " << record.age << endl;
        cout << "Current Gender: " << record.gender << endl;
        cout << "Current Disease Description: " << record.diseaseDescription << endl;
        cout << "Current Specialist Room Number: " << record.specialistRoomNumber << endl;

        string fieldToEdit;
        cout << "Enter the field to edit (name, address, age, gender, disease description, specialist room number): ";
        cin >> fieldToEdit;

        if (fieldToEdit == "name") {
            cin.ignore();
            cout << "New name: ";
            getline(cin, record.name);
        }
        else if (fieldToEdit == "address") {
            cin.ignore();
            cout << "New address: ";
            getline(cin, record.address);
        }
        else if (fieldToEdit == "age") {
            int newAge;
            cout << "New age: ";
            cin >> newAge;
            cin.ignore();
            record.age = newAge;
        }
        else if (fieldToEdit == "gender") {
            while (record.gender != 'M' && record.gender != 'F') {
                cout << "M for Male & F for Female" << endl;
                cout << "New gender: ";
                cin >> record.gender;
            }
            cin.ignore();
        }
        else if (fieldToEdit == "disease description") {
            cin.ignore();
            cout << "New disease description: ";
            getline(cin, record.diseaseDescription);
        }
        else if (fieldToEdit == "specialist room number") {
            int newRoomNumber;
            cout << "New specialist room number: ";
            cin >> newRoomNumber;
            cin.ignore();
            record.specialistRoomNumber = newRoomNumber;
        }
        else {
            cout << "Invalid field." << endl;
        }

        cout << "Record edited successfully." << endl;
    }


};