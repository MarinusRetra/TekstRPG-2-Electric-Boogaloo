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

	//TODO: Print an error ingame when saving or loading fails.

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

		while (true) // While the file can read in the order of "string" then integer.
		{
			file >> name >> value;
			if (file.fail())
			{
				break;
			}

			for (int i = 0; i < NUM_MAIN_SETTINGS; i++)
			{
				if (SettingsArray[i].name == name)
				{
					SettingsArray[i].value = value;
					break;
				}
			}
		}

		return true;
	}
}
