#include <iostream>
#include <string>
#include <vector>
#include <cctype>

const char encoder[5][5] = { {'A','B','C','D','E'},
                            {'F','G','H','I','K'},
                            {'L','M','N','O','P'},
                            {'Q','R','S','T','U'},
                            {'V','W','X','Y','Z'} };

void prepare_key(const std::string& key, std::vector<std::vector<char>>& table) {
    // Initialize the table with the key
    int row = 0, col = 0;
    std::vector<bool> used(26, false);

    for (char c : key) {
        if (c == 'J') c = 'I'; // Replace 'J' with 'I'

        if (!used[c - 'A']) {
            table[row][col] = c;
            used[c - 'A'] = true;
            col++;

            if (col == 5) {
                col = 0;
                row++;
            }
        }
    }

    // Fill in the remaining characters
    for (char c = 'A'; c <= 'Z'; c++) {
        if (c == 'J') continue;

        if (!used[c - 'A']) {
            table[row][col] = c;
            col++;

            if (col == 5) {
                col = 0;
                row++;
            }
        }
    }
}

void get_positions(const std::vector<std::vector<char>>& table, char c, int& row, int& col) {
    for (row = 0; row < 5; row++) {
        for (col = 0; col < 5; col++) {
            if (table[row][col] == c)
                return;
        }
    }
}

std::string playfair_encrypt(const std::string& plaintext, const std::vector<std::vector<char>>& table) {
    std::string ciphertext;
    size_t len = plaintext.length();
    for (size_t i = 0; i < len; i += 2) {
        char a = plaintext[i];
        char b = (i + 1 < len) ? plaintext[i + 1] : 'X'; // Append 'X' if the length is odd
        if (a == 'J') a = 'I'; // Replace 'J' with 'I'
        if (b == 'J') b = 'I'; // Replace 'J' with 'I'
        int row_a, col_a, row_b, col_b;
        get_positions(table, a, row_a, col_a);
        get_positions(table, b, row_b, col_b);
        if (row_a == row_b) {
            ciphertext += table[row_a][(col_a + 1) % 5];
            ciphertext += table[row_b][(col_b + 1) % 5];
        }
        else if (col_a == col_b) {
            ciphertext += table[(row_a + 1) % 5][col_a];
            ciphertext += table[(row_b + 1) % 5][col_b];
        }
        else {
            ciphertext += table[row_a][col_b];
            ciphertext += table[row_b][col_a];
        }
    }
    return ciphertext;
}

std::string playfair_decrypt(const std::string& ciphertext, const std::vector<std::vector<char>>& table) {
    std::string plaintext;
    size_t len = ciphertext.length();
    for (size_t i = 0; i < len; i += 2) {
        char a = ciphertext[i];
        char b = ciphertext[i + 1];
        int row_a, col_a, row_b, col_b;
        get_positions(table, a, row_a, col_a);
        get_positions(table, b, row_b, col_b);
        if (row_a == row_b) {
            plaintext += table[row_a][(col_a + 4) % 5];
            plaintext += table[row_b][(col_b + 4) % 5];
        }
        else if (col_a == col_b) {
            plaintext += table[(row_a + 4) % 5][col_a];
            plaintext += table[(row_b + 4) % 5][col_b];
        }
        else {
            plaintext += table[row_a][col_b];
            plaintext += table[row_b][col_a];
        }
    }
    return plaintext;
}

int main() {
    std::string key, plaintext;

    // Get the key and plaintext from the user
    std::cout << "Enter the key: ";
    std::cin >> key;
    std::cout << "Enter the plaintext: ";
    std::cin.ignore(); // Clear the newline character
    std::getline(std::cin, plaintext);

    // Ensure the key and plaintext are in uppercase
    for (char& c : key)
        c = std::toupper(c);
    for (char& c : plaintext)
        c = std::toupper(c);

    // Create the Playfair table
    std::vector<std::vector<char>> table(5, std::vector<char>(5));
    prepare_key(key, table);

    // Encrypt
    std::string ciphertext = playfair_encrypt(plaintext, table);
    std::cout << "Encrypted: " << ciphertext << std::endl;

    // Decrypt
    std::string decrypted = playfair_decrypt(ciphertext, table);
    std::cout << "Decrypted: " << decrypted << std::endl;

    return 0;
}
