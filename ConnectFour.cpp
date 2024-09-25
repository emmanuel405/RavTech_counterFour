#include <iostream>
#include "GameConnectFour.h"

int main()
{
	std::cout << "Welcome to Connect4!\n";
	std::cout << "There are 3 options:\n"
		"1. 2 users\n"
		"2. 1 vs computer (with random choice)\n"
		"3. 1 vs computer (better algorithm)" << std::endl;

	std::cout << "Please select your choice. press q / Q to exit\n";

	char c = ' ';
	do {
		c = getchar();
		if (isspace(c))
			continue;

		if (c == '1')
		{
			GameConnectFour connect4_twoPlayers;
			connect4_twoPlayers.run();
		}
		else if (c == '2')
		{
			GameConnectFour connect4VSComputer{ true };
			connect4VSComputer.run();
		}
		else if (c == '3')
		{
			GameConnectFour connect4VSComputer{ true, false };
			connect4VSComputer.run();
		}
	} while (c != 'q' && c != 'Q');

	return 0;
}
