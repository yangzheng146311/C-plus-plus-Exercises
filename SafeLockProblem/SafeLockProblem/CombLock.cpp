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
int  CombLock::UHF_POS[16][4] = { {0,0,0,0}, {0,0,0,0}, {0,0,0,0}, {0,0,0,0},
								  {0,0,0,0}, {0,0,0,0}, {0,0,0,0}, {0,0,0,0},
								  {0,0,0,0}, {0,0,0,0}, {0,0,0,0}, {0,0,0,0},
								  {0,0,0,0}, {0,0,0,0}, {0,0,0,0}, {0,0,0,0} };
                                  
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

void CombLock::Generate_UHF_POS()
{
	int n = 0;//0-16 
	//Initialize
	for (int a = 0; a < 16; a++)
	{
		for (int i = 0; i < 4; i++)
		{
			UHF_POS[a][i] = UHF[i];
		}
	}

	//Reverse 0 digit result save in UHF_POS[0]
	for (int i = 0; i < 4; i++)
	{

		UHF_POS[n][4] = UHF[i];
	}
	n++;

	//Reverse 1 digit result save in UHF_POS[1-4]
	for (int a = 0; a < 4; a++)
	{
		//reverse 1 digit one time from left to right temporaryly
		int r = Reverse(UHF[a]);
		UHF[a] = r;

		for (int i = 0; i < 4; i++)
		{

			UHF_POS[n][i] = UHF[i];

		}
		n++;
		UHF[a] = Reverse(r);
		//UHF is static,so I have to reverse it back

	}

	//Reverse 2 digit result save in UHF_POS[5-10]
	for (int a = 0; a < 4; a++)
	{
		for (int b = 1; b <= 3 - a; b++)
		{
			//reverse 2 digit one time from left to right temporaryly
			int r = Reverse(UHF[a]);
			int r2 = Reverse(UHF[a + b]);
			UHF[a] = r;
			UHF[a + b] = r2;

			for (int i = 0; i < 4; i++)
			{

				UHF_POS[n][i] = UHF[i];
			}
			n++;
			//UHF is static,so I have to reverse it back
			UHF[a] = Reverse(r);
			UHF[a + b] = Reverse(r2);
		}

	}

	//Reverse 3 digit result save in UHF_POS[10-14]
	for (int a = 0; a < 4; a++)
	{
		int d1, d2, d3;
		int r, r2, r3;
		if (a == 0)
		{

			d1 = a + 1; d2 = a + 2; d3 = a + 3;
			//reverse 3 digit one time 
			r = Reverse(UHF[d1]);
			r2 = Reverse(UHF[d2]);
			r3 = Reverse(UHF[d3]);
			UHF[d1] = r;
			UHF[d2] = r2;
			UHF[d3] = r3;
		}

		if (a == 1)
		{

			d1 = a - 1; d2 = a + 1; d3 = a + 2;
			//reverse 3 digit one time 
			r = Reverse(UHF[d1]);
			r2 = Reverse(UHF[d2]);
			r3 = Reverse(UHF[d3]);
			UHF[d1] = r;
			UHF[d2] = r2;
			UHF[d3] = r3;
		}

		if (a == 2)
		{

			d1 = a - 2; d2 = a - 1; d3 = a + 1;
			//reverse 3 digit one time 
			r = Reverse(UHF[d1]);
			r2 = Reverse(UHF[d2]);
			r3 = Reverse(UHF[d3]);
			UHF[d1] = r;
			UHF[d2] = r2;
			UHF[d3] = r3;
		}

		if (a == 3)
		{

			d1 = a - 3; d2 = a - 2; d3 = a - 1;
			//reverse 3 digit one time 
			r = Reverse(UHF[d1]);
			r2 = Reverse(UHF[d2]);
			r3 = Reverse(UHF[d3]);
			UHF[d1] = r;
			UHF[d2] = r2;
			UHF[d3] = r3;
		}

		for (int i = 0; i < 4; i++)
		{

			UHF_POS[n][i] = UHF[i];
		}
		n++;
		//UHF is static,so I have to reverse it back
		UHF[d1] = Reverse(r);
		UHF[d2] = Reverse(r2);
		UHF[d3] = Reverse(r3);
	}

	//Reverse 4 digit result save in UHF_POS[15]
	for (int i = 0; i < 4; i++)
	{
		
		
		UHF_POS[n][i] = Reverse(UHF[i]);
		

	}

	//CHECK Print
	/*for (int i = 0; i < 16; i++)
	{
		
		for (int j = 0; j < 4; j++)
		{
			
			cout << showpos << UHF_POS[i][j] << " ";

		}
		cout << endl;
	}*/
	
	
}
	
bool CombLock::Generate_CN()
{
	int CN0_Num = 0;
	int CN1_Num = 1;
	//Genertate CN0 and CN1
	for (int j = 0; j < 2; j++)
	{
		for (int i = 0; i < 4; i++)
		{
			CN_Temp[j][i] = rand() % 10;
		}
	}
	
	//Check CN0 and CN1 if each one contain different number
	for (int k = 0; k < 2; k++)
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = i + 1; j < 4; j++)
			{
				if (CN_Temp[k][i] == CN_Temp[k][j]) {
					
					return false;
				}
			}
		}
	}
	
	CN0_Num = CN_Temp[0][0] * 1000 + CN_Temp[0][1] * 100 + CN_Temp[0][2] * 10 + CN_Temp[0][3] * 1;
	CN1_Num = CN_Temp[1][0] * 1000 + CN_Temp[1][1] * 100 + CN_Temp[1][2] * 10 + CN_Temp[1][3] * 1;

	if (CN0_Num > CN1_Num) return false;

	int UHF_1[4] = { 0,0,0,0 };
	int UHF_2[4] = { 0,0,0,0 };

	//comfirm UHF
	for (int i = 0; i < 4; i++)
	{

		UHF_1[i] = CN_Temp[0][i] - ROOT[i];
		UHF_2[i]= CN_Temp[1][i] - HN_Temp[0][i];

		if (UHF_1[i] != UHF_2[i])
		{
			if (abs(UHF_1[i] - UHF_2[i]) != 10) return false;
		}
		UHF[i] = UHF_1[i];
	}


	return true;

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
		if (temp < -10) temp += 10;
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

int CombLock::TimesLimitVaildOutput(int times)
{
	int countFound = 0;
	for (int i = 1; i <= times; i++)
	{
		if (!CombLock::Build_SafeLock())
		{
			std::cout << "This is the " << i << "  times" << std::endl;
			//CombLock::myfile_o << "This is the " << i << "times" << std::endl;
		}
		else
		{
			countFound++;
			
		}
	}
	
	return countFound;
}

void CombLock::StopUntilOutputEnoughVaild(int soluNum,int timeToChangeHash)
{
	int i = 0;
	CombLock::myfile_o << "NS " << soluNum << endl;
	for (int t=1; t <=soluNum; t++)
	{
		while (!CombLock::Build_SafeLock())
		{
			i++;
			if (i > timeToChangeHash)
			{
				CombLock::Generate_UHF();
				CombLock::Generate_LHF();
				CombLock::Generate_PHF();
				i = 0;
			}
		}
		//while (!CombLock::Build_SafeLock())
		//{

		//	i++;
		//	std::cout << "This is the " << i << "  times" << std::endl;
		//	//CombLock::myfile_o << "This is the " << i << " times" << std::endl;

		//}
		/*while (!CombLock::TimesLimitVaildOutput(timeToChangeHash))
		{
			CombLock::Generate_UHF();
			CombLock::Generate_LHF();
			CombLock::Generate_PHF();

		}*/
		
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
					//cout << endl;
				}
				while (!Generate_OriginKeyfile())
				{

					/*cout << "This is " << time << " times" << endl;
					time++;*/
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
	CombLock::Generate_UHF_POS();
	

	
	for (int t = 0; t < 16; t++)
	{
		//repalce the UHF to enum 16 situations
		for (int i = 0; i < 4; i++)
		{

			UHF[i] = UHF_POS[t][i];

		}

	//calculate the CN0-CN5
		for (int c= 0; c< 4; c++)
		{
			CN_Temp[0][c] = Temp_Turn(ROOT[c], UHF[c]);
			//if(CN_Temp[0][i]<0) return false;

		}


		for (int e = 1; e < 5; e++)
		{
			for (int j = 0; j < 4; j++)
			{
				CN_Temp[e][j] = Temp_Turn(HN_Temp[e-1][j], UHF[j]);
				//if(CN_Temp[i][j]<0) return false;
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

	 }

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

int CombLock::Reverse(int num)
{
	if (num >0) return -(10 - num);
	if (num < 0) return 10 - abs(num);
	if (num = 0) return 0;
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