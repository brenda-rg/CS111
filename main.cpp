/* --- Want to do ----
    - Take in three integers (e,n,m (# of characters in message))
    - Take in the cyphertext #in case of our example 181

    - test if public key is valid --> if not output "Public Key is not valid!" & quit [program]
    - decode message
    - output p,q,phi(n), d
    - on newline output decoded msg in ints
    - on newline output decoded msg in english **All chars should be uppercase
    - mapping assigned as stated A-Z = 5-30

*/


#include <iostream>
#include <cmath>
#include <vector>
#include <numeric>
//#include "decode.cpp"

using namespace std;

bool verifyPubKey(int& e, int& n, int& d, int& phi_n, int& p, int& q);

bool findFactors(const int& n, int& p, int&q);

int findPhi_n(const int& p, const int& q);

bool checkRPrime(const int& e, const int& phi_n);

int findD(const int& e, const int& phi_n);


int extendedEuclid(int a, int b, int& x, int& y);


bool checkIsPrime(int& val);

std::vector<int>& decrypt(const int& m, const int& d, const int& n, std::vector<int>& M );

std::vector<char>& convertToChar(const std::vector<char> Legend,std::vector<int>& M, std::vector<char>& M_e);

void outputM(const std::vector<int>& M);

void outputM_e(const std::vector<char>& M_e);

int main() {

    //-- declare & initialize vars --
    int e,n,m,p,q,phi_n,d = 0;
    std::vector<int> M;
    std::vector<char> M_e;
    const std::vector<char> Legend{'A', 'B', 'C', 'D', 'E', 'F','G','H', 'I',
     'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U',
      'V', 'W', 'X', 'Y', 'Z', ' ', '\"', ',', '.', '\''};

    //remove for turnin 
    //std::cout << "Please enter  e, n (the public key for RSA), and m (the number of characters in the message)" << std::endl;

    //------- take in inputs --------
    std::cin >> e >> n >> m;

    //-- test if Public Key is Valid --
    if (verifyPubKey(e, n, d, phi_n, p, q) == 0) {
        std::cout << "Public key is not valid!";
    }
    else {
    //Decrypt Message
    M = decrypt(m,d,n,M);
    M_e = convertToChar(Legend, M, M_e);

    //-- Output message in numbers and english
    std::cout << p << ' ' << q << ' ' << phi_n << ' ' << d << std::endl;
    outputM(M);
    std::cout << std::endl;
    outputM_e(M_e);
    }

    return 0;
}
bool verifyPubKey(int& e, int& n, int& d, int& phi_n, int& p, int& q) {
    if(findFactors(n,p,q) == 0) {
        return false;
    }
    phi_n = findPhi_n(p,q);
    if(checkRPrime(e,phi_n) == 0) {
        return false;
    }
    d = findD(e,phi_n);

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
    int x,y;
    return extendedEuclid(e,phi_n,x,y);
}


int extendedEuclid(int a, int b, int& x, int& y) 
{ 
    if (a == 0) 
    { 
        x = 0; 
        y = 1; 
        return x; 
    } 

    int x1, y1;
    int calc = extendedEuclid(b%a, a, x1, y1); 

    x = y1 - (b/a) * x1; 
    y = x1; 

    return x; 
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
        M.push_back((val*crypt)%n);
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
        cout << M.at(i) << " ";
        // if (i < M.size()-1) {
        //     cout << " ";
        // }
    }
}

void outputM_e(const vector<char>& M_e) {
    for (int i = 0; i < M_e.size(); i++) {
        cout << M_e.at(i);
    }
}