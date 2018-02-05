/* 
A C-program for MT19937, with initialization improved 2002/1/26.
Coded by Takuji Nishimura and Makoto Matsumoto.

Before using, initialize the state by using setSeed(seed)  
or init_by_array(init_key, key_length).

Copyright (C) 1997 - 2002, Makoto Matsumoto and Takuji Nishimura,
All rights reserved.                          

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions
are met:

1. Redistributions of source code must retain the above copyright
notice, this list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright
notice, this list of conditions and the following disclaimer in the
documentation and/or other materials provided with the distribution.

3. The names of its contributors may not be used to endorse or promote 
products derived from this software without specific prior written 
permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
"AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR
CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.


Any feedback is very welcome.
http://www.math.sci.hiroshima-u.ac.jp/~m-mat/MT/emt.html
email: m-mat @ math.sci.hiroshima-u.ac.jp (remove space)
*/

#include "RandNumMT.h"

RandNumMT::RandNumMT(unsigned long seed)
{
	setSeed(seed);
}

RandNumMT::~RandNumMT()
{

}

double RandNumMT::getRandnum(void)
{
	return genrand_int32()*(1.0/4294967296.0); 
	/* divided by 2^32 */
}

/* initializes mt[624] with a seed */
void RandNumMT::setSeed(unsigned long s)
{
	m_mt[0]= s & 0xffffffffUL;
	for (m_mti=1; m_mti<624; m_mti++) {
		m_mt[m_mti] = 
			(1812433253UL * (m_mt[m_mti-1] ^ (m_mt[m_mti-1] >> 30)) + m_mti); 
		/* See Knuth TAOCP Vol2. 3rd Ed. P.106 for multiplier. */
		/* In the previous versions, MSBs of the seed affect   */
		/* only MSBs of the array mt[].                        */
		/* 2002/01/09 modified by Makoto Matsumoto             */
		m_mt[m_mti] &= 0xffffffffUL;
		/* for >32 bit machines */
	}
}

/* initialize by an array with array-length */
/* init_key is the array for initializing keys */
/* key_length is its length */
/* slight change for C++, 2004/2/26 */
void RandNumMT::init_by_array(unsigned long init_key[], int key_length)
{
	int i, j, k;
	setSeed(19650218UL);
	i=1; j=0;
	k = (624>key_length ? 624 : key_length);
	for (; k; k--) {
		m_mt[i] = (m_mt[i] ^ ((m_mt[i-1] ^ (m_mt[i-1] >> 30)) * 1664525UL))
			+ init_key[j] + j; /* non linear */
		m_mt[i] &= 0xffffffffUL; /* for WORDSIZE > 32 machines */
		i++; j++;
		if (i>=624) { m_mt[0] = m_mt[624-1]; i=1; }
		if (j>=key_length) j=0;
	}
	for (k=624-1; k; k--) {
		m_mt[i] = (m_mt[i] ^ ((m_mt[i-1] ^ (m_mt[i-1] >> 30)) * 1566083941UL))
			- i; /* non linear */
		m_mt[i] &= 0xffffffffUL; /* for WORDSIZE > 32 machines */
		i++;
		if (i>=624) { m_mt[0] = m_mt[624-1]; i=1; }
	}

	m_mt[0] = 0x80000000UL; /* MSB is 1; assuring non-zero initial array */ 
}

/* generates a random number on [0,0xffffffff]-interval */
unsigned long RandNumMT::genrand_int32(void)
{
	unsigned long y;
	static unsigned long mag01[2]={0x0UL, m_MATRIX_A};
	/* mag01[x] = x * MATRIX_A  for x=0,1 */

	if (m_mti >= 624) { /* generate N words at one time */
		int kk;

		if (m_mti == 624+1)   /* if setSeed() has not been called, */
			setSeed(5489UL); /* a default initial seed is used */

		for (kk=0;kk<624-397;kk++) {
			y = (m_mt[kk]&m_UPPER_MASK)|(m_mt[kk+1]&m_LOWER_MASK);
			m_mt[kk] = m_mt[kk+397] ^ (y >> 1) ^ mag01[y & 0x1UL];
		}
		for (;kk<624-1;kk++) {
			y = (m_mt[kk]&m_UPPER_MASK)|(m_mt[kk+1]&m_LOWER_MASK);
			m_mt[kk] = m_mt[kk+(397-624)] ^ (y >> 1) ^ mag01[y & 0x1UL];
		}
		y = (m_mt[624-1]&m_UPPER_MASK)|(m_mt[0]&m_LOWER_MASK);
		m_mt[624-1] = m_mt[397-1] ^ (y >> 1) ^ mag01[y & 0x1UL];

		m_mti = 0;
	}

	y = m_mt[m_mti++];

	/* Tempering */
	y ^= (y >> 11);
	y ^= (y << 7) & 0x9d2c5680UL;
	y ^= (y << 15) & 0xefc60000UL;
	y ^= (y >> 18);

	return y;
}

/* generates a random number on [0,0x7fffffff]-interval */
long RandNumMT::genrand_int31(void)
{
	return (long)(genrand_int32()>>1);
}

/* generates a random number on [0,1]-real-interval */
double RandNumMT::genrand_real1(void)
{
	return genrand_int32()*(1.0/4294967295.0); 
	/* divided by 2^32-1 */ 
}

/* generates a random number on [0,1)-real-interval */
double RandNumMT::genrand_real2(void)
{
	return genrand_int32()*(1.0/4294967296.0); 
	/* divided by 2^32 */
}

/* generates a random number on (0,1)-real-interval */
double RandNumMT::genrand_real3(void)
{
	return (((double)genrand_int32()) + 0.5)*(1.0/4294967296.0); 
	/* divided by 2^32 */
}

/* generates a random number on [0,1) with 53-bit resolution*/
double RandNumMT::genrand_res53(void) 
{ 
	unsigned long a=genrand_int32()>>5, b=genrand_int32()>>6; 
	return(a*67108864.0+b)*(1.0/9007199254740992.0); 
} 
/* These real versions are due to Isaku Wada, 2002/01/09 added */
