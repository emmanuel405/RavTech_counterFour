#pragma once
#include <vector>
#include <stack>
#include "CUtils.h"
#include "Board.h"

class GameConnectFour {
private:
	bool isComputerPlayer, isComputerRandomAlgorithm;
	std::vector<CUtils::Color> players;
	int currentPlayer;
	Board board;
	std::stack<int> dropHistory;

	void updatePlayerTurn();
	void playTurn(int& chooseColFromUser);
	bool isWinner() const;
	void chooseColForComputerPlayer(int& choosePlayerCol) const;

public:
	GameConnectFour(const bool isComputerPlayer = false, const bool isComputerRandomAlgorithm = true);
	~GameConnectFour();

	void run();
};
