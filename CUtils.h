#pragma once
#include <string>

#define NUMBER_PLAYERS 2
#define BOARD_ROWS 6
#define BOARD_COLS 7
#define NUMBER_CONCECUTIVE_WIN 4

namespace CUtils {

	enum class Color {
		RED = 0,
		YELLLOW = 1,
		NONE = 2
	};
	
	static std::string colorToStringForDisplay(const Color c) {
		std::string res = "";
		switch (c)
		{
		case Color::RED:
			res = "X";
			break;
		case Color::YELLLOW:
			res = "O";
			break;
		case Color::NONE:
			res = "-";
			break;
		default:
			break;
		}

		return res;
	}
};

