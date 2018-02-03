
#include <stdio.h>
#include "board.h"

CBoard::CBoard() : m_Street(BOARD_BLANK) 
{

}

CBoard::CBoard(const CBoard& rhs)
	: m_Street(rhs.m_Street)
	, m_Flop1(rhs.m_Flop1)
	, m_Flop2(rhs.m_Flop2)
	, m_Flop3(rhs.m_Flop3)
	, m_Turn(rhs.m_Turn)
	, m_River(rhs.m_River)
{

}

CBoard::~CBoard()
{

}
  
CBoard & CBoard::operator=(const CBoard &rhs)
{
  
  if(this == &rhs)
    return *this;

  m_Street = rhs.m_Street;
  m_Flop1 = rhs.m_Flop1;
  m_Flop2 = rhs.m_Flop2;
  m_Flop3 = rhs.m_Flop3;

  m_Turn = rhs.m_Turn;
  
  m_River = rhs.m_River;
  
  return *this;

}
  
bool CBoard::operator==(const CBoard &rhs) const
{
  return(m_Street == rhs.m_Street &&
	 m_Flop1 == rhs.m_Flop1 &&
	 m_Flop2 == rhs.m_Flop2 &&
	 m_Flop3 == rhs.m_Flop3 &&
	 m_Turn == rhs.m_Turn &&
	 m_River == rhs.m_River);
}

bool CBoard::operator!=(const CBoard &rhs) const
{
  return !operator==(rhs);
}

void CBoard::reset(void)
{
  m_Street = BOARD_BLANK;
  m_Flop1.reset();
  m_Flop2.reset();
  m_Flop3.reset();
  m_Turn.reset();
  m_River.reset();
}

void CBoard::dealFlop(CDeck &deck)
{
  m_Flop1 = deck.dealCard();
  m_Flop2 = deck.dealCard();
  m_Flop3 = deck.dealCard();

  m_Street = BOARD_FLOP;
}

void CBoard::dealTurn(CDeck &deck)
{
  m_Turn = deck.dealCard();

  m_Street = BOARD_TURN;
}

void CBoard::dealRiver(CDeck &deck)
{
  m_River = deck.dealCard();

  m_Street = BOARD_RIVER;
}

void CBoard::catASCII(std::ostream &os)
{

	if(m_Street == BOARD_BLANK)
	{
		os << "Board empty!";
		return;
	}

	if(m_Street >= BOARD_FLOP)
	{
		m_Flop1.catASCII(os);
		os << ",";
		m_Flop2.catASCII(os);
		os << ",";
		m_Flop3.catASCII(os);
	}

	if(m_Street >= BOARD_TURN)
	{
		os << ",";
		m_Turn.catASCII(os);
	}

	if(m_Street >= BOARD_RIVER)
	{
		os << ",";
		m_River.catASCII(os);
	}
}

