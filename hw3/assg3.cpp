#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <iostream>
using namespace std;
typedef struct{
    int sign;
    char num_str[200];
    int num_int[200];    // one thousand positions
    int length;         // length
}BigNumber;
bool prime[10001];// 1~10000 prime table
BigNumber* Plus(BigNumber* a, BigNumber* b);//initialize
BigNumber* Minus(BigNumber* a, BigNumber* b);//initialize
void makePrimeTable(){
    int x,y;
    for(x=2;x<=10000;x++)
        prime[x]=true;
    prime[1]=false;
    for(x=2;x<=100;x++){
        if(prime[x]==true){
            for(y=2;x*y<=10000;y++)
                prime[x*y]=false;
        }
    }
    return;
}
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
            case 'a':
                num->num_int[x] = 10;break;
            case 'b':
                num->num_int[x] = 11;break;
            case 'c':
                num->num_int[x] = 12;break;
            case 'd':
                num->num_int[x] = 13;break;
            case 'e':
                num->num_int[x] = 14;break;
            case 'f':
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
                num->num_str[x] = 'a';break;
            case 11:
                num->num_str[x] = 'b';break;
            case 12:
                num->num_str[x] = 'c';break;
            case 13:
                num->num_str[x] = 'd';break;
            case 14:
                num->num_str[x] = 'e';break;
            case 15:
                num->num_str[x] = 'f';break;
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
    int len = (a->length>b->length)?a->length:b->length;
    bool flag=true;
    for(int i=0; i<len; i++){
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
    		return Minus(temp,b);
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
    int l_m_s = a->length - b->length;
    if(Larger(a,b)==b) return a;
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
    free(dividend);free(temp);
    return quot;
}
BigNumber* divisionMod(BigNumber* a, BigNumber* b){//new kinds mod implemention
    int l_m_s = a->length - b->length;
    if(Larger(a,b)==b) return a;
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
    free(dividend);free(temp);
    return Minus(a, times(quot, b));
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
    BigNumber *one; one = (BigNumber*)malloc(sizeof(BigNumber));    memset(one->num_int, 0, 200*sizeof(int));    one->num_int[0] = 1;    one->length = 1;    intToHex(one);	one->sign = 0;
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
BigNumber* getPassTableTestNum(){
    int flag = true;// There's no change at flag if pass this test!
    srand(time(NULL));
    
    BigNumber* n;
    while(1){
        // malloc a new space and random a 256-bit number
        n = (BigNumber*)malloc(sizeof(BigNumber));  memset(n->num_int, 0, 200*sizeof(int));	n->sign = 0;
        n->num_int[0] = 1 + 2*(rand()%(7-0+1)+0); //2*(0~7)+1 for odd number        
        for(int i=1; i<63; i++)
            n->num_int[i] = rand()%(15-0+1)+0;
        n->num_int[63] = rand()%(15-1+1)+1; //let the number can surely print 64 characters
        n->length = 64;// fixed for clear 256-bit output(because the upper line)
        intToHex(n);
        
        for(int i = 2; i<=10000; i++){
            if(prime[i]){
                if(isDivideInteger(n, i)){// true occur -> n is a composite
                    flag = false;
                    break;
                }
            }
        }

        if(!flag){  // it is a composite, we need to regenerate another 'a'
            free(n);
            flag = true;
            continue;
        }
        else
            break;
    }
    return n;
}
bool MillerRabinPrimalityTest(BigNumber* n){

    int a_temp = rand() % (RAND_MAX-2+1) + 2;
    BigNumber *a;   a = (BigNumber*)malloc(sizeof(BigNumber));  memset(a->num_int, 0, 200*sizeof(int));	a->sign = 0;
    sprintf(a->num_str, "%x", a_temp);
    a->length = strlen(a->num_str);
    hexToInt(a);

    BigNumber *one; one = (BigNumber*)malloc(sizeof(BigNumber));    memset(one->num_int, 0, 200*sizeof(int));   one->num_int[0] = 1;    one->length = 1;    intToHex(one);	one->sign = 0;
    BigNumber *u = Minus(n, one);
    int t = 0;

    while (isDivideInteger(u, 2)){ // while(u % 2 == 0){}
        u = divideByTwo(u);// u >>= 1;
        t++;
    }
    
    BigNumber *n_m_1 = Minus(n,one);// for future use of "equal 'n Minus 1'"
    BigNumber *x = pow(a, u, n);// x = a ^ u % n;
    
    if (Equal(x, one) || Equal(x, n_m_1)) return true;
    for (int i=0; i<t-1; i++){
        x = divisionMod(times(x, x), n);   // x = x * x % n;
        if (Equal(x, one)) return false;
        if (Equal(x, n_m_1)) return true;
    }
    free(a);free(one);
    return false;
}
BigNumber* squareRoot(BigNumber *ciphertext, BigNumber *p){// sample input clp,clq = 1, b = p-1 let (b/p) = -1, s are both 1
	BigNumber *one; one = (BigNumber*)malloc(sizeof(BigNumber));    memset(one->num_int, 0, 200*sizeof(int));    one->num_int[0] = 1;    one->length = 1;    intToHex(one);	one->sign = 0;
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
void gcd(BigNumber *a, BigNumber *b, BigNumber **i, BigNumber **j){
    BigNumber *one; one = (BigNumber*)malloc(sizeof(BigNumber));    memset(one->num_int, 0, 200*sizeof(int));    one->num_int[0] = 1;    one->length = 1;    intToHex(one);	one->sign = 0;
    BigNumber *zero; zero = (BigNumber*)malloc(sizeof(BigNumber));    memset(zero->num_int, 0, 200*sizeof(int));	memset(zero->num_str, 0, 200*sizeof(char));	zero->length = 0;	zero->sign = 0;
    BigNumber *i_;	i_ = (BigNumber*)malloc(sizeof(BigNumber));	memcpy(i_, one, sizeof(BigNumber));
    BigNumber *j_;	j_ = (BigNumber*)malloc(sizeof(BigNumber));	memcpy(j_, zero, sizeof(BigNumber));
    memcpy(*i, zero, sizeof(BigNumber));
    memcpy(*j, one, sizeof(BigNumber));
    BigNumber *c; c = (BigNumber*)malloc(sizeof(BigNumber));	memcpy(c, Larger(a,b), sizeof(BigNumber));
    BigNumber *d; d = (BigNumber*)malloc(sizeof(BigNumber));	memcpy(d, Smaller(a,b), sizeof(BigNumber));
	
	BigNumber *q, *r, *t;
    t = (BigNumber*)malloc(sizeof(BigNumber));
    while (1){
        q = divisionQuot(c,d);
        r = divisionMod(c,d);
        //printBigNumber(c);
        //printBigNumber(d);
        //if (Equal(r, one)) break;
        memcpy(c, d, sizeof(BigNumber));
        memcpy(d, r, sizeof(BigNumber));
        memcpy(t, i_, sizeof(BigNumber));	memcpy(i_, *i, sizeof(BigNumber));	*i = Minus(t, times(q,*i));
        memcpy(t, j_, sizeof(BigNumber));	memcpy(j_, *j, sizeof(BigNumber));	*j = Minus(t, times(q,*j));
        if (Equal(r, one)) break;
    }
    if(Larger(a,b) == b){
    	BigNumber **temp;
    	*temp = *i; *i = *j; *j = *temp;
    }
    free(one);free(zero);free(i_);free(j_);free(c);free(d);free(t);
    return;
}
int main(){
//MILLER RABIN PRIMALITY TEST
    printf("<Miller-Rabin>\n");

    makePrimeTable();
    BigNumber *n;
    
    while(1){
        n = getPassTableTestNum();
        if(MillerRabinPrimalityTest(n)) break;
        else free(n);
    }
    printBigNumber(n);
    putchar('\n');
    

//RABIN ENCRYPTION
    printf("<Rabin Encryption>\n");

    BigNumber *p, *q, *N;
    p = (BigNumber*)malloc(sizeof(BigNumber));  memset(p->num_int, 0, 200*sizeof(int));	p->sign = 0;
    q = (BigNumber*)malloc(sizeof(BigNumber));  memset(q->num_int, 0, 200*sizeof(int)); q->sign = 0;
    printf("p = ");
    scanf("%s", p->num_str);
    printf("q = ");
    scanf("%s", q->num_str);
    p->length = strlen(p->num_str); q->length = strlen(q->num_str);
    hexToInt(p);    hexToInt(q);
    N = times(p, q);
    printf("n = pq = ");printBigNumber(N);
    putchar('\n');

    BigNumber *plaintext, *ciphertext;
    plaintext = (BigNumber*)malloc(sizeof(BigNumber));  memset(plaintext->num_int, 0, 200*sizeof(int));	plaintext->sign = 0;
    printf("Plaintext: ");
    scanf("%s", plaintext->num_str);
    plaintext->length = strlen(plaintext->num_str);
    for(int i=0; i<4; i++)
        plaintext->num_str[plaintext->length + i] = plaintext->num_str[plaintext->length-4 + i]; // padding 16 bit
    plaintext->length += 4;
    hexToInt(plaintext);
    
    ciphertext = divisionMod(times(plaintext, plaintext), N);
    printf("Ciphertext = ");printBigNumber(ciphertext);

    free(ciphertext);free(plaintext);free(p);free(q);free(N);

//RABIN DECRYPTION
    printf("<Rabin Decryption>\n");

    //BigNumber *one; one = (BigNumber*)malloc(sizeof(BigNumber));    memset(one->num_int, 0, 200*sizeof(int));    one->num_int[0] = 1;    one->length = 1;    intToHex(one);
    ciphertext = (BigNumber*)malloc(sizeof(BigNumber));  memset(ciphertext->num_int, 0, 200*sizeof(int));	ciphertext->sign = 0;
    printf("Ciphertext = ");
    scanf("%s", ciphertext->num_str);
    ciphertext->length = strlen(ciphertext->num_str);
    hexToInt(ciphertext);

    p = (BigNumber*)malloc(sizeof(BigNumber));  memset(p->num_int, 0, 200*sizeof(int));	p->sign = 0;
    q = (BigNumber*)malloc(sizeof(BigNumber));  memset(q->num_int, 0, 200*sizeof(int));	q->sign = 0;
    printf("Private Key:\n");
    printf("p = ");
    scanf("%s", p->num_str);
    printf("q = ");
    scanf("%s", q->num_str);
    p->length = strlen(p->num_str); q->length = strlen(q->num_str);
    hexToInt(p);    hexToInt(q);
    N = times(p,q);
    
    //square root of cmodp and cmodq
    BigNumber *r = squareRoot(ciphertext, p);	r->sign = 0;
    BigNumber *s = squareRoot(ciphertext, q);	s->sign = 0;
    putchar('\n');
    //printf("r: ");printBigNumber(r);
    //printf("s: ");printBigNumber(s);

	BigNumber *c, *d;
	c = (BigNumber*)malloc(sizeof(BigNumber));	d = (BigNumber*)malloc(sizeof(BigNumber));
	
	gcd(p,q,&c,&d);// get cp+dq = 1
	//printf("cp: ");printBigNumber(times(c,p));
	//printf("dq: ");printBigNumber(times(d,q));
	//x = rdq+scp, -x = -rdq-scp, y = rdq-scp, -y = -rdq+scp
	BigNumber *x, *x_, *y, *y_, *rdq, *scp;
    rdq = times(r, times(d,q));
    scp = times(s, times(c,p));
    //printf("rdq: ");printBigNumber(rdq);
    //printf("scp: ");printBigNumber(scp);
    if(c->sign == 1){
    	x = Plus(rdq, scp);
    	y = Minus(rdq, scp);
    	x_ = (BigNumber*)malloc(sizeof(BigNumber));	memcpy(x_, x, sizeof(BigNumber));	x_->sign = (x_->sign+1)%2;	x_ = Plus(x_, N);
    	y_ = (BigNumber*)malloc(sizeof(BigNumber));	memcpy(y_, y, sizeof(BigNumber));	y_->sign = (y_->sign+1)%2;	y_ = Plus(y_, N);
    	x = divisionMod(x, N);
    	y = divisionMod(y, N);
    	x_ = divisionMod(x_, N);
    	y_ = divisionMod(y_, N);
    }
    // !!!!
    else if(d->sign == 1){
    	x_ = Plus(rdq, scp);
    	y_ = Minus(scp, rdq);
    	x = (BigNumber*)malloc(sizeof(BigNumber));	memcpy(x, x_, sizeof(BigNumber));	x->sign = (x->sign+1)%2;	x = Plus(x, N);
    	y = (BigNumber*)malloc(sizeof(BigNumber));	memcpy(y, y_, sizeof(BigNumber));	y->sign = (y->sign+1)%2;	y = Plus(y, N);
    	x = divisionMod(x, N);
    	y = divisionMod(y, N);
    	x_ = divisionMod(x_, N);
    	y_ = divisionMod(y_, N);
    }
    //printf("x: ");printBigNumber(x);
    //printf("y: ");printBigNumber(y);
    //printf("x_: ");printBigNumber(x_);
    //printf("y_: ");printBigNumber(y_);

    bool flag1 = false, flag2 = false, flag3 = false, flag4 = false;
    if(x->num_str[x->length-8] == x->num_str[x->length-4] && x->num_str[x->length-7] == x->num_str[x->length-3] && x->num_str[x->length-6] == x->num_str[x->length-2] && x->num_str[x->length-5] == x->num_str[x->length-1])
    	flag1 = true;
    else if(y->num_str[y->length-8] == y->num_str[y->length-4] && y->num_str[y->length-7] == y->num_str[y->length-3] && y->num_str[y->length-6] == y->num_str[y->length-2] && y->num_str[y->length-5] == y->num_str[y->length-1])
    	flag2 = true;
    else if(x_->num_str[x_->length-8] == x_->num_str[x_->length-4] && x_->num_str[x_->length-7] == x_->num_str[x_->length-3] && x_->num_str[x_->length-6] == x_->num_str[x_->length-2] && x_->num_str[x_->length-5] == x_->num_str[x_->length-1])
    	flag3 = true;
    else if(y->num_str[y->length-8] == y_->num_str[y_->length-4] && y_->num_str[y_->length-7] == y_->num_str[y_->length-3] && y_->num_str[y_->length-6] == y_->num_str[y_->length-2] && y_->num_str[y_->length-5] == y_->num_str[y_->length-1])
    	flag4 = true;

    printf("Plaintext = ");

    if(flag1 == true){
    	x->length -= 4;
    	if(x->length != 56){
    		for(int i = 56-1; i>=x->length; i--)
    			putchar('0');
    	}
    	printBigNumber(x);
    }
    else if(flag2 == true){
    	y->length -= 4;
    	if(y->length != 56){
    		for(int i = 56-1; i>=y->length; i--)
    			putchar('0');
    	}
    	printBigNumber(y);
    }
    else if(flag3 == true){
    	x_->length -= 4;
    	if(x_->length != 56){
    		for(int i = 56-1; i>=x_->length; i--)
    			putchar('0');
    	}
    	printBigNumber(x_);
    }
    else if(flag4 == true){
    	y_->length -= 4;
    	if(y_->length != 56){
    		for(int i = 56-1; i>=y_->length; i--)
    			putchar('0');
    	}
    	printBigNumber(y_);
    }

    return 0;
}
