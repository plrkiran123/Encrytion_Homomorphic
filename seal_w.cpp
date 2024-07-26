#include "seal_wrapper.h"
#include <seal/seal.h>
#include <string>
#include <cstring>

using namespace seal;
using namespace std;

char* encrypt(const char* plaintext) {
    
    // Sample encryption 
    string encrypted_text = string(plaintext) + "_encrypted";
    char* encrypted = (char*)malloc(encrypted_text.size() + 1);
    strcpy(encrypted, encrypted_text.c_str());
    return encrypted;
}

char* decrypt(const char* ciphertext) {
    // Sample decryption 
    string decrypted_text = string(ciphertext);
    decrypted_text = decrypted_text.substr(0, decrypted_text.size() - 10);
    char* decrypted = (char*)malloc(decrypted_text.size() + 1);
    strcpy(decrypted, decrypted_text.c_str());
    return decrypted;
}
