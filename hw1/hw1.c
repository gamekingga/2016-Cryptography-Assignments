#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct
{
    char num_str[1000];
    int num_int[1000];    // 一個欄位存一個數字，可以存 1000 位數
    int length;         // 位數
}BigNumber;
BigNumber* Larger(BigNumber* a, BigNumber* b){//先比length再比strcmp
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
int Equal(BigNumber* a, BigNumber* b){
	if(strcmp(a->num_str,b->num_str) == 0)
		return 1;
	else
		return 0;
}
BigNumber* Smaller(BigNumber* a, BigNumber* b){//先比length再比strcmp
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
BigNumber* plus(BigNumber* a, BigNumber* b){
	//為要return的資料開空間、初始化
	BigNumber *res_plus;
	res_plus = (BigNumber*)malloc(sizeof(BigNumber));	memset(res_plus->num_int, 0, 1000*sizeof(int));
	res_plus->length = (Larger(a, b))->length;
	
	//相加，調整進位
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
BigNumber* minus(BigNumber* a, BigNumber* b){//會自動執行大減小,負號要不要print由main去用smaller判斷
	//為要return的資料開空間、初始化
	BigNumber *res_minus;
	res_minus = (BigNumber*)malloc(sizeof(BigNumber));	memset(res_minus->num_int, 0, 1000*sizeof(int));

	//必須是larger - smaller
	BigNumber *larger = Larger(a,b);
	int larger_length = larger->length;

	BigNumber *smaller = Smaller(a,b);
	int smaller_length = smaller->length;// <= no use

	//相減，調整退位
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
	res_minus->length = x+1;//若減出來是0，x變-1，加1變成0，可以被printfBigNumber處理
	intToHex(res_minus);
	return res_minus;
}
BigNumber* times(BigNumber* a, BigNumber* b){
	//為要return的資料開空間、初始化
	BigNumber *res_times;
	res_times = (BigNumber*)malloc(sizeof(BigNumber));	memset(res_times->num_int, 0, 1000*sizeof(int));
	
	BigNumber *larger = Larger(a,b);//大的當x部分
	int larger_length = larger->length;

	BigNumber *smaller = Smaller(a,b);//小的當y部分
	int smaller_length = smaller->length;

	//相乘，調整進位
	int x, y;
	for(x=0;x<larger_length;x++){
		for(y=0;y<smaller_length;y++)
			res_times->num_int[x+y] += larger->num_int[x] * smaller->num_int[y];
	}
	for(x=0;x<a->length + b->length;x++){//最大長度m+n
		while(res_times->num_int[x]>15){//因為要重複跑這個if判斷，所以用while展現
			res_times->num_int[x] -= 16;
			res_times->num_int[x+1] += 1;
		}
	}
	//edit res_times length
	int real_length=0;
	for(x=0;x<a->length + b->length;x++){//最大長度m+n
		if(res_times->num_int[x] > 0)
			real_length = x+1;//last position plus 1
	}
	res_times->length = real_length;
	intToHex(res_times);
	return res_times;
}
BigNumber* divideByTwo(BigNumber* num){//除法要使用的「固定除以二」功能
	BigNumber *res_div2;
	res_div2 = (BigNumber*)malloc(sizeof(BigNumber));
	
	//大數除以int，ref 演算法筆記
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
BigNumber* divisionQuot(BigNumber* a, BigNumber* b){
	BigNumber *dividend, *divisor;
	dividend = (BigNumber*)malloc(sizeof(BigNumber));
	divisor = (BigNumber*)malloc(sizeof(BigNumber));
	memcpy(dividend, a, sizeof(BigNumber));//memcpy(dest_pointer, source_pointer, copysize);
	memcpy(divisor, b, sizeof(BigNumber));

	BigNumber *res_divide, *res_mod;
	res_divide = (BigNumber*)malloc(sizeof(BigNumber));	memset(res_divide->num_int, 0, 1000*sizeof(int));	
	res_mod = (BigNumber*)malloc(sizeof(BigNumber));	memset(res_mod->num_int, 0, 1000*sizeof(int));
	
	//for fast doubling and equal
	BigNumber *one, *two;
	one = (BigNumber*)malloc(sizeof(BigNumber));	one->num_int[0] = 1;	one->length = 1;	intToHex(one);
	two = (BigNumber*)malloc(sizeof(BigNumber));	two->num_int[0] = 2;	two->length = 1;	intToHex(two);

	if(Larger(dividend, divisor) == divisor){
		if(Equal(dividend, divisor)){
			res_divide = one;
			res_mod->length = 0;
		}
		else{
			res_divide->length = 0;
			res_mod = dividend;
		}
		return res_divide;
	}

	//fast doubling
	res_divide = one;//we can consider that res_divide is a multiplier, start from 1
	while(Larger(dividend, times(divisor, times(res_divide,two))) == dividend){//乘以2會超過或會剛好一樣時跳出
		res_divide = times(res_divide, two);
	}
	BigNumber *scanner;//再來是用一個位數一個位數往上加。
	scanner = (BigNumber*)malloc(sizeof(BigNumber));
	memcpy(scanner, res_divide, sizeof(BigNumber));
	while(scanner->length != 0){
		if(Larger(dividend, times(divisor, plus(res_divide, scanner))) == dividend)
			res_divide = plus(res_divide, scanner);
		scanner = divideByTwo(scanner);
	}
	
	//edit res_divide and res_mod
	if(!Equal(dividend, times(divisor, plus(res_divide,one))))
		res_mod = minus(dividend, times(divisor, res_divide));
	else{
		res_divide = plus(res_divide, one);
		res_mod->length = 0;
	}

	return res_divide;
}
BigNumber* divisionMod(BigNumber* a, BigNumber* b){//和divisionQuot內容一樣，只是回傳值不同而已
	BigNumber *dividend, *divisor;
	dividend = (BigNumber*)malloc(sizeof(BigNumber));
	divisor = (BigNumber*)malloc(sizeof(BigNumber));
	memcpy(dividend, a, sizeof(BigNumber));//memcpy(dest_pointer, source_pointer, copysize);
	memcpy(divisor, b, sizeof(BigNumber));

	BigNumber *res_divide, *res_mod;
	res_divide = (BigNumber*)malloc(sizeof(BigNumber));	memset(res_divide->num_int, 0, 1000*sizeof(int));	
	res_mod = (BigNumber*)malloc(sizeof(BigNumber));	memset(res_mod->num_int, 0, 1000*sizeof(int));
	
	//for fast doubling and equal
	BigNumber *one, *two;
	one = (BigNumber*)malloc(sizeof(BigNumber));	one->num_int[0] = 1;	one->length = 1;	intToHex(one);
	two = (BigNumber*)malloc(sizeof(BigNumber));	two->num_int[0] = 2;	two->length = 1;	intToHex(two);

	if(Larger(dividend, divisor) == divisor){
		if(Equal(dividend, divisor)){
			res_divide = one;
			res_mod->length = 0;
		}
		else{
			res_divide->length = 0;
			res_mod = dividend;
		}
		return res_mod;
	}
	
	//fast doubling
	res_divide = one;//we can consider that res_divide is a multiplier, start from 1
	while(Larger(dividend, times(divisor, times(res_divide,two))) == dividend){//乘以2會超過或會剛好一樣時跳出
		res_divide = times(res_divide, two);
	}
	BigNumber *scanner;
	scanner = (BigNumber*)malloc(sizeof(BigNumber));
	memcpy(scanner, res_divide, sizeof(BigNumber));
	while(scanner->length != 0){
		if(Larger(dividend, times(divisor, plus(res_divide, scanner))) == dividend)
			res_divide = plus(res_divide, scanner);
		scanner = divideByTwo(scanner);
	}

	if(!Equal(dividend, times(divisor, plus(res_divide,one))))
		res_mod = minus(dividend, times(divisor, res_divide));
	else{
		res_divide = plus(res_divide, one);
		res_mod->length = 0;
	}

	return res_mod;
}
int main(int argc, char const *argv[])
{
	BigNumber *a, *b, *res_plus, *res_minus, *res_times, *res_divide, *res_mod;
	a = (BigNumber*)malloc(sizeof(BigNumber));	memset(a->num_int, 0, 1000*sizeof(int));
	b = (BigNumber*)malloc(sizeof(BigNumber));	memset(b->num_int, 0, 1000*sizeof(int));
	
	printf("a = ");
	scanf("%s", a->num_str);
	printf("b = ");
	scanf("%s", b->num_str);
	
	a->length = strlen(a->num_str);	b->length = strlen(b->num_str);
	hexToInt(a);	hexToInt(b);

	res_plus = plus(a,b);
	free(res_plus);
	printf("a+b = ");	printBigNumber(res_plus);

	res_minus = minus(a,b);
	printf("a-b = ");	if(Smaller(a,b) == a)putchar('-');	printBigNumber(res_minus);

	res_times = times(a,b);
	printf("a*b = ");	printBigNumber(res_times);

	res_divide = divisionQuot(a,b);
	printf("a/b = ");	printBigNumber(res_divide);

	res_mod = divisionMod(a, b);
	printf("a%%b = ");	printBigNumber(res_mod);
	return 0;
}