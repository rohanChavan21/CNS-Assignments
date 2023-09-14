#include <bits/stdc++.h>
using namespace std;

string format(string &str) {
    stringstream res;
    for (auto ch : str) {
        if (ch != ' ') {
            res << (char)tolower(ch);
        }
    }
    return res.str();
}

string encrypt(string &plain, string &key) {
    vector<vector<char>> matrix(key.size());

    int rowNumber = 0;
    int flag = 1;
    for (int i = 0; i < plain.size(); i++) {
        matrix[rowNumber].push_back(plain[i]);
        rowNumber += flag;
        if (rowNumber == 0)
            flag = 1;

        if (rowNumber == key.size() - 1)
            flag = -1;
    }

    stringstream cipher;
    for (int i = 0; i < key.size(); i++) {
        for (int j = 0; j < matrix[i].size(); j++)
            cipher << char(matrix[i][j]);
    }
    return cipher.str();
}

string decrypt(string &cipher, string &key) {
    vector<vector<int>> matrixDecry(key.size());
    int rowNumber = 0;
    int flag = 1;

    int n = cipher.length();

    for (int i = 0; i < n; i++) {
        matrixDecry[rowNumber].push_back(i);
        rowNumber += flag;
        if (rowNumber == (key.size() - 1))
            flag = -1;
        if (rowNumber == 0)
            flag = 1;
    }

    vector<int> mapping;
    for (int i = 0; i < key.size(); i++) {
        for (int j = 0; j < matrixDecry[i].size(); j++)
            mapping.push_back(matrixDecry[i][j]);
    }

    map<int, char> m;
    for (int i = 0; i < n; i++)
        m[mapping[i]] = cipher[i];

    stringstream plain;
    for (int i = 0; i < n; i++)
        plain << char(m[i]);

    return plain.str();
}

int main() {
    string input, key;
    
    cout << "Enter text to encrypt: ";
    getline(cin, input);
    input = format(input);

    cout << "Enter key (string): ";
    getline(cin, key);
    key = format(key);

    string cipher = encrypt(input, key);
    cout << "Encrypted text: " << cipher << endl;

    string decrypted = decrypt(cipher, key);
    cout << "Decrypted text: " << decrypted << endl;

    return 0;
}
