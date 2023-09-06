#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// Function to encrypt a message using the Columnar Transposition Cipher
string encryptColumnarTranspositionCipher(const string& message, const string& key) {
    string encryptedMessage;
    int keyLength = key.length();
    int messageLength = message.length();

    // Calculate the number of rows needed
    int numRows = (messageLength + keyLength - 1) / keyLength;

    // Create a matrix to hold the message
    vector<vector<char>> matrix(numRows, vector<char>(keyLength, ' '));

    // Fill in the matrix with the message
    int index = 0;
    for (int col = 0; col < keyLength; col++) {
        for (int row = 0; row < numRows; row++) {
            if (index < messageLength) {
                matrix[row][col] = message[index++];
            }
        }
    }

    // Read the matrix in column order according to the key
    for (char c : key) {
        int col = key.find(c);
        for (int row = 0; row < numRows; row++) {
            encryptedMessage += matrix[row][col];
        }
    }

    return encryptedMessage;
}

// Function to decrypt a message encrypted with the Columnar Transposition Cipher
string decryptColumnarTranspositionCipher(const string& encryptedMessage, const string& key) {
    string decryptedMessage;
    int keyLength = key.length();
    int messageLength = encryptedMessage.length();

    // Calculate the number of rows needed
    int numRows = (messageLength + keyLength - 1) / keyLength;

    // Calculate the number of columns needed
    int numCols = keyLength;

    // Create a matrix to hold the message
    vector<vector<char>> matrix(numRows, vector<char>(numCols, ' '));

    // Calculate the number of characters in the last row
    int lastRowChars = messageLength % numRows;

    // Determine how many rows have one more character
    int rowsWithExtraChar = min(lastRowChars, numRows - 1);

    // Calculate the number of rows with one less character
    int rowsWithOneLessChar = numRows - rowsWithExtraChar;

    // Fill in the matrix with the encrypted message
    int index = 0;
    for (char c : key) {
        int col = key.find(c);
        int numRowsForCol = (col < rowsWithExtraChar) ? numRows : rowsWithOneLessChar;
        for (int row = 0; row < numRowsForCol; row++) {
            matrix[row][col] = encryptedMessage[index++];
        }
    }

    // Read the matrix in row order
    for (int row = 0; row < numRows; row++) {
        for (int col = 0; col < numCols; col++) {
            decryptedMessage += matrix[row][col];
        }
    }

    return decryptedMessage;
}

int main() {
    string message, key;

    cout << "Enter a message: ";
    getline(cin, message);

    cout << "Enter the encryption key: ";
    cin >> key;

    string encryptedMessage = encryptColumnarTranspositionCipher(message, key);
    string decryptedMessage = decryptColumnarTranspositionCipher(encryptedMessage, key);

    cout << "Encrypted message: " << encryptedMessage << endl;
    cout << "Decrypted message: " << decryptedMessage << endl;

    return 0;
}
