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
#include "decode.cpp"

using namespace std;

int main() {
    int e,n,m,p,q,phi_n,d = 0;
    std::vector<int> M;
    std::vector<char> M_e;
    const std::vector<char> Legend{'A', 'B', 'C', 'D', 'E', 'F','G','H', 'I',
     'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U',
      'V', 'W', 'X', 'Y', 'Z', ' ', '\"', ',', '.', '\''};

    std::cout << "Please enter  e, n (the public key for RSA), and m (the number of characters in the message)" << std::endl;
    std::cin >> e >> n >> m;

    std::cout << verifyPubKey(e, n, d, phi_n, p, q) << std::endl;
    M = decrypt(m,d,n,M);
    M_e = convertToChar(Legend, M, M_e);
    outputM(M);
    std::cout << std::endl;
    outputM_e(M_e);

    return 0;
}