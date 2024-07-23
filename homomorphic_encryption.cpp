#include "seal/seal.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;
using namespace seal;

void performOperation(const string &operation, const string &inputFile, const string &outputFile);

int main(int argc, char *argv[]) {
    if (argc < 4) {
        cerr << "Usage: " << argv[0] << " <operation> <local path of my file> <output_file>" << endl;
        return 1;
    }
    // local paths 

    string operation = argv[1];
    string inputFile = argv[2];
    string outputFile = argv[3];

    performOperation(operation, inputFile, outputFile);

    return 0;
}

void performOperation(const string &operation, const string &inputFile, const string &outputFile) {
    ifstream pub_key_file("shared_data/public_key.bin", ios::binary);
    PublicKey public_key;
    public_key.load(pub_key_file);
    pub_key_file.close();

    ifstream sec_key_file("shared_data/secret_key.bin", ios::binary);
    SecretKey secret_key;
    secret_key.load(sec_key_file);
    sec_key_file.close();

    ifstream relin_key_file("shared_data/relin_keys.bin", ios::binary);
    RelinKeys relin_keys;
    relin_keys.load(relin_key_file);
    relin_key_file.close();

    EncryptionParameters parms(scheme_type::ckks);
    size_t poly_modulus_degree = 16384;
    parms.set_poly_modulus_degree(poly_modulus_degree);
    parms.set_coeff_modulus(CoeffModulus::Create(poly_modulus_degree, {60, 40, 40, 60}));
    auto context = SEALContext::Create(parms);

    ifstream input(inputFile, ios::binary);
    Ciphertext encrypted_data;
    encrypted_data.load(context, input);
    input.close();

    Evaluator evaluator(context);
    Ciphertext result;
    if (operation == "add") {
        evaluator.add(encrypted_data, encrypted_data, result); 
    } else if (operation == "multiply") {
        evaluator.multiply(encrypted_data, encrypted_data, result); 
    } else {
        cerr << "Unsupported operation: " << operation << endl;
        return;
    }

    ofstream output(outputFile, ios::binary);
    result.save(output);
    output.close();
}
