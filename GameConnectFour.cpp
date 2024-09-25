#include <iostream>
#include <vector>
#include <stack>
#include "CUtils.h"
#include "Board.h"
#include "GameConnectFour.h"

GameConnectFour::GameConnectFour(const bool isComputerPlayer, const bool isComputerRandomAlgorithm) {
	this->isComputerPlayer = isComputerPlayer;
	this->isComputerRandomAlgorithm = isComputerRandomAlgorithm;
	currentPlayer = 0;

	players.resize(NUMBER_PLAYERS);
	players[0] = CUtils::Color::RED;
	players[1] = CUtils::Color::YELLLOW;
}
GameConnectFour::~GameConnectFour() {

	while (!dropHistory.empty())
		dropHistory.pop();

}

void GameConnectFour::updatePlayerTurn() {
	currentPlayer = (currentPlayer + 1) % NUMBER_PLAYERS;
	return;
}

void GameConnectFour::chooseColForComputerPlayer(int& choosePlayerCol) const {

	// random
	if (isComputerRandomAlgorithm)
		choosePlayerCol = static_cast<int>(std::rand() % BOARD_COLS);

	// random around the second player
	else
	{
		const int lastDrop = dropHistory.top();
		const int minLimit = std::max(0, lastDrop - 1);
		const int maxLimit = std::min(BOARD_COLS - 1, lastDrop + 1);
		choosePlayerCol = static_cast<int>(rand() % (maxLimit - minLimit + 1) + minLimit);
	}

	std::cout << "computer choice: " << (choosePlayerCol + 1) << std::endl;
}

void GameConnectFour::playTurn(int& choosePlayerCol)
{
	std::cout << "\nPlayer " << (currentPlayer + 1) << " turn" << std::endl;

	const bool computerTurn = (isComputerPlayer && currentPlayer == 1);

	if (computerTurn)
		std::cout << " {computer turn}.." << std::endl;
	else
		std::cout << "Please choose your column when do you want to drop the token: (number 1 - " << BOARD_COLS << ")" << std::endl;
	
	bool chooseAgain = true;
	while (chooseAgain)
	{
		if (computerTurn)
			chooseColForComputerPlayer(choosePlayerCol);
		else
		{
			std::cin >> choosePlayerCol;
			choosePlayerCol--; // vector starts from index 0..
		}

		if (choosePlayerCol >= 0 && choosePlayerCol <= BOARD_COLS)
		{
			if (!board.setInPosition(choosePlayerCol, players[currentPlayer]))
			{
				if (!computerTurn)
					std::cout << "\nPlease choose again " << std::endl;
			}
			else
			{
				dropHistory.push(choosePlayerCol);
				chooseAgain = false;
			}
		}
		else
		{
			if (!computerTurn)
				std::cout << "\nPlease choose again " << std::endl;
		}
	}
}

void GameConnectFour::run() {
	
	/*
		1. display the board

		2. player x start the turn

		3. check if the player win

		4. update the player turn
	*/

	bool playTheGame = true;
	while (playTheGame && dropHistory.size() < BOARD_ROWS * BOARD_COLS)
	{
		// 1. display the board
		board.toString();

		// 2. player x start the turn
		int chooseColFromUser;
		playTurn(chooseColFromUser);

		// 3. check if the player win
		if (isWinner())
		{
			std::cout << "player num " << (currentPlayer + 1) << " won the game!" << std::endl;
			playTheGame = false;
		}
		else // 4. update the player turn
			updatePlayerTurn();
	}

	board.toString();
	std::cout << "\nPlay again :)\n choose 1, 2 or 3 (or q / Q to exit)" << std::endl;
}
bool GameConnectFour::isWinner() const {
	return board.hasFourConsecutive();
}