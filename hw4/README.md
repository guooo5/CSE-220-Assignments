# CSE-220-Homework4
Name: Guo Chen
ID: 115922846

This is a program that encrypts/decrypts alphanumerical messages using the Ceasar Cipher Algorithm. You can skip over/ ignore non alphanumeric characters.

NOTE: All test cases are tested using Criterion. There is no main.c file. To test on your machine use:

    make 
    make test

# Guidelines:

1. The following content is a sample to follow. Describe the function in your own words. Design and describe your testcases under the student suite section.

2. Please use gcc compiler to compile the code. To ensure your code is compiled with the C99 standard, you should use the -std=c99 flag when compiling with GCC.

3. The submitted code shouldn't produce any errors or warning messages.

4. Write brief comments in the source file to explain your thinking and work. AI generated comments or content will lead to severe penalty. You may use AI to aid your learning.

# Information about encrypt()/decrypt()

// Give short description about the function you implemented

## int encrypt(const char *plaintext, char *ciphertext, int key)

    Purpose: to perform the caesar cipher encryption on strings, we right shift each character's by key positions. 

    Parameters: plaintext - the string we are to encrypt
                ciphertext - the string the function writes into as it does the encryption with the plaintext
                key - how much to shift the characters by 

    Return Value: the sucessful number of characters that were encrypted (or 0 if plaintext length is 0 or all alphanumerics)
                  -1 if we couldn't encode eom marker
                  -2 if any parameter is null 

## int decrypt(const char *ciphertext, char *plaintext, int key) 

    Purpose: to perform the caesar cipher decryption on strings, we left shift each character's by key positions. 
     
    Parameters: plaintext - the string we are to encrypt
                ciphertext - the string the function writes into as it does the encryption with the plaintext
                key - how much to shift the characters by 
    
    Return Value: the sucessful number of characters that were encrypted (or 0 if plaintext length is 0 or all alphanumerics)
                  -1 if ciphertext is mising EOM, ciphertext is invalid
                  -2 if any parameter is NULL

 ## Your Helper function (arguments,...)

    Purpose:
  
    Parameters:

# Test Cases

## Student Suite

Includes various test cases to validate the `encrypt` and `decrypt` functions under different scenarios.

### Encrypt Tests
### Decrypt Tests


## Base Suite

Includes baseline tests provided by TAs to validate the `encrypt` and `decrypt` functions.

### Encrypt Tests

1. **Test Case: "System Fundamentals"**
   - **Plaintext**: "System Fundamentals"
   - **Ciphertext**: "Tztufn Gvoebnfoubmt__EOM__"
   - **Description**: Tests if a full plaintext message can be encrypted with key `1`.

2. **Test Case: "Cse220"**
   - **Plaintext**: "Cse220"
   - **Ciphertext**: "Dtf331__EOM__"
   - **Description**: Tests if a full plaintext message with numbers can be encrypted with key `1`.

#### Decrypt Tests

1. **Test Case: "Tztufn Gvoebnfoubmt__EOM__"**
   - **Ciphertext**: "Tztufn Gvoebnfoubmt__EOM__"
   - **Plaintext**: "System Fundamentals"
   - **Description**: Tests if a full ciphertext message can be decrypted with key `1`.

2. **Test Case: "Dtf331__EOM__"**
   - **Ciphertext**: "Dtf331__EOM__"
   - **Plaintext**: "Cse220"
   - **Description**: Tests if a full ciphertext message with numbers can be decrypted with key `1`.
