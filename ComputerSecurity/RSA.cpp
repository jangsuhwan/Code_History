#include <random>
#include <ctime>
#include <iostream>
#include <string>
#include <bitset>
#include "xxhash.h"
#include <stdio.h>
using namespace std;
int p, q, N, r, e, d, phi;
unsigned __int64 hashv;
//Find d modulo inverse of e
int gcdExtended(int a, int mod, int *x, int *y);
int extendedEuclid(int a, int mod) {
	int x, y;
	int g = gcdExtended(a, mod, &x, &y);
	if (g != 1) {
		cout << "no Inverse" << endl;
	}
	else {
		int result = (x%mod + mod) % mod;
		return result;
	}
}
int gcdExtended(int a, int mod, int *x, int *y)
{
	//GCD(d, e) = 1 mod totient(n)
	if (a == 0) {
		*x = 0, *y = 1;
		return mod;
	}

	int x1, y1;
	int gcd = gcdExtended(mod%a, a, &x1, &y1);

	*x = y1 - (mod / a)*x1;
	*y = x1;
	return gcd;
}
//square and multiply algorithm for modular exponentiation
long long squareAndMultiply(long long base, unsigned int exponent, unsigned int n)
{
	long long result = 1;
	
	base = base % n;
	while (exponent > 0) {
		//if y is odd, multiply with result.
		if (exponent & 1)
			result = (result*base) % n;
		base = (base * base) % n; // "square"
		exponent >>= 1;
	}
	return result;
}
bool millerTest(int q, int n)
{
	//Select a random integer a, 1 < a < n-1
	int a = 2 + rand() % (n - 4);
	//a^q%n
	int x = squareAndMultiply(a, q, n);
	//if a^q mod n == 1 or n == n-1
	if (x == 1 || x == n - 1)
		return true;

	while (q != n - 1)
	{
		x = (x*x) % n;
		q *= 2;

		if (x == 1) return false;
		if (x == n - 1) return true;
	}
	
	return false;

}
// It returns false if n is composite and returns true if n
// is probably prime.  
bool isPrime(int n)
{
	//2 is prime
	if (n == 2) return true;
	if (n % 2 == 0 || n <= 1) return false;

	int testCount = 20;
	//find an odd number q such that n-1 = 2^k*q
	int q = n - 1;
	while (q % 2 == 0) {
		q /= 2;
	}

	for (int i = 0; i < testCount; i++) {
		//do while q doesn't become n-1
		if (!millerTest(q, n))
			return false;
	}
	return true;
}
bool millerRabin(int p)
{
	return isPrime(p);
}
int GCD(int a, int b) {
	if (b == 0) return a;
	else return GCD(b, a%b);
}
void generateE() {
	
	while (true) {
		//1 < e < phi
		e = rand() % (phi - 1) + 1;
		if (GCD(e, phi) == 1) break;
	}
}
void generateD() {

	d = extendedEuclid(e, phi);
}
void generateKeys() {

	while (!millerRabin(p)) {
		p = rand()%(1<<10);
	}
	cout << "p = " << p << endl;
	while (!millerRabin(q)) {
		q = rand()%(1<<10);
	}
	cout << "q = " << q << endl;
	while (!millerRabin(r)) {
		r = rand()%(1<<10);
	}
	cout << "r = " << r << endl;
	N = p * q*r;
	phi = (p - 1)*(q - 1)*(r - 1);
	cout << "N = " << N << endl;
	cout << "phi = " << phi << endl;
	//gcd(e, phi) = 1 for 1 < e < phi
	generateE();
	cout << "e = " << e << endl;
	generateD();
	cout << "d = " << d << endl;
}
int chineseRemainderTheorem(int message) {
	//m + n*t = message^d
	//m + p*q*r*t = message^d;
	int Dp, Dq,Dr,Mr, Mp, Mq, inverseP, inverseQ, inverseR;
	Dp = d % (p-1);
	Dq = d % (q - 1);
	Dr = d % (r - 1);

	Mp = squareAndMultiply(message, Dp, p);
	Mq = squareAndMultiply(message, Dq, q);
	Mr = squareAndMultiply(message, Dr, r);

	inverseP = extendedEuclid(N/p, p);
	inverseQ = extendedEuclid(N/q, q);
	inverseR = extendedEuclid(N/r, r);
	long long j =(((long long)Mp*inverseP)*(N / p));
	j += (((long long)Mq*inverseQ)*(N / q));
	j += (((long long)Mr*inverseR)*(N / r));

	long long res = j % N;
	return res;
}
int encryption(int message) {
	return squareAndMultiply(message, e, N);
}
int decryption(int message) {

	int decrypted = chineseRemainderTheorem(message);
	return decrypted;
}
int generateHash(int message) {
	char buf[65] = {};
	sprintf(buf, "%I64u", message);
	hashv = XXH64(buf, sizeof(buf) - 1, 0);

	hashv = hashv % N;
	return hashv;
}
int main(int argc, char** argv)
{
	srand((unsigned int)time(NULL));
	generateKeys();
	cout << endl;
	cout << "Message Input :";
	int input;
	cin >> input;
	cout << "Message = " << input << endl;
	cout << endl;
	//encryption
	cout << "**Encryption\ncipher : ";
	int cipher = encryption(input);
	cout << cipher << endl;
	cout << endl;
	cout << "**Generate signature" << endl;
	unsigned __int64 hashv = generateHash(input);
	cout << "message's hash value : " << hashv << endl;
	int signature = squareAndMultiply(hashv, e, N);
	cout << "generated sigature : " << signature << endl;
	cout << "\n**Decryption\ndecrypted cipher : ";
	int decrypted = decryption(cipher);
	cout << decrypted << endl;
	cout << endl;

	cout << "**Verify signature" << endl;
	cout << "received signature value : " << signature << endl;
	
	int V1 = generateHash(decrypted);
	int V2 = generateHash(decryption(cipher));
	cout << "decrypted message's hash value : " << V1 << endl;
	cout << "verify value from signature : " << V2 << endl;
	if (V1 == V2) {
		cout << "Signature valid!" << endl;
	}
	else {
		cout << "Signature invalid" << endl;
	}
}