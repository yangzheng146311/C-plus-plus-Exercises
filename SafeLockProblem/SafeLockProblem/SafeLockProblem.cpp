#include"CombLock.h"

int main()
{


	CombLock::InitialisePesudoRandom();
	CombLock::myfile.open("example.txt", std::ofstream::out);
	
	//CombLock::StopUntilOutputOneVaild();
	CombLock::TimesLimitVaildOutput(1000);
	
	CombLock::myfile.close();
	
	

}


