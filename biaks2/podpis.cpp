#include <iostream>
#include <string> 
#include <vector>
#include <bitset>

const int SHIFT = 5;

using namespace std;

string myHash(string data) {

	string cryptedMsg = "";
	string hashedMsg = "";
	
	for (int i = 0; i < data.length(); ++i)
		cryptedMsg += (int(data[i]) + SHIFT);

	for (int i = cryptedMsg.size() - 1; i > cryptedMsg.size() - 33; --i)
		hashedMsg += bitset<8>(cryptedMsg.c_str()[i]).to_string();

	return hashedMsg;
}

int main(void)
{	
	string msg = "toto je tajna sprava, toto je tajna sprava, toto je tajna sprava, toto je tajna sprava, toto je tajna sprava, toto je tajna sprava, toto je tajna sprava, toto je tajna sprava,toto je tajna sprava, toto je tajna sprava, toto je tajna sprava, toto je tajna sprava";
	cout << "Hashed msg: " << myHash(msg) << endl << endl;

	return 0;
}