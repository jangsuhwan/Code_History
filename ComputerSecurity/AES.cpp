#include <iostream>
#include <sstream>
#include <bitset>
#include <string>
#include <vector>
#include <fstream>
#include <istream>
#include <iterator>
#include <iomanip>
using namespace std;
enum eDirection { left, right };
unsigned int SBox[16][16];
unsigned int inverseSBox[16][16];
unsigned int RC[10];
const int m = 0x169; //m(x) = x ^ 8 + x ^ 6 + x ^ 5 + x ^ 3 + 1
unsigned int roundKey[11][18];

//Convert integer hex into 9length binary string
string hexToBinaryNineSize(int hexValue)
{
	bitset<9> bitset(hexValue);
	string str_bits = bitset.to_string();
	return str_bits;
}
//Convert integer hex into 20length binary string
string hexToBinary(int hexValue)
{
	bitset<20> bitset(hexValue);
	string str_bits = bitset.to_string();
	return str_bits;
}
//binary long division algorithm
int* divide(int dividend, int divisor)
{
	int* arr = new int[2];
	string strDividend = hexToBinary(dividend);
	string strDivisor = hexToBinary(divisor);

	//align digit into most significant bit of dividend.
	int diff = (strDivisor.find("1") - strDividend.find("1"));
	for (int i = 0; i < diff; i++) {
		divisor <<= 1;
	}

	int msbLocation = strDividend.find("1");
	int remainder = 0, quotient = 0;
	for (int i = 0; i < diff + 1; i++)
	{
		string str = hexToBinary(dividend);
		char msb = str[msbLocation++];
		quotient <<= 1;
		/*
		if msb of dividend is 0, it can't divide.
		ex) dividend : 011 / divisor : 100
		*/
		if (msb == '1') {
			//can dinvide, increment quotient
			quotient |= 1;
			remainder = dividend ^ divisor;
		}
		divisor >>= 1;
		dividend = remainder;
	}
	arr[0] = quotient;
	arr[1] = remainder;
	return arr;
}
//finite field multiplication
int multiple(int a, int b)
{
	string strA = hexToBinary(a);
	int temp = 0;
	//left 1 shift b whenever the bit of A in binary format is 1 
	for (int i = strA.find("1"); i <= 20; i++)
	{
		if (strA[i] == '1')
		{
			// in Rijndael's finite field
			temp ^= (b << (19 - i));
			if ((temp >> 8) != 0) {
				//followed by division using the reducing polynomial as the divisor
				temp = divide(temp, m)[1];
			}
		}
	}
	return temp;
}
//find the inverse of multiplication
int extendedEuclid(int d)
{
	//GCD(d, m(x)) = 1, m(x) = x^8+x^6+x^5+x^3+1 hex : 169

	int X1 = 1, X2 = 0, X3 = m;
	int Y1 = 0, Y2 = 1, Y3 = d;
	int T1, T2, T3;
	int Q;
	while (1) {
		if (Y3 == 0) return 0;
		else if (Y3 == 1) return Y2;

		int* quotientAndRemainder = divide(X3, Y3);
		Q = quotientAndRemainder[0];
		T1 = X1 ^ multiple(Q, Y1), T2 = X2 ^ multiple(Q, Y2), T3 = quotientAndRemainder[1];
		X1 = Y1, X2 = Y2, X3 = Y3;
		Y1 = T1, Y2 = T2, Y3 = T3;
	}
}

void printLine(string header, unsigned int* values, int size = 16)
{

	cout << header << ": ";
	for (int i = 0; i < size; i++)
	{
		cout << setfill('0') << setw(2) << uppercase << hex << values[i] << " ";
	}
	cout << endl;
}
void rightShift(unsigned int* row, int size)
{
	int* temp = new int[size];
	int lastValue = row[size - 1];

	for (int i = 0; i < size; i++)
	{
		temp[i + 1] = row[i];
	}
	temp[0] = lastValue;

	for (int i = 0; i < size; i++)
	{
		row[i] = temp[i];
	}
}
//shift by jump
void rotate(unsigned int* row, int jump, eDirection dir)
{
	int temp[4] = { 0, };
	memcpy(temp, row, 16);

	//left shift row in encryption
	if (dir == eDirection::left) {
		for (int i = 0; i < 4; i++)
		{
			int nextPos = (i - jump) < 0 ? (i + 4 - jump) : i - jump;
			row[nextPos] = temp[i];
		}
	}
	//right shift inverse row in decryption
	else {
		for (int i = 0; i < 4; i++)
		{
			int nextPos = (i + jump) >= 4 ? (i + jump) % 4 : i + jump;
			row[nextPos] = temp[i];
		}
	}

}
void makeForwardingSBox()
{
	//make affine matrix
	unsigned int matrixFactor[8][8];
	unsigned int row[8] = { 1, 0, 0, 0, 1, 1, 1, 1 };
	string constantString = hexToBinaryNineSize(0x15);

	for (int j = 0; j < 8; j++) {

		for (int i = 0; i < 8; i++) {
			matrixFactor[j][i] = row[i];
		}
		rightShift(row, 8);
	}

	int inputValue = 0x00;
	//matrix multiplication about affine and input
	for (int i = 0; i < 16; i++) {
		for (int j = 0; j < 16; j++) {
			int i_j = 0;
			int inverseInput = extendedEuclid(inputValue);
			string bitsets = hexToBinaryNineSize(inverseInput);
			for (int k = 0; k < 8; k++) {
				int l = 0;
				for (int p = 0; p < 8; p++) {
					if (matrixFactor[k][p] == 1)
						l = l ^ (bitsets[8 - p] - '0');
				}
				//XOR with constant column
				l ^= (constantString[8 - k] - '0');
				if (l == 1) {
					i_j += 1 << k;
				}
			}
			SBox[i][j] = i_j;
			inputValue++;
		}
	}
}
void makeInverseSBox()
{
	/*
	Use fowarding sbox to make inverseSBox
	ex)
	sbox[i][j] = 0xXY;
	inverseSBox[X][Y] = 0xij;
	*/

	for (int i = 0; i < 16; i++) {
		for (int j = 0; j < 16; j++) {
			int value = SBox[i][j];
			int col = value / 16;
			int row = value % 16;
			inverseSBox[col][row] = i * 16 + j;
		}
	}
}
//substitute on Box
unsigned int substitute(unsigned int(*box)[16], unsigned int k)
{
	int col = k / 16;
	int row = k % 16;
	return box[col][row];
}
unsigned int* R_function(unsigned int* row, int round)
{
	rotate(row, 1, eDirection::left);

	unsigned int* output = new unsigned int[4];
	int rc = RC[round];
	for (int col = 0; col < 4; col++)
	{
		unsigned int substitution = substitute(SBox, row[col]);
		if (col == 0) {
			output[col] = substitution ^ rc;
		}
		else {
			output[col] = substitution;
		}
	}
	return output;
}
unsigned int* nextRoundKey(unsigned int* key, int round)
{
	unsigned int fourthRow[4] = { key[12], key[13], key[14], key[15] };
	unsigned int* convertedFourthRow = R_function(fourthRow, round);
	unsigned int* nextRoundKey = new unsigned int[16];

	for (int k = 0; k < 16; k++)
	{
		if (k < 4) {
			nextRoundKey[k] = key[k] ^ convertedFourthRow[k];
		}
		else {
			nextRoundKey[k] = nextRoundKey[k - 4] ^ key[k];
		}
	}
	return nextRoundKey;
}
unsigned int* readFile(const char* filename)
{
	ifstream file(filename, ios::in | ios::binary);
	char buf[17] = { '0' };

	if (file.is_open())
	{
		file.seekg(0, ios::end);
		int sz = file.tellg();
		file.seekg(0, ios::beg);
		file.read(buf, sz);
		file.close();
	}
	else {
		cerr << "can't find " << filename << endl;
		system("pause");
	}

	unsigned int* ubuf = new unsigned int[16];
	for (int i = 0; i < 16; i++)
	{
		ubuf[i] = (int)((unsigned char)buf[i]);
	}
	if (filename == "plain.bin") {
		printLine("PLAIN", ubuf);
	}
	else {
		printLine("KEY", ubuf);
	}
	return ubuf;
}
void keyExpansion(unsigned int* &key) {

	cout << "KEY EXPANSION" << endl;

	for (int round = 0; round <= 10; round++)
	{
		for (int j = 0; j < 16; j++) {
			roundKey[round][j] = key[j];
		}
		printLine("ROUND" + to_string(round), key);
		key = nextRoundKey(key, round);
	}
	cout << endl;
}
void addRoundKey(unsigned int* plainText, unsigned int* roundKey)
{
	for (int i = 0; i < 16; i++)
	{
		plainText[i] ^= roundKey[i];
	}
	printLine("AR", plainText);
}
//substitute text on Box.
void subBytes(unsigned int(*box)[16], unsigned int* &text)
{
	for (int i = 0; i < 16; i++)
	{
		text[i] = substitute(box, text[i]);
	}
	printLine("SB", text);
}
void shiftRows(unsigned int* input, eDirection dir)
{
	unsigned int** matrix = new unsigned int*[4];
	for (int i = 0; i < 4; i++) {
		matrix[i] = new unsigned int[4];
	}

	for (int j = 0; j < 4; j++)
	{
		for (int i = 0; i < 4; i++)
		{
			matrix[i][j] = input[j * 4 + i];
		}
	}

	for (int j = 1; j < 4; j++)
	{
		rotate(matrix[j], j, dir);
	}

	for (int j = 0; j < 4; j++)
	{
		for (int i = 0; i < 4; i++)
		{
			input[i + (j * 4)] = matrix[i][j];
		}
	}
	for (int i = 0; i < 4; ++i) { delete[] matrix[i]; }
	delete[] matrix;

	printLine("SR", input);
}
void mixColumns(unsigned int* plainText)
{
	unsigned int factorRow[4] = { 2, 3, 1, 1 };
	unsigned int matrix[4][4] = { 0, };
	unsigned int input[4][4] = { 0, };
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			matrix[i][j] = factorRow[j];
			input[i][j] = plainText[i + j * 4];
		}
		rightShift(factorRow, 4);
	}
	unsigned int output[4][4] = { 0, };
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			for (int k = 0; k < 4; k++)
			{
				output[i][j] ^= multiple(matrix[i][k], input[k][j]);
			}
		}
	}
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			plainText[j + 4 * i] = output[j][i];
		}
	}
	printLine("MC", plainText);
}
void inverseMixColumns(unsigned int* cipherText)
{
	unsigned int factorRow[4] = { 0xE, 0xB, 0xD, 0x9 };
	unsigned int matrix[4][4] = { 0, };
	unsigned int input[4][4] = { 0, };
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			matrix[i][j] = factorRow[j];
			input[i][j] = cipherText[i + j * 4];
		}
		rightShift(factorRow, 4);
	}
	unsigned int output[4][4] = { 0, };
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			for (int k = 0; k < 4; k++)
			{
				output[i][j] ^= multiple(matrix[i][k], input[k][j]);
			}
		}
	}
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			cipherText[j + 4 * i] = output[j][i];
		}
	}
	printLine("MC", cipherText);
}
//round constant rcon for round i of the key expansion
void makeRC() {
	for (int i = 0; i < 10; i++) {
		if (i == 0) {
			RC[i] = 1;
		}
		else if (i>=1 && RC[i - 1] < 0x80) {
			RC[i] = RC[i - 1] << 1;
		}
		else {
			RC[i] = (RC[i - 1] << 1) ^ 0x169;
		}
	}
	printLine("RC", RC, 10);
}
//make RC and read necessary files.
void preprocessing(unsigned int* &in, unsigned int* &key) {
	makeRC();
	in = readFile("plain.bin");
	key = readFile("key.bin");
}

void encryptionForRound(unsigned int* &input) {
	for (int round = 0; round < 10; round++) {
		cout << "Round " << round << endl;
		if (round != 0) {
			subBytes(SBox, input);
			shiftRows(input, eDirection::left);
			mixColumns(input);
			addRoundKey(input, roundKey[round]);
		}
		else {
			addRoundKey(input, roundKey[round]);
		}
		cout << endl;
	}
	cout << "Round 10" << endl;
	subBytes(SBox, input);
	shiftRows(input, eDirection::left);
	addRoundKey(input, roundKey[10]);
}

void decryptionForRound(unsigned int* &input) {
	for (int round = 0; round < 10; round++) {
		cout << "Round " << round << endl;
		if (round != 0) {
			shiftRows(input, eDirection::right);
			subBytes(inverseSBox, input);
			addRoundKey(input, roundKey[10 - round]);
			inverseMixColumns(input);
		}
		else {
			addRoundKey(input, roundKey[10 - round]);
		}
		cout << endl;
	}
	cout << "Round 10" << endl;
	shiftRows(input, eDirection::right);
	subBytes(inverseSBox, input);
	addRoundKey(input, roundKey[0]);
}

void Encryption(unsigned int* &plainText, unsigned int* &key) {

	cout << "\n" << "<----ENCRYPTION---->" << endl;
	cout << endl;

	makeForwardingSBox();
	keyExpansion(key);
	encryptionForRound(plainText);
	cout << endl;
	printLine("CIPHER: ", plainText);
}

void Decryption(unsigned int* &cipherText, unsigned int* &key) {

	cout << "\n" << "<----DECRYPTION---->" << endl;
	cout << endl;

	makeInverseSBox();
	decryptionForRound(cipherText);
	cout << endl;
	printLine("DECRYPTED ", cipherText);
}
int main()
{
	unsigned int* input = nullptr;
	unsigned int* key = nullptr;
	preprocessing(input, key);
	Encryption(input, key);

	cout << "\n" << "\n";

	Decryption(input, key);
}