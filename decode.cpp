#ifndef DECODE_CPP
#define DECODE_CPP

#include "decode.h"
#include <numeric>

/*
**Equations to have **
n = pq --> where p and q are prime numbers
phi(n) = (p-1)(q-1)
d = (e^-1)mod(phi(n))
or
(ed)mod(phi(n)) = 1
C^d rem n = D(C)
M^e rem n = E(M)
Secret key = (d,n)
e(mod(phi(n))) = 1
*/

bool valid = 0;

bool verifyPubKey(int& e, int& n, int& d, int& phi_n, int& p, int& q) {
    std::cout << "--- Finish verifyPubKey function ---" << std::endl;
    if(findFactors(n,p,q) == 0) {
        return false;
    }
    phi_n = findPhi_n(p,q);
    if(checkRPrime(e,phi_n) == 0) {
        return false;
    }
    d = findD(e, phi_n);

    return true;
}

bool findFactors(const int& n, int& p, int&q) {
    for (int i = 2; i <= n/2; i++) {
        if(n%i == 0) {
            p = i;
            q = n/i;
            if(checkIsPrime(p) && checkIsPrime(q)) {
                return true;
            }
        }
    }
    return false;
}

int findPhi_n(const int& p, const int& q) {
    return (p-1)*(q-1);
}

bool checkRPrime(const int& e, const int& phi_n) {
    if(gcd(e,phi_n) == 1) {
        return true;
    }
    return false;
}

int findD(const int& e, const int& phi_n) {
    //Needs to be fixed
    return (1 + phi_n) / e ;
}

//code taken from geeksforgeeks :: https://www.geeksforgeeks.org/prime-numbers/
bool checkIsPrime(int& val) {
    if(val <= 1) {
        val = 0;
        return false;
    }
    for(int i = 2; i <= sqrt(val); i++) {
        if(val%i == 0) {
            val = 0;
            return false;
        }
    }
    return true;
}

std::vector<int>& decrypt(const int& m , const int& d, const int& n, std::vector<int>& M ) {
    int crypt;
    for(int i = 0; i < m; i++) {
        cin >> crypt;
        int d_2 = d;
        int val = 1;
        while(d_2 > 1) {
                if(d_2%2 == 0) {
                    crypt = fmod(pow(crypt,2),n);
                    d_2 = d_2/2;
                }
                else {
                    val = val*crypt;
                    crypt = fmod(pow(crypt,2),n);
                    d_2 = (d_2-1)/2;
                }
                if(val > n) {
                    val = val%n;
                }
        }
        M.push_back((val*m)%n);
    }
    return M;
}

std::vector<char>& convertToChar(const vector<char> Legend, std::vector<int>& M, std::vector<char>& M_e) {
    for(int i = 0; i < M.size(); i++) {
        M_e.push_back(Legend.at(M.at(i)-5));
    }
    return M_e;
}

void outputM(const std::vector<int>& M) {
    for (int i = 0; i < M.size(); i++) {
        cout << M.at(i);
        if (i < M.size()-1) {
            cout << " ";
        }
    }
}

void outputM_e(const vector<char>& M_e) {
    for (int i = 0; i < M_e.size(); i++) {
        cout << M_e.at(i);
    }
}

#endif //DECODE_CPP