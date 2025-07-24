#include "ceasar.h"

int encrypt(const char *plaintext, char *ciphertext, int key){

    //returns -2 if any of the plantext or ciphertext is null
    if (plaintext == NULL || ciphertext == NULL) return -2;

    int i = 0;
    int j = 0;
    int count = 0;

    while(plaintext[i] != '\0'){ //go through every character until we reaach null character
        char character = plaintext[i];

        //encrypton: get position of character, then add key positions to move right, then mod to take care of wrap arounds, then get the character back
        if (isupper(character)) { //encryption of uppercase character
            ciphertext[j] = ((character - 'A' + key) % 26) + 'A';
            count++;
        }
        else if (islower(character)) {//encryption of lowercase character
            ciphertext[j] = ((character - 'a' + key) % 26) + 'a';
            count++;
        }
        else if (isdigit(character)) {//encryption of digits
            ciphertext[j] = ((character - '0' + key) % 10) + '0';
            count++;
        }
        else {//skips through non alphanumerics
            ciphertext[j] = character;  
        }
        i++;
        j++; 

    }

    if (strlen("__EOM__") + j + 1 > strlen(ciphertext) + 7) return -1; //checks that there will be sufficient space to store eom marker

    strcpy(&ciphertext[j], "__EOM__"); //copies eom marker to the end of ciphertext
    j += 7; //since we added eom marker to ciphertext, increase 7 characters
    ciphertext[j] = '\0'; //puts null character at end of ciphertext

    return count;
}


int decrypt(const char *ciphertext, char *plaintext, int key) {

    //returns -2 if any of the plantext or ciphertext is null
    if (plaintext == NULL || ciphertext == NULL) return -2;

    //checks if eom exists
    int eom_found = 0;
    for (int i = 0; ciphertext[i] != '\0'; i++) {
        if (strncmp(&ciphertext[i], "__EOM__", 7) == 0) { //checks for 7 continuous characters that exactly equals the eom marker 
            eom_found = 1;
            break;
        }
    }
    if (!eom_found) return -1;


    int i = 0;
    int j = 0;
    int count = 0;

    while (strncmp(&ciphertext[i], "__EOM__", 7) != 0 && ciphertext[i] != '\0') { //goes through every character and decrypt until we the eom marker or the null character 
        char character = ciphertext[i];

        //decryption: get position of the character, then subtract key position to move left, then +26 to stay positive, then mod to take care of wrap arounds, then get the character back
        if (isupper(character)) {
            plaintext[j] = ((character - 'A' - key + 26) % 26) + 'A';
            count++;
        }
        else if (islower(character)) {
            plaintext[j] = ((character - 'a' - key + 26) % 26) + 'a';
            count++;
        }
        else if (isdigit(character)) {
            plaintext[j] = ((character - '0' - key + 10) % 10) + '0';
            count++;
        }
        else {
            plaintext[j] = character;

        }
        i++;
        j++;
    }

    plaintext[j] = '\0'; //make sure to null terminate plantext message
    return count;
}
