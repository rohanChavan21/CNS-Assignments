#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// Function to generate the Playfair key matrix from the key
vector<vector<char>> generateKeyMatrix(const string& key) {
    string alphabet = "ABCDEFGHIKLMNOPQRSTUVWXYZ"; // Exclude 'J'

    // Remove duplicates from the key and append the alphabet
    string keyWithoutDuplicates = "";
    for (char c : key) {
        if (keyWithoutDuplicates.find(c) == string::npos) {
            keyWithoutDuplicates += c;
        }
    }
    string combinedKey = keyWithoutDuplicates + alphabet;

    // Create a 5x5 key matrix
    vector<vector<char>> keyMatrix(5, vector<char>(5));

    int index = 0;
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            keyMatrix[i][j] = combinedKey[index++];
        }
    }

    return keyMatrix;
}

// Function to encrypt a message using the Playfair cipher
string encryptPlayfairCipher(const string& message, const string& key) {
    vector<vector<char>> keyMatrix = generateKeyMatrix(key);
    string plaintext = message;
    string ciphertext = "";

    // Remove spaces and convert to uppercase
    plaintext.erase(remove_if(plaintext.begin(), plaintext.end(), ::isspace), plaintext.end());
    transform(plaintext.begin(), plaintext.end(), plaintext.begin(), ::toupper);

    // Replace 'J' with 'I' in the plaintext
    replace(plaintext.begin(), plaintext.end(), 'J', 'I');

    int messageLength = plaintext.length();
    int index = 0;

    while (index < messageLength) {
        char first = plaintext[index];
        char second = (index + 1 < messageLength) ? plaintext[index + 1] : 'X'; // Use 'X' as filler if needed

        int row1, col1, row2, col2;

        // Find the positions of the letters in the key matrix
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 5; j++) {
                if (keyMatrix[i][j] == first) {
                    row1 = i;
                    col1 = j;
                }
                if (keyMatrix[i][j] == second) {
                    row2 = i;
                    col2 = j;
                }
            }
        }

        char encryptedFirst, encryptedSecond;

        // Apply the Playfair rules to encrypt the digram
        if (row1 == row2) {
            // Same row, shift right
            encryptedFirst = keyMatrix[row1][(col1 + 1) % 5];
            encryptedSecond = keyMatrix[row2][(col2 + 1) % 5];
        } else if (col1 == col2) {
            // Same column, shift down
            encryptedFirst = keyMatrix[(row1 + 1) % 5][col1];
            encryptedSecond = keyMatrix[(row2 + 1) % 5][col2];
        } else {
            // Forming a rectangle, swap horizontally
            encryptedFirst = keyMatrix[row1][col2];
            encryptedSecond = keyMatrix[row2][col1];
        }

        ciphertext += encryptedFirst;
        ciphertext += encryptedSecond;

        index += 2;
    }

    return ciphertext;
}

// Function to decrypt a message encrypted with the Playfair cipher
string decryptPlayfairCipher(const string& ciphertext, const string& key) {
    vector<vector<char>> keyMatrix = generateKeyMatrix(key);
    string decryptedMessage = "";

    int ciphertextLength = ciphertext.length();
    int index = 0;

    while (index < ciphertextLength) {
        char first = ciphertext[index];
        char second = ciphertext[index + 1];

        int row1, col1, row2, col2;

        // Find the positions of the letters in the key matrix
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 5; j++) {
                if (keyMatrix[i][j] == first) {
                    row1 = i;
                    col1 = j;
                }
                if (keyMatrix[i][j] == second) {
                    row2 = i;
                    col2 = j;
                }
            }
        }

        char decryptedFirst, decryptedSecond;

        // Apply the Playfair rules to decrypt the digram
        if (row1 == row2) {
            // Same row, shift left
            decryptedFirst = keyMatrix[row1][(col1 + 4) % 5];
            decryptedSecond = keyMatrix[row2][(col2 + 4) % 5];
        } else if (col1 == col2) {
            // Same column, shift up
            decryptedFirst = keyMatrix[(row1 + 4) % 5][col1];
            decryptedSecond = keyMatrix[(row2 + 4) % 5][col2];
        } else {
            // Forming a rectangle, swap horizontally
            decryptedFirst = keyMatrix[row1][col2];
            decryptedSecond = keyMatrix[row2][col1];
        }

        decryptedMessage += decryptedFirst;
        decryptedMessage += decryptedSecond;

        index += 2;
    }

    // Remove any trailing 'X' fillers
    size_t pos = decryptedMessage.find_last_not_of('X');
    if (pos != string::npos) {
        decryptedMessage = decryptedMessage.substr(0, pos + 1);
    }

    return decryptedMessage;
}


int main() {
    string message, key;

    cout << "Enter a message: ";
    getline(cin, message);

    cout << "Enter the encryption key: ";
    cin >> key;

    string encryptedMessage = encryptPlayfairCipher(message, key);
    string decryptedMessage = decryptPlayfairCipher(encryptedMessage, key);

    cout << "Encrypted message: " << encryptedMessage << endl;
    cout << "Decrypted message: " << decryptedMessage << endl;

    return 0;
}
