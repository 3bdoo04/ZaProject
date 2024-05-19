#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <string>
#include <limits>
#include <algorithm>
#include <sstream> 

using namespace std;

class PatientRecordManager {

public:
    struct PatientRecord {
        string name;
        string address;
        int age;
        char gender;
        string diseaseDescription;
        int specialistRoomNumber;
        string service;
    };

private:
    vector<PatientRecord> records;

public:
    void addNewPatient(string name, string address, int age, char gender, string diseaseDescription, int specialistRoomNumber, string service) {
        PatientRecord record = { name, address, age, gender, diseaseDescription, specialistRoomNumber, service };
        records.push_back(record);
    }

    const vector<PatientRecord>& getRecords() const {
        return records;
    }

    void searchOrEditPatientRecord(int recordNumber) {
        if (recordNumber >= 1 && recordNumber <= records.size()) {
            PatientRecord& record = records[recordNumber - 1];
            cout << "Record found." << endl << "Enter new name: ";
            string newName;
            cin.ignore();
            getline(cin, newName);
            record.name = newName;
        }
        else {
            cout << "Record not found." << endl;
        }
    }

    void searchOrEditPatientRecord(string fullName) {
        for (auto& record : records) {
            if (record.name == fullName) {
                cout << "Record found." << endl;
                cout << "Enter new name: ";
                string newName;
                cin.ignore();
                getline(cin, newName);
                record.name = newName;
                return;
            }
        }
        cout << "Record not found." << endl;
    }

    void listPatientRecords(string choice) {
        for (const auto& record : records) {
            cout << "Name: " << record.name << ", Address: " << record.address
                << ", Age: " << record.age << ", Gender: " << record.gender
                << ", Disease: " << record.diseaseDescription
                << ", Room: " << record.specialistRoomNumber
                << ", Service: " << record.service << endl;
        }
    }

    void deletePatientRecord(int recordNumber) {
        if (recordNumber >= 1 && recordNumber <= records.size()) {
            records.erase(records.begin() + (recordNumber - 1));
            cout << "Record deleted." << endl;
        }
        else {
            cout << "Record not found." << endl;
        }
    }
};

class FinancialRecordManager {
private:
    struct FinancialRecord {
        double totalCharge;
        double totalDeposited;
        double totalMoneyToReturn;
    };

    unordered_map<int, FinancialRecord> records;

public:
    void addFinancialRecord(int recordNumber, double totalCharge, double totalDeposited, double totalMoneyToReturn) {
        records[recordNumber] = { totalCharge, totalDeposited, totalMoneyToReturn };
    }

    void editFinancialRecord(int recordNumber, double totalCharge, double totalDeposited, double totalMoneyToReturn) {
        if (records.find(recordNumber) != records.end()) {
            records[recordNumber] = { totalCharge, totalDeposited, totalMoneyToReturn };
        }
        else {
            cout << "Financial Record not found for Record Number: " << recordNumber << endl;
        }
    }

    void displayFinancialRecords(int recordNumber) {
        auto it = records.find(recordNumber);
        if (it != records.end()) {
            cout << "Financial Records for Record Number: " << recordNumber << endl;
            cout << "Total Charge: " << it->second.totalCharge << endl;
            cout << "Total Deposited: " << it->second.totalDeposited << endl;
            cout << "Total Money to Return: " << it->second.totalMoneyToReturn << endl;
        }
        else {
            cout << "Financial Records not found for Record Number: " << recordNumber << endl;
        }
    }
};

class TreatmentManager {
private:
    unordered_map<int, string> treatments;

public:
    void addTreatment(int recordNumber, string treatmentDescription) {
        treatments[recordNumber] = treatmentDescription;
    }

    void displayTreatment(int recordNumber) {
        auto it = treatments.find(recordNumber);
        if (it != treatments.end()) {
            cout << "Treatment for Record Number: " << recordNumber << ": " << it->second << endl;
        }
        else {
            cout << "Treatment not found for Record Number: " << recordNumber << endl;
        }
    }

    void editTreatment(int recordNumber, string newTreatmentDescription) {
        if (treatments.find(recordNumber) != treatments.end()) {
            treatments[recordNumber] = newTreatmentDescription;
            cout << "Treatment updated." << endl;
        }
        else {
            cout << "Treatment not found for Record Number: " << recordNumber << endl;
        }
    }

    void deleteTreatment(int recordNumber) {
        if (treatments.erase(recordNumber)) {
            cout << "Treatment deleted." << endl;
        }
        else {
            cout << "Treatment not found for Record Number: " << recordNumber << endl;
        }
    }
};

class MedicineManager {
private:
    unordered_map<int, vector<string>> medicineLists;

public:
    void addMedicine(int recordNumber, string medicine) {
        medicineLists[recordNumber].push_back(medicine);
    }

    void displayMedicine(int recordNumber) {
        auto it = medicineLists.find(recordNumber);
        if (it != medicineLists.end()) {
            cout << "Medicines for Record Number: " << recordNumber << ": ";
            for (const auto& medicine : it->second) {
                cout << medicine << ", ";
            }
            cout << endl;
        }
        else {
            cout << "Medicines not found for Record Number: " << recordNumber << endl;
        }
    }

    void deleteMedicine(int recordNumber, string medicine) {
        auto it = medicineLists.find(recordNumber);
        if (it != medicineLists.end()) {
            auto& medicines = it->second;
            auto pos = std::find(medicines.begin(), medicines.end(), medicine);
            if (pos != medicines.end()) {
                medicines.erase(pos);
                cout << "Medicine deleted." << endl;
            }
            else {
                cout << "Medicine not found." << endl;
            }
        }
        else {
            cout << "Medicines not found for Record Number: " << recordNumber << endl;
        }
    }
};

class FileHandler {
public:
    struct PatientRecord {
        string name;
        string address;
        int age;
        char gender;
        string diseaseDescription;
        int specialistRoomNumber;
        string service;
    };

    void saveToFile(const vector<PatientRecordManager::PatientRecord>& patientRecords) {
        ofstream outFile("HospitalData.txt");
        if (outFile.is_open()) {
            outFile << patientRecords.size() << endl;
            for (const auto& record : patientRecords) {
                outFile << record.name << endl
                    << record.address << endl
                    << record.age << endl
                    << record.gender << endl
                    << record.diseaseDescription << endl
                    << record.specialistRoomNumber << endl
                    << record.service << endl;
            }
            outFile.close();
            cout << "Patient records saved to file." << endl;
        }
        else {
            cout << "Unable to open file for saving patient records." << endl;
        }
    }

    vector<PatientRecord> readFromFile() {
        vector<PatientRecord> patientRecords;
        ifstream inFile("HospitalData.txt");
        if (inFile.is_open()) {
            int size;
            inFile >> size;
            inFile.ignore();
            for (int i = 0; i < size; ++i) {
                PatientRecord record;
                getline(inFile, record.name);
                getline(inFile, record.address);
                inFile >> record.age;
                inFile.ignore();
                inFile >> record.gender;
                inFile.ignore();
                getline(inFile, record.diseaseDescription);
                inFile >> record.specialistRoomNumber;
                inFile.ignore();
                getline(inFile, record.service);
                patientRecords.push_back(record);
            }
            inFile.close();
        }
        else {
            cout << "Unable to open file for reading patient records." << endl;
        }
        return patientRecords;
    }

    void updateFile(const vector<PatientRecordManager::PatientRecord>& patientRecords) {
        saveToFile(patientRecords);
    }
};

class Menu {
public:
    void displayMainMenu() {
        cout << "\t\t\t\t**Hospital Management System*" << endl << endl;
        cout << "1.  Add New Patient Record" << endl;
        cout << "2.  Search/Edit Patient Record" << endl;
        cout << "3.  Display the List Patient Records" << endl;
        cout << "4.  Delete a Patient Record" << endl;
        cout << "5.  Add/Edit Financial Records of patients" << endl;
        cout << "6.  Display Financial Records of patients" << endl;
        cout << "7.  Add Treatment details for patient" << endl;
        cout << "8.  Display Treatment details of a patient" << endl;
        cout << "9.  Edit Treatment details of a patient" << endl;
        cout << "10. Delete Treatment details of a patient" << endl;
        cout << "11. Add Medicines for a patient" << endl;
        cout << "12. Display Medicines for a patient" << endl;
        cout << "13. Delete Medicines for a patient" << endl;
        cout << "14. Save to File" << endl;
        cout << "15. Exit" << endl;
    }

    int getUserChoice() {
        int choice;
        cout << endl << "Enter your choice: ";
        cin >> choice;
        return choice;
    }

    int getRecordNumberInput() {
        int recordNumber;
        cout << "Enter the patient record number: ";
        while (true) {
            cin >> recordNumber;
            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input. Please enter a valid record number: ";
            }
            else {
                break;
            }
        }
        return recordNumber;
    }

    string getListChoice() {
        string choice;
        cout << "Enter choice (all/specific): ";
        cin.ignore();
        getline(cin, choice);
        return choice;
    }

    string getServiceChoice() {
        string service;
        cout << "Enter service: ";
        cin.ignore();
        getline(cin, service);
        return service;
    }

    void displayFinancialMenu() {
        cout << "1. Add Financial Record" << endl;
        cout << "2. Edit Financial Record" << endl;
        cout << "3. Go Back" << endl;
    }

    int getFinancialChoice() {
        int choice;
        cout << "Enter your choice: ";
        cin >> choice;
        return choice;
    }
};

int main() {
    PatientRecordManager patientRecordManager;
    FinancialRecordManager financialRecordManager;
    TreatmentManager treatmentManager;
    MedicineManager medicineManager;
    FileHandler fileHandler;
    Menu menu;

    vector<FileHandler::PatientRecord> patientRecordsFromFile = fileHandler.readFromFile();
    for (const auto& record : patientRecordsFromFile) {
        patientRecordManager.addNewPatient(record.name, record.address, record.age, record.gender, record.diseaseDescription, record.specialistRoomNumber, record.service);
    }

    int choice;
    do {
        menu.displayMainMenu();
        choice = menu.getUserChoice();

        switch (choice) {
        case 1: {
            string name, address, diseaseDescription, service;
            int age, specialistRoomNumber;
            char gender;

            cout << "Enter patient details:" << endl;
            cout << "Name: ";
            cin.ignore();
            getline(cin, name);
            cout << "Address: ";
            getline(cin, address);
            cout << "Age: ";
            while (true) {
                cin >> age;
                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Invalid input for age. Please enter a number: ";
                }
                else {
                    break;
                }
            }
            cout << "Gender (M/F): ";
            while (true) {
                cin >> gender;
                if (gender == 'M' || gender == 'F') {
                    break;
                }
                else {
                    cout << "Invalid input! Please enter M or F: ";
                }
            }
            cin.ignore();
            cout << "Disease Description: ";
            getline(cin, diseaseDescription);
            cout << "Specialist Room Number: ";
            while (true) {
                cin >> specialistRoomNumber;
                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Invalid input for room number. Please enter a number: ";
                }
                else {
                    break;
                }
            }
            service = menu.getServiceChoice();
            patientRecordManager.addNewPatient(name, address, age, gender, diseaseDescription, specialistRoomNumber, service);
            cout << endl;
            break;
        }
        case 2: {
            int recordNumber = menu.getRecordNumberInput();
            patientRecordManager.searchOrEditPatientRecord(recordNumber);
            break;
        }
        case 3: {
            string choice = menu.getListChoice();
            patientRecordManager.listPatientRecords(choice);
            break;
        }
        case 4: {
            int recordNumber = menu.getRecordNumberInput();
            patientRecordManager.deletePatientRecord(recordNumber);
            break;
        }
        case 5: {
            int recordNumber = menu.getRecordNumberInput();
            menu.displayFinancialMenu();
            int financialChoice = menu.getFinancialChoice();
            if (financialChoice == 1) {
                double totalCharge, totalDeposited, totalMoneyToReturn;
                cout << "Enter total charge: ";
                cin >> totalCharge;
                cout << "Enter total deposited: ";
                cin >> totalDeposited;
                cout << "Enter total money to return: ";
                cin >> totalMoneyToReturn;
                financialRecordManager.addFinancialRecord(recordNumber, totalCharge, totalDeposited, totalMoneyToReturn);
            }
            else if (financialChoice == 2) {
                double totalCharge, totalDeposited, totalMoneyToReturn;
                cout << "Enter total charge: ";
                cin >> totalCharge;
                cout << "Enter total deposited: ";
                cin >> totalDeposited;
                cout << "Enter total money to return: ";
                cin >> totalMoneyToReturn;
                financialRecordManager.editFinancialRecord(recordNumber, totalCharge, totalDeposited, totalMoneyToReturn);
            }
            break;
        }
        case 6: {
            int recordNumber = menu.getRecordNumberInput();
            financialRecordManager.displayFinancialRecords(recordNumber);
            break;
        }
        case 7: {
            int recordNumber = menu.getRecordNumberInput();
            string treatment;
            cout << "Enter treatment description: ";
            cin.ignore();
            getline(cin, treatment);
            treatmentManager.addTreatment(recordNumber, treatment);
            break;
        }
        case 8: {
            int recordNumber = menu.getRecordNumberInput();
            treatmentManager.displayTreatment(recordNumber);
            break;
        }
        case 9: {
            int recordNumber = menu.getRecordNumberInput();
            string newTreatment;
            cout << "Enter new treatment description: ";
            cin.ignore();
            getline(cin, newTreatment);
            treatmentManager.editTreatment(recordNumber, newTreatment);
            break;
        }
        case 10: {
            int recordNumber = menu.getRecordNumberInput();
            treatmentManager.deleteTreatment(recordNumber);
            break;
        }
        case 11: {
            int recordNumber = menu.getRecordNumberInput();
            string medicine;
            cout << "Enter medicine: ";
            cin.ignore();
            getline(cin, medicine);
            medicineManager.addMedicine(recordNumber, medicine);
            break;
        }
        case 12: {
            int recordNumber = menu.getRecordNumberInput();
            medicineManager.displayMedicine(recordNumber);
            break;
        }
        case 13: {
            int recordNumber = menu.getRecordNumberInput();
            string medicine;
            cout << "Enter medicine to delete: ";
            cin.ignore();
            getline(cin, medicine);
            medicineManager.deleteMedicine(recordNumber, medicine);
            break;
        }
        case 14: {
            fileHandler.updateFile(patientRecordManager.getRecords());
            break;
        }
        case 15: {
            fileHandler.saveToFile(patientRecordManager.getRecords());
            cout << "Exiting program . . ." << endl;
            return 0;
        }
        default:
            cout << "Invalid input. Please enter a number between 1 and 15." << endl;
        }

    } while (choice != 15);

    return 0;
}