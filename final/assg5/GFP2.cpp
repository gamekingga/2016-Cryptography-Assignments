#include "GFP2.h"
#define self (*this)

GFP2::GFP2(){
}
GFP2::~GFP2(){
}

GFP2
GFP2::operator +(const GFP2& b){
	GFP res1 = self.first + b.first;//x1+y1
	GFP res2 = self.second + b.second;//x2+y2
	GFP2 r;	r.setNum(res1, res2);
	return r;
}
GFP2
GFP2::operator -(const GFP2& b){
	GFP res1 = self.first - b.first;//x1-y1
	GFP res2 = self.second - b.second;//x2-y2
	GFP2 r;	r.setNum(res1, res2);
	return r;
}
GFP2
GFP2::operator *(const GFP2& b){
	/*	
		Z = X*Y = z1a + z2a^2

		z1 = x2y2 - (x1y2 + x2y1)
		z2 = x1y1 - (x1y2 + x2y1)
	*/
	GFP cross = self.first*b.second + self.second*b.first;//x1y2+x2y1
	GFP res1 = self.second*b.second - cross;
	GFP res2 = self.first*b.first - cross;
	GFP2 r;	r.setNum(res1, res2);
	return r;
}

GFP2
GFP2::GFP2_2(){
	/*
		Z = X^2 = X*X
   
		z1 = x2 * x2 - 2 * x1 * x2
		z2 = x1 * x1 - 2 * x1 * x2
	*/
	GFP res1 = self.second*self.second - self.first*self.second - self.first*self.second;
	GFP res2 = self.first*self.first - self.first*self.second - self.first*self.second;
	GFP2 r;	r.setNum(res1, res2);
	return r;
}
GFP2
GFP2::GFP2_P(){
	GFP2 r;	r.setNum(self.second, self.first);
	return r;
}
/*
GFP2
GFP2::C2n(GFP2 cn){
	//C{2n} = C{n}^2 - 2*(C{n})^p
	return GFP2_2(cn) - GFP2_P(cn) - GFP2_P(cn);
}
GFP2
GFP2::Cnp2(GFP2 c, GFP2 cnm1, GFP2 cn, GFP2 cnp1){
	//C{n+2} = C * C{n+1} - C^p * C{n} + C{n-1}
	return cnp1*c - GFP2_P(c)*cn + cnm1;
}
GFP2
GFP2::C2nm1(GFP2 c, GFP2 cnm1, GFP2 cn, GFP2 cnp1){
	//C{2n-1} = C{n-1} * C{n} - C^p * (C{n})^p + (C{n+1})^p
	return cnm1*cn - GFP2_P(c)*GFP2_P(cn) + GFP2_P(cnp1);
}
GFP2
GFP2::C2np1(GFP2 c, GFP2 cnm1, GFP2 cn, GFP2 cnp1){
	//C{2n+1} = C{n+1} * C{n} - C1 * (C{n})^p + (C{n-1})^p
	return cnp1*cn - c*GFP2_P(cn) + GFP2_P(cnm1);
}
*/
void
GFP2::setNum(GFP a, GFP b){
	self.first = a;
	self.second = b;
}

