#ifndef __GFP2_H__
#define __GFP2_H__
#include <stdio.h>
#include <stdlib.h>
#include "BigNumber.h"
#include "GFP.h"

class GFP2{
	public:
		GFP2();	//constructor
		~GFP2();//destructor

		void setNum(GFP a, GFP b);
		GFP2 operator +(const GFP2& b);
		GFP2 operator -(const GFP2& b);
		GFP2 operator *(const GFP2& b);

		GFP2 GFP2_2();
		GFP2 GFP2_P();

		GFP2 C2n(GFP2 cn);
		GFP2 Cnp2(GFP2 c, GFP2 cnm1, GFP2 cn, GFP2 cnp1);
		GFP2 C2nm1(GFP2 c, GFP2 cnm1, GFP2 cn, GFP2 cnp1);
		GFP2 C2np1(GFP2 c, GFP2 cnm1, GFP2 cn, GFP2 cnp1);

		void print(){
			printf("first: ");	first.print();
			printf("second:");	second.print();
		}

		GFP first;
		GFP second;
};

#endif /*__GFP2_H__*/