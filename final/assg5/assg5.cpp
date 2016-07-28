#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <iostream>
#include <algorithm>
#include "BigNumber.h"
#include "GFP.h"
#include "GFP2.h"
typedef struct{
	GFP2 n_prev;
	GFP2 n;
	GFP2 n_next;
}S;

GFP2 C2n(GFP2 cn){
	//C{2n} = C{n}^2 - 2*(C{n})^p
	return cn.GFP2_2() - cn.GFP2_P() - cn.GFP2_P();
}
GFP2 Cnp2(GFP2 c, GFP2 cnm1, GFP2 cn, GFP2 cnp1){
	//C{n+2} = C * C{n+1} - C^p * C{n} + C{n-1}
	return c*cnp1 - (c.GFP2_P())*cn + cnm1;
}
GFP2 C2nm1(GFP2 c, GFP2 cnm1, GFP2 cn, GFP2 cnp1){
	//C{2n-1} = C{n-1} * C{n} - C^p * (C{n})^p + (C{n+1})^p
	return cnm1*cn - (c.GFP2_P())*(cn.GFP2_P()) + cnp1.GFP2_P();
}
GFP2 C2np1(GFP2 c, GFP2 cnm1, GFP2 cn, GFP2 cnp1){
	//C{2n+1} = C{n+1} * C{n} - C * (C{n})^p + (C{n-1})^p
	return cnp1*cn - c*(cn.GFP2_P()) + cnm1.GFP2_P();
}

void hexToBin(char* mp, int hex){
	switch(hex){
		case 0:
			*(mp) = 0;	*(mp+1) = 0;	*(mp+2) = 0;	*(mp+3) = 0;	break;
		case 1:
			*(mp) = 1;	*(mp+1) = 0;	*(mp+2) = 0;	*(mp+3) = 0;	break;
		case 2:
			*(mp) = 0;	*(mp+1) = 1;	*(mp+2) = 0;	*(mp+3) = 0;	break;
		case 3:
			*(mp) = 1;	*(mp+1) = 1;	*(mp+2) = 0;	*(mp+3) = 0;	break;
		case 4:
			*(mp) = 0;	*(mp+1) = 0;	*(mp+2) = 1;	*(mp+3) = 0;	break;
		case 5:
			*(mp) = 1;	*(mp+1) = 0;	*(mp+2) = 1;	*(mp+3) = 0;	break;
		case 6:
			*(mp) = 0;	*(mp+1) = 1;	*(mp+2) = 1;	*(mp+3) = 0;	break;
		case 7:
			*(mp) = 1;	*(mp+1) = 1;	*(mp+2) = 1;	*(mp+3) = 0;	break;
		case 8:
			*(mp) = 0;	*(mp+1) = 0;	*(mp+2) = 0;	*(mp+3) = 1;	break;
		case 9:
			*(mp) = 1;	*(mp+1) = 0;	*(mp+2) = 0;	*(mp+3) = 1;	break;
		case 10:
			*(mp) = 0;	*(mp+1) = 1;	*(mp+2) = 0;	*(mp+3) = 1;	break;
		case 11:
			*(mp) = 1;	*(mp+1) = 1;	*(mp+2) = 0;	*(mp+3) = 1;	break;
		case 12:
			*(mp) = 0;	*(mp+1) = 0;	*(mp+2) = 1;	*(mp+3) = 1;	break;
		case 13:
			*(mp) = 1;	*(mp+1) = 0;	*(mp+2) = 1;	*(mp+3) = 1;	break;
		case 14:
			*(mp) = 0;	*(mp+1) = 1;	*(mp+2) = 1;	*(mp+3) = 1;	break;
		case 15:
			*(mp) = 1;	*(mp+1) = 1;	*(mp+2) = 1;	*(mp+3) = 1;	break;
		default:
			*(mp) = 0;	*(mp+1) = 0;	*(mp+2) = 0;	*(mp+3) = 0;	break;
	}
	return;
}

void Sn(BigNumber n, GFP2 c, GFP2* result){//let c become cn, assume n>2
	
		// we need to build S0, S1, S2, S3 first
		// so we need c-1, c0, c1, c2, c3, c4

		// there are a special number of GFP2: three
		// it means that three.first = -3, three.second = -3
		// so that it accords to the rule of a^2 + a + 1 = 0 in GFP2
	
	BigNumber t;	t.num_int[0] = 3;	t.length = 1;	t.sign = 1;
	GFP t_temp;	t_temp = t;	//It means setNum of GFP.
	GFP2 three;	three.setNum(t_temp, t_temp);

	GFP2 c_1, c0, c1, c2, c3, c4;
	c_1 = c.GFP2_P();
	c0 = three;
	c1 = c;
	c2 = C2n(c1);
	c3 = Cnp2(c, c0, c1, c2);//n=1->n=3 => Cnp2(c, c0, c1, c2)
	c4 = C2n(c2);

		// for finding Sn (n>2), we need to look at m(calculated from n) in base_2(bitlook)
		// and use the algorith of fast computing
		// For Example:
		// 		BigNumber m = 135792468
		// 		value that stored in num_int array: 864297531
		// 		m.getLength() = 9;
		// 		store in m_bitlook array(char type): 0001 0110 0010 0100 1001 1110 1010 1100 1000 (8 6 4 2 9 7 5 3 1)
		// 		start_index of fast computing: (9*4-1)-3-1	(next bit of first '1')	

		// In the following source code, we don't store m_bar, we calculate m directly.
		// If n is even => m_bar=n-1 => m = (n/2)-1.
		// If n is odd  => m_bar=n   => m = (n-1)/2.
	
	BigNumber m;
	BigNumber one;	one.num_int[0] = 1;	one.length = 1;
	BigNumber two;	two.num_int[0] = 2;	two.length = 1;
	bool flag;//n is odd or even(false: even, odd: true)
	if(n.isDivideInteger(2)){// n%2 == 0
		m = (n/two)-one;
		flag = false;
	}
	else{
		m = (n-one)/two;
		flag = true;
	}
	
	char m_bitlook[800] = {};
	for(int x=0; x<m.getLength(); x++)
		hexToBin( &m_bitlook[4*x] , m.num_int[x] );
	int start_index = 4*m.getLength()-1;
	for(; start_index>=0; start_index--){
		if(m_bitlook[start_index]!=0)
			break;
	}
	start_index--;
	
	S res;	res.n_prev = c2;	res.n = c3;	res.n_next = c4;
	GFP2 temp1, temp2, temp3;
	for(int x = start_index; x>=0; x--){
		temp1 = res.n_prev;
		temp2 = res.n;
		temp3 = res.n_next;
		if(m_bitlook[x] == 0){//mj = 0
			res.n_prev = C2n(temp1);
			res.n = C2nm1(c, temp1, temp2, temp3);
			res.n_next = C2n(temp2);
		}
		else{//mj = 1
			res.n_prev = C2n(temp2);
			res.n = C2np1(c, temp1, temp2, temp3);
			res.n_next = C2n(temp3);
		}
	}

	if(flag){// n is odd
		*result = res.n;
		return;
	}
	else{//n is even, need to do some process(return next)
		*result = res.n_next;
		return;
	}
}
int main(int argc, char const *argv[])
{
	char input[200]={};
	char ch;//for discarding input

	BigNumber p, q;
	printf("p = ");	scanf("%s", input);	p.hexToInt(input);
	GFP::mod_prime = p;
	printf("q = ");	scanf("%s", input);	q.hexToInt(input);	//q is nouse if we know "1 < a,b < q-2"
	
	BigNumber temp1, temp2;	GFP tp1, tp2;
	GFP2 Trg, Trga, Trgb, Trgab;
	printf("Tr(g) = ");
	scanf("%c%c%c", &ch, &ch, &ch);
	scanf("%s", input);	temp1.hexToInt(input);	tp1.setNum(temp1);
	scanf("%c%c%c", &ch, &ch, &ch);
	scanf("%s", input);	temp2.hexToInt(input);	tp2.setNum(temp2);
	scanf("%c%c%c", &ch, &ch, &ch);
	Trg.setNum(tp1, tp2);

	BigNumber a, b;
	printf("a = ");	scanf("%s", input);	a.hexToInt(input);
	printf("b = ");	scanf("%s", input);	b.hexToInt(input);

	Sn(a, Trg, &Trga);
	printf("Tr(g^a) = { ");	Trga.first.print();	printf(" , ");	Trga.second.print();	printf("}\n");
	Sn(b, Trg, &Trgb);
	printf("Tr(g^b) = { ");	Trgb.first.print();	printf(" , ");	Trgb.second.print();	printf("}\n");
	Sn(a, Trgb, &Trgab);
	printf("Tr(g^ab) = { ");	Trgab.first.print();	printf(" , ");	Trgab.second.print();	printf("}\n");
	
	
	return 0;
}