#include <iostream>
#include <string>

using namespace std;

// Function to encrypt a message using the Caesar cipher
string encryptCaesarCipher(string message, int key) {
    string encryptedMessage = "";

    for (char c : message) {
        if (isalpha(c)) {
            char shift = isupper(c) ? 'A' : 'a';
            encryptedMessage += (char)(((c - shift + key) % 26) + shift);
        } else {
            encryptedMessage += c; // Leave non-alphabetic characters unchanged
        }
    }

    return encryptedMessage;
}

// Function to decrypt a message encrypted with the Caesar cipher
string decryptCaesarCipher(string encryptedMessage, int key) {
    return encryptCaesarCipher(encryptedMessage, 26 - key); // Decrypt by shifting in the opposite direction
}

int main() {
    string message;
    int key;

    cout << "Enter a message: ";
    getline(cin, message);

    cout << "Enter the Caesar cipher key (an integer): ";
    cin >> key;

    string encryptedMessage = encryptCaesarCipher(message, key);
    string decryptedMessage = decryptCaesarCipher(encryptedMessage, key);

    cout << "Encrypted message: " << encryptedMessage << endl;
    cout << "Decrypted message: " << decryptedMessage << endl;

    return 0;
}
