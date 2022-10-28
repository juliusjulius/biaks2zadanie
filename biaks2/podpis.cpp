#include <iostream>
#include <string> 
#include <vector>
#include <bitset>

const int SHIFT = 5;

using namespace std;

string myHash(string data) {

	string hashedMsg;

	for (int i = 0; i < data.length(); ++i)
		hashedMsg += (int(data[i]) + SHIFT);

	return hashedMsg;
}

//string myUnhash(string data) {      // SPRAVU NETREBA ODHASHOVAT KEDZE SA POSIELA NEHESHOVANA A HASH STACI POROVNAT
//
//	string unHashedMsg;
//
//	for (int i = 0; i < data.length(); ++i)
//		unHashedMsg += (int(data[i]) - SHIFT);
//
//	return unHashedMsg;
//}

int main(void)
{	
	string temp;
	string msg = "toto je tajna sprava, toto je tajna sprava, toto je tajna sprava, toto je tajna sprava, toto je tajna sprava, toto je tajna sprava, toto je tajna sprava, toto je tajna sprava,toto je tajna sprava, toto je tajna sprava, toto je tajna sprava, toto je tajna sprava";
	
	/*temp = myHash(msg);
	cout << "hashed msg: " << temp << endl << endl;

	temp = myUnhash(temp);
	cout << "hashed msg: " << temp << endl << endl;*/


	string mojString = "";
	for (int i = msg.size() - 1; i > msg.size() - 33; --i)
	{
		//cout << bitset<8>(msg.c_str()[i]) << endl;   VYPIS
		mojString += bitset<8>(msg.c_str()[i]).to_string();
	}
	
	cout << endl << "moje bitiky: " << mojString;

	return 0;
}