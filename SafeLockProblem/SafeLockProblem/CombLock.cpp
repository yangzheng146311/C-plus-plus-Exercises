#include "CombLock.h"


//FILE CombLock::myFile = FILE("test.txt");
ofstream CombLock::myfile = ofstream();

int CombLock::ROOT[4] = { 0,0,0,0 };
int CombLock::UHF[4] = { 0,0,0,0 };
int CombLock::LHF[4] = { 0,0,0,0 };
int CombLock::PHF[4] = { 0,0,0,0 };

//First Lock Constructor
CombLock::CombLock()
{
	

	id = 0;
	cout << "CN"<<id << " ";
	myfile<< "CN" << id << " ";
	for (int i = 0; i < 4; i++)
	{
		CN[i] = Turn(ROOT[i], UHF[i]);
		cout << CN[i];
		myfile << CN[i];
	}
	cout << "\t";
	myfile<< "\t";
	cout << "LN" << id << " ";
	myfile << "LN" << id << " ";
	for (int i = 0; i < 4; i++)
	{
		LN[i] = Turn(CN[i], LHF[i]);
		cout << LN[i];
		myfile << LN[i];
	}
	cout << "\t";
	myfile << "\t";
	cout << "HN" << id << " ";
	myfile << "HN" << id << " ";
	for (int i = 0; i < 4; i++)
	{
		NH[i] = Turn(LN[i], PHF[i]);
		cout << NH[i];
		myfile << NH[i];
	}
	cout << endl;
	myfile << endl;

	
}

CombLock::CombLock(const CombLock &comblock)
{
	id = comblock.id + 1;
	cout << "CN" << id << " ";
	myfile << "CN" << id << " ";
	for (int i = 0; i < 4; i++)
	{
		CN[i] = Turn(comblock.NH[i], UHF[i]);
		cout << CN[i];
		myfile << CN[i];
	}
	cout << "\t";
	myfile << "\t";
	cout << "LN" << id << " ";
	myfile << "LN" << id << " ";
	for (int i = 0; i < 4; i++)
	{
		LN[i] = Turn(CN[i], LHF[i]);
		cout << LN[i];
		myfile << LN[i];
	}
	cout << "\t";
	myfile << "\t";
	cout << "HN" << id << " ";
	myfile << "HN" << id << " ";
	for (int i = 0; i < 4; i++)
	{
		NH[i] = Turn(LN[i], PHF[i]);
		cout << NH[i];
		myfile << NH[i];
	}

	cout << endl;
	myfile << endl;

}

CombLock::~CombLock() {
}

void CombLock::Generate_ROOT()
{
	srand(time(0));
	cout << "ROOT\t";
	myfile << "ROOT\t";
	for (int i = 0; i < 4; i++)
	{
		
		ROOT[i] = rand() % 10;
		
		
			cout << ROOT[i];
			myfile << ROOT[i];
	}
	cout << endl;
	myfile << endl;
}

void CombLock::Generate_UHF()
{
	srand(time(0));
	cout << "UHF\t";
	myfile << "UHF\t";
	for (int i = 0; i < 4; i++)
	{

		UHF[i] = rand() % 18 - 9;
		if (UHF[i] > 0) { cout << "+"; myfile << "+"; }
		cout << UHF[i]<<"\t";
		myfile << UHF[i] << "\t";
	}
	cout << endl;
	myfile << endl;
}

void CombLock::Generate_LHF()
{
	srand(time(0));
	cout << "LHF\t";
	myfile << "LHF\t";
	for (int i = 0; i < 4; i++)
	{

		LHF[i] = rand() % 18 - 9;
		if (LHF[i] > 0) { cout << "+"; myfile << "+"; }
		cout << LHF[i] << "\t";
		myfile<< LHF[i] << "\t";
	}
	cout << endl;
	myfile << endl;
}

void CombLock::Generate_PHF()
{
	srand(time(0));
	cout << "PHF\t";
	myfile << "PHF\t";
	for (int i = 0; i < 4; i++)
	{

		PHF[i] = rand() % 18 - 9;
		if (PHF[i] > 0) { cout << "+"; myfile << "+"; }
		cout << PHF[i] << "\t";
		myfile << PHF[i] << "\t";
	}
	cout << endl;
	myfile << endl;
}

bool CombLock::Build_SafeLock()
{
	


	CombLock::Generate_ROOT();
	

	CombLock::Generate_UHF();
	Sleep(1000);
	CombLock::Generate_LHF();
	Sleep(1000);
	CombLock::Generate_PHF();
	CombLock c1;
	CombLock c2(c1);
	CombLock c3(c2);
	CombLock c4(c3);
	CombLock c5(c4);


	if (!c1.CheckCN()) return false;
	if (!c2.CheckCN()) return false;
	if (!c3.CheckCN()) return false;
	if (!c4.CheckCN()) return false;
	if (!c5.CheckCN()) return false;

	
	return true;
}

int CombLock::Turn(int x,int y) {
	if (x + y < 0) return x + y + 10;
    if (x + y > 9) return x + y - 10;
    return x + y;

}

bool CombLock::CheckCN()
{
	for (int i=0; i<4 ;i++)
	{
		for (int j = i+1; j < 4;j++)
		{
			if (CN[i] == CN[j]) { cout << "UnMatched" << endl;myfile << "UnMatched" << endl; return false; }
		}
	}


	cout << "Matched" << endl;
	myfile << "Matched" << endl;
	return true;



}