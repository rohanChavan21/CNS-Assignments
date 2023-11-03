#include <bits/stdc++.h>
using namespace std;
long long powM(long long a, long long b, long long n){
if (b == 1){
return a % n;
}
long long x = powM(a, b / 2, n);
x = (x * x) % n;
if (b % 2){
x = (x * a) % n;
}
return x;
}
bool isPrimitiveRoot(long long alpha, long long q){
map<long long, int> m;
for (long long i = 1; i < q; i++){
long long x = powM(alpha, i, q);
if (m.find(x) != m.end()){
return 0;
}
m[x] = 1;
}
return 1;
}
int main(){
long long q, alpha;
q = 17; // A prime number q is taken
alpha = 5; // A primitive root of q
if (isPrimitiveRoot(alpha, q) == 0){
cout << "alpha is not primitive root of q";
return 0;
}else {
cout << alpha << " is primitive root of " << q << endl;
}
long long xa, ya;
xa = 4; // xa is the chosen private key
ya = powM(alpha, xa, q); // public key of alice
cout << "private key of A is " << xa << endl;
cout << "public key of A is " << ya << endl << endl;
long long xb, yb;
xb = 6; // xb is the chosen private key
yb = powM(alpha, xb, q); // public key of bob
cout << "private key of B is " << xb << endl;
cout << "public key of B is " << yb << endl << endl;
//key generation
long long k1, k2;
k1 = powM(yb, xa, q); // Secret key for Alice
k2 = powM(ya, xb, q); // Secret key for Bob
cout << "generated key by A is " << k1 << endl;
cout << "generated key by B is " << k2 << endl;
return 0;
}