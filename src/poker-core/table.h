
#ifndef TABLE_H
#define TABLE_H

#include <vector>
#include "player.h"

class CTable
{
public:
	CTable();
	~CTable();

	void pushPlayer(CPlayer *player);

private:
	std::vector<CPlayer *> m_players;
};

#endif // TABLE_H