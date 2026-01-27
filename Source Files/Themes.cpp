#include "Header Files/Themes.h"
namespace themes
{ 
	ThemesClass ThemesInstance;
    Theme CurrentTheme;

	ThemesClass::ThemesClass() : ThemesArray{ // Initialize ThemesArray before the constructor body runs.
		{
			    "Bright",		// Name
				0xff333333,		// TextColor
				0xfff7f1e3,		// BackgroundColor
				'X',			// BorderSymbol1
				'O',			//BorderSymbol2
		},
		{ "Dark", 0xffe4e4e4, 0xff121212, '■', '█' },
		{ "Default", 0xffcccccc, 0xff222222, 0x2588, '#' },
		{ "Rock", 0xff715a5a, 0xff37353e, 'O', 'X' },
		{ "Grass", 0xffebd5ab, 0xff628141, '~', '#' }
	} {}


}