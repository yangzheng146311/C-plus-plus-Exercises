#include "CombLock.h"
//FILE CombLock::myfile_o = FILE("test.txt");
ofstream CombLock::myfile_o = ofstream();
ifstream CombLock::myfile_f = ifstream();
vector<CombLock> CombLock::CombVector = vector<CombLock>(5);
int CombLock::ROOT[4] = { 0,0,0,0 };
int CombLock::UHF[4] = { 0,0,0,0 };
int CombLock::LHF[4] = { 0,0,0,0 };
int CombLock::PHF[4] = { 0,0,0,0 };
int  CombLock::CN_Temp[5][4] = { {0,0,0,0}, {0,0,0,0}, {0,0,0,0}, {0,0,0,0}, {0,0,0,0}};
int  CombLock::LN_Temp[5][4] = { {0,0,0,0}, {0,0,0,0}, {0,0,0,0}, {0,0,0,0}, {0,0,0,0}};
int  CombLock::HN_Temp[5][4] = { {0,0,0,0}, {0,0,0,0}, {0,0,0,0}, {0,0,0,0}, {0,0,0,0}};
//First Lock Constructor
CombLock::CombLock()
{
	id = 0;
	for (int i = 0; i < 4; i++)
	{
		CN[i] = Turn(ROOT[i], UHF[i]);

	}
	for (int i = 0; i < 4; i++)
	{
		LN[i] = Turn(CN[i], LHF[i]);

	}
	for (int i = 0; i < 4; i++)
	{
		HN[i] = Turn(LN[i], PHF[i]);

	}
	
}

CombLock::CombLock(const CombLock &comblock)
{
	id = comblock.id + 1;
	for (int i = 0; i < 4; i++)
	{
		CN[i] = Turn(comblock.HN[i], UHF[i]);
		
	}

	for (int i = 0; i < 4; i++)
	{
		LN[i] = Turn(CN[i], LHF[i]);
	
	}
	
	for (int i = 0; i < 4; i++)
	{
		HN[i] = Turn(LN[i], PHF[i]);
	
	}

}

CombLock::CombLock(int id,int CN[], int LN[], int HN[])
{
	this->id = id;
	for (int i = 0; i < 4; i++)
	{
		this->CN[i] = CN[i];
		this->LN[i] = LN[i];
		this->HN[i] = HN[i];
	}
}

CombLock::~CombLock() {
}

void CombLock::Initialise()
{
	srand(time(0));
	CombLock::Generate_UHF();
	CombLock::Generate_LHF();
	CombLock::Generate_PHF();
	
}

int CombLock::Temp_Turn(int x, int y)
{
	if (x + y < 0) return x + y + 10;
	if (x + y > 9) return x + y - 10;
	return x + y;
}

void CombLock::Generate_ROOT()
{
	
	for (int i = 0; i < 4; i++)
	{
		
		ROOT[i] = rand() % 10;
		
	}

}

void CombLock::Generate_UHF()
{
	
	for (int i = 0; i < 4; i++)
	{

		UHF[i] = rand() % 18 - 9;
	
	}

}

void CombLock::Generate_LHF()
{
	
	for (int i = 0; i < 4; i++)
	{

		LHF[i] = rand() % 18 - 9;
	
	}
	
}

void CombLock::Generate_PHF()
{
	
	for (int i = 0; i < 4; i++)
	{

		PHF[i] = rand() % 18 - 9;
		
	}
	
}

void CombLock::Calculate_PHF()
{
	int temp = 0;
	//cout << "PHF:";
	for (int i = 0; i < 4; i++)
	{

		temp = (LN_Temp[1][i] - 2 * LN_Temp[0][i] + ROOT[i]);
		if (temp >=10) temp -= 10;
		if (temp <= -10) temp += 10;
		PHF[i] = temp;
		//cout <<PHF[i]<<endl;
	}
	//cout << endl;
}

void CombLock::Calculate_LHF()
{
	int temp = 0;
	//cout << "LHF:";
	for (int i = 0; i < 4; i++)
	{

		temp = (LN_Temp[0][i]-ROOT[i]-UHF[i]);
		if (temp >= 10) temp -= 10;
		if (temp <= -10) temp += 10;
		LHF[i] = temp;
		//cout << PHF[i] << endl;
	}
	//cout << endl;
}

bool CombLock::Build_SafeLock()
{
	
	CombLock::Generate_ROOT();
	

	CombLock c1; CombVector[0] = c1;
	CombLock c2(c1); CombVector[1] = c2;
	CombLock c3(c2); CombVector[2] = c3;
	CombLock c4(c3); CombVector[3] = c4;
	CombLock c5(c4); CombVector[4] = c5;


	
	
	if (!CheckAllCN())  return false;
	if (!CheckSum())    return false;
	if (!CheckEven())   return false;
	DataStruture_Key_Only();
	
	return true;
}

bool CombLock::TimesLimitVaildOutput(int times)
{
	bool ifFound = false;
	for (int i = 1; i <= times; i++)
	{
		if (!CombLock::Build_SafeLock())
		{
			std::cout << "This is the " << i << "  times" << std::endl;
			//CombLock::myfile_o << "This is the " << i << "times" << std::endl;
		}
		else
		{
			ifFound = true;
			return ifFound;
		}
	}
	if (!ifFound)
	{
		//std::cout << "Solution not found in " << times << "times" << std::endl;
		//CombLock::myfile_o << "Solution not found in " << times << " times" << std::endl;
		return ifFound;
		
	}

}

void CombLock::StopUntilOutputEnoughVaild(int soluNum,int timeToChangeHash)
{
	int i = 0;
	CombLock::myfile_o << "NS " << soluNum << endl;
	for (int t=1; t <=soluNum; t++)
	{
		
		//while (!CombLock::Build_SafeLock())
		//{

		//	i++;
		//	std::cout << "This is the " << i << "  times" << std::endl;
		//	//CombLock::myfile_o << "This is the " << i << " times" << std::endl;

		//}
		while (!CombLock::TimesLimitVaildOutput(timeToChangeHash))
		{
			CombLock::Generate_UHF();
			CombLock::Generate_LHF();
			CombLock::Generate_PHF();

		}
	}

}

void CombLock::ReadKeyFile(string filename,string output_filename)
{
	CombLock::myfile_f.open(filename);
	CombLock::myfile_o.open(output_filename, std::ofstream::out);
	string str;
	char buff_c;
	bool ifoutput = false;
	int op = -1;
	cout << "Press '1' for multi_safe_file" << endl;
	cout << "Press '2' for locked_file" << endl;
	std::cin >> op;
	while (!CombLock::myfile_f.eof())

	{
	  getline(CombLock::myfile_f, str);
	   if (str.length() > 0)
			{
		        ifoutput = false;
			    vector<string> v = String_Split(str, ' ');
			
				if (v[0] == "ROOT")
				{
					for (int i=0;i<4;i++)
					{
						buff_c = v[1][i];
						ROOT[i]= atoi(&buff_c);
						
					}		
				}
				else
				{
			     vector<string> v1 = String_Split(v[1], ',');
				 for (int i = 0; i < 4; i++)
				 {

					 if (v[0] == "UHF") UHF[i] = stoi(v1[i]);
					 if (v[0] == "LHF") LHF[i] = stoi(v1[i]);
					 if (v[0] == "PHF") PHF[i] = stoi(v1[i]); 
				 }
				}					
		}
	   else
		   if (ifoutput == false)
		   {
			   switch (op)
			   {
			   case 1:Generate_MultiSafeFile(); break;
			   case 2:Generate_LockedSafeFile(); break;
			   default:
				   break;
			   }

			   ifoutput = true;
		   }

	}

	CombLock::myfile_f.close();

	CombLock::myfile_o.close();

}

void CombLock::WriteKeyFile(string filename)
{
	int op = -1;
	int times = -1;
	int num = -1;
	int timeToChangeHash = -1;
	CombLock::Initialise();

	CombLock::myfile_o.open(filename, std::ofstream::out);

	cout << "Please select modes" << endl;
	cout << "Press '1':Generate keys  in limited times" << endl;
	cout << "Press '2':Generate keys with referred number"<< endl;

	cin >> op;

	switch (op)
	{
	case 1:
		
		cout << "Please input the times limited:" << endl;
		cin >> times;
		while (!CombLock::TimesLimitVaildOutput(times))
		{
			CombLock::Generate_UHF();
			CombLock::Generate_LHF();
			CombLock::Generate_PHF();

		}
		
		break;

	case 2:
		
		cout << "Please input specific number of keys" << endl;
		cin >> num;
		cout << "Please input the specific time to change the Hash Function if enough solutions can not be found " << endl;
		cin >> timeToChangeHash;
		CombLock::StopUntilOutputEnoughVaild(num,timeToChangeHash);
	default:
		break;
	}

	CombLock::myfile_o.close();

}

void CombLock::ReadLockedSafeFile(string filename, string output_filename)
{
	CombLock::myfile_f.open(filename);
	CombLock::myfile_o.open(output_filename, std::ofstream::out);
	string str;
	string buff_s;
	bool ifoutput = false;
	vector<string> v;
	int time = 1;//run times
	while (!CombLock::myfile_f.eof())

	{
		getline(CombLock::myfile_f, str);

		//Read LN0-LN5 from txt 
		if (str.length() > 0)
		{
			ifoutput = false;
			v = String_Split(str, ' ');

			if (v[0] == "ROOT:")
			{
				for (int i = 1; i <= 4; i++)
				{
					buff_s = v[i];
					ROOT[i-1] = stoi(buff_s);

				}
			}
			if (v[0] == "LN0:")
			{
				for (int i = 1; i <= 4; i++)
				{
					buff_s = v[i];
					LN_Temp[0][i-1] = stoi(buff_s);

				}
			}
			if (v[0] == "LN1:")
			{
				for (int i = 1; i <= 4; i++)
				{
					buff_s = v[i];
					LN_Temp[1][i-1] = stoi(buff_s);

				}
			}
			if (v[0] == "LN2:")
			{
				for (int i = 1; i <= 4; i++)
				{
					buff_s = v[i];
					LN_Temp[2][i-1] = stoi(buff_s);

				}
			}
			if (v[0] == "LN3:")
			{
				for (int i = 1; i <= 4; i++)
				{
					buff_s = v[i];
					LN_Temp[3][i-1] = stoi(buff_s);

				}
			}
			if (v[0] == "LN4:")
			{
				for (int i = 1; i <= 4; i++)
				{
					buff_s = v[i];
					LN_Temp[4][i-1] = stoi(buff_s);

				}
			}
		}
		else
			if (ifoutput == false)
			{
				//Calculate the PHF by formula
				Calculate_PHF();
				//calculate the HN0-HN5
				for (int i = 0; i < 5; i++)
				{
					for (int j = 0; j < 4; j++)
					{
						HN_Temp[i][j] = Temp_Turn(LN_Temp[i][j], PHF[j]);
					}
					cout << endl;
				}
				while (!Generate_OriginKeyfile())
				{

					cout << "This is " << time << " times" << endl;
					time++;
				}
				
				ifoutput = true;
			}

	}

	CombLock::myfile_f.close();
	CombLock::myfile_o.close();

	
}

void CombLock::DataStruture_Key_Only()
{
	myfile_o << "ROOT ";
	for (int i = 0; i < 4; i++)
	{
		myfile_o << ROOT[i];
	}
	myfile_o << endl;

	myfile_o << "UHF ";
	for (int i = 0; i < 4; i++)
	{
		/*if (UHF[i] > 0) { 
			myfile_o << "+";
		}*/
		
		myfile_o << std::showpos<< UHF[i];
		if (i != 3) myfile_o << ",";
			
	}
	myfile_o << endl;

	myfile_o << "LHF ";
	for (int i = 0; i < 4; i++)
	{
		/*if (LHF[i] > 0) { 
			myfile_o << "+";
		}*/
		
		myfile_o << LHF[i];
		if (i != 3) myfile_o << ",";
	}
	myfile_o << endl;

	myfile_o << "PHF ";
	for (int i = 0; i < 4; i++)
	{
		/*if (PHF[i] > 0) { 
			myfile_o << "+";
		}*/
	
		myfile_o <<PHF[i];
		if (i != 3) myfile_o << ",";
	}
	myfile_o << std::noshowpos << endl<<endl;

	/*for (auto it = CombVector.begin(); it < CombVector.end(); it++)
	{
		myfile_o <<"CN"<<it->id << " ";
		for (int i = 0; i < 4; i++)
		{
			myfile_o  << it->CN[i];
		}
		myfile_o << ",";

		myfile_o << "LN" << it->id << " ";
		for (int i = 0; i < 4; i++)
		{
			myfile_o  << it->LN[i];
		}
		myfile_o << ",";

		myfile_o << "HN" << it->id << " ";
		for (int i = 0; i < 4; i++)
		{
			myfile_o  << it->HN[i];
		}
		myfile_o << endl;
	}

	myfile_o << endl;*/
}

void CombLock::DataStruture_CLHN_Only(string check_result)
{
	//cout << check_result << endl;
	myfile_o << check_result << endl;

	for (auto it = CombVector.begin(); it < CombVector.end(); it++)
	{
		myfile_o << "CN" << it->id << " ";
		//cout<< "CN" << it->id << " ";
		for (int i = 0; i < 4; i++)
		{
			myfile_o << it->CN[i];
			//cout << it->CN[i];
		}
		myfile_o << ",";
		//cout << ",";

		myfile_o << "LN" << it->id << " ";
		//cout<< "LN" << it->id << " ";
		for (int i = 0; i < 4; i++)
		{
			myfile_o << it->LN[i];
			//cout<< it->LN[i];
		}
		myfile_o << ",";
		//cout<< ",";

		myfile_o << "HN" << it->id << " ";
		//cout << "HN" << it->id << " ";
		for (int i = 0; i < 4; i++)
		{
			myfile_o << it->HN[i];
			//cout << it->HN[i];
		}
		myfile_o << endl;
		//cout << endl;
	}
	myfile_o << endl;
	//cout << endl;
}

void CombLock::DataStruture_LN_Only()
{
	
	myfile_o << "ROOT: ";
	for (int i = 0; i < 4; i++)
	{
		myfile_o << ROOT[i] << " ";;
	}
	myfile_o << endl;

	for (auto it = CombVector.begin(); it < CombVector.end(); it++)
	{
		myfile_o << "LN" << it->id << ": ";
		
		for (int i = 0; i < 4; i++)
		{
			myfile_o << it->LN[i]<<" ";
			
		}
		myfile_o << "\n";
		
	}
	myfile_o << endl;
	
}

void CombLock::Generate_MultiSafeFile()
{
	string check_result = "";
	int op = -1;
	CombLock c1; CombVector[0] = c1;
	CombLock c2(c1); CombVector[1] = c2;
	CombLock c3(c2); CombVector[2] = c3;
	CombLock c4(c3); CombVector[3] = c4;
	CombLock c5(c4); CombVector[4] = c5;

	if (!CheckAllCN() || !CheckEven() || !CheckSum())
		check_result = "NOT VALID";
	else
	{
		check_result = "VALID";
	}

	DataStruture_CLHN_Only(check_result);


	
	
}

void CombLock::Generate_LockedSafeFile()
{
	string check_result = "";
	int op = -1;
	CombLock c1; CombVector[0] = c1;
	CombLock c2(c1); CombVector[1] = c2;
	CombLock c3(c2); CombVector[2] = c3;
	CombLock c4(c3); CombVector[3] = c4;
	CombLock c5(c4); CombVector[4] = c5;

	DataStruture_LN_Only();



}

bool CombLock::Generate_OriginKeyfile()
{
	
	//Generate the UHF randomly to try
	CombLock::Generate_UHF();
	//calculate the CN0-CN5
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			CN_Temp[i][j] = Temp_Turn(CN_Temp[i][j], UHF[j]);
		}
		
	}

	CombLock c1(0, CN_Temp[0], LN_Temp[0], HN_Temp[0]); CombVector[0] = c1;
	CombLock c2(1, CN_Temp[1], LN_Temp[1], HN_Temp[1]); CombVector[1] = c2;
	CombLock c3(2, CN_Temp[2], LN_Temp[2], HN_Temp[2]); CombVector[2] = c3;
	CombLock c4(3, CN_Temp[3], LN_Temp[3], HN_Temp[3]); CombVector[3] = c4;
	CombLock c5(4, CN_Temp[4], LN_Temp[4], HN_Temp[4]); CombVector[4] = c5;
	

	if (!CheckAllCN())  return false;
	if (!CheckSum())    return false;
	if (!CheckEven())   return false;

	//When UHF is proved to right,then Calculate the LHF and output it
	Calculate_LHF();


	DataStruture_Key_Only();

	
	return true;






	



	
}

vector<string> CombLock::String_Split(const string& s, const char& c)
{
	string buff = "";
	vector<string> v;
	for (auto t : s)
	{
		if (t != c)
		{
			buff += t;
		}

		else if(buff!="")
		{
			v.push_back(buff);
			buff = "";
		}
	}

	if (buff != "")
		v.push_back(buff);

	return v;
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
			if (CN[i] == CN[j]) { 
				//myfile_o << "CN UnMatched" << endl; 
				return false; }
		}
	}


	//cout << "Matched" << endl;
	//myfile_o << "CN Matched" << endl;
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

int CombLock::CN_Number()
{
	return Generate_Number(CN);

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
		
		if ((it->CN_Sum() >=(it + 1)->CN_Sum()))
		{
			//myfile_o << "CN_Sum_Less UnMatched" << endl;
			return false;
		}
	}
	//myfile_o << "CN_Sum_Less Matched" << endl;
	return true;
}

bool CombLock::CheckEven()
{
	int sum = 0;
	for (auto it = CombVector.begin(); it < CombVector.end(); it++)
	{
		sum += it->CN_Number();
	}
	//myfile_o << "sum ="<<sum << endl;
	if (sum % 2 != 0) return false;
	
	//myfile_o << " Sum Even Matched" << endl;
	return true;
}