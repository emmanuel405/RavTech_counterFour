#pragma once

class Board {
private:
	std::vector<std::vector<CUtils::Color>> board;
	std::vector<int> upperPosition;

	bool isPositionFree(const int choiceCol) const;
	int getUpperPositionSpecificCol(const int choiceCol) const;

	bool fourInRow() const;
	bool fourInCol() const;
	bool fourInDiag() const;

public:
	Board();
	~Board();

	bool hasFourConsecutive() const;
	void toString() const;
	bool setInPosition(const int choiceCol, const CUtils::Color colorPlayer);

};