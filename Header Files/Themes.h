#ifndef THEMES_H
#define THEMES_H

#include <BearLibTerminal.h>

namespace themes
{
	struct Theme {
		color_t TextColor = 0xffcccccc;
		color_t BackgroundColor = 0xff222222;
		int BorderSymbol1 = 0x2588;
		int BorderSymbol2 = '#';
	};

	class AllThemes
	{
	public:
		Theme BrightTheme = {
		0xff333333, // TextColor
		0xfff7f1e3, // BackgroundColor
		'X', // BorderSymbol1
		'O', //BorderSymbol2
		};

		Theme DarkTheme = {
			0xffe4e4e4, // TextColor
			0xff121212, // BackgroundColor
			'■', // BorderSymbol1
			'█', //BorderSymbol2
		};

		Theme DefaultTheme = {
			0xffcccccc, // TextColor
			0xff222222, // BackgroundColor
			0x2588, // BorderSymbol1
			'#', //BorderSymbol2
		};

		Theme RockTheme = {
			0xff715a5a, // TextColor
			0xff37353e, // BackgroundColor
			'O', // BorderSymbol1
			'X', //BorderSymbol2
		};

		Theme GrassTheme = {
			0xffebd5ab, // TextColor
			0xff628141, // BackgroundColor
			'~', // BorderSymbol1
			'#', //BorderSymbol2
		};
	};
	static AllThemes EveryTheme;
}

#endif
