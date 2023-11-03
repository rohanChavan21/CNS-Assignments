#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <random>

using namespace std;

// Function for extended Euclidean Algorithm
int ansS, ansT;
int findGcdExtended(int r1, int r2, int s1, int s2, int t1, int t2) {
    int s = 0; // Declare 's' here
    int t = 0; // Declare 't' here

    if (r2 == 0) {
        ansS = s1;
        ansT = t1;
        return r1;
    }

    int q = r1 / r2;
    int r = r1 % r2;

    s = s1 - q * s2;
    t = t1 - q * t2;

    return findGcdExtended(r2, r, s2, s, t2, t);
}

int modInverse(int A, int M) {
    int x, y;
    int g = findGcdExtended(A, M, 1, 0, 0, 1);
    if (g != 1) {
        cout << "Inverse doesn't exist";
        return 0;
    } else {
        int res = (ansS % M + M) % M;
        return res;
    }
}

long long powM(long long a, long long b, long long n) {
    if (b == 1)
        return a % n;
    long long x = powM(a, b / 2, n);
    x = (x * x) % n;
    if (b % 2)
        x = (x * a) % n;
    return x;
}

int findGCD(int num1, int num2) {
    if (num1 == 0)
        return num2;
    return findGCD(num2 % num1, num1);
}

// Function to convert text to a numerical representation
vector<int> textToNumbers(const string& text) {
    vector<int> numbers;
    for (char c : text) {
        numbers.push_back(static_cast<int>(c));
    }
    return numbers;
}

// Function to convert numerical representation to text
string numbersToText(const vector<int>& numbers) {
    string text;
    for (int num : numbers) {
        text.push_back(static_cast<char>(num));
    }
    return text;
}

// Code to demonstrate RSA algorithm for text
int main() {
    // Two random prime numbers (modify these)
    long long p, q;
    cout << "Enter two prime numbers (p and q): ";
    cin >> p >> q;

    // First part of public key: n = p * q
    long long n = p * q;

    // Finding other part of public key (e stands for encrypt)
    long long e;
    cout << "Enter the public exponent (e): ";
    cin >> e;

    // Private key (d stands for decrypt)
    long long d = modInverse(e, (p - 1) * (q - 1));

    // Display public and private keys
    cout << "Public key: <" << e << "," << n << ">" << endl;
    cout << "Private key: <" << d << "," << n << ">" << endl;

    // Message to be encrypted
    string message;
    cout << "Enter the message to encrypt: ";
    cin.ignore(); // Ignore any previous newline character
    getline(cin, message);

    // Convert message to numbers
    vector<int> numbers = textToNumbers(message);

    // Encrypt the message
    vector<int> encrypted_message;
    for (int num : numbers) {
        long long c = powM(num, e, n);
        encrypted_message.push_back(static_cast<int>(c));
    }

    cout << "Encrypted Message: ";
    for (int num : encrypted_message) {
        cout << num << " ";
    }
    cout << endl;

    // Decrypt the message
    vector<int> decrypted_numbers;
    for (int num : encrypted_message) {
        long long m = powM(num, d, n);
        decrypted_numbers.push_back(static_cast<int>(m));
    }

    string decrypted_message = numbersToText(decrypted_numbers);
    cout << "Decrypted Message: " << decrypted_message << endl;

    return 0;
}
