#pragma once
#include<stdlib.h>
#include<iostream>
#include<time.h>
#include<Windows.h>
#include<fstream>
#include<iomanip>
#include<vector>
#include<string>

using namespace std;

class CombLock
{
private:
	static int ROOT[4];
	static int UHF[4];
	static int LHF[4];
	static int PHF[4];

	static int CN_Temp[5][4];
	static int LN_Temp[5][4];
	static int HN_Temp[5][4];
	
	
	int id = -1;
	int CN[4] = { 0,0,0,0 };
	int LN[4] = { 0,0,0,0 };
	int HN[4] = { 0,0,0,0 };

	int Turn(int x, int y);
	int  Generate_Number(int num[]);
	bool CheckCN();
	
	static int Temp_Turn(int x, int y);
	static void Generate_ROOT();
	static void Generate_UHF();
	static void Generate_LHF();
	static void Generate_PHF();
	static void Calculate_PHF();
	static void Calculate_LHF();
	static bool CheckSum();//Check if each digit in a CN is same or not
	static bool CheckAllCN();//Check if all the combination locks satisfy the rule
	static bool CheckEven();//Check if the Sum of all CN is even
	static void DataStruture_Key_Only();
	static void DataStruture_CLHN_Only(string check_result);
	static void DataStruture_LN_Only();
	static void Generate_MultiSafeFile();
	static void Generate_LockedSafeFile();
	static bool Generate_OriginKeyfile();
	static vector<string> String_Split(const string& s, const char& c);
	

public:
	static ofstream myfile_o;
	static ifstream myfile_f;
	static vector<CombLock> CombVector;
	CombLock();//First Lock Constructor
	CombLock(const CombLock &comblock);//After Lock Constructor
	CombLock(int id,int CN[],int LN[],int HN[]);
	~CombLock();
	int  CN_Sum();
	int  LN_Sum();
	int  HN_Sum();
	int  CLHN_Sum();
	int  CN_Number();
	static void Initialise();
	static bool Build_SafeLock();
	static bool TimesLimitVaildOutput(int times);
	static void StopUntilOutputEnoughVaild(int soluNum,int timeToChangeHash);
	static void ReadKeyFile(string filename,string output_filename);
	static void WriteKeyFile(string filename);
	static void ReadLockedSafeFile(string filename, string output_filename);

	
	
	
	
	
};
