#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <iostream>
using namespace std;
typedef struct{
    int sign;
    int _0203;
    char num_str[200];
    int num_int[200];    // one thousand positions
    int length;         // length
}BigNumber;
BigNumber* Plus(BigNumber* a, BigNumber* b);//initialize
BigNumber* Minus(BigNumber* a, BigNumber* b);//initialize
void hexToInt(BigNumber* num){
    int x;
    for(x=0;x<num->length;x++){
        switch(num->num_str[num->length-x-1]){
            case '0':
                num->num_int[x] = 0;break;
            case '1':
                num->num_int[x] = 1;break;
            case '2':
                num->num_int[x] = 2;break;
            case '3':
                num->num_int[x] = 3;break;
            case '4':
                num->num_int[x] = 4;break;
            case '5':
                num->num_int[x] = 5;break;
            case '6':
                num->num_int[x] = 6;break;
            case '7':
                num->num_int[x] = 7;break;
            case '8':
                num->num_int[x] = 8;break;
            case '9':
                num->num_int[x] = 9;break;
            case 'A':
                num->num_int[x] = 10;break;
            case 'B':
                num->num_int[x] = 11;break;
            case 'C':
                num->num_int[x] = 12;break;
            case 'D':
                num->num_int[x] = 13;break;
            case 'E':
                num->num_int[x] = 14;break;
            case 'F':
                num->num_int[x] = 15;break;
            default:
                num->num_int[x] = 0;break;
        }
    }
}
void intToHex(BigNumber* num){
    int x;
    for(x=0;x<num->length;x++){
        switch(num->num_int[num->length-x-1]){
            case 0:
                num->num_str[x] = '0';break;
            case 1:
                num->num_str[x] = '1';break;
            case 2:
                num->num_str[x] = '2';break;
            case 3:
                num->num_str[x] = '3';break;
            case 4:
                num->num_str[x] = '4';break;
            case 5:
                num->num_str[x] = '5';break;
            case 6:
                num->num_str[x] = '6';break;
            case 7:
                num->num_str[x] = '7';break;
            case 8:
                num->num_str[x] = '8';break;
            case 9:
                num->num_str[x] = '9';break;
            case 10:
                num->num_str[x] = 'A';break;
            case 11:
                num->num_str[x] = 'B';break;
            case 12:
                num->num_str[x] = 'C';break;
            case 13:
                num->num_str[x] = 'D';break;
            case 14:
                num->num_str[x] = 'E';break;
            case 15:
                num->num_str[x] = 'F';break;
            default:
                num->num_str[x] = '0';break;
        }
    }
}
void printBigNumber(BigNumber* num){
    int x;
    if(num->sign)	putchar('-');
    if(num->length <= 0){
        putchar('0');
    }
    else{
        for(x=0;x<num->length;x++){
            putchar(num->num_str[x]);
        }
    }
    putchar('\n');
}
BigNumber* Larger(BigNumber* a, BigNumber* b){//compare length, and compare strcmp
    if(a->length > b->length)
        return a;
    else if(a->length < b->length)
        return b;
    else{
        if(strcmp(a->num_str,b->num_str) > 0)
            return a;
        else
            return b;
    }
}
bool Equal(BigNumber* a, BigNumber* b){
    //printf("a: ");printBigNumber(a);
    //printf("a->length: %d\n", a->length);
    //printf("b: ");printBigNumber(b);
    //printf("b->length: %d\n", b->length);
    int len = (a->length>b->length)?a->length:b->length;//get the bigger one
    //printf("len: %d\n", len);
    bool flag=true;
    for(int i=0; i<len; i++){
        //printf("a->num_str[%d]: %c", i, a->num_str[i]);
        //printf("b->num_str[%d]: %c", i, b->num_str[i]);
        if(a->num_str[i] != b->num_str[i]){
            flag = false;
            break;
        }
    }
    return flag;
}
BigNumber* Smaller(BigNumber* a, BigNumber* b){//compare length, and compare strcmp
    if(a->length > b->length)
        return b;
    else if(a->length < b->length)
        return a;
    else{
        if(strcmp(a->num_str,b->num_str) >= 0)
            return b;
        else
            return a;
    }
}
BigNumber* Plus(BigNumber* a, BigNumber* b){
    //allocate a space and initialize for the returning data
    BigNumber *res_plus;
    res_plus = (BigNumber*)malloc(sizeof(BigNumber));   memset(res_plus->num_int, 0, 200*sizeof(int));	res_plus->sign = 0;
    res_plus->length = (Larger(a, b))->length;
    
    if(a->sign != b->sign){
    	if(a->sign == 1){
    		BigNumber *temp;	temp = (BigNumber*)malloc(sizeof(BigNumber));	memcpy(temp, a, sizeof(BigNumber));
    		temp->sign = 0;
    		return Minus(b,temp);
    	}
    	else if(b->sign == 1){
    		BigNumber *temp;	temp = (BigNumber*)malloc(sizeof(BigNumber));	memcpy(temp, b, sizeof(BigNumber));
    		temp->sign = 0;
    		return Minus(a,temp);
    	}
    }
    else if(a->sign == 1)// a, b are both negative
    	res_plus->sign = 1;
    //plus two BigNumber and adjust carry
    int x;
    for(x=0;x<res_plus->length;x++)
        res_plus->num_int[x] = a->num_int[x] + b->num_int[x];

    for(x=0;x<res_plus->length;x++){
        if(res_plus->num_int[x]>15){
            res_plus->num_int[x] -= 16;
            res_plus->num_int[x+1] += 1;
        }
    }

    //edit res_plus->length
    if(res_plus->num_int[res_plus->length] > 0){
        res_plus->length += 1;
    }
    intToHex(res_plus);
    return res_plus;
}
BigNumber* Minus(BigNumber* a, BigNumber* b){//will do larger-smaller, main will consider whether the negative sign should print ny using "Smaller()"
    //allocate a space and initialize for the returning data
    BigNumber *res_minus;
    res_minus = (BigNumber*)malloc(sizeof(BigNumber));  memset(res_minus->num_int, 0, 200*sizeof(int));	res_minus->sign = 0;

    //need to be larger - smaller
    BigNumber *larger = Larger(a,b);
    int larger_length = larger->length;

    BigNumber *smaller = Smaller(a,b);
    int smaller_length = smaller->length;// <= no use

    if(a->sign!=b->sign){
    	if(a->sign == 1){	//a->sign == 1, b->sign == 0
    		BigNumber *temp;	temp = (BigNumber*)malloc(sizeof(BigNumber));	memcpy(temp, a, sizeof(BigNumber));
    		temp->sign = 0;
    		memcpy(res_minus, Plus(temp,b), sizeof(BigNumber));
    		res_minus->sign = 1;
    		return res_minus;
    	}
    	else{	//a->sign == 0, b->sign == 1
    		BigNumber *temp;	temp = (BigNumber*)malloc(sizeof(BigNumber));	memcpy(temp, b, sizeof(BigNumber));
    		temp->sign = 0;
    		memcpy(res_minus, Plus(a,temp), sizeof(BigNumber));
    		res_minus->sign = 0;
    		return res_minus;
    	}
    }
    
    if(a->sign == 1){	//a->sign == 1, b->sign == 1
    	if(larger == a)
    		res_minus->sign = 1;
    }
    else{
    	if(larger == b)
    		res_minus->sign = 1;
    }

    //minus two BigNumber and adjust carry
    int x;
    for(x=0;x<larger->length;x++)
        res_minus->num_int[x] = larger->num_int[x] - smaller->num_int[x];
    for(x=0;x<larger->length;x++){
        if(res_minus->num_int[x]<0){
            res_minus->num_int[x] += 16;
            res_minus->num_int[x+1] -= 1;
        }
    }

    //edit res_minus->length
    for(x=larger->length-1;x>=0;x--){
        if(res_minus->num_int[x]!=0)
            break;
    }
    res_minus->length = x+1;//if a-b = 0, x will be -1, x+1 will be zero, so we can use printBigNumber to handle
    intToHex(res_minus);
    if(res_minus->length == 0)	res_minus->sign = 0;
    return res_minus;
}
BigNumber* times(BigNumber* a, BigNumber* b){
    //allocate a space and initialize for the returning data
    BigNumber *res_times;
    res_times = (BigNumber*)malloc(sizeof(BigNumber));  memset(res_times->num_int, 0, 200*sizeof(int));	res_times->sign = 0;
    
    BigNumber *larger = Larger(a,b);//for x
    int larger_length = larger->length;

    BigNumber *smaller = Smaller(a,b);//for y
    int smaller_length = smaller->length;

    //times two numbers, adjust carry
    int x, y;
    for(x=0;x<larger_length;x++){
        for(y=0;y<smaller_length;y++)
            res_times->num_int[x+y] += larger->num_int[x] * smaller->num_int[y];
    }
    for(x=0;x<a->length + b->length;x++){//max length of m*n is len(m)+len(n)
        while(res_times->num_int[x]>15){//adjust carry
            res_times->num_int[x] -= 16;
            res_times->num_int[x+1] += 1;
        }
    }
    //edit res_times length
    int real_length=0;
    for(x=0;x<a->length + b->length;x++){//max length of m*n is len(m)+len(n)
        if(res_times->num_int[x] > 0)
            real_length = x+1;//last position plus 1
    }
    res_times->length = real_length;
    intToHex(res_times);
    if(a->sign != b->sign)	res_times->sign = 1;
    return res_times;
}
BigNumber* divideByTwo(BigNumber* num){
    BigNumber *res_div2;
    res_div2 = (BigNumber*)malloc(sizeof(BigNumber));	res_div2->sign = 0;
    
    //bignum/int，ref 'algo note'
    int i;
    int r = 0;
    for(i = num->length-1; i>=0; i--){
        r = r*16 + num->num_int[i];
        res_div2->num_int[i] = r/2;
        r %= 2;
    }

    for(i = num->length-1; i>=0; i--){
        if(res_div2->num_int[i]!=0)
            break;
    }
    res_div2->length = i+1;
    intToHex(res_div2);
    return res_div2;
}
BigNumber* divisionQuot(BigNumber* a, BigNumber* b){//new kinds mod implemention
    bool flag = false,	flag2 = false;
    BigNumber *zero; zero = (BigNumber*)malloc(sizeof(BigNumber));    memset(zero->num_int, 0, 200*sizeof(int));	memset(zero->num_str, 0, 200*sizeof(char));	zero->length = 0;	zero->sign = 0;
    if(a->sign == 1){
    	a->sign = 0;
    	flag = true;
    }
    if(b->sign == 1){
    	b->sign = 0;
    	flag2 = true;
    }
    int l_m_s = a->length - b->length;
    if(Larger(a,b)==b) return zero;
    BigNumber *dividend;
    dividend = (BigNumber*)malloc(sizeof(BigNumber));	dividend->sign = 0;
    memcpy(dividend, a, sizeof(BigNumber));//memcpy(dest_pointer, source_pointer, copysize);
    BigNumber *quot;
    quot = (BigNumber*)malloc(sizeof(BigNumber));	quot->sign = 0;
    int k;
    BigNumber *temp;
    

    for(int i=l_m_s; i>=0; i--){
        k=0;
        temp = (BigNumber*)malloc(sizeof(BigNumber));	temp->sign = 0;
        memcpy(temp, b, sizeof(BigNumber));
        for(int j = 0; j < i; j++)
            temp->num_str[temp->length+j] = '0';
        temp->length += i;
        hexToInt(temp);

        while(Larger(dividend, temp) == dividend){
            dividend = Minus(dividend, temp);
            k++;
        }
        free(temp);
        quot->num_int[i] = k;
    }
    for(int i=l_m_s; i>=0; i--){
        if(quot->num_int[i]!=0){
            quot->length = i+1;
            break;
        }
    }
    intToHex(quot);
    free(dividend);
    if(!(flag^flag2))	return quot;
    else{	quot->sign = 1;	return quot;}
    //else{return Minus(b,quot);}
}
BigNumber* divisionMod(BigNumber* a, BigNumber* b){//new kinds mod implemention
    bool flag = false;
    if(a->sign == 1){
    	a->sign = 0;
    	flag = true;
    }

    int l_m_s = a->length - b->length;
    if(Larger(a,b)==b) {
    	if(flag == false)	return a;
    	else return Minus(b,a);
    }
    BigNumber *dividend;
    dividend = (BigNumber*)malloc(sizeof(BigNumber));	dividend->sign = 0;
    memcpy(dividend, a, sizeof(BigNumber));//memcpy(dest_pointer, source_pointer, copysize);
    BigNumber *quot;
    quot = (BigNumber*)malloc(sizeof(BigNumber));	quot->sign = 0;
    int k;
    BigNumber *temp;
    

    for(int i=l_m_s; i>=0; i--){
        k=0;
        temp = (BigNumber*)malloc(sizeof(BigNumber));	temp->sign = 0;
        memcpy(temp, b, sizeof(BigNumber));
        for(int j = 0; j < i; j++)
            temp->num_str[temp->length+j] = '0';
        temp->length += i;
        hexToInt(temp);

        while(Larger(dividend, temp) == dividend){
            dividend = Minus(dividend, temp);
            k++;
        }
        free(temp);
        quot->num_int[i] = k;
    }
    for(int i=l_m_s; i>=0; i--){
        if(quot->num_int[i]!=0){
            quot->length = i+1;
            break;
        }
    }
    intToHex(quot);
    free(dividend);
    if(flag == false){
    	return Minus(a, times(quot, b));
    }
    else{
    	return Minus(b,Minus(a, times(quot, b)));
    }
}
bool isDivideInteger(BigNumber* num, int divisor){// the return value is true if the BigNumber parameter can divided by divisor
    BigNumber* quot;
    quot = (BigNumber*)malloc(sizeof(BigNumber));	quot->sign = 0;

    int i;
    int r = 0;
    for (i=num->length-1; i>=0; i--){
        r = r * 16 + num->num_int[i];
        quot->num_int[i] = r / divisor;
        r %= divisor;
    }
    for(i = num->length-1; i>=0; i--){
        if(quot->num_int[i]!=0)
            break;
    }
    quot->length = i+1;
    intToHex(quot);

    BigNumber* prime_big;
    prime_big = (BigNumber*)malloc(sizeof(BigNumber));	prime_big->sign = 0;
    sprintf(prime_big->num_str ,"%x", divisor);
    prime_big->length = strlen(prime_big->num_str);
    hexToInt(prime_big);

    BigNumber* time_res;
    time_res = times(quot, prime_big);

    bool res = Equal(time_res, num);
    free(quot);free(prime_big);// !!!
    return res;
}
BigNumber* pow(BigNumber* a, BigNumber* e, BigNumber* n){// a ^ e % n
    BigNumber *one; one = (BigNumber*)malloc(sizeof(BigNumber));    memset(one->num_int, 0, 200*sizeof(int));	memset(one->num_str, 0, 200*sizeof(char));    one->num_int[0] = 1;    one->length = 1;    intToHex(one);	one->sign = 0;
    BigNumber *coeff = times(one,one);// initialize coefficient
    while(e->length != 0){
        if(isDivideInteger(e,2)){// e % 2 == 0
            e = divideByTwo(e);
            a = divisionMod(times(a,a), n);// a^2 mod n
        }
        else{
            e = Minus(e, one);
            coeff = divisionMod(times(a,coeff), n);
        }
    }
    free(one);
    return coeff;
}
BigNumber* squareRoot(BigNumber *ciphertext, BigNumber *p){// sample input clp,clq = 1, b = p-1 let (b/p) = -1, s are both 1
	BigNumber *one; one = (BigNumber*)malloc(sizeof(BigNumber));    memset(one->num_int, 0, 200*sizeof(int));	memset(one->num_str, 0, 200*sizeof(char));    one->num_int[0] = 1;    one->length = 1;    intToHex(one);	one->sign = 0;
    BigNumber *clp = pow(ciphertext, divideByTwo(Minus(p, one)), p);
    BigNumber *b = Minus(p, one);// b will let (b/p) = -1
    BigNumber *t = Minus(p, one);
    int s = 0;
    while(isDivideInteger(t, 2)){
    	t = divideByTwo(t);
    	s++;
    }

    BigNumber *af = pow(ciphertext, Minus(divideByTwo(Minus(p, one)), one), p);
    BigNumber *c = pow(b, t, p);
    BigNumber *r = pow(ciphertext, divideByTwo(Plus(t, one)), p);
    BigNumber *d;
    for(int i = 1; i<s; i++){ // from 1 to s-1
    	d = times(one, one);
    	int d_pow = int(pow(2, s-i-1));
    	for(int j = 0; j<d_pow; j++){
    		d = times(d, divisionMod(times(divisionMod(times(r,r), p), af), p));
    		if(Equal(d, Minus(p, one))) r = divisionMod(times(r,c),p);
    		c = divisionMod(times(c,c), p);
    	}
    }
    free(one);
    return r;
}
BigNumber* gcd(BigNumber *a, BigNumber *b){
    BigNumber *one; one = (BigNumber*)malloc(sizeof(BigNumber));    memset(one->num_int, 0, 200*sizeof(int));	memset(one->num_str, 0, 200*sizeof(char));    one->num_int[0] = 1;    one->length = 1;    intToHex(one);	one->sign = 0;
    BigNumber *zero; zero = (BigNumber*)malloc(sizeof(BigNumber));    memset(zero->num_int, 0, 200*sizeof(int));	memset(zero->num_str, 0, 200*sizeof(char));	zero->length = 0;	zero->sign = 0;
    BigNumber *i_;	i_ = (BigNumber*)malloc(sizeof(BigNumber));	memcpy(i_, one, sizeof(BigNumber));
    BigNumber *j_;	j_ = (BigNumber*)malloc(sizeof(BigNumber));	memcpy(j_, zero, sizeof(BigNumber));
    BigNumber *i;	i = (BigNumber*)malloc(sizeof(BigNumber));	memcpy(i, zero, sizeof(BigNumber));
    BigNumber *j;	j = (BigNumber*)malloc(sizeof(BigNumber));	memcpy(j, one, sizeof(BigNumber));
    BigNumber *c; c = (BigNumber*)malloc(sizeof(BigNumber));	memcpy(c, Larger(a,b), sizeof(BigNumber));
    BigNumber *d; d = (BigNumber*)malloc(sizeof(BigNumber));	memcpy(d, Smaller(a,b), sizeof(BigNumber));
	/*printf("gcd i_: ");printBigNumber(i_);
	printf("gcd j_: ");printBigNumber(j_);
	printf("gcd i: ");printBigNumber(i);
	printf("gcd j: ");printBigNumber(j);
	printf("gcd c: ");printBigNumber(c);
	printf("gcd d: ");printBigNumber(d);*/
	BigNumber *q, *r, *t;
    t = (BigNumber*)malloc(sizeof(BigNumber));
    while (1){
        q = divisionQuot(c,d);
        //printf("gcd q: ");printBigNumber(q);
        r = divisionMod(c,d);
        //printf("gcd r: ");printBigNumber(r);
        memcpy(c, d, sizeof(BigNumber));
        //printf("gcd c: ");printBigNumber(c);
        memcpy(d, r, sizeof(BigNumber));
        //printf("gcd d: ");printBigNumber(d);
        memcpy(t, i_, sizeof(BigNumber));
        //printf("gcd t: ");printBigNumber(t);	
        memcpy(i_, i, sizeof(BigNumber));
        //printf("gcd i_: ");printBigNumber(i_);	
        i = Minus(t, times(q,i));
        //printf("gcd i: ");printBigNumber(i);

        memcpy(t, j_, sizeof(BigNumber));
        //printf("gcd t: ");printBigNumber(t);	
        memcpy(j_, j, sizeof(BigNumber));
        //printf("gcd j_: ");printBigNumber(j_);	
        j = Minus(t, times(q,j));
        //printf("gcd j: ");printBigNumber(j);
        //printf("gcd r: ");printBigNumber(r);
        //printf("gcd one: ");printBigNumber(one);
        if (Equal(r, one))	break;
    }
    if(Larger(a,b) == b){
    	BigNumber *temp;
    	temp = i; i = j; j = temp;
    	//printf("gcd i: ");printBigNumber(i);
    	//printf("gcd j: ");printBigNumber(j);
    }
    free(one);free(zero);free(i_);free(j_);free(c);free(d);free(t);
    return i;
}
void findMxMy(BigNumber* M, BigNumber** return_Mx, BigNumber** return_My, BigNumber *a, BigNumber *b, BigNumber *p){
	BigNumber *one; one = (BigNumber*)malloc(sizeof(BigNumber));    memset(one->num_int, 0, 200*sizeof(int));	memset(one->num_str, 0, 200*sizeof(char));    one->num_int[0] = 1;    one->length = 1;    intToHex(one);	one->sign = 0;
	BigNumber *Mx = (BigNumber*)malloc(sizeof(BigNumber));	memcpy(Mx, M, sizeof(BigNumber));
	BigNumber *My = (BigNumber*)malloc(sizeof(BigNumber));	memset(My->num_int, 0, 200*sizeof(int));	My->sign = 0;
	Mx->num_str[Mx->length] = '0';	Mx->num_str[Mx->length+1] = '0';	Mx->length += 2;	hexToInt(Mx);
	int c = 255;
	BigNumber *right;
	while(c--){
		right = divisionMod(Plus(Plus(times(Mx,times(Mx,Mx)),times(a,Mx)),b),p);
		My = squareRoot( right , p );
		if(Equal(right,divisionMod(times(My,My),p))&&!isDivideInteger(My,2))
			break;
		else
			Mx = Plus(Mx, one);
	}
	*return_Mx = Mx;	*return_My = My;
    free(one);free(right);
	return;
}
BigNumber* findY(BigNumber* Mx, BigNumber *a, BigNumber *b, BigNumber *p){
	BigNumber *right = divisionMod(Plus(Plus(times(Mx,times(Mx,Mx)),times(a,Mx)),b),p);
	return squareRoot( right , p );
}
void EC_Multiplication(BigNumber* a, BigNumber* x1, BigNumber* y1, BigNumber** return_x, BigNumber** return_y, BigNumber* p){
	BigNumber* x_2 = divisionMod(times(x1, x1),p);
	BigNumber* divisor = divisionMod(Plus(y1, y1),p);printf("EC_M divisor: ");printBigNumber(divisor);
	BigNumber* divisor_inv = divisionMod(gcd(divisor, p),p);printf("EC_M divisor_inv: ");printBigNumber(divisor_inv);
	//printf("EC_M divisor_inv: ");printBigNumber(divisor_inv);
	BigNumber* lambda = divisionMod(times(Plus(Plus(x_2, Plus(x_2, x_2)),a), divisor_inv),p);printf("EC_M lambda: ");printBigNumber(lambda);
    //printBigNumber(lambda);
	*return_x = divisionMod(Minus(times(lambda, lambda), Plus(x1, x1)),p);printf("EC_M x3: ");printBigNumber(*return_x);
	*return_y = divisionMod(Minus(times(lambda, Minus(x1, *return_x)), y1),p);printf("EC_M y3: ");printBigNumber(*return_y);putchar('\n');
    free(x_2);free(divisor);free(divisor_inv);free(lambda);
	return;
}
void EC_Addition(BigNumber* a, BigNumber* x1, BigNumber* y1, BigNumber* x2, BigNumber* y2, BigNumber** return_x, BigNumber** return_y, BigNumber* p){
	if(x1->length == 0 && y1->length == 0){
		*return_x = x2;	*return_y = y2;
		return;
	}
	if(x2->length == 0 && y2->length == 0){
		*return_x = x1;	*return_y = y1;
		return;
	}
	if(Equal(x1,x2)&&Equal(y1,y2)){
		BigNumber *two; two = (BigNumber*)malloc(sizeof(BigNumber));    memset(two->num_int, 0, 200*sizeof(int));    two->num_int[0] = 2;    two->length = 1;    intToHex(two);	two->sign = 0;
    	EC_Multiplication(a, x1, y1, return_x, return_y, p);
    	return;
	}
	BigNumber *divisor, *divisor_inv;
	divisor = divisionMod(Minus(x2, x1),p);
    printf("EC_A divisor: ");printBigNumber(divisor);
	divisor_inv = divisionMod(gcd(divisor, p),p);
	printf("EC_A divisor_inv: ");printBigNumber(divisor_inv);
	//BigNumber* lambda = divisionMod(times(Minus(y2, y1), divisor_inv),p);
    BigNumber* lambda = times(Minus(y2, y1), divisor_inv);
    printf("EC_A lambda(no mod): ");printBigNumber(lambda);
	BigNumber* x3 = divisionMod(Minus(times(lambda, lambda),Plus(x1,x2)),p);
    printf("EC_A x3: ");printBigNumber(x3);
	BigNumber* y3 = divisionMod(Minus(times(lambda,Minus(x1,x3)),y1),p);
    printf("EC_A y3: ");printBigNumber(y3);putchar('\n');
	*return_x = x3;	*return_y = y3;
    free(divisor);free(divisor_inv);free(lambda);
	return;
}
void scalarMultiplication(BigNumber* a, BigNumber* a_x, BigNumber* a_y, BigNumber* c, BigNumber* p, BigNumber **return_x, BigNumber **return_y){
	BigNumber *one; one = (BigNumber*)malloc(sizeof(BigNumber));    memset(one->num_int, 0, 200*sizeof(int));	memset(one->num_str, 0, 200*sizeof(char));    one->num_int[0] = 1;    one->length = 1;    intToHex(one);	one->sign = 0;
    BigNumber *zero; zero = (BigNumber*)malloc(sizeof(BigNumber));    memset(zero->num_int, 0, 200*sizeof(int));	memset(zero->num_str, 0, 200*sizeof(char));	zero->length = 0;	zero->sign = 0;
    BigNumber *coeff_x;	coeff_x = (BigNumber*)malloc(sizeof(BigNumber));	memcpy(coeff_x, zero, sizeof(BigNumber));
    BigNumber *coeff_y;	coeff_y = (BigNumber*)malloc(sizeof(BigNumber));	memcpy(coeff_y, zero, sizeof(BigNumber));
    
    BigNumber *lambda, *x1, *y1, *x3, *y3, *x_2, *divisor, *divisor_inv;
    //BigNumber *two; two = (BigNumber*)malloc(sizeof(BigNumber));    memset(two->num_int, 0, 200*sizeof(int));    two->num_int[0] = 4;    two->length = 1;    intToHex(two);	two->sign = 0;
    //c = two;
    x1 = a_x;	y1 = a_y;
    while(c->length != 0){
        if(isDivideInteger(c,2)){// e % 2 == 0
            c = divideByTwo(c);
            printf("EC_M c:");printBigNumber(c);
            EC_Multiplication(a, x1, y1, &x1, &y1, p);
        }
        else{
            c = Minus(c, one);
            printf("EC_A c:");printBigNumber(c);
            EC_Addition(a, x1, y1, coeff_x, coeff_y, &coeff_x, &coeff_y, p);
        }
    }
    free(one);
    *return_x = coeff_x;	*return_y = coeff_y;
    return;
}
int main(){
	BigNumber *p;	p = (BigNumber*)malloc(sizeof(BigNumber));	memset(p->num_int, 0, 200*sizeof(int));	sprintf(p->num_str, "FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF7FFFFFFF");	p->length = 40;		hexToInt(p);	p->sign = 0;
	BigNumber *a;	a = (BigNumber*)malloc(sizeof(BigNumber));	memset(a->num_int, 0, 200*sizeof(int));	sprintf(a->num_str, "FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF7FFFFFFC");	a->length = 40;		hexToInt(a);	a->sign = 0;
	BigNumber *b;	b = (BigNumber*)malloc(sizeof(BigNumber));	memset(b->num_int, 0, 200*sizeof(int));	sprintf(b->num_str, "1C97BEFC54BD7A8B65ACF89F81D4D4ADC565FA45");	b->length = 40;		hexToInt(b);	b->sign = 0;
	BigNumber *Gx;	Gx = (BigNumber*)malloc(sizeof(BigNumber));	memset(Gx->num_int, 0, 200*sizeof(int));	sprintf(Gx->num_str, "4A96B5688EF573284664698968C38BB913CBFC82");	Gx->length = 40;		hexToInt(Gx);	Gx->sign = 0;
	BigNumber *Gy;	Gy = (BigNumber*)malloc(sizeof(BigNumber));	memset(Gy->num_int, 0, 200*sizeof(int));	sprintf(Gy->num_str, "23A628553168947D59DCC912042351377AC5FB32");	Gy->length = 40;		hexToInt(Gy);	Gy->sign = 0;
	BigNumber *n;	n = (BigNumber*)malloc(sizeof(BigNumber));	memset(n->num_int, 0, 200*sizeof(int));	sprintf(n->num_str, "0100000000000000000001F4C8F927AED3CA752257");	n->length = 42;		hexToInt(n);	n->sign = 0;
	BigNumber *tempx, *tempy;
	BigNumber *M, *Pa, *Pay, *nk, *Mx, *My, *Pk, *Pky, *Pb, *Pby, *na;
    

	printf("<EC-ElGamal encryption>\n");
	//allocate input size and eat input
	M = (BigNumber*)malloc(sizeof(BigNumber));	memset(M->num_int, 0, 200*sizeof(int));	M->sign = 0;
	printf("Plaintext M = ");	scanf("%s", M->num_str);	M->length = strlen(M->num_str);	hexToInt(M);
	Pa = (BigNumber*)malloc(sizeof(BigNumber));	memset(Pa->num_int, 0, 200*sizeof(int));	Pa->sign = 0;
	printf("Pa = ");	scanf("%d", &Pa->_0203);	scanf("%s", Pa->num_str);	Pa->length = strlen(Pa->num_str);	hexToInt(Pa);
	nk = (BigNumber*)malloc(sizeof(BigNumber));	memset(nk->num_int, 0, 200*sizeof(int));	nk->sign = 0;
	printf("nk = ");	scanf("%s", nk->num_str);	nk->length = strlen(nk->num_str);	hexToInt(nk);
	
	//use Data Embedding Method to find correct Mx and My
	findMxMy(M,&Mx,&My,a,b,p);
	printf("Mx = ");	printBigNumber(Mx);
	printf("My = ");	printBigNumber(My);
	
	//scalarMultiplication(a, Gx, Gy, nk, p, &Pk, &Pky);
	//printf("Cm = {Pk,Pb} = {");	printBigNumber(Pk);
	Pay = findY(Pa, a, b, p);
	if( (Pa->_0203)%2 ){//03
		if(isDivideInteger(Pay,2))
			Pay = Minus(p,Pay);
	}
	else{//02
		if(isDivideInteger(Pay,2))
			Pay = Minus(p,Pay);
	}
	printf("Pa_x: ");printBigNumber(Pa);
    printf("Pa_y: ");printBigNumber(Pay);
	scalarMultiplication(a, Pa, Pay, nk, p, &tempx, &tempy);
    printf("nkPa_x: ");printBigNumber(tempx);
    printf("nkPa_y: ");printBigNumber(tempy);
	EC_Addition(a, Mx, My, tempx, tempy, &Pb, &Pby, p);
	printf(", ");	printBigNumber(Pb);  printf("}\n\n");

	free(M);	free(Pa);	free(nk);	free(Mx);	free(My);	free(Pk);	free(Pky);	free(Pb);	free(Pby);	free(tempx);	free(tempy);
/*

	printf("<EC-ElGamal decryption>\n");
	//allocate input size and eat input
	Pk = (BigNumber*)malloc(sizeof(BigNumber));	memset(Pk->num_int, 0, 200*sizeof(int));	Pk->sign = 0;
	printf("Pk = ");	scanf("%d", &Pk->_0203);	scanf("%s", Pk->num_str);	Pk->length = strlen(Pk->num_str);	hexToInt(Pk);
	Pb = (BigNumber*)malloc(sizeof(BigNumber));	memset(Pb->num_int, 0, 200*sizeof(int));	Pb->sign = 0;
	printf("Pb = ");	scanf("%d", &Pb->_0203);	scanf("%s", Pb->num_str);	Pb->length = strlen(Pb->num_str);	hexToInt(Pb);
	na = (BigNumber*)malloc(sizeof(BigNumber));	memset(na->num_int, 0, 200*sizeof(int));	na->sign = 0;
	printf("na = ");	scanf("%s", na->num_str);	na->length = strlen(na->num_str);	hexToInt(na);

	Pky = findY(Pk, a, b, p);
	if( (Pk->_0203)%2 ){//03	
        if(isDivideInteger(Pky,2))	
            Pky = Minus(p,Pky);
    }
	else{
		if(!isDivideInteger(Pky,2))	
            Pky = Minus(p,Pky);
    }
    Pby = findY(Pb, a, b, p);
	if( (Pb->_0203)%2 ){//03
		if(isDivideInteger(Pby,2))	
            Pby = Minus(p,Pby);
    }
	else{
		if(!isDivideInteger(Pby,2))	
            Pby = Minus(p,Pby);
    }
    printf("Plaintext = ");
	scalarMultiplication(a, Pk, Pky, na, p, &tempx, &tempy);
    //printBigNumber(tempx);
    //printBigNumber(tempy);
	tempy = Minus(p,tempy);
	EC_Addition(a, Pb, Pby, tempx, tempy, &Mx, &My, p);
	Mx->length -=2;	printBigNumber(Mx);
*/
	return 0;
}
