#ifndef VIEWCONTROLSSTATE_H
#define VIEWCONTROLSSTATE_H

#include "Header Files/IState.h"
#include "Header Files/GameContext.h"
#include <string>

using namespace context;

namespace states
{
	class ViewControlsState : public IState<GameContext>
	{

	public:
		void Enter(GameContext* p_gameContext) override;

		void Update(GameContext* p_gameContext) override;

		void Exit(GameContext* p_gameContext) override;
	private:
		void PrintControls() const;
	};

	//TODO: Make a struct with a template so I can setup key value pairs a bit better.
	struct ControlText
	{
		std::string Button;
		std::string Description;
	};

	extern ViewControlsState ViewControlsStateInstance;
}

#endif 
