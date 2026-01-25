#ifndef SETTINGDATA_H
#define SETTINGDATA_H

#include <string>

namespace gamedata
{
	enum SettingsMenuChoices { GAME_SOUND_EFFECTS, MUSIC, MENU_SOUNDS, BACK, NUM_MAIN_SETTINGS };

	struct Slider {
		std::string name = "DEFAULT";
		int value = 5;
		int max = 10;
		int min = 0;

		std::string GetAndUpdateSetting()
		{
			std::string sliderVisual = "";
			
			for (int i = name.size(); i < (max); i++) // This is so that all the sliders always line up without me needing to make every name the same lenght.
			{
				sliderVisual += " ";
			}
			
			sliderVisual += "[[";

			for (int i = 0; i < max; i++)
			{
				if (i < value) 
				{
					sliderVisual += "▋";
				} 
				else 
				{
					sliderVisual += " ";
				}
			}
			sliderVisual += "]]";
			return name + sliderVisual;
		}
	};

	static class SettingsData
	{
	private:
		Slider SettingsArray[NUM_MAIN_SETTINGS] = {
		{ "SFX", 5, 10, 0 },
		{ "Music", 5, 10, 0 },
		{ "Menu_Sound", 5, 10, 0 },
		{ "Back", 0, 10, 0 },
	};

	public:
		/// <summary>
		/// The int passed in is used to grab a reference of the Slider object equal to what setting is listed in SettingsMenuChoiches.
		/// </summary>
		/// <param name="0 = Game_SFX_Volume, 1 = Music, 2 = Menu_Sounds, 3 = BACK(Don't edit settings on this option)"></param>
		/// <returns></returns>
		Slider& GetSelectedSlider(int choiceIn)
		{
			return SettingsArray[choiceIn];
		}
	};
	static SettingsData SettingsDataInstance;
}

#endif