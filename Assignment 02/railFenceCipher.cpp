#include <iostream>
#include <string>

using namespace std;

// Function to encrypt a message using the Rail Fence Cipher
string encryptRailFenceCipher(const string& message, int rails) {
    string encryptedMessage;
    string railMatrix[rails];
    
    int row = 0;
    bool down = true;

    for (char c : message) {
        railMatrix[row] += c;
        
        if (row == 0) {
            down = true;
        } else if (row == rails - 1) {
            down = false;
        }

        if (down) {
            row++;
        } else {
            row--;
        }
    }

    for (int i = 0; i < rails; i++) {
        encryptedMessage += railMatrix[i];
    }

    return encryptedMessage;
}

// Function to decrypt a message encrypted with the Rail Fence Cipher
string decryptRailFenceCipher(const string& encryptedMessage, int rails) {
    string decryptedMessage;
    string railMatrix[rails];
    
    int messageLength = encryptedMessage.length();
    int railLengths[rails];
    
    int row = 0;
    bool down = true;

    // Calculate the length of each rail
    for (int i = 0; i < rails; i++) {
        railLengths[i] = 0;
    }

    for (int i = 0; i < messageLength; i++) {
        railLengths[row]++;
        
        if (row == 0) {
            down = true;
        } else if (row == rails - 1) {
            down = false;
        }

        if (down) {
            row++;
        } else {
            row--;
        }
    }

    // Fill in the rail matrix with the encrypted message
    row = 0;
    int index = 0;

    for (int i = 0; i < messageLength; i++) {
        railMatrix[row] += encryptedMessage[index++];
        
        if (row == 0) {
            down = true;
        } else if (row == rails - 1) {
            down = false;
        }

        if (down) {
            row++;
        } else {
            row--;
        }
    }

    // Decrypt the message
    row = 0;
    for (int i = 0; i < rails; i++) {
        decryptedMessage += railMatrix[i].substr(0, railLengths[i]);
        railMatrix[i].erase(0, railLengths[i]);
    }

    return decryptedMessage;
}

int main() {
    string message;
    int rails;

    cout << "Enter a message: ";
    getline(cin, message);

    cout << "Enter the number of rails: ";
    cin >> rails;

    string encryptedMessage = encryptRailFenceCipher(message, rails);
    string decryptedMessage = decryptRailFenceCipher(encryptedMessage, rails);

    cout << "Encrypted message: " << encryptedMessage << endl;
    cout << "Decrypted message: " << decryptedMessage << endl;

    return 0;
}
