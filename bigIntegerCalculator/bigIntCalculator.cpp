//============================================================================
// Name        : bigIntCalculator.cpp
// Author      : Shuo Wang (github.com/surew963)
// Version     : 2016-10-01
// Description : Sudoku Game (generator and solver) in C++
//============================================================================
#include <iostream>
#include <cstring>
using namespace std;

string remove0(string s) {
	while (s[0] == '0' && s.length()>1)
            s = s.substr(1);
	return s;
}

string operator+(string sa, string sb) {
	int nsa = sa.length(), nsb = sb.length();
	int nmax = nsa > nsb ? nsa : nsb;
	int ida, idb, idc = 0;
	char c[nmax+2];
	c[nmax+1] = '\0';
	for (int i = 1; i < nmax+2; i++) {
		if (nsa >= i) ida = sa[nsa-i]-'0';
		else ida = 0;
		if (nsb >= i) idb = sb[nsb-i]-'0';
		else idb = 0;
		idc += ida+idb;
		c[nmax+1-i] = '0'+idc%10;
                idc /= 10;
	}
	string sc = string(c);
	sc = remove0(sc);
	return sc;
}

bool compare(string sa, string sb) {
	int na = sa.length();
	if (na < sb.length()) return true;
	if (na == sb.length())
		for (int i = 0; i < na; i++){
		if(sa[i] < sb[i]) return true;
		if(sa[i] > sb[i]) return false;
	}
	return false;
}

string operator-(string sa, string sb) {
	int na = sa.length(), nb = sb.length();
	int slmax = na, idr = 0, idam = 0, ida, idb, idc;
	bool neg = compare(sa,sb);
	if (neg) swap(sa, sb);
	char c[slmax+1];
	c[slmax] = '\0';
	for (int i = 1; i < slmax+1; i++) {
                ida = sa[na-i]-'0';
		if (nb >= i) idb = sb[nb-i]-'0';
		else idb = 0;
		if (ida < idb+idam) idr = 10;
		idc = ida-idb+idr-idam;
		if (ida < idb+idam) {
                    idr = 0;
                    idam = 1;
                }
		else idam = 0;
		c[slmax-i] = '0'+idc;
	}
	string sc = string(c);
	sc = remove0(sc);
	if (neg) sc = '-'+sc;
	return sc;
}

string operator*(string sa,string sb){
	string sdbm, res = "0";
	if (compare(sa, sb)) swap(sa, sb);
	int nb = sb.length();
	for (int i = 1; i <= nb; i++){
                int idb = sb[nb-i]-'0';
		sdbm = "0";
		for (int j = 1; j <= idb; j++) 
                    sdbm = sdbm+sa;
		int k = i;
		while (k-- > 1){
                    sdbm += '0';
                }
		res = res+sdbm;
	}
	return res;
}

string operator/(string sa,string sb) {
	string sc = "0", s10 = "10";
	if (compare(sa, sb)) return sc;
	int na = sa.length(), nb = sb.length();
	int nc = na-nb;
	string sat = sa.substr(0, nb-1);
	for (int i = 0; i <= nc; i++) {
		sat = sat*s10 + sa.substr(nb+i-1, 1);
		if (compare(sat, sb)) sc += '0';
		else {
                    int dt = 0;
                        while (!compare(sat, sb)) {
				sat = sat-sb;
                                dt++;
			}
                        sc +='0'+dt;
		}
	}
	sc = remove0(sc);
	return sc;
}

int main() {
    char a[101], b[101];
    char o;
    string sc;
	cout << "Input integers must be positive and less than 100 digits."
                << endl << "Please enter 3 lines." << endl <<
        "Line 1: a big integer." << endl <<
        "Line 2: +,-,* or /. " << endl << 
        "Line 3: a big integer."
        << endl << endl;
    cin >> a >> o >> b;
    string sa = string(a);
    string sb = string(b);
    if (o == '+') sc = sa+sb;
    else if (o == '-') sc = sa-sb;
    else if (o == '*') sc = sa*sb;
    else if (o == '/') sc = sa/sb;
    cout << "="<< endl << sc << endl;
    return 0;
}

