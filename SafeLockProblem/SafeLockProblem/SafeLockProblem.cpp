#include"CombLock.h"

int main()
{


	CombLock::Initialise();
	
	CombLock::myfile.open("example.txt", std::ofstream::out);
	
	CombLock::StopUntilOutputOneVaild(1);
	//CombLock::TimesLimitVaildOutput(1000);
	
	CombLock::myfile.close();
	
	

}


