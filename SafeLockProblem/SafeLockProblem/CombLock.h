#pragma once
#include<stdlib.h>
#include<iostream>
#include<time.h>
#include<Windows.h>
#include<fstream>
#include<iomanip>
#include<vector>

using namespace std;

class CombLock
{
private:
	static int ROOT[4];
	static int UHF[4];
	static int LHF[4];
	static int PHF[4];
	
	
	int id = -1;
	int CN[4] = { 0,0,0,0 };
	int LN[4] = { 0,0,0,0 };
	int HN[4] = { 0,0,0,0 };

	int Turn(int x, int y);
	int  Generate_Number(int num[]);
	bool CheckCN();
	static void Generate_ROOT();
	static void Generate_UHF();
	static void Generate_LHF();
	static void Generate_PHF();

public:
	static ofstream myfile;
	static vector<CombLock> CombVector;
	CombLock();//First Lock Constructor
	CombLock(const CombLock &comblock);//After Lock Constructor
	~CombLock();
	int  CN_Sum();
	int  LN_Sum();
	int  HN_Sum();
	int  CLHN_Sum();
	static void InitialisePesudoRandom();
	static bool Build_SafeLock();
	static bool CheckSum();
	static bool CheckAllCN();
	static bool CheckEven();
	
};
