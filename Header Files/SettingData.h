#ifndef SETTINGDATA_H
#define SETTINGDATA_H

#include <string>
#include <fstream>
#include "Themes.h"


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

	class SettingsData
	{
	private:
		Slider SettingsArray[NUM_MAIN_SETTINGS];

	public:
		SettingsData();

		Slider& GetSelectedSlider(int choiceIn);
		bool SaveToFile(const std::string& filename);
		bool LoadFromFile(const std::string& filename);
	};

	extern SettingsData SettingsDataInstance;
}

#endif