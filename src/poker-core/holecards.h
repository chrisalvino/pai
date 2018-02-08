
#ifndef HOLECARDS_H
#define HOLECARDS_H

#include "card.h"
#include "deck.h"
#include <string>
 
class CHoleCards {

public:

  CHoleCards();
  CHoleCards(const CHoleCards& rhs);
  CHoleCards(const CCard &c1,const CCard &c2);
  ~CHoleCards();
  
  CHoleCards & operator=(const CHoleCards &rhs);
  bool operator==(const CHoleCards &rhs) const;
  
  bool areValid(void) const;
  
  void deal(CDeck &deck);
  
  void catASCII(std::ostream &os);

  void catASCIIHoleCardType(std::ostream &os);

  static void catASCIIHoleCardTypeFromIndex(int hctypeindex, std::ostream &os);	
  static std::string getStringHoleCardTypeFromIndex(int hctypeindex);

  CCard getCard1(void) const { return m_Card1; }
  CCard getCard2(void) const { return m_Card2; }

  void setCard1(const CCard &c) { m_Card1 = c; }
  void setCard2(const CCard &c) { m_Card2 = c; }

  int getTypeIndex(void);

 private:
  CCard m_Card1;
  CCard m_Card2;
  
private:
	static const char hcTypeArray[169*3+1];

};

inline bool CHoleCards::operator==(const CHoleCards &rhs) const 
{
  return(rhs.m_Card1 == m_Card1 &&
	 rhs.m_Card2 == m_Card2);     
}

inline bool CHoleCards::areValid(void) const
{
  return(m_Card1.isValid() &&
	 m_Card2.isValid());
}

inline void CHoleCards::deal(CDeck &deck)
{
  m_Card1 = deck.dealCard();
  m_Card2 = deck.dealCard();
}

#endif
