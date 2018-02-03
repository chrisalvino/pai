
#include "deck.h"
#include <windows.h>

CDeck::CDeck(unsigned long seed)
	: m_numLeft(0)
	, m_pRNG(0)
	, m_ExternalRNG(false)
{
	m_pRNG = new RandNumMT(seed);
	shuffle();
}

CDeck::CDeck(RandNumMT *pRNG)
	: m_numLeft(0)
	, m_pRNG(pRNG)
	, m_ExternalRNG(true)
{
	shuffle();
}

void CDeck::shuffle(void)
{	
	eCardRank ranks[13] = { 
		RANK_TWO,
		RANK_THREE,
		RANK_FOUR,
		RANK_FIVE,
		RANK_SIX,
		RANK_SEVEN,
		RANK_EIGHT,
		RANK_NINE,
		RANK_TEN,
		RANK_JACK,
		RANK_QUEEN,
		RANK_KING,
		RANK_ACE 
	};

	eCardSuit suits[4] = {  
		SUIT_CLUBS,
		SUIT_DIAMONDS,
		SUIT_HEARTS,
		SUIT_SPADES 
	};

	int i = 0;
	for(unsigned char r=0;r<13;r++)
	{
		for(unsigned char s=0;s<4;s++) 
		{
			m_cards[i].setRank(ranks[r]);
			m_cards[i].setSuit(suits[s]);
			i++; 
		}
	}

	m_numLeft = 52;
}

CDeck::CDeck(const CDeck& rhs)
	: m_ExternalRNG(rhs.m_ExternalRNG)
{
  for(int c=0;c < rhs.m_numLeft;c++)
    m_cards[c] = rhs.m_cards[c];

  m_numLeft = rhs.m_numLeft;

  if(m_ExternalRNG)
  {
	  // copy the pointer
	  m_pRNG = rhs.m_pRNG;
  }
  else
  {
	  m_pRNG = new RandNumMT;
  }
}

CDeck::~CDeck()
{
	if(!m_ExternalRNG && m_pRNG)
	{
		delete m_pRNG;
	}
}

CDeck & CDeck::operator=(const CDeck &rhs)
{
  if(this == &rhs)
    return *this;

  for(int c=0;c<rhs.m_numLeft;c++)
    m_cards[c] = rhs.m_cards[c];

  m_numLeft = rhs.m_numLeft;

  m_ExternalRNG = rhs.m_ExternalRNG;
  if(m_ExternalRNG)
  {
	  // copy the pointer
	  m_pRNG = rhs.m_pRNG;
  }
  else
  {
	  m_pRNG = new RandNumMT;
  }

  return *this;
}

CCard CDeck::dealCard(void)	
{
  float f = (float)m_pRNG->getRandnum();

  CCard c;
  int i;
  
  if(f == 1.0f)  // error condition that very rarely happens 
  {
	  i = m_numLeft - 1;
  }
  else
  {
	  i = (int)(m_numLeft*f);
  }
  
  c = m_cards[i];
  m_numLeft--;
  
  if (i != m_numLeft) 
    m_cards[i] = m_cards[m_numLeft];
  
  return c;
}

void CDeck::pullCard(const CCard &pullcard)	
{
  int i=4*(pullcard.getRank()-RANK_TWO)
    + pullcard.getSuit() - SUIT_CLUBS;
  
  // if the pull card is greater than the num cards left
  // then scan them all until you find it
  if(i >= m_numLeft)
  {
	  i = m_numLeft-1;
  }

  m_numLeft--;

  while(i >= 0)	
  {
	  if(m_cards[i] == pullcard)  
	  {
		  m_cards[i] = m_cards[m_numLeft];
		  return;
	  }
	  i--;
  }

  throw std::runtime_error("CDeck::pullCard(): requested card not found in deck!");
}

CCard CDeck::peekCard(void) 
{
  float f = (float)m_pRNG->getRandnum();

  int i;  
  if(f == 1.0f)  // error condition that very rarely happens 
  {
	  i = m_numLeft - 1;
  }
  else
  {
	  i = (int)(m_numLeft*f);
  }
  
  return m_cards[i];
};

