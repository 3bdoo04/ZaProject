#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include"PatientRecordManager.h"
#pragma once

using namespace std;

class MedicineManager : public PatientRecordManager
{

protected:

    struct PatientMedicine {

        int recordNumber;
        vector<string> medicineList;
    };

    vector<PatientMedicine> patients;

public:

    void addMedicine(int recordNumber, string medicine) {
        auto it = find_if(patients.begin(), patients.end(), [recordNumber](const PatientMedicine& pm) {
            return pm.recordNumber == recordNumber;
            });

        if (it != patients.end()) {
            it->medicineList.push_back(medicine);
            cout << "Medicine added successfully for record number " << recordNumber << endl;
        }
        else {
            PatientMedicine pm;
            pm.recordNumber = recordNumber;
            pm.medicineList.push_back(medicine);
            patients.push_back(pm);
            cout << "Medicine added successfully for record number " << recordNumber << endl;
        }
    }

    void displayMedicine(int recordNumber) {
        auto it = find_if(patients.begin(), patients.end(), [recordNumber](const PatientMedicine& pm) {
            return pm.recordNumber == recordNumber;
            });

        if (it != patients.end()) {
            cout << "Medicine prescribed for record number " << recordNumber << ":" << endl;
            for (const string& medicine : it->medicineList) {
                cout << "- " << medicine << endl;
            }
        }
        else {
            cout << "No medicine found for record number " << recordNumber << endl;
        }
    }

    void deleteMedicine(int recordNumber, string medicine) {
        auto it = find_if(patients.begin(), patients.end(), [recordNumber](const PatientMedicine& pm) {
            return pm.recordNumber == recordNumber;
            });

        if (it != patients.end()) {
            auto& medicineList = it->medicineList;
            auto medicineIt = find(medicineList.begin(), medicineList.end(), medicine);
            if (medicineIt != medicineList.end()) {
                medicineList.erase(medicineIt);
                cout << "Medicine deleted successfully for record number " << recordNumber << endl;
            }
            else {
                cout << "Medicine not found for record number " << recordNumber << ". Cannot delete." << endl;
            }
        }
        else {
            cout << "No medicine found for record number " << recordNumber << ". Cannot delete." << endl;
        }
    }

};

