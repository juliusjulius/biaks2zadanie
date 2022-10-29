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
const cpp_int HASH = 1315423911;
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

cpp_int myHash(string data) {

	cpp_int hashedMsg = HASH;

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

cpp_int encryptHash(cpp_int hashedMessage, cpp_int e, cpp_int N)
{
	return boost::multiprecision::powm(hashedMessage, (cpp_int)e, N); //public key is N and e   // c(m) = m^e mod N   (message)     ENCRYPT
}

cpp_int decryptHash(cpp_int cryptedHash, cpp_int D, cpp_int N)
{
	return boost::multiprecision::powm(cryptedHash, (cpp_int)D, N);  //private key is N and D  // m(c) = c^D mod N   (cypted message)    DECRYPT
}

int main(void)
{	
	string msg = "This is secret message";   // msg can't be longer than N (took me few hours..)
	cpp_int hashedMessage = myHash(msg);

	prime1 = getPrime();
	prime2 = getPrime();

	cpp_int N = prime1 * prime2;
	cpp_int phi = (prime1 - 1) * (prime2 - 1);         

	int e = 2;			// 1 < e < phi
	while (boost::math::gcd(e, phi) != 1)
		e++;
	
	cpp_int D = boost::integer::mod_inverse((cpp_int)e, phi);      




	cpp_int cryptedHash = encryptHash(hashedMessage,e , N);
	cout << "Hashed message: " << hashedMessage << endl << endl << "Encypting..." << endl << "EncryptedHash: " << cryptedHash << endl << endl << endl;


	cpp_int decryptedHash = decryptHash(cryptedHash, D, N);
	cout << "Decypting..." << endl << "decrypted hash: " << decryptedHash << endl << endl << endl;
	

	cout << "prime1: " << prime1 << endl << endl;
	cout << "prime2: " << prime2 << endl << endl;
	cout << "N: " << N << endl << endl;
	cout << "phi: " << phi << endl << endl;
	cout << "e: " << e << endl << endl;
	cout << "D: " << D << endl << endl;

	return 0;
}