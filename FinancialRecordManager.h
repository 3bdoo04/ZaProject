#include<iostream>
#include"PatientRecordManager.h"
#include<vector>
#pragma once

using namespace std;

class FinancialRecordManager : public PatientRecordManager
{

protected:

	double totalCharge;
	double totalDeposited;
	double totalMoneyToReturn;

public:

	FinancialRecordManager(double charge, double deposited)
		: totalCharge(charge), totalDeposited(deposited) {
		totalMoneyToReturn = totalDeposited - totalCharge;
	}
		void displayFinancialRecords(int recordNumber) {
			cout << "Financial Records for Patient with Record Number: " << recordNumber << endl;
			cout << "Total Charge: " << totalCharge << endl;
			cout << "Total Deposited: " << totalDeposited << endl;
			cout << "Total Money to Return: " << totalMoneyToReturn << endl;
		}
};

