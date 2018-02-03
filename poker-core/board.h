
#ifndef BOARD_H
#define BOARD_H

#include "card.h"
#include "deck.h"
 
enum eBoardStreet
{
	BOARD_BLANK = 0,
	BOARD_FLOP  = 1,
	BOARD_TURN  = 2,
	BOARD_RIVER = 3
};

class CBoard {

public:

  CBoard();
  CBoard(const CBoard& rhs);
  ~CBoard();
  
  CBoard & operator=(const CBoard &rhs);
  
  bool operator==(const CBoard &rhs) const;
  bool operator!=(const CBoard &rhs) const;

  void reset(void);

  void dealFlop(CDeck &deck);
  void dealTurn(CDeck &deck);
  void dealRiver(CDeck &deck);

  void catASCII(std::ostream &os);

  void setFlop1(const CCard &c) { m_Flop1 = c; }
  void setFlop2(const CCard &c) { m_Flop2 = c; }
  void setFlop3(const CCard &c) { m_Flop3 = c; }
  void setTurn(const CCard &c) { m_Turn = c; }
  void setRiver(const CCard &c) { m_River = c; }

  void setStreet(eBoardStreet s) { m_Street = s; }

  CCard getFlop1(void) const { return m_Flop1; }
  CCard getFlop2(void) const { return m_Flop2; }
  CCard getFlop3(void) const { return m_Flop3; }
  CCard getTurn(void) const { return m_Turn; }
  CCard getRiver(void) const { return m_River; }

  eBoardStreet getStreet(void) const { return m_Street; }
  
 private:
  eBoardStreet m_Street;
  CCard m_Flop1;
  CCard m_Flop2;
  CCard m_Flop3;

  CCard m_Turn;
  CCard m_River;
};

#endif
