#include<iostream>
#include<string>
#include<vector>
#include<unordered_map>
#include"PatientRecordManager.h"
#pragma once

using namespace std;

class TreatmentManager : public PatientRecordManager
{

protected:

	int recordNumber;
	string treatmentDescription;
	unordered_map<int, string> treatments;

public:

    void addTreatment(int recordNumber, string treatmentDescription) {
        treatments[recordNumber] = treatmentDescription;
        cout << "Treatment added successfully for record number " << recordNumber << endl;
    }

    void displayTreatment(int recordNumber) {
        auto it = treatments.find(recordNumber);
        if (it != treatments.end()) {
            cout << "Treatment for record number " << recordNumber << ": " << it->second << endl;
        }
        else {
            cout << "No treatment found for record number " << recordNumber << endl;
        }
    }

    void editTreatment(int recordNumber, string newTreatmentDescription) {
        auto it = treatments.find(recordNumber);
        if (it != treatments.end()) {
            it->second = newTreatmentDescription;
            cout << "Treatment edited successfully for record number " << recordNumber << endl;
        }
        else {
            cout << "No treatment found for record number " << recordNumber << ". Cannot edit." << endl;
        }
    }

    void deleteTreatment(int recordNumber) {
        auto it = treatments.find(recordNumber);
        if (it != treatments.end()) {
            treatments.erase(it);
            cout << "Treatment deleted successfully for record number " << recordNumber << endl;
        }
        else {
            cout << "No treatment found for record number " << recordNumber << ". Cannot delete." << endl;
        }
    }
};

