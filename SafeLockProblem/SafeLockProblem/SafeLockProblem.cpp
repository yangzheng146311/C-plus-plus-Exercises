#include"CombLock.h"

int main()
{
    int op =- 1;
	string output_filename = " ";
	string origin_filename = " ";
	cout << "Please select options:" << endl;
	cout << "Press '1':Generate key file" << endl;
	cout << "Press '2':Generate safe file" << endl;
	cout << "Press '3':Generate origin key file from lock safe file" << endl;

	cin >> op;

	switch (op)
	{
	case 1:
		cout << "Please input the file name you want" << endl;
		cin >> output_filename;
		CombLock::WriteKeyFile(output_filename);
		break;
		
	case 2:
		cout << "Please input the original key file name" << endl;
		cin >> origin_filename;
		cout << "Please input the safe file name" << endl;
		cin >> output_filename;
		CombLock::ReadKeyFile(origin_filename, output_filename);
		break;

	case 3:
		cout << "Please input the lock safe file name" << endl;
		cin >> origin_filename;
		cout << "Please input the origin key file name" << endl;
		cin >> output_filename;
		CombLock::ReadLockedSafeFile(origin_filename, output_filename);
		break;
	default:
		break;
	}
	
	//CombLock::ReadLockedSafeFile("lock.txt", "original.txt");




}


