#include "unit_tests.h"

TestSuite(student_suite, .timeout=TEST_TIMEOUT);

/*
Test(student_suite, name_of_test, .description="description of test") {
    // Steps of unit test go here
}
*/

//-----tests on homework document-----

//encrypt tests

Test(student_suite, encrypt_basic_abc, .description="Encrypt basic letters abc with key = 2") {
    const char *plaintext = "abc";
    char ciphertext_act[50] = "I can store any text here!";
    int count_act = encrypt(plaintext, ciphertext_act, 2);
    char *ciphertext_exp = "cde__EOM__";
    int count_exp = 3;
    cr_expect_str_eq(ciphertext_act, ciphertext_exp, "ciphertext was: %s\nbut it should have been: %s", ciphertext_act, ciphertext_exp);
    cr_expect_eq(count_act, count_exp, "Return value was %d, but it should have been %d.\n", count_act, count_exp);
}

Test(student_suite, encrypt_mixed_letters, .description="Encrypt mixed case letters Ayb with key = 3") {
    const char *plaintext = "Ayb";
    char ciphertext_act[50] = "I can store any text here!";
    int count_act = encrypt(plaintext, ciphertext_act, 3);
    char *ciphertext_exp = "Dbe__EOM__";
    int count_exp = 3;
    cr_expect_str_eq(ciphertext_act, ciphertext_exp, "ciphertext was: %s\nbut it should have been: %s", ciphertext_act, ciphertext_exp);
    cr_expect_eq(count_act, count_exp, "Return value was %d, but it should have been %d.\n", count_act, count_exp);
}


Test(student_suite, encrypt_key_zero, .description="Encrypt with the key = 0") {
    const char *plaintext = "CS";
    char ciphertext_act[50] = "I can store any text here!";
    int count_act = encrypt(plaintext, ciphertext_act, 0);
    char *ciphertext_exp = "CS__EOM__";
    int count_exp = 2;
    cr_expect_str_eq(ciphertext_act, ciphertext_exp, "ciphertext was: %s\nbut it should have been: %s", ciphertext_act, ciphertext_exp);
    cr_expect_eq(count_act, count_exp, "Return value was %d, but it should have been %d.\n", count_act, count_exp);
}

Test(student_suite, encrypt_empty_string, .description="Encrypt empty string returns 0 and only EOM marker") {
    const char *plaintext = "";
    char ciphertext_act[50] = "I can store any text here!";
    int count_act = encrypt(plaintext, ciphertext_act, 4);
    char *ciphertext_exp = "__EOM__";
    int count_exp = 0;
    cr_expect_str_eq(ciphertext_act, ciphertext_exp, "ciphertext was: %s\nbut it should have been: %s", ciphertext_act, ciphertext_exp);
    cr_expect_eq(count_act, count_exp, "Return value was %d, but it should have been %d.\n", count_act, count_exp);
}

//decrypt tests

Test(student_suite, decrypt_basic_cde, .description="Decrypt basic cde__EOM__ with key = 2") {
    const char *ciphertext = "cde__EOM__";
    char plaintext_act[50] = "I can store any text here";
    int count_act = decrypt(ciphertext, plaintext_act, 2);
    char *plaintext_exp = "abc";
    int count_exp = 3;
    cr_expect_str_eq(plaintext_act, plaintext_exp, "plaintext was: %s\nbut it should have been: %s", plaintext_act, plaintext_exp);
    cr_expect_eq(count_act, count_exp, "Return value was %d, but it should have been %d.\n", count_act, count_exp);
}

Test(student_suite, decrypt_mixed_letters, .description="Decrypt basic Dbe__EOM__ with key = 3") {
    const char *ciphertext = "Dbe__EOM__";
    char plaintext_act[50] = "I can store any text here";
    int count_act = decrypt(ciphertext, plaintext_act, 3);
    char *plaintext_exp = "Ayb";
    int count_exp = 3;
    cr_expect_str_eq(plaintext_act, plaintext_exp, "plaintext was: %s\nbut it should have been: %s", plaintext_act, plaintext_exp);
    cr_expect_eq(count_act, count_exp, "Return value was %d, but it should have been %d.\n", count_act, count_exp);
}


Test(student_suite, decrypt_empty_marker, .description="Decrypt eom marker with any key returns empty string") {
    const char *ciphertext = "__EOM__";
    char plaintext_act[50] = "I can store any text here";
    int count_act = decrypt(ciphertext, plaintext_act, 5);
    char *plaintext_exp = "";
    int count_exp = 0;
    cr_expect_str_eq(plaintext_act, plaintext_exp, "plaintext was: %s\nbut it should have been: %s", plaintext_act, plaintext_exp);
    cr_expect_eq(count_act, count_exp, "Return value was %d, but it should have been %d.\n", count_act, count_exp);
}

//----addtional tests----

Test(student_suite, encrypt_null_input, .description="Encrypt returns -2 if plaintext or ciphertext is NULL") {
    char ciphertext_act[50] = "I can store any text here";
    int count_act_1 = encrypt(NULL, ciphertext_act, 2);
    int count_act_2 = encrypt("abc", NULL, 2);
    int count_exp = -2;
    cr_expect_eq(count_act_1, count_exp, "Return value was %d, but it should have been %d.\n", count_act_1, count_exp);
    cr_expect_eq(count_act_2, count_exp, "Return value was %d, but it should have been %d.\n", count_act_2, count_exp);
}

Test(student_suite, decrypt_null_input, .description="Decrypt returns -2 if ciphertext or plaintext is NULL") {
    char plaintext_act[50] = "I can store any text here";
    int count_act_1 = decrypt(NULL, plaintext_act, 2);
    int count_act_2 = decrypt("abc__EOM__", NULL, 2);
    int count_exp = -2;
    cr_expect_eq(count_act_1, count_exp, "Return value was %d, but it should have been %d.\n", count_act_1, count_exp);
    cr_expect_eq(count_act_2, count_exp, "Return value was %d, but it should have been %d.\n", count_act_2, count_exp);
}


Test(student_suite, encrypt_insufficient_memory, .description="Encrypt returns -1 if ciphertext buffer too small for __EOM__") {
    const char *plaintext = "abc";
    char ciphertext_act[6];  //too small for stirng cde__EOM__
    int count_act = encrypt(plaintext, ciphertext_act, 2);
    int count_exp = -1;
    cr_expect_eq(count_act, count_exp, "Return value was %d, but it should have been %d.\n", count_act, count_exp);
}

Test(student_suite, encrypt_wrap, .description="Encrypt characters that are uppercase, lowercase, and digit to wrap around with key = 2") {
    const char *plaintext = "Zz9";
    char ciphertext_act[50] = "I can store any text here";
    int count_act = encrypt(plaintext, ciphertext_act, 2);
    char *ciphertext_exp = "Bb1__EOM__";
    int count_exp = 3;
    cr_expect_str_eq(ciphertext_act, ciphertext_exp, "ciphertext was: %s\nbut it should have been: %s", ciphertext_act, ciphertext_exp);
    cr_expect_eq(count_act, count_exp, "Return value was %d, but it should have been %d.\n", count_act, count_exp);
}

Test(student_suite, decrypt_wrap, .description="Decrypt lowercase, uppercase, and digit wth key = 2") {
    const char *ciphertext = "Bb1__EOM__";
    char plaintext_act[50] = "I can store any text here";
    int count_act = decrypt(ciphertext, plaintext_act, 2);
    char *plaintext_exp = "Zz9";
    int count_exp = 3;
    cr_expect_str_eq(plaintext_act, plaintext_exp, "plaintext was: %s\nbut it should have been: %s", plaintext_act, plaintext_exp);
    cr_expect_eq(count_act, count_exp, "Return value was %d, but it should have been %d.\n", count_act, count_exp); 
}

Test(student_suite, encrypt_large_key, .description="Encrypt basic ABC with key = 27 which should behave like key = 1") {
    const char *plaintext = "ABC";
    char ciphertext_act[50] = "I can store any text here";
    int count_act = encrypt(plaintext, ciphertext_act, 27);
    char *ciphertext_exp = "BCD__EOM__";
    int count_exp = 3;
    cr_expect_str_eq(ciphertext_act, ciphertext_exp, "ciphertext was: %s\nbut it should have been: %s", ciphertext_act, ciphertext_exp);
    cr_expect_eq(count_act, count_exp, "Return value was %d, but it should have been %d.\n", count_act, count_exp);
}

