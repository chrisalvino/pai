
#include "holding.h"
#include <stdio.h>

CHolding::CHolding() 
	: m_NumCards(0)
	, m_Evaluated(false)
	, m_Sorted(false)
{

}

CHolding::CHolding(const CHoleCards &holecards, const CBoard &board)
{

	m_NumCards = 0;
	m_Evaluated = false;
	m_Sorted = false;

	if(holecards.areValid())
	{
		m_cards[0] = holecards.getCard1();
		m_cards[1] = holecards.getCard2();
		m_NumCards = 2;
	}

	if(board.getStreet() >= BOARD_FLOP)
	{
		m_cards[2] = board.getFlop1();
		m_cards[3] = board.getFlop2();
		m_cards[4] = board.getFlop3();
		m_NumCards = 5;
	}

	if(board.getStreet() >= BOARD_TURN)
	{
		m_cards[5] = board.getTurn();
		m_NumCards = 6;
	}

	if(board.getStreet() >= BOARD_RIVER)
	{
		m_cards[6] = board.getRiver();
		m_NumCards = 7;
	}
}

CHolding::~CHolding()
{

}

CHolding & CHolding::operator=(const CHolding &rhs)
{
	if(this == &rhs)
		return *this;

	m_NumCards = rhs.m_NumCards;

	m_cards[0] = rhs.m_cards[0];
	m_cards[1] = rhs.m_cards[1];
	m_cards[2] = rhs.m_cards[2];
	m_cards[3] = rhs.m_cards[3];
	m_cards[4] = rhs.m_cards[4];
	m_cards[5] = rhs.m_cards[5];
	m_cards[6] = rhs.m_cards[6];

	if(rhs.m_Evaluated)
	{ // only need to copy the best cards if its
		// been evaluated
		m_bestCards[0] = rhs.m_bestCards[0];
		m_bestCards[1] = rhs.m_bestCards[1];
		m_bestCards[2] = rhs.m_bestCards[2];
		m_bestCards[3] = rhs.m_bestCards[3];
		m_bestCards[4] = rhs.m_bestCards[4];
	}

	m_Evaluated = rhs.m_Evaluated;
	m_Sorted = rhs.m_Sorted;

	return *this;
}

void CHolding::reset(void)
{

	m_NumCards = 0;
	m_Evaluated = false;
	m_Sorted = false;

}

void CHolding::createHolding(const CHoleCards &holecards,
	const CBoard &board)
{
	m_NumCards = 0;

	if(holecards.getCard1().isValid() &&
		holecards.getCard2().isValid())
	{
		m_cards[0] = holecards.getCard1();
		m_cards[1] = holecards.getCard2();
		m_NumCards = 2;
	}

	if(board.getStreet() >= BOARD_FLOP)
	{
		m_cards[2] = board.getFlop1();
		m_cards[3] = board.getFlop2();
		m_cards[4] = board.getFlop3();
		m_NumCards = 5;
	}

	if(board.getStreet() >= BOARD_TURN)
	{
		m_cards[5] = board.getTurn();
		m_NumCards = 6;
	}

	if(board.getStreet() >= BOARD_RIVER)
	{
		m_cards[6] = board.getRiver();
		m_NumCards = 7;
	}

	m_Evaluated = false;
	m_Sorted = false;

}

void CHolding::sort(void)
{
	int i;
	int low=0,high=m_NumCards-1;
	int max=0,maxindex=0,min=15,minindex=0;

	while(low<high) 
	{
		for(i=low;i<=high;i++) 
		{ 
			if(m_cards[i].getRank() >= max) 
			{
				max=m_cards[i].getRank();
				maxindex=i;
			} 
			if(m_cards[i].getRank() < min) 
			{
				min = m_cards[i].getRank();
				minindex=i;
			};
		};
		max=0;min=15;
		if(low==maxindex || high==minindex) 
		{
			if(low!=maxindex) 
			{/* only high==minindex */
				swapcards(m_cards[minindex],m_cards[low]);	      
				swapcards(m_cards[maxindex],m_cards[high]);
			} 
			else
				if(high!=minindex)
				{ /*only low==maxindex */
					swapcards(m_cards[maxindex],m_cards[high]);
					swapcards(m_cards[minindex],m_cards[low]);	      
				}
				else 
					swapcards(m_cards[high],m_cards[low]); 
		}
		else
		{
			swapcards(m_cards[maxindex],m_cards[high]);
			swapcards(m_cards[minindex],m_cards[low]);	      
		}
		low++;high--;
	};

	m_Sorted = true;
}

void CHolding::evaluate(void) 
{

	int fullof = 0;
	int j=4;
	int i,max,rankindex=0;
	int diff;
	int pairs[15];
	int suits[5];
	int straightlength = 1;
	int highcard = 0;
	int besthandsofar = HOLDING_HIGHCARD; /* start out with high card hand (guaranteed) */
	eCardSuit flushsuit = SUIT_BLANK; /* assumed no flush */
	int markedcards[7]; /* cards to mark */
	int nomarkedcards = 0; /* number of marked cards */
	int wheel[5] = {0,0,0,0,0}; /* wheel possibility */

	m_Evaluated = true;

	if(!m_Sorted)
	{
		sort();
	}

	/* First check for a flush */
	for(i=0;i<5;i++)
	{
		suits[i] = 0;
	}

	/* Increment suits as necessary */
	for(i=0;i<m_NumCards;i++)
	{
		suits[m_cards[i].getSuit()]++;
	}

	/* Check for flush */
	for(i=1;i<5;i++) 
	{
		if (suits[i] >= 5) 
		{
			/* Flush exists in suit 'i' */
			besthandsofar = HOLDING_FLUSH;
			flushsuit = (eCardSuit)i;
		};
	};

	if (besthandsofar == HOLDING_FLUSH)	
	{
		/* First mark cards that are in flush */
		for(i=0;i<m_NumCards;i++)	
		{
			if(m_cards[i].getSuit()==flushsuit)	
			{
				markedcards[nomarkedcards++]=i;
			};
		};
		/* Check for straight flush */
		straightlength = 1;
		for(i=1;i<nomarkedcards;i++)	
		{
			diff = m_cards[markedcards[i]].getRank() - 
				m_cards[markedcards[i-1]].getRank();
			if (diff==1)	
			{
				straightlength++;
				if (straightlength >=5)	
				{
					besthandsofar = HOLDING_STRAIGHTFLUSH; /* Have a straightflush!!!! */
					highcard = i;
				};
			};
			if (diff>=2) 
				straightlength = 1;
		};

		if(besthandsofar != HOLDING_STRAIGHTFLUSH)  /* if no other straightflush was found */
			highcard = nomarkedcards-1;

		/* now mark 5 highest flush (or straight flush) cards */
		for(i=0;i<5;i++)	
		{
			m_bestCards[4-i].setRank(m_cards[markedcards[highcard-i]].getRank());
			m_bestCards[4-i].setSuit(flushsuit);
		};

	};

	if (besthandsofar == HOLDING_STRAIGHTFLUSH)
	{
		m_handQuality = (eHoldingType)besthandsofar;
		return;
	}
	if (besthandsofar == HOLDING_FLUSH)	
	{
		/* check for the wheel! */
		if (m_cards[markedcards[highcard]].getRank() == RANK_ACE && 
			m_cards[markedcards[0]].getRank() == RANK_TWO &&
			m_cards[markedcards[1]].getRank() == RANK_THREE && 
			m_cards[markedcards[2]].getRank() == RANK_FOUR &&
			m_cards[markedcards[3]].getRank() == RANK_FIVE)
		{  /* if wheel! */
			m_bestCards[4].setRank(RANK_FIVE);
			m_bestCards[4].setSuit(flushsuit);
			m_bestCards[3].setRank(RANK_FOUR);
			m_bestCards[3].setSuit(flushsuit);
			m_bestCards[2].setRank(RANK_THREE);
			m_bestCards[2].setSuit(flushsuit);
			m_bestCards[1].setRank(RANK_TWO);
			m_bestCards[1].setSuit(flushsuit);
			m_bestCards[0].setRank(m_cards[markedcards[highcard]].getRank());
			m_bestCards[0].setSuit(flushsuit);
			besthandsofar = HOLDING_STRAIGHTFLUSH;
		};
		m_handQuality = (eHoldingType)besthandsofar;
		return;
	};

	/* So now we know its not a flush or a straigh flush... check for rest */
	for(i=0;i<15;i++)
		pairs[i] = 0;

	if(m_cards[0].getRank()==RANK_TWO)
		wheel[1]++;  /* increment the proper wheel counter */

	for(i=1;i<m_NumCards;i++)	
	{
		switch(m_cards[i].getRank())	
		{
		case RANK_THREE:
			wheel[2]++;
			break;
		case RANK_FOUR: 
			wheel[3]++;
			break;
		case RANK_FIVE:
			wheel[4]++;
			break;
		case RANK_ACE:
			wheel[0]++;
			break;
		default:
			break;
		}
		diff = m_cards[i].getRank() - m_cards[i-1].getRank();
		if (diff==0)
			pairs[m_cards[i].getRank()]++;
		if (diff==1)	
		{
			straightlength++;
			if (straightlength >=5)	
			{
				besthandsofar = HOLDING_STRAIGHT; /* Have a straight */
				highcard = m_cards[i].getRank();
			};
		};
		if (diff>=2) 
			straightlength = 1;
	};

	wheel[0] = ((besthandsofar!=HOLDING_STRAIGHT) && 
		wheel[0] && 
		wheel[1] && 
		wheel[2] && 
		wheel[3] && 
		wheel[4]);
	/* if there's a wheel and there's no other straight */
	/* put it in wheel[0] */
	besthandsofar = ( wheel[0] ? HOLDING_STRAIGHT : besthandsofar);

	if(besthandsofar==HOLDING_STRAIGHT)	
	{  /* if straight then stack it */
		if(wheel[0])	
		{
			/* stack wheel */
			m_bestCards[4].setRank(RANK_FIVE);
			m_bestCards[3].setRank(RANK_FOUR);
			m_bestCards[2].setRank(RANK_THREE);
			m_bestCards[1].setRank(RANK_TWO);
			m_bestCards[0].setRank(RANK_ACE);
			for(i=0;i<m_NumCards;i++)  
			{
				switch(m_cards[i].getRank()) 
				{
				case 5:
					m_bestCards[4].setSuit(m_cards[i].getSuit());
					break;
				case 4:
					m_bestCards[3].setSuit(m_cards[i].getSuit());
					break;
				case 3:
					m_bestCards[2].setSuit(m_cards[i].getSuit());
					break;
				case 2:
					m_bestCards[1].setSuit(m_cards[i].getSuit());
					break;
				case 14:
					m_bestCards[0].setSuit(m_cards[i].getSuit());
					break;
				default:
					break;
				};
			};

		}
		else	{  /* stack normal straight */
			j=4;
			for(i=m_NumCards-1;i>=0;i--)	
			{
				if(m_cards[i].getRank()==highcard) 
				{
					m_bestCards[j] = m_cards[i];
					j--;
					highcard--;
					if(j==-1)
						break;
				};
			};
		};
		m_handQuality = (eHoldingType)besthandsofar;
		return;
	};

	/* now decipher the number of pairs */
	max = 0;
	for(i=2;i<15;i++)	
	{
		if(pairs[i] >= max)	
		{
			max = pairs[i];
			rankindex = i;
		};
	};

	if(max==3)	{  /* quads! */
		/* now find the hand */
		besthandsofar = HOLDING_FOUROFAKIND;
		for(i=m_NumCards-1;i>=0;i--)	
		{
			if(m_cards[i].getRank() != rankindex)
			{	/* found kicker */
				m_bestCards[0] = m_cards[i];
				break; /* from for loop */
			};
		};
		/* the rest are by default the quads */
		m_bestCards[1].setRank((eCardRank)rankindex);
		m_bestCards[1].setSuit(SUIT_CLUBS);
		m_bestCards[2].setRank((eCardRank)rankindex);
		m_bestCards[2].setSuit(SUIT_DIAMONDS);
		m_bestCards[3].setRank((eCardRank)rankindex);
		m_bestCards[3].setSuit(SUIT_HEARTS);
		m_bestCards[4].setRank((eCardRank)rankindex);
		m_bestCards[4].setSuit(SUIT_SPADES);
		m_handQuality = (eHoldingType)besthandsofar;
		return;
	};


	if(max==2)
	{  /* check for full house  */
		for(i=2;i<15;i++)	
		{
			if ((i!=rankindex)&&(pairs[i]>=1))
			{  /* find out what it is full of */
				fullof = i;
			};
		};

		if (fullof != 0)
		{ /* full house exists !!!*/
			besthandsofar = HOLDING_FULLHOUSE;
			/* hand is decided... now we just have to stack it */
			for(i=0;i<m_NumCards;i++)
			{
				if(m_cards[i].getRank() == rankindex)	{
					m_bestCards[j] = m_cards[i];
					j--;
				};
			};
			for(i=0;i<m_NumCards;i++)	{
				if(m_cards[i].getRank() == fullof) {
					m_bestCards[j] = m_cards[i];
					j--;
					if(j==-1)
						break;
				};
			};
			m_handQuality = (eHoldingType)besthandsofar;
			return;
		};


		besthandsofar=HOLDING_THREEOFAKIND; /* then trips */
		/* stack trips */
		j=4;
		for(i=0;i<m_NumCards;i++)	
		{
			/* go through and find trips  */
			if(m_cards[i].getRank()==rankindex)	
			{
				m_bestCards[j] = m_cards[i];
				j--;
			};
		};
		for(i=m_NumCards-1;i>=0;i--)	
		{
			/* go through and find kickers */
			if(m_cards[i].getRank()!=rankindex)	
			{
				m_bestCards[j] =m_cards[i];
				j--;
				if(j==-1)
					break;
			};
		};
		m_handQuality = (eHoldingType)besthandsofar;
		return;
	};

	/* if there exists at least 1 pair */
	if(max==1)
	{ /* either two pairs or one pair */
		fullof=0;
		for(i=2;i<15;i++)	
		{
			if ((i!=rankindex)&&(pairs[i]>=1))
			{  /* find out what it is 'full of' */
				fullof = i;
			};
		};
		if(fullof==0)
		{ /* only a pair */
			j=4;
			besthandsofar=HOLDING_PAIR;
			for(i=0;i<m_NumCards;i++)	
			{
				if(m_cards[i].getRank()==rankindex)	
				{
					m_bestCards[j] = m_cards[i];
					j--;
				};
			};
			for(i=m_NumCards-1;i>=0;i--)	
			{
				if(m_cards[i].getRank()!= rankindex)  
				{
					m_bestCards[j] = m_cards[i];
					j--;
				};
				if (j==-1)
					break;
			};
		}
		else 
		{  /* two pair */
			besthandsofar=HOLDING_TWOPAIR;
			i=m_NumCards-1;
			do 
			{
				if(m_cards[i].getRank()==rankindex)	
				{
					m_bestCards[j] = m_cards[i];
					j--;
				};
				i--;
			} while (j>2);
			i=m_NumCards-3; /* start here and count down */
			do {
				if(m_cards[i].getRank()==fullof)	
				{
					m_bestCards[j] = m_cards[i];
					j--;
				}
				i--;
			} while(j>0);
			// just need to populate final card
			for(i=m_NumCards-1;i>=0;--i)
			{
				if((m_cards[i].getRank()!= rankindex ) && 
					(m_cards[i].getRank() != fullof))  
				{
					m_bestCards[j] = m_cards[i];
					break;
				};
			};
		};
		m_handQuality = (eHoldingType)besthandsofar;
		return;
	};

	/* stack high card hand */
	j=4;

	for(i=m_NumCards-1;i>=0;i--)	
	{
		m_bestCards[j] = m_cards[i];
		j--;
		if (j==-1)
			break;
	};

	m_handQuality = (eHoldingType)besthandsofar;
	return;

};

bool CHolding::operator==(CHolding &rhs)
{

	if(this == &rhs)
		return true;

	if(m_Evaluated == 0)
		this->evaluate();

	if(m_Evaluated == 0)
		rhs.evaluate();

	if(m_handQuality != rhs.m_handQuality)
		return false;

	for(int i=4;i>=0;i--)	
	{
		if(m_bestCards[i].getRank() > rhs.m_bestCards[i].getRank() ||
			m_bestCards[i].getRank() < rhs.m_bestCards[i].getRank())
			return(false);
	};
	return(true);

}

bool CHolding::operator>(CHolding &rhs) 
{

	if(this == &rhs)
		return false;

	if(m_Evaluated == 0)
		this->evaluate();

	if(rhs.m_Evaluated == 0)
		rhs.evaluate();

	if(m_handQuality > rhs.m_handQuality)
		return true;

	if(m_handQuality < rhs.m_handQuality)
		return false;

	for(int i=4;i>=0;i--)	
	{
		if(m_bestCards[i].getRank() > rhs.m_bestCards[i].getRank())
			return true;
		if(m_bestCards[i].getRank() < rhs.m_bestCards[i].getRank())
			return false ;
	};
	// they are equal
	return false;
}

bool CHolding::operator<(CHolding &rhs) 
{

	if(this == &rhs)
		return false;

	if(m_Evaluated == 0)
		evaluate();

	if(rhs.m_Evaluated == 0)
		rhs.evaluate();

	if(m_handQuality < rhs.m_handQuality)
		return true;

	if(m_handQuality > rhs.m_handQuality)
		return false;

	for(int i=4;i>=0;i--)	
	{
		if(m_bestCards[i].getRank() < rhs.m_bestCards[i].getRank())
			return true;
		if(m_bestCards[i].getRank() > rhs.m_bestCards[i].getRank())
			return false;
	};
	// they are equal
	return false;
}

