
#include <stdio.h>
#include "holecards.h"

const char CHoleCards::hcTypeArray[] = "AA KK QQ JJ TT 99 88 77 66 55 44 33 22 \
AKsAQsAJsATsA9sA8sA7sA6sA5sA4sA3sA2s\
KQsKJsKTsK9sK8sK7sK6sK5sK4sK3sK2s\
QJsQTsQ9sQ8sQ7sQ6sQ5sQ4sQ3sQ2s\
JTsJ9sJ8sJ7sJ6sJ5sJ4sJ3sJ2s\
T9sT8sT7sT6sT5sT4sT3sT2s\
98s97s96s95s94s93s92s\
87s86s85s84s83s82s\
76s75s74s73s72s\
65s64s63s62s\
54s53s52s\
43s42s\
32s\
AKoAQoAJoAToA9oA8oA7oA6oA5oA4oA3oA2o\
KQoKJoKToK9oK8oK7oK6oK5oK4oK3oK2o\
QJoQToQ9oQ8oQ7oQ6oQ5oQ4oQ3oQ2o\
JToJ9oJ8oJ7oJ6oJ5oJ4oJ3oJ2o\
T9oT8oT7oT6oT5oT4oT3oT2o\
98o97o96o95o94o93o92o\
87o86o85o84o83o82o\
76o75o74o73o72o\
65o64o63o62o\
54o53o52o\
43o42o\
32o";

CHoleCards::CHoleCards()
{
  
}

CHoleCards::CHoleCards(const CHoleCards& rhs)
	: m_Card1(rhs.m_Card1)
	, m_Card2(rhs.m_Card2)
{

}

CHoleCards::CHoleCards(const CCard &c1,const CCard &c2)
{
  m_Card1 = c1;
  m_Card2 = c2;
}

CHoleCards::~CHoleCards()
{

}

CHoleCards & CHoleCards::operator=(const CHoleCards &rhs)
{
  if(this == &rhs)
    return *this;

  m_Card1 = rhs.m_Card1;
  m_Card2 = rhs.m_Card2;

  return *this;
}
  
void CHoleCards::catASCII(std::ostream &os)
{
	m_Card1.catASCII(os);
	os << ",";
	m_Card2.catASCII(os);
}

int CHoleCards::getTypeIndex(void)
{
	// pairs
	if(m_Card1.getRank() == m_Card2.getRank())
	{
		return (12-(m_Card1.getRank()-RANK_TWO));
	}

	// determine index
	int index;
	if(m_Card1.getRank() > m_Card2.getRank())
	{
		index = (14-m_Card1.getRank())*13 + (m_Card1.getRank()-m_Card2.getRank()-1)-(14-m_Card1.getRank()+1)*(14-m_Card1.getRank()) / 2;
	}
	else
	{
		index = (14-m_Card2.getRank())*13 + (m_Card2.getRank()-m_Card1.getRank()-1)-(14-m_Card2.getRank()+1)*(14-m_Card2.getRank()) / 2;
	}

	// now add index to correct number whether its suited or not
	if(m_Card1.getSuit() == m_Card2.getSuit())
	{
		return 13 + index;
	}
	else
	{
		return 13 + 78 + index;
	}
}

void CHoleCards::catASCIIHoleCardType(std::ostream &os)
{
	int hctypeindex = getTypeIndex();
	os << hcTypeArray[hctypeindex*3] << hcTypeArray[hctypeindex*3+1] << hcTypeArray[hctypeindex*3+2];
}

void CHoleCards::catASCIIHoleCardTypeFromIndex(int hctypeindex, std::ostream &os)
{
	os << hcTypeArray[hctypeindex*3] << hcTypeArray[hctypeindex*3+1] << hcTypeArray[hctypeindex*3+2];	
}

std::string CHoleCards::getStringHoleCardTypeFromIndex(int hctypeindex)
{
	std::string str;
	str.push_back(hcTypeArray[hctypeindex*3]);
	str.push_back(hcTypeArray[hctypeindex*3+1]);
	str.push_back(hcTypeArray[hctypeindex*3+2]);
	return str;
}