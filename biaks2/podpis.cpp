#include <iostream>
#include <string> 
#include <vector>
#include <bitset>
#include <boost/multiprecision/miller_rabin.hpp>
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/independent_bits.hpp>
// https://www.numberempire.com/primenumbers.php prime number checker

using namespace std;
using namespace boost::multiprecision;
using namespace boost::random;

const int SHIFT = 5;
cpp_int privateKey;
cpp_int publicKey;

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

	privateKey = getPrime();
	publicKey = getPrime();

	while (privateKey == publicKey) 
	{
		publicKey = getPrime();
	}

	cout << "private: " << privateKey << endl << endl << endl;
	cout << "public: " << publicKey << endl << endl << endl;

	return 0;
}