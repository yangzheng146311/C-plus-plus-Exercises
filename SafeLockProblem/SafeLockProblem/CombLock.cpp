#include "CombLock.h"


//FILE CombLock::myFile = FILE("test.txt");
ofstream CombLock::myfile = ofstream();
vector<CombLock> CombLock::CombVector = vector<CombLock>(5);
int CombLock::ROOT[4] = { 0,0,0,0 };
int CombLock::UHF[4] = { 0,0,0,0 };
int CombLock::LHF[4] = { 0,0,0,0 };
int CombLock::PHF[4] = { 0,0,0,0 };

//First Lock Constructor
CombLock::CombLock()
{
	id = 0;
	//cout << "CN"<<id << " ";
	myfile<< "CN" << id << " ";
	for (int i = 0; i < 4; i++)
	{
		CN[i] = Turn(ROOT[i], UHF[i]);
		//cout << CN[i];
		myfile << CN[i];
	}
	//cout << "\t";
	myfile<< "\t";
	//cout << "LN" << id << " ";
	myfile << "LN" << id << " ";
	for (int i = 0; i < 4; i++)
	{
		LN[i] = Turn(CN[i], LHF[i]);
		//cout << LN[i];
		myfile << LN[i];
	}
	//cout << "\t";
	myfile << "\t";
	//cout << "HN" << id << " ";
	myfile << "HN" << id << " ";
	for (int i = 0; i < 4; i++)
	{
		HN[i] = Turn(LN[i], PHF[i]);
		//cout << NH[i];
		myfile << HN[i];
	}
	//cout << endl;
	myfile << endl;

	
}

CombLock::CombLock(const CombLock &comblock)
{
	id = comblock.id + 1;
	//cout << "CN" << id << " ";
	myfile << "CN" << id << " ";
	for (int i = 0; i < 4; i++)
	{
		CN[i] = Turn(comblock.HN[i], UHF[i]);
		//cout << CN[i];
		myfile << CN[i];
	}
	//cout << "\t";
	myfile << "\t";
	//cout << "LN" << id << " ";
	myfile << "LN" << id << " ";
	for (int i = 0; i < 4; i++)
	{
		LN[i] = Turn(CN[i], LHF[i]);
		//cout << LN[i];
		myfile << LN[i];
	}
	//cout << "\t";
	myfile << "\t";
	//cout << "HN" << id << " ";
	myfile << "HN" << id << " ";
	for (int i = 0; i < 4; i++)
	{
		HN[i] = Turn(LN[i], PHF[i]);
		//cout << NH[i];
		myfile << HN[i];
	}

	//cout << endl;
	myfile << endl;

}

CombLock::~CombLock() {
}

void CombLock::InitialisePesudoRandom()
{
	srand(time(0));
}

void CombLock::Generate_ROOT()
{
	//cout << "ROOT\t";
	myfile << "ROOT\t";
	for (int i = 0; i < 4; i++)
	{
		
		ROOT[i] = rand() % 10;
		
		
			//cout << ROOT[i];
			myfile << ROOT[i];
	}
	//cout << endl;
	myfile << endl;
}

void CombLock::Generate_UHF()
{
	//cout << "UHF\t";
	myfile << "UHF\t";
	for (int i = 0; i < 4; i++)
	{

		UHF[i] = rand() % 18 - 9;
		if (UHF[i] > 0) { //cout << "+"; 
			myfile << "+"; }
		//cout << UHF[i]<<"\t";
		myfile << UHF[i] << "\t";
	}
	//cout << endl;
	myfile << endl;
}

void CombLock::Generate_LHF()
{
	//cout << "LHF\t";
	myfile << "LHF\t";
	for (int i = 0; i < 4; i++)
	{

		LHF[i] = rand() % 18 - 9;
		if (LHF[i] > 0) { //cout << "+"; 
			myfile << "+"; }
		//cout << LHF[i] << "\t";
		myfile<< LHF[i] << "\t";
	}
	//cout << endl;
	myfile << endl;
}

void CombLock::Generate_PHF()
{
	//cout << "PHF\t";
	myfile << "PHF\t";
	for (int i = 0; i < 4; i++)
	{

		PHF[i] = rand() % 18 - 9;
		if (PHF[i] > 0) { //cout << "+";
			myfile << "+"; }
		//cout << PHF[i] << "\t";
		myfile << PHF[i] << "\t";
	}
	//cout << endl;
	myfile << endl;
}

bool CombLock::Build_SafeLock()
{
	

	CombLock::Generate_ROOT();
	CombLock::Generate_UHF();
	CombLock::Generate_LHF();
	CombLock::Generate_PHF();

	CombLock c1; CombVector[0] = c1;
	CombLock c2(c1); CombVector[1] = c2;
	CombLock c3(c2); CombVector[2] = c3;
	CombLock c4(c3); CombVector[3] = c4;
	CombLock c5(c4); CombVector[4] = c5;

	
	if (!CheckAllCN()) return false;
	if (!CheckEven())   return false;

	
	return true;
}

int CombLock::Turn(int x,int y) {
	if (x + y < 0) return x + y + 10;
    if (x + y > 9) return x + y - 10;
    return x + y;

}

int CombLock::Generate_Number(int num[])
{
	return num[0] * 1000 + num[1] * 100 + num[2] * 10 + num[3] * 1;
}

bool CombLock::CheckCN()
{
	for (int i=0; i<4 ;i++)
	{
		for (int j = i+1; j < 4;j++)
		{
			if (CN[i] == CN[j]) { //cout << "UnMatched" << endl;
				myfile << "CN UnMatched" << endl; return false; }
		}
	}


	//cout << "Matched" << endl;
	myfile << "CN Matched" << endl;
	return true;



}

int CombLock::CN_Sum()
{
	int sum = 0;
	for (int i = 0; i < 4; i++)
	{
		sum += CN[i];
	}
	return sum;

}

int CombLock::LN_Sum()
{
	int sum = 0;
	for (int i = 0; i < 4; i++)
	{
		sum += LN[i];
	}
	return sum;

}

int CombLock::HN_Sum()
{
	int sum = 0;
	for (int i = 0; i < 4; i++)
	{
		sum += HN[i];
	}
	return sum;

}

int CombLock::CLHN_Sum()
{
	int sum = 0;
    sum= Generate_Number(CN) + Generate_Number(LN) + Generate_Number(HN);
	return sum;
}

bool CombLock::CheckAllCN()
{

	for (auto it = CombVector.begin(); it < CombVector.end(); it++)
	{
		if (!it->CheckCN()) return false;
	}

	return true;
}

bool CombLock::CheckSum()
{
	for (auto it = CombVector.begin(); it < CombVector.end()-1; it++)
	{
		
		if ((it->CN_Sum() >=(it + 1)->CN_Sum())|| (it->LN_Sum() >= (it + 1)->LN_Sum())|| (it->HN_Sum() >= (it + 1)->HN_Sum())) {
			myfile << "Sum UnMatched" << endl;
			return false;
		}
	}
	return true;
}

bool CombLock::CheckEven()
{
	int sum = 0;
	for (auto it = CombVector.begin(); it < CombVector.end(); it++)
	{
		sum += it->CLHN_Sum();
	}
	myfile << "sum ="<<sum << endl;
	if (sum % 2 != 0) return false;

	return true;
}