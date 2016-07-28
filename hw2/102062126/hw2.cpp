#include <iostream>
#include <stdio.h>
using namespace std;

uint8_t GF256_add(uint8_t a, uint8_t b, uint8_t mx){ // a^b uint_8
	return a^b;
	///
}
uint8_t GF256_mult_x(uint8_t a, uint8_t mx){ //uint_8 polynomial mult_x == left shift one bit
	// divide to two situation: x^7 is one or zero
	uint16_t new_mx = mx;
	if((a >> 7)&1){// x^7 is one
		uint16_t temp = a << 1;
		while((new_mx >> 8)&1 == 0){// now m(x)'s highest degree is not eight, cannot help clean a's x^8
			new_mx = mx << 1;//m(x) multiply by x is same to left shift one bit
		}
		temp = temp ^ new_mx;//we can sure that this is the answer of 'a mod mx'
		return (uint8_t)temp;
	}
	else// x^7 is zero
		return a << 1;
}
uint8_t GF256_mult(uint8_t a, uint8_t b, uint8_t mx){ //two polynomial multiplication by using linear combination of mult_x
	uint8_t return_value = 0;
	uint8_t temp;
	int i, j;
	for(i=0;i<8;i++){//look for b's x^i
		if((b >> i)&1){// x^i is one
			temp = a;
			for(j=0; j<i; j++)
				temp = GF256_mult_x(temp, mx);// mult_x n time is same to times x^n
			return_value = GF256_add(return_value, temp, mx);
		}
	}
	return return_value;
}
uint8_t GF256_inv(uint8_t a, uint8_t mx){ // bytesub step 1 -> get polynomial's inverse
	uint8_t return_value;
	if(a == 0) return 0;
	
	for(return_value = 0; return_value <= 0xFF; return_value++){
		if(GF256_mult(a, return_value, mx) == 1)
			break;
	}
	return return_value;
}

bool affine_array[8][8] = 
{
	{1,0,0,0,1,1,1,1},
	{1,1,0,0,0,1,1,1},
	{1,1,1,0,0,0,1,1},
	{1,1,1,1,0,0,0,1},
	{1,1,1,1,1,0,0,0},
	{0,1,1,1,1,1,0,0},
	{0,0,1,1,1,1,1,0},
	{0,0,0,1,1,1,1,1}
};
bool affine_array_inverse[8][8] = 
{
	{0,0,1,0,0,1,0,1},
	{1,0,0,1,0,0,1,0},
	{0,1,0,0,1,0,0,1},
	{1,0,1,0,0,1,0,0},
	{0,1,0,1,0,0,1,0},
	{0,0,1,0,1,0,0,1},
	{1,0,0,1,0,1,0,0},
	{0,1,0,0,1,0,1,0}
};
uint8_t affineTrans(uint8_t inv){ // bytesub step 2 -> transform inverse value to a new value
	uint8_t return_value = 0;
	int i,j;
	for(i=7; i>=0; i--){ // finish temporary y7 -> y0
		return_value <<= 1;
		for(j=0; j<8; j++)
			return_value ^= ( affine_array[i][j]*((inv>>j)&1) );
	}
	return_value ^= 0x63; // plus(XOR) [1,1,0,0,0,1,1,0] to [y0,y1,y2,y3,y4,y5,y6,y7] for result y
	return return_value;
}
uint8_t affineTrans_inverse(uint8_t inv){
	uint8_t return_value = 0;
	int i,j;
	
	inv ^= 0x63; // plus(XOR) [1,1,0,0,0,1,1,0] to [y0,y1,y2,y3,y4,y5,y6,y7] for getting x
	for(i=7; i>=0; i--){ // finish x7 -> x0
		return_value <<= 1;
		for(j=0; j<8; j++)
			return_value ^= ( affine_array_inverse[i][j]*((inv>>j)&1) );
	}
	return return_value;
}
void subBytes_16(uint8_t *input, uint8_t mx){ // do subbyte
	int i;
	for(i=0;i<16;i++)
		input[i] = affineTrans(GF256_inv(input[i], mx));
	return;
}
void subBytes_16_inverse(uint8_t *input, uint8_t mx){ 
	int i;
	for(i=0;i<16;i++)
		input[i] = GF256_inv(affineTrans_inverse(input[i]), mx);
	return;
}
void subBytes_4(uint8_t *input, uint8_t mx){ // do subbyte in key expansion
	int i;
	for(i=0;i<4;i++)
		input[i] = affineTrans(GF256_inv(input[i], mx));
	return;
}
void subBytes_4_inverse(uint8_t *input, uint8_t mx){ // no use
	int i;
	for(i=0;i<4;i++)
		input[i] = GF256_inv(affineTrans_inverse(input[i]), mx);
	return;
}
void shiftRows(uint8_t *input){ // left shift
	int i,j;
	uint8_t input_array[4][4] = {0};
	for(i=0;i<4;i++){
		for(j=0;j<4;j++)
			input_array[j][i] = input[i*4+j];
	}
	uint8_t *temp = new uint8_t[4];
	for(i=0; i<4; i++){
		for(j=0;j<4;j++)
			temp[j] = input_array[i][j];
		for(j=0;j<4;j++)	//printf("j-i = %d\n", (j+(4-i))%4);//(j+(4-i))%4 is right shift
			input_array[i][j] = temp[(j + i)%4];//encryption -> left shift
	}
	for(i=0;i<4;i++){
		for(j=0;j<4;j++)
			input[i*4+j] = input_array[j][i];
	}
	return;
}
void shiftRows_inverse(uint8_t *input){ // right shift
	int i,j;
	uint8_t input_array[4][4] = {0};
	for(i=0;i<4;i++){
		for(j=0;j<4;j++)
			input_array[j][i] = input[i*4+j];
	}
	uint8_t *temp = new uint8_t[4];
	for(i=0; i<4; i++){
		for(j=0;j<4;j++)
			temp[j] = input_array[i][j];
		for(j=0;j<4;j++)	//printf("j-i = %d\n", (j+(4-i))%4);//(j+(4-i))%4 is right shift
			input_array[i][j] = temp[(j + 4-i)%4];//decryption -> right shift
	}
	for(i=0;i<4;i++){
		for(j=0;j<4;j++)
			input[i*4+j] = input_array[j][i];
	}
	return;
}
uint8_t mix_column_array[4][4] = 
{
	{2,3,1,1},
	{1,2,3,1},
	{1,1,2,3},
	{3,1,1,2}
};
uint8_t mix_column_array_inverse[4][4] = 
{
	{0xe,0xb,0xd,0x9},
	{0x9,0xe,0xb,0xd},
	{0xd,0x9,0xe,0xb},
	{0xb,0xd,0x9,0xe}
};
void mixColumn(uint8_t *input, uint8_t mx){ // a matrix multiplication, using GF256_mult
	int i,j,k;
	uint8_t input_array[4][4] = {0};
	for(i=0;i<4;i++){
		for(j=0;j<4;j++)
			input_array[j][i] = input[i*4+j];
	}
	uint8_t result_array[4][4] = {0};
	for(i=0;i<4;i++){
		for(j=0;j<4;j++){
			for(k=0;k<4;k++)
				result_array[i][j] ^= GF256_mult(mix_column_array[i][k], input_array[k][j], mx);
		}
	}
	for(i=0;i<4;i++){
		for(j=0;j<4;j++)
			input[i*4+j] = result_array[j][i];
	}
}
void mixColumn_inverse(uint8_t *input, uint8_t mx){
	int i,j,k;
	uint8_t input_array[4][4] = {0};
	for(i=0;i<4;i++){
		for(j=0;j<4;j++)
			input_array[j][i] = input[i*4+j];
	}
	uint8_t result_array[4][4] = {0};
	for(i=0;i<4;i++){
		for(j=0;j<4;j++){
			for(k=0;k<4;k++)
				result_array[i][j] ^= GF256_mult(mix_column_array_inverse[i][k], input_array[k][j], mx);
		}
	}
	for(i=0;i<4;i++){
		for(j=0;j<4;j++)
			input[i*4+j] = result_array[j][i];
	}
}
void keyExpansion(uint8_t *key, uint8_t mx, uint8_t **output){ // we can get ten round's round key 
	//we need mx because of 'SubWord'
	
	// generate Rcon table
	uint8_t Rcon[11] = {0x00, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36};

	//output is word[44] -> uint_8[44][4]
	// key round0
	int i,j,k;
	for(i=0; i<4; i++){
		for(j=0; j<4; j++)
			output[i][j] = key[i*4+j];
	}
	// key round1~10
	uint8_t buffer[4];
	for(i=4; i<44; i = i+4){//ten round
		//RotWord
		for(j=0; j<4; j++)
			buffer[j] = output[i-1][(j+1)%4];// encryption -> left shift(right shift is (j+3)%4)
		//SubWord
		subBytes_4(buffer, mx);
		//XOR with Rcon
		buffer[0] ^= Rcon[i/4];
		
		//create w[i]
		for(j=0; j<4; j++)
			output[i][j] = output[i-4][j]^buffer[j];
		//create w[i+1] to w[i+3]
		for(j=1; j<=3; j++){
			for(k=0; k<4; k++)
				output[i+j][k] = output[(i+j)-1][k]^output[(i+j)-4][k];
		}
	}
	return;
}
uint8_t* extractRoundKey(uint8_t **word, int Round){ // get the round key we 
	uint8_t *roundkey = new uint8_t[16];
	int i,j;
	for(i=0; i<4; i++){
		for(j=0; j<4; j++)
			roundkey[i*4+j] = word[Round*4+i][j];
	}
	return roundkey;
}
void addRoundKey(uint8_t *input, uint8_t **word, int Round){
	uint8_t *roundkey = extractRoundKey(word, Round);
	int i;
	for(i=0;i<16;i++)
		input[i] ^= roundkey[i];
	return;
}
void input(uint8_t* input){ // eat input which looks like '00 01 02 0a 1b 2c ....'
	uint8_t temp[49];
	int ch,i,c;
	int temp1[49];
	for(c=0;c<48;c++)
		temp[c]=getchar(); //collect input(hex)

	for(c=0;c<48;c++){ //transform to decimal
		if(temp[c] >= '0' && temp[c] <= '9') temp1[c]= temp[c]-'0';
		if(temp[c] >= 'a' && temp[c] <= 'f') temp1[c]= 10+temp[c]-'a';
		if(temp[c] >= 'A' && temp[c] <= 'F') temp1[c]= 10+temp[c]-'A';
		for(i=0;i<16;i++)
			input[i]=((16*temp1[3*i])+temp1[3*i+1]); //transform to binary, 3*i:0-> A, 3*i+1:1-> D, and an unused character  => AD 
	}
}
void printText(uint8_t *input){ // print plaintext, key, ciphertext
	int i;
	for(i=0;i<16;i++)
		printf("%02x ", input[i]);
	putchar('\n');
}
void AES_Encrypt(uint8_t* plaintext, uint8_t* ciphertext, uint8_t* key){
	int i,j;

	// AES Encryption
	printf("<AES Encryption>\n");
	printf("Plaintext: ");	printText(plaintext);
	printf("Key: ");		printText(key);
	printf("----------Encryption----------\n");

	// key expansion of encryption
	uint8_t **word = new uint8_t*[44];
	for(i=0; i<44; i++)
		word[i] = new uint8_t[4];
	keyExpansion(key, 0x1b, word);

	// An initial Round Key addition(now we XOR our 'key'(w[0,3]), same P&K's index will XOR to same index ciphertext)
	printf("State0: ");
	for(i=0; i<16; i++)
		ciphertext[i] = GF256_add(plaintext[i], key[i], 0x1b);
	printText(ciphertext);

	//Round 1 to Round 9
	for(i=1; i<=9; i++){
		printf("State%d: ", i);
		
		//bytesub
		subBytes_16(ciphertext, 0x1b);
		//shift
		shiftRows(ciphertext);
		//mix column
		mixColumn(ciphertext, 0x1b);
		//add round key
		addRoundKey(ciphertext, word, i);

		printText(ciphertext);
	}
	printf("Ciphertext: ");
	
	subBytes_16(ciphertext, 0x1b);
	shiftRows(ciphertext);
	addRoundKey(ciphertext, word, i);
	
	printText(ciphertext);
}
void AES_Decrypt(uint8_t* plaintext, uint8_t* ciphertext, uint8_t* key){
	int i, j;

	// AES Decryption
	printf("<AES Decryption>\n");
	printf("Ciphertext: ");	printText(ciphertext);
	printf("Key: ");		printText(key);
	printf("----------Decryption----------\n");

	// key expansion of encryption
	uint8_t **word = new uint8_t*[44];
	for(i=0; i<44; i++)
		word[i] = new uint8_t[4];
	keyExpansion(key, 0x1b, word);

	// An initial Round Key addition(now we XOR our 'key'(w[40,43]), same C&K's index will XOR to same index plaintext)
	printf("State0: ");
	uint8_t *initial_roundkey = new uint8_t[16];
	initial_roundkey = extractRoundKey(word, 10);
	for(i=0; i<16; i++)
		plaintext[i] = ciphertext[i]^initial_roundkey[i];
	printText(plaintext);

	//Round 1 to Round 9
	for(i=1; i<=9; i++){
		printf("State%d: ", i);
		
		//shift
		shiftRows_inverse(plaintext);
		//bytesub
		subBytes_16_inverse(plaintext, 0x1b);
		//add round key
		addRoundKey(plaintext, word, 10-i);
		//mix column
		mixColumn_inverse(plaintext, 0x1b);
		
		printText(plaintext);
	}
	printf("Plaintext: ");

	shiftRows_inverse(plaintext);
	subBytes_16_inverse(plaintext, 0x1b);
	addRoundKey(plaintext, word, 0);
	
	printText(plaintext);
}
int main(int argc, char const *argv[])
{
	// input and output are all a 128-bit(16 bytes) string, store in a uint_8[16] array.
	uint8_t *plaintext = new uint8_t[16];
	input(plaintext);
	uint8_t *key = new uint8_t[16];
	input(key);
	uint8_t *ciphertext = new uint8_t[16];

	// we just input plaintext and key
	AES_Encrypt(plaintext, ciphertext, key);
	putchar('\n');
	// we use what we encrypt to decrypt
	AES_Decrypt(plaintext, ciphertext, key);
	return 0;
}