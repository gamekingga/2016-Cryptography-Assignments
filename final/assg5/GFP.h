#ifndef __GFP_H__
#define __GFP_H__
#include <stdio.h>
#include <stdlib.h>
#include "BigNumber.h"

class GFP{
	public:
		GFP();	//constructor
		~GFP();	//destructor

		void setNum(BigNumber a);

		GFP operator +(const GFP& b);
		GFP operator -(const GFP& b);
		GFP operator *(const GFP& b);
		GFP operator ^(const GFP& b);
		void operator =(const BigNumber& b);

		void print(){
			num.printBigNumber();
		}

		static BigNumber mod_prime;// for sharing the same memory
		BigNumber num;
};

#endif	/*__GFP_H__*/