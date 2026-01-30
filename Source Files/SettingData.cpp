#include "Header Files/SettingData.h"

namespace gamedata
{
	SettingsData SettingsDataInstance;

	SettingsData::SettingsData() : SettingsArray{
		{ "SFX", 5, 10, 0 },
		{ "Music", 5, 10, 0 },
		{ "Menu_Sound", 5, 10, 0 },
		{ "Back", 0, 10, 0 },
	} {}

	/// <summary>
	/// The int passed in is used to grab a reference of the Slider object equal to what setting is listed in SettingsMenuChoiches.
	/// </summary>
	/// <param name="0 = Game_SFX_Volume, 1 = Music, 2 = Menu_Sounds, 3 = BACK(Don't edit settings on this option)"></param>
	/// <returns></returns>
	Slider& SettingsData::GetSelectedSlider(int choiceIn)
	{
		return SettingsArray[choiceIn];
	}

	bool SettingsData::SaveToFile(const std::string& filename)
	{
		std::ofstream file(filename);
		if (!file)
		{
			return false;
		}
		 
		for (int i = 0; i < NUM_MAIN_SETTINGS; i++)
		{
			file << SettingsArray[i].name << " " << SettingsArray[i].value << "\n";
		}
		file << themes::CurrentTheme.name << "\n";

		return true;
	}

	bool SettingsData::LoadFromFile(const std::string& filename)
	{
		std::ifstream file(filename);
		if (!file)
		{
			return false;
		}

		std::string name;
		int value;

		while (file >> name >> value) // While the file can read in the order of "string" then integer.
		{
			for (int i = 0; i < NUM_MAIN_SETTINGS; i++)
			{
				if (SettingsArray[i].name == name)
				{
					SettingsArray[i].value = value;
					break;
				}
			}
		}
		// This works because the while loop fails when it can't read a newline with in the order string,int.
		// It fails when it reads the line with the theme on it, because it's just a single string followed up by nothing.
		// But when it fails it still assigns the name variable to the saved theme.  
		// || The comment is long but no one would otherwise be able to easily infer as to why this even works.
		for (int i = 0; i < themes::NUM_THEMES; i++) 
		{
			if (themes::ThemesInstance.ThemesArray[i].name == name) // If the name being read is a name of an existing theme set the current theme to that theme.
			{
				themes::CurrentTheme = themes::ThemesInstance.ThemesArray[i];
				break;
			}
		}

		return true;
	}
}
