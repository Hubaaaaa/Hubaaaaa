#include <iostream>
#include <string>
#include <bitset>

using namespace std;

string encrypt(const string& text, const string& key) {
    string result;
    size_t textLength = text.length();
    size_t keyLength = key.length();

    string binaryText;
    string binaryKey;
    string binaryResult;

    for (size_t i = 0; i < textLength; i++) {
        char textChar = text[i];
        char keyChar = key[i % keyLength]; // Repeating key if it's shorter

        // Perform bitwise XOR between the text and key characters
        char encryptedChar = textChar ^ keyChar;

        // Convert the text character, key character, and result to binary
        binaryText += bitset<8>(textChar).to_string() + " ";
        binaryKey += bitset<8>(keyChar).to_string() + " ";
        binaryResult += bitset<8>(encryptedChar).to_string() + " ";
    }

    result += "Plaintext (in binary): " + binaryText + "\n";
    result += "Key (in binary):       " + binaryKey + "\n";
    result += "Result (in binary):    " + binaryResult + "\n";

    return result;
}

int main() {
    string plaintext, key;

    cout << "Enter the plaintext: ";
    getline(cin, plaintext);
    cout << "Enter the key: ";
    getline(cin, key);

    string ciphertext;

    if (key.length() >= plaintext.length()) {
        // If the key is longer or equal to the plaintext, encrypt using the key
        ciphertext = encrypt(key, plaintext);
    }
    else {
        // If the key is shorter, encrypt using the plaintext
        cout<<"The Key is shorter than PlainText : " <<key + plaintext << " " << endl;
    }

    cout << ciphertext;

    return 0;
}
