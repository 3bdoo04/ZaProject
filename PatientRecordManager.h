#include<iostream>
#include<string>
#include<vector>
#include"PatientRecord.h"
#pragma once

using namespace std;

class PatientRecordManager
{

private:

	vector <PatientRecord> records;
	int nextRecordNumber;

public:
	PatientRecordManager() { nextRecordNumber = 1; }
	void addNewPatient(string serviceType) {

		PatientRecord record;

		cin.ignore();
		cout << "Patient Name: ";
		getline(cin, record.name);

		cin.ignore();
		cout << "Address: ";
		getline(cin, record.address);
		cin.ignore();

		cout << "Age: ";
		cin >> record.age;
		cin.ignore();

		while (record.gender != 'M' && record.gender != 'F') {

			cout << "M for Male & F for Female" << endl;
			cout << "Gender: ";
			cin >> record.gender;
		}
		cin.ignore();

		cout << "Disease description: ";
		getline(cin, record.diseaseDescription);
		cin.ignore();

		cout << "Specialist room number: ";
		cin >> record.specialistRoomNumber;
		cin.ignore();

		record.name += " (" + serviceType + ") ";

		records.push_back(record);
		cout << "Record " << nextRecordNumber << " have been added successfully";
		nextRecordNumber++;

	}
	void findRecordIndex(int recordNumber) {

		for (int i = 0; i < records.size(); i++) {

			if(records[i].name)
		}
	}
	void searchOrEditPatientRecord(int recordNumber) {

		int i = findRecordIndex(recordNumber);

		if (i == -1) {

			cout << " no such record is found! ";

		}

		int choice;
		cout << "1. View Record ";
		cout << "2. Edit Record ";
		cout << "Pick choice 1 or 2 ";
		cin >> choice;

		while (choice != 1 && choice != 2) {

			cout << "Invalid choice";
			cout << "type 1 for viewing and 2 for editing ";
			cin >> choice;
		}
		if (choice == 1) {

			displayRecord(i);
		}
		else if (choice == 2) {

			editRecord(i);
		}
		


	}





};

