
#ifndef PLAYER_H
#define PLAYER_H

#include "action.h"

class CPlayer
{
public:
	CPlayer();
	virtual ~CPlayer();

	virtual eAction getAction(void) = 0;

private:

};

#endif // PLAYER_H