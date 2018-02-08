
#include <ostream>
#include "card.h"

const char CCard::ranksAscii[15] = {'X','X','2','3','4',
			     '5','6','7','8','9',
			     'T','J','Q','K','A'};

const char CCard::suitsAscii[5] = {'X','C','D','H','S'};

CCard::CCard() 
	: m_Rank(RANK_BLANK)
	, m_Suit(SUIT_BLANK)
{

}

CCard::CCard(unsigned char r, unsigned char s)
	: m_Rank(r)
	, m_Suit(s)
{

}

CCard::CCard(const CCard &rhs)
{
	m_Rank = rhs.m_Rank;
	m_Suit = rhs.m_Suit;
}

CCard::~CCard()
{

}

CCard & CCard::operator=(const CCard &rhs) 
{
  if(this == &rhs)
    return *this;

  m_Rank = rhs.m_Rank;
  m_Suit = rhs.m_Suit;
  return *this;
}
	
bool CCard::operator==(const CCard &rhs) const
{
	if(m_Rank == rhs.m_Rank && 
	   m_Suit == rhs.m_Suit)
		return true;

	return false;
}

bool CCard::operator!=(const CCard &rhs) const
{
	return !operator==(rhs);
}

void CCard::reset(void)
{
	m_Rank = RANK_BLANK;
	m_Suit = SUIT_BLANK;
}

void CCard::catASCII(std::ostream &os)
{
  os << ranksAscii[m_Rank] << suitsAscii[m_Suit];
}
