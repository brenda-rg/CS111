#ifndef DECODE_CPP
#define DECODE_CPP

#include "decode.h"

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
    std::cout << "--- Make verifyPubKey fucntion ---" << std::endl;
    if(findFactors(n,p,q)) {
        phi_n = findPhi_n(p,q);
    }
    
    return findFactors(n,p,q);
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

bool findD(int p) {
    std::cout << "--- Make findD function ---" << std::endl;
    return valid;
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

std::vector<int>& decrypt(int& m_num , int& d, const int& n, std::vector<int>& M ) {
    int m;
    for(int i = 0; i < m_num; i++) {
        cin >> m;
        int val = 1;
        d = 1031;
        while(d > 1) {
                if(d%2 == 0) {
                    m = fmod(pow(m,2),n);
                    d = d/2;
                }
                else {
                    val = val*m;
                    m = fmod(pow(m,2),n);
                    d = (d-1)/2;
                }
                if(val > n) {
                    val = val%n;
                }
                //cout << val << " " << d  << " " << m <<endl;
        }
        //cout << (val*m)%n << endl;
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