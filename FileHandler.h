#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include"PatientRecordManager.h"
#include"FinancialRecordManager.h"
#include"TreatmentManager.h"
#include"MedicineManager.h"
#pragma once

using namespace std;

class FileHandler  {

public:
    void saveToFile(const vector<PatientRecordManager::PatientRecord>& patientRecords) {
        ofstream outFile("patient_records.txt");
        cout << patientRecords.size() << endl;
        if (outFile.is_open()) {
            for (const auto& record : patientRecords) {
                outFile << record.name << "," << record.address << "," << record.age << "," << record.sex << ","
                    << record.diseaseDescription << "," << record.specialistRoomNumber << endl;
            }
            outFile.close();
            cout << "Patient records saved to file." << endl;
        }
        else {
            cout << "Unable to open file for saving patient records." << endl;
        }
    }

    void readFromFile(vector<PatientRecordManager::records>& patientRecords) {
        ifstream inFile("patient_records.txt");

        if (inFile.is_open()) {
            string line;
            while (getline(inFile, line)) {
                std::istringstream ss(line);

                string name, address, diseaseDescription;
                int age, specialistRoomNumber;
                char sex;
                getline(ss, name, ',');
                getline(ss, address, ',');
                ss >> age;
                ss.ignore();
                ss >> sex;
                ss.ignore();
                getline(ss, diseaseDescription, ',');
                ss >> specialistRoomNumber;
                patientRecords.push_back({ name, address, age, sex, diseaseDescription, specialistRoomNumber });
            }
            inFile.close();
            cout << "Patient records loaded from file." << endl;
        }
        else {
            cout << "Unable to open file for reading patient records." << endl;
        }
    }

    void updateFile(const vector<PatientRecordManager::PatientRecord>& patientRecords) {
        saveToFile(patientRecords);
    }





};

