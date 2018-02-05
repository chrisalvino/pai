
#ifndef HOLDING_H
#define HOLDING_H

#include "holecards.h"
#include "card.h"
#include "board.h"
 
enum eHoldingType 
{
	HOLDING_HIGHCARD = 1,
	HOLDING_PAIR = 2,
	HOLDING_TWOPAIR = 3,
	HOLDING_THREEOFAKIND = 4,
	HOLDING_STRAIGHT = 5,
	HOLDING_FLUSH = 6,
	HOLDING_FULLHOUSE = 7,
	HOLDING_FOUROFAKIND = 8,
	HOLDING_STRAIGHTFLUSH = 9
};

class CHolding {

public:

  CHolding();
  CHolding(const CHoleCards &holecards,const CBoard &board);
  ~CHolding();
  
  CHolding & operator=(const CHolding &rhs);

  inline void reset(void);
  void createHolding(const CHoleCards &holecards,const CBoard &board);

  void sort(void);
  void evaluate(void);
  
  bool operator==(CHolding &rhs);
  bool operator>(CHolding &rhs);
  bool operator<(CHolding &rhs);

  eHoldingType getHandQuality(void) const { return m_handQuality; }

 private:
  inline void swapcards(CCard &c1, CCard &c2);	  

 private:
  int m_NumCards;
  CCard m_cards[7];

  bool m_Evaluated;
  bool m_Sorted;
  CCard m_bestCards[5];
  eHoldingType m_handQuality; // 1 = high card, 2 = pair, 3 = two pair, etc.
  
};

inline void CHolding::swapcards(CCard &c1, CCard &c2)	
{
  CCard tempcard;
  
  tempcard = c1;
  c1 = c2;
  c2 = tempcard;
}

#endif

