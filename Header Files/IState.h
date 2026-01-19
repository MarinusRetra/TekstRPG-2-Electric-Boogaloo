#ifndef STATE_H // I'm not using pragma because it is not the C++ standard and this is a little more reliable. (Even though pragma works with most compilers modern, it's a small change to make so why not.)
#define STATE_H

template<typename ContextType>
class IState
{
public:
    virtual ~IState() {}

    virtual void Enter(ContextType* p_gameContext) {}
    virtual void Update(ContextType* p_gameContext) = 0;
    virtual void Exit(ContextType* p_gameContext) {}
};
#endif

