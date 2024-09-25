#include <iostream>
#include <vector>
#include <string>
#include "CUtils.h"
#include "Board.h"

Board::Board() {
	board.reserve(BOARD_ROWS);

	for (int i = 0; i < board.capacity(); i++)
	{
		std::vector<CUtils::Color>v(BOARD_COLS, CUtils::Color::NONE);
		board.emplace_back(v);
	}

	upperPosition.reserve(BOARD_COLS);
	for (int i = 0; i < BOARD_COLS; i++)
	{
		upperPosition.emplace_back(BOARD_ROWS - 1);
	}
}
Board::~Board(){}

bool Board::isPositionFree(const int choiceCol) const {
	return upperPosition[choiceCol] >= 0;
}

int Board::getUpperPositionSpecificCol(const int choiceCol) const {
	return upperPosition[choiceCol];
}

bool Board::setInPosition(const int choiceCol, const CUtils::Color colorPlayer) {

	if (!isPositionFree(choiceCol))
		return false;

	board[getUpperPositionSpecificCol(choiceCol)][choiceCol] = colorPlayer;
	upperPosition[choiceCol]--;

	return true;
}

bool countConsecutiveColor(const CUtils::Color& currentColor, CUtils::Color& prevColor, int& count) {
	
	if (currentColor == CUtils::Color::NONE)
	{
		count = 0;
		return false;
	}

	if (prevColor == CUtils::Color::NONE)
	{
		prevColor = currentColor;
		count = 1;
	}
	else
	{
		if (prevColor == currentColor)
		{
			count++;
			if (count == NUMBER_CONCECUTIVE_WIN)
				return true;
		}
		else
		{
			prevColor = currentColor;
			count = 1;
		}
	}

	return false;
}

bool Board::fourInRow() const {

	for (int r = 0; r < board.size(); r++)
	{
		int count = 0;
		const auto& currentBoard = board[r];

		CUtils::Color prevColor = CUtils::Color::NONE;
		for (const auto& curColor : currentBoard)
		{
			if (countConsecutiveColor(curColor, prevColor, count))
				return true;
		}
	}

	return false;
}

bool Board::fourInCol() const {

	for (int c = 0; c < BOARD_COLS; c++)
	{
		int count = 0;
		CUtils::Color prevColor = CUtils::Color::NONE;
		for (int r = 0; r < BOARD_ROWS; r++)
		{
			if (countConsecutiveColor(board[r][c], prevColor, count))
				return true;
		}
	}

	return false;
}

bool Board::fourInDiag() const {

	for (int row = NUMBER_CONCECUTIVE_WIN - 1; row < BOARD_ROWS; row++)
	{
		int c = 0, r = row;
		int count = 0;
		CUtils::Color prevColor = CUtils::Color::NONE;
		for (; r >= 0 && c < BOARD_COLS; r--, c++)
		{
			if (countConsecutiveColor(board[r][c], prevColor, count))
				return true;
		}

		c = BOARD_COLS - 1;
		r = row;
		count = 0;
		prevColor = CUtils::Color::NONE;
		for (; r >= 0 && c >= 0; r--, c--)
		{
			if (countConsecutiveColor(board[r][c], prevColor, count))
				return true;
		}
	}
	
	for (int col = 1; col < BOARD_COLS - NUMBER_CONCECUTIVE_WIN + 1; col++)
	{
		int c = col, r = BOARD_ROWS - 1;
		int count = 0;
		CUtils::Color prevColor = CUtils::Color::NONE;
		for (; c < BOARD_COLS && r >= 0; c++, r--)
		{
			if (countConsecutiveColor(board[r][c], prevColor, count))
				return true;
		}

		c = BOARD_COLS - col, r = BOARD_ROWS - 1;
		count = 0;
		prevColor = CUtils::Color::NONE;
		for (; c >= 0 && r >= 0; c--, r--)
		{
			if (countConsecutiveColor(board[r][c], prevColor, count))
				return true;
		}
	}

	return false;
}

bool Board::hasFourConsecutive() const {
	return (fourInRow() || fourInCol() || fourInDiag());
}

void Board::toString() const{
	std::cout << "Board:\n";

	for (int i = 1; i <= BOARD_COLS; i++)
		std::cout << " " << i << "  ";
	std::cout << std::endl;

	for (int r = 0; r < board.size(); r++)
	{
		const auto& currentRowVec = board[r];
		for (int c = 0; c < currentRowVec.size(); c++)
		{
			std::cout << "[" << CUtils::colorToStringForDisplay(currentRowVec[c]) << "] ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}