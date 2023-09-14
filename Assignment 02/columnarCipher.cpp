#include <iostream>
#include <string>
#include <map>

using namespace std;

void setPermutationOrder(const string& key, map<char, int>& keyMap) {
    for (int i = 0; i < key.length(); i++) {
        keyMap[key[i]] = i;
    }
}

string encryptMessage(const string& msg, const string& key, map<char, int>& keyMap) {
    int row, col, j;
    string cipher = "";
    
    col = key.length();
    row = msg.length() / col;
    
    if (msg.length() % col) {
        row += 1;
    }

    char matrix[row][col];

    for (int i = 0, k = 0; i < row; i++) {
        for (int j = 0; j < col; ) {
            if (msg[k] == '\0') {
                matrix[i][j] = '_';
                j++;
            }

            if (isalpha(msg[k]) || msg[k] == ' ') {
                matrix[i][j] = msg[k];
                j++;
            }
            k++;
        }
    }

    for (map<char, int>::iterator ii = keyMap.begin(); ii != keyMap.end(); ++ii) {
        j = ii->second;
        for (int i = 0; i < row; i++) {
            if (isalpha(matrix[i][j]) || matrix[i][j] == ' ' || matrix[i][j] == '_') {
                cipher += matrix[i][j];
            }
        }
    }

    return cipher;
}

string decryptMessage(const string& cipher, const string& key, map<char, int>& keyMap) {
    int col = key.length();
    int row = cipher.length() / col;
    char cipherMat[row][col];

    for (int j = 0, k = 0; j < col; j++) {
        for (int i = 0; i < row; i++) {
            cipherMat[i][j] = cipher[k++];
        }
    }

    int index = 0;
    for (map<char, int>::iterator ii = keyMap.begin(); ii != keyMap.end(); ++ii) {
        ii->second = index++;
    }

    char decCipher[row][col];

    for (int k = 0, l, j; key[k] != '\0'; k++) {
        l = keyMap[key[k]];
        for (int i = 0; i < row; i++) {
            decCipher[i][k] = cipherMat[i][l];
        }
    }

    string msg = "";
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            if (decCipher[i][j] != '_') {
                msg += decCipher[i][j];
            }
        }
    }
    return msg;
}

int main() {
    string message, key;

    cout << "Enter a message: ";
    getline(cin, message);

    cout << "Enter the encryption key: ";
    cin >> key;

    map<char, int> keyMap;
    setPermutationOrder(key, keyMap);

    string encryptedMessage = encryptMessage(message, key, keyMap);
    string decryptedMessage = decryptMessage(encryptedMessage, key, keyMap);

    cout << "Encrypted Message: " << encryptedMessage << endl;
    cout << "Decrypted Message: " << decryptedMessage << endl;

    return 0;
}
