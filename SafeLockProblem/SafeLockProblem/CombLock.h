#pragma once
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
	int NH[4] = { 0,0,0,0 };
	
	
public:
	CombLock();//First Lock Constructor
	CombLock(const CombLock &comblock);//After Lock Constructor
	~CombLock();
	static void Generate_ROOT();
	static void Generate_UHF();
	static void Generate_LHF();
	static void Generate_PHF();
	static bool Build_SafeLock();
	int Turn(int x,int y);
	bool CheckCN();
	
	

	
};