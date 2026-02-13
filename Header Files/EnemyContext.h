#ifndef ENEMYCONTEXT_H
#define ENEMYCONTEXT_H

#include "Header Files/StateMachine.h"

namespace context
{
	struct EnemyContext
	{
		StateMachine<EnemyContext> m_StateMachine;
		int m_Health;
	};
}

#endif