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

class FileHandler : public PatientRecordManager : public FinancialRecordManager : public TreatmentManager : public MedicineManager
{







};

