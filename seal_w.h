#ifndef SEAL_WRAPPER_H
#define SEAL_WRAPPER_H

#ifdef __cplusplus
extern "C" {
#endif

char* encrypt(const char* plaintext);
char* decrypt(const char* ciphertext);

#ifdef __cplusplus
}
#endif

#endif // SEAL_WRAPPER_H
