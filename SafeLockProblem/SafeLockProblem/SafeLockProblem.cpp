#include"CombLock.h"

int main()
{

	int i = 0;
	CombLock::InitialisePesudoRandom();

	CombLock::myfile.open("example.txt", std::ofstream::out);
	
	while (!CombLock::Build_SafeLock())
	{
		
		i++;
		std::cout << "This is the " << i << "  times" << std::endl;
		CombLock::myfile << "This is the " << i << "times" << std::endl;
		
    }
	
	CombLock::myfile.close();
	
	

}


