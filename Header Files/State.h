#ifndef STATE_H // I'm not using pragma because it is not the C++ standard and this is a little more reliable. (Even though pragma works with most compilers modern, it's a small change to make so why not.)
#define STATE_H

    // Forward decleration because I only need to no that game context exists.
    class GameContext;

    class State
    {
    public:
        virtual ~State() {}

        virtual void Enter(GameContext* p_gameContext) {}
        virtual void Update(GameContext* p_gameContext) = 0;
        virtual void Exit(GameContext* p_gameContext) {}
    };
#endif

