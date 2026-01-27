#ifndef THEMES_H
#define THEMES_H

#include <BearLibTerminal.h>

namespace themes
{
	const int NUM_THEMES = 5;
	struct Theme {
		std::string name = "Default";
		color_t TextColor = 0xffcccccc;
		color_t BackgroundColor = 0xff222222;
		int BorderSymbol1 = 0x2588;
		int BorderSymbol2 = '#';
	};

	class ThemesClass
	{
	public:
		ThemesClass();
		Theme ThemesArray[NUM_THEMES];
	};

	extern Theme CurrentTheme;
	extern ThemesClass ThemesInstance;
}

#endif
