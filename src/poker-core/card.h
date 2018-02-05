#ifndef CARD_H
#define CARD_H

#include <ostream>

enum eCardRank
{
	RANK_BLANK        = 1,
	RANK_TWO          = 2,
	RANK_THREE        = 3,
	RANK_FOUR         = 4,
	RANK_FIVE         = 5,
	RANK_SIX          = 6,
	RANK_SEVEN        = 7,
	RANK_EIGHT        = 8,
	RANK_NINE         = 9,
	RANK_TEN          = 10,
	RANK_JACK         = 11,
	RANK_QUEEN        = 12,
	RANK_KING         = 13,
	RANK_ACE          = 14
};

enum eCardSuit 
{
	SUIT_BLANK		  = 0,
	SUIT_CLUBS        = 1,
	SUIT_DIAMONDS     = 2,
	SUIT_HEARTS       = 3,
	SUIT_SPADES       = 4
};

class CCard {

public:  
  static const char ranksAscii[15];
  static const char suitsAscii[5];

  CCard();
  CCard(unsigned char r, unsigned char s);
  CCard(const CCard& rhs);
  ~CCard();
  
  CCard & operator=(const CCard &rhs);
  
  bool operator==(const CCard &rhs) const;
  bool operator!=(const CCard &rhs) const;

  void setRank(eCardRank r) { m_Rank = static_cast<unsigned char>(r); };
  void setSuit(eCardSuit s) { m_Suit = static_cast<unsigned char>(s); };

  eCardRank getRank(void) const { return (eCardRank)m_Rank; };
  eCardSuit getSuit(void) const { return (eCardSuit)m_Suit; };

  void reset(void);
  bool isValid(void) const { return (m_Rank >= RANK_TWO && m_Rank <= RANK_ACE && m_Suit >= SUIT_CLUBS && m_Suit <= SUIT_SPADES); };
  void catASCII(std::ostream &os);
  
 private:
  unsigned char m_Rank;
  unsigned char m_Suit; 
};

#endif

