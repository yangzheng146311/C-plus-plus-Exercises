#include "pch.h"
#include "CombLock.h"
#include<stdlib.h>
#include<iostream>
#include<time.h>
#include<Windows.h>
using namespace std;
int CombLock:: ROOT[4] = { 0,0,0,0 };
int CombLock:: UHF[4] = { 0,0,0,0 };
int CombLock:: LHF[4] = { 0,0,0,0 };
int CombLock:: PHF[4] = { 0,0,0,0 };

//First Lock Constructor
CombLock::CombLock()
{
	id = 0;
	cout << "CN"<<id << " ";
	for (int i = 0; i < 4; i++)
	{
		CN[i] = Move(ROOT[i], UHF[i]);
		cout << CN[i];
	}
	cout << "\t";
	cout << "LN" << id << " ";
	for (int i = 0; i < 4; i++)
	{
		LN[i] = Move(CN[i], LHF[i]);
		cout << LN[i];
	}
	cout << "\t";
	cout << "HN" << id << " ";
	for (int i = 0; i < 4; i++)
	{
		NH[i] = Move(LN[i], PHF[i]);
		cout << NH[i];
	}
	cout << endl;
}

CombLock::CombLock(const CombLock &comblock)
{
	id = comblock.id + 1;
	cout << "CN" << id << " ";
	for (int i = 0; i < 4; i++)
	{
		CN[i] = Move(comblock.NH[i], UHF[i]);
		cout << CN[i];
	}
	cout << "\t";
	cout << "LN" << id << " ";
	for (int i = 0; i < 4; i++)
	{
		LN[i] = Move(CN[i], LHF[i]);
		cout << LN[i];
	}
	cout << "\t";
	cout << "HN" << id << " ";
	for (int i = 0; i < 4; i++)
	{
		NH[i] = Move(LN[i], PHF[i]);
		cout << NH[i];
	}

	cout << endl;

}

CombLock::~CombLock() {}

void CombLock::Generate_ROOT()
{
	srand(time(0));
	cout << "ROOT\t";
	for (int i = 0; i < 4; i++)
	{
		
		ROOT[i] = rand() % 10;
		cout << ROOT[i];
	}
	cout << endl;
}

void CombLock::Generate_UHF()
{
	srand(time(0));
	cout << "UHF\t";
	for (int i = 0; i < 4; i++)
	{

		UHF[i] = rand() % 18 - 9;
		cout << UHF[i]<<"\t";
	}
	cout << endl;
}

void CombLock::Generate_LHF()
{
	srand(time(0));
	cout << "LHF\t";
	for (int i = 0; i < 4; i++)
	{

		LHF[i] = rand() % 18 - 9;
		cout << LHF[i] << "\t";
	}
	cout << endl;
}

void CombLock::Generate_PHF()
{
	srand(time(0));
	cout << "PHF\t";
	for (int i = 0; i < 4; i++)
	{

		PHF[i] = rand() % 18 - 9;
		cout << PHF[i] << "\t";
	}
	cout << endl;
}

void CombLock::Build_SafeLock()
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
}

int CombLock::Move(int x,int y) {
	if (x + y < 0) return x + y + 10;
    if (x + y > 9) return x + y - 10;
    return x + y;

}