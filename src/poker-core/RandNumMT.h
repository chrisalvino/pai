
#ifndef RANDNUMMT_H
#define RANDNUMMT_H

//! RandNumMT -- Random number generator wrapping Mersenne Twister
/*! \author Chris Alvino

Fast good random number generator provided in a class to allow the user more control

Use it by creating and instance of RandNumMT and then (optionally) calling setSeed()
before doing a sequence of getRandnum() calls (one for each random number needed).

You only need to seed once, and seeding simply initializes the random number generator
*/
class RandNumMT
{
public:
	//! Constructor (with optional seed)
	/*! \param seed		starting seed
	*/
	RandNumMT(unsigned long seed=0);

	/// Destructor
	~RandNumMT();

	//! Get a random number in the interval [0,1)
	/*! \return Random number
	*/
	double getRandnum(void);

	//! Set the seed (only needs to be done once)
	/*! \param s	Random number seed
	\return none
	*/
	void setSeed(unsigned long s);

protected:
	/// Protected function
	void init_by_array(unsigned long init_key[], int key_length);

	/// Protected function
	unsigned long genrand_int32(void);

	/// Protected function
	long genrand_int31(void);

	/// Protected function
	double genrand_real1(void);

	/// Protected function
	double genrand_real2(void);

	/// Protected function
	double genrand_real3(void);

	/// Protected function
	double genrand_res53(void);

private:	
	/// disabled copy constructor
	RandNumMT(const RandNumMT& rhs);

	/// disabled assignment operator
	RandNumMT & operator=(const RandNumMT& rhs);

private:
	unsigned long m_mt[624];	///< Internal random number state
	int m_mti;					///< Internal random number state

	static const unsigned long m_MATRIX_A = 0x9908b0df;		///< Internal random period parameters, do not modify
	static const unsigned long m_UPPER_MASK = 0x80000000;   ///< Internal random period parameters, do not modify
	static const unsigned long m_LOWER_MASK = 0x7fffffff;   ///< Internal random period parameters, do not modify
};

#endif  // RANDNUMMT_H





