#pragma once
#include<stdlib.h>
#include<iostream>
#include<time.h>
#include<Windows.h>
#include<fstream>
#include<iomanip>
#include<vector>
#include<string>

#include<cmath>

using namespace std;

class CombLock
{
private:
	static int ROOT[4];//Used to store the ROOT generated randomly
	static int UHF_POS[16][4];
	static int UHF[4];//Used to store the UHF generated randomly
	static int LHF[4];//Used to store the LHF generated randomly
	static int PHF[4];//Used to store the PHF generated randomly
	

	static int CN_Temp[5][4];//Used to store the CN generated randomly and temporarily in coursework2
	static int LN_Temp[5][4];//Used to store the LN given in Lock Safed File in coursework2
	static int HN_Temp[5][4];//Used to store the HN generated by calculated PHF to work for coursework2

	
	
	int id = -1;//the id of a lock 
	int CN[4] = { 0,0,0,0 };//the CN number of a lock
	int LN[4] = { 0,0,0,0 };//the LN number of a lock
	int HN[4] = { 0,0,0,0 };//the HN number of a lock

	
	int Turn(int x, int y);//used to turn the lock digits from left to right or from right to left,parameter x is an original digit and parameter y is the direction and number that have to turn
	int  Generate_Number(int num[]);//uesd to create a int number from an int array
	bool CheckCN();//used to check if the CN of a lock contain same number of not
	static int myABS(int num);
	static int Reverse(int num);
	static int Temp_Turn(int x, int y);//the static version of Turn()
	static void Generate_ROOT();//used to generate the ROOT randomly
	static void Generate_UHF();//used to generate the UHF randomly
	static void Generate_LHF();//used to generate the LHF randomly
	static void Generate_PHF();//used to generate the PHF randomly
	static void Generate_UHF_POS();//used to enum all the UHF
	static bool Generate_CN();//used to generate CN1 and CN0 to make a sub to calculate UHF to decode for coursework2
	static void Calculate_PHF();//used to calculate the PHF for coursework2
	static void Calculate_LHF();//used to calculate the LHF for coursework2
	static bool CheckSum();//check if the sum of each digit in a CN order from large to small  
	static bool CheckAllCN();//check if each CN of a combination lock is same or not
	static bool CheckEven();//check if the Sum of all CN is even
	static void DataStruture_Key_Only();//output the key file 
	static void DataStruture_CLHN_Only(string check_result);//output the MultiSafe file and checked result
	static void DataStruture_LN_Only();//output the locksafe file
	static void Generate_MultiSafeFile();//Calculate the data used to generate multisafe file
	static void Generate_LockedSafeFile();//Calculate the data used to generate locksafe file
	static bool Generate_OriginKeyfile();//Calculate the data used to generate origina key file
	static vector<string> String_Split(const string& s, const char& c);//used to split string by specific char
	

public:
	static ofstream myfile_o;//use to output data in a txt file
	static ifstream myfile_f;//use to read data from a txt file
	static vector<CombLock> CombVector;//use to store 5 locks
	CombLock();//First Lock Constructor
	CombLock(const CombLock &comblock);//After Lock Constructor
	CombLock(int id,int CN[],int LN[],int HN[]);//specific Lock Construtor
	~CombLock();//deconstructor
	int  CN_Sum();//return the Sum of each digit of CN 
	int  LN_Sum();//return the Sum of each digit of LN
	int  HN_Sum();//return the Sum of each digit of HN
	int  CLHN_Sum();//return the Sum CN + LN + HN
	int  CN_Number();//return the number of CN
	static void Initialise();//Just initialise
	static bool Build_SafeLock();//create a correct multisafe lock
	static int TimesLimitVaildOutput(int times);//create a correct multisafe lock in limited time
	static void StopUntilOutputEnoughVaild(int soluNum,int timeToChangeHash);//create specific number of  correct multisafe locks by the same hash function with different Root,change the hash after specific time
	static void ReadKeyFile(string filename,string output_filename);//Read the key file
	static void WriteKeyFile(string filename);//Output keyfile
	static void ReadLockedSafeFile(string filename, string output_filename);//Output lock safe file

	
	
	
	
	
};


