
#include "pch.h"
#include <iostream>
#include"CombLock.h"
#include <windows.h>

int main()
{
	int i = 0;

	while (!CombLock::Build_SafeLock())
	{
		
		i++;
		std::cout << "This is the " << i << "times" << std::endl;
		
    }
	
	
	
	

}


