#ifndef DECK_H
#define DECK_H

#include "card.h"
#include "RandNumMT.h"

class CDeck {

public:  
  CDeck(unsigned long seed=0);
  CDeck(RandNumMT *pRNG);
  CDeck(const CDeck& rhs);
  ~CDeck();
  
  CDeck & operator=(const CDeck &rhs);
  
  void shuffle(void);
  CCard dealCard(void);
  CCard peekCard(void);
  void pullCard(const CCard &pullcard);

 private: // this shouldn't be used
  bool operator==(const CDeck &rhs) const;
    
 private:
  int m_numLeft;
  CCard m_cards[52];
  RandNumMT *m_pRNG;
  bool m_ExternalRNG;

};

#endif

