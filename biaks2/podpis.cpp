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

//old hash binary
/*string myHash(string data) {

	string cryptedMsg = "";
	string hashedMsg = "";
	
	for (int i = 0; i < data.length(); ++i)  //my old hash fucntion 
		cryptedMsg += (int(data[i]) + SHIFT);

	for (int i = cryptedMsg.size() - 1; i > cryptedMsg.size() - 33; --i)
		hashedMsg += bitset<8>(cryptedMsg.c_str()[i]).to_string();

	return hashedMsg;
}*/

unsigned int myHash(string data) {

	unsigned int hashedMsg = 1315423911;

	for (int i = 0; i < data.length(); ++i)
		hashedMsg ^= ((hashedMsg << 5) + (data[i]) + (hashedMsg >> 2));

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
	string msg = "toto je tajna sprava";
	cout << "Hashed msg: " << myHash(msg) << endl << endl;

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
	
	e = 17;

	//double tempD = 1 / (double)e;
		//double D = fmod(tempD, (double)phi);

	int D = boost::integer::mod_inverse(e, phi);  

	cpp_int m = 65;
	cpp_int c = 0;
	 

	// crypted = m^d * (mod n)????????  // z videa od dievciny


	//public key is N and e   // c(m) = m^e mod N   (message)			CRYPT
	//c = boost::multiprecision::pow(m, e);
	cpp_int cryptedHash = boost::multiprecision::powm(m, e, N);
	//cpp_int cryptedHash = c % (int)N;

	cout << "cypting" << endl;
	cout << "m: " << m << endl;
	cout << "e: " << e << endl;
	cout << "c: " << c << endl;
	cout << "cryptedHash: " << cryptedHash << endl << endl << endl;

	

	//private key is N and D  // c(c) = c^D mod N   (cypted message)    DECRYPT
	cpp_int uncryptedHash = 0;
	m = pow(cryptedHash, D);
	uncryptedHash = m % N;

	cout << "decypting" << endl;
	cout << "uncrypted hash: " << uncryptedHash << endl << endl << endl;
	



	cout << "prime1: " << prime1 << endl;
	cout << "prime2: " << prime2 << endl;
	cout << "N: " << N << endl;
	cout << "phi: " << phi << endl;
	cout << "e: " << e << endl << endl;
	//cout << "doublePhi: " << (double)phi << endl << endl << endl;
	cout << "D: " << D << endl << endl << endl;

	return 0;
}