#ifndef DECODE_H
#define DECODE_H

#include <cmath>
#include <iostream>
#include <vector>
using namespace std;

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

bool verifyPubKey(int e, int n, int d, int phi_n, int p, int q);

bool findFactors(const int& n, int& p, int&q);

bool findPhi_n(const int& p, const int& q, int& phi_n);

bool findD(int p);

bool checkIsPrime(const int& n);

std::vector<int>& decrypt(int& m, int& d, const int& n, std::vector<int>& M );

std::vector<char>& convertToChar(const std::vector<char> Legend,std::vector<int>& M, std::vector<char>& M_e);

void outputM(const std::vector<int>& M);

void outputM_e(const std::vector<char>& M_e);




#endif //DECODE_HPP