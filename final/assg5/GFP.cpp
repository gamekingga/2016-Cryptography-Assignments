#include "GFP.h"
#define self (*this)
BigNumber GFP::mod_prime;
// avoiding the error of undefined reference

GFP::GFP(){
}
GFP::~GFP(){
}

GFP
GFP::operator +(const GFP& b){
	GFP r;	r.setNum( (self.num + b.num)%mod_prime );
	return r;
}
GFP
GFP::operator -(const GFP& b){
	GFP r;	r.setNum( (self.num - b.num)%mod_prime );
	return r;
}
GFP
GFP::operator *(const GFP& b){
	GFP r;	r.setNum( (self.num * b.num)%mod_prime );
	return r;
}
GFP
GFP::operator ^(const GFP& b){
	GFP r;	r.setNum( self.num.Pow(b.num, mod_prime) );
	return r;
}
void
GFP::operator =(const BigNumber& b){
	self.setNum( b );
	return;
}

void
GFP::setNum(BigNumber a){
	self.num = a;
	return;
}
