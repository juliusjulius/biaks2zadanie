#include <iostream>
#include <string> 
#include <vector>
#include <bitset>
#include<math.h>
#include <boost/multiprecision/miller_rabin.hpp>
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/independent_bits.hpp>
#include <boost/math/common_factor.hpp>
#include <boost/integer/extended_euclidean.hpp>
#include <boost/integer/mod_inverse.hpp>
// https://www.numberempire.com/primenumbers.php prime number checker

using namespace std;
using namespace boost::multiprecision;
using namespace boost::random;

const int SHIFT = 5;
cpp_int privateKey;
cpp_int publicKey;
cpp_int prime1;
cpp_int prime2;

string myHash(string data) {

	string cryptedMsg = "";
	string hashedMsg = "";
	
	for (int i = 0; i < data.length(); ++i)
		cryptedMsg += (int(data[i]) + SHIFT);

	for (int i = cryptedMsg.size() - 1; i > cryptedMsg.size() - 33; --i)
		hashedMsg += bitset<8>(cryptedMsg.c_str()[i]).to_string();

	return hashedMsg;
}

cpp_int getPrime()
{
	mt11213b base_gen(clock());
	boost::random::independent_bits_engine<mt11213b, 512, cpp_int> gen(base_gen);

	cpp_int n = 1;
	do
	{
		n = gen();
	} while (!miller_rabin_test(n, 25));
	return n;
}

int main(void)
{	
	string msg = "toto je tajna sprava, toto je tajna sprava, toto je tajna sprava, toto je tajna sprava, toto je tajna sprava, toto je tajna sprava, toto je tajna sprava, toto je tajna sprava,toto je tajna sprava, toto je tajna sprava, toto je tajna sprava, toto je tajna sprava";
	//cout << "Hashed msg: " << myHash(msg) << endl << endl;

	//prime1 = getPrime();
	//prime2 = getPrime();

	//while (prime1 == prime2)
	//	prime2 = getPrime();

	//cpp_int N = prime1 * prime2;
	//cpp_int phi = (prime1 - 1) * (prime2 - 1); 
	// 
	//int e = 2;			// 1 < e < phi
	//while (boost::math::gcd(e, phi) != 1) 
	//	e++;




	//double tempD = 1 / (double)e;
	//long double D = fmod(tempD, (long double)phi);



	prime1 = 61;
	prime2 = 53;

	cpp_int N = prime1 * prime2;
	int phi = ((int)prime1 - 1) * ((int)prime2 - 1);

	int e = 2;			// 1 < e < phi
	while (boost::math::gcd(e, phi) != 1)
		e++;
	

	double tempD = 1 / (double)e;

	int D = boost::integer::mod_inverse(e, phi);  

	//double D = fmod(tempD, (double)phi);

	





	//public key is N and e
	//private key is N and D



	cout << "prime1: " << prime1 << endl << endl << endl;
	cout << "prime2: " << prime2 << endl << endl << endl;
	cout << "N: " << N << endl << endl << endl;
	cout << "phi: " << phi << endl << endl << endl;
	cout << "e: " << e << endl << endl << endl;

	cout << "tempD: " << tempD << endl << endl << endl;
	cout << "doublePhi: " << (double)phi << endl << endl << endl;
	cout << "D: " << D << endl << endl << endl;

	return 0;
}