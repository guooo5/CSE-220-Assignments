#include "global.h"
#include "unit_tests.h"

TestSuite(student_suite, .timeout=TEST_TIMEOUT);

/*
Test(student_suite, name_of_test, .description="description of test") {
    // Steps of unit test go here
}
*/


// ---- sparse matrix tests ----
Test(student_suite, SparseMatrix_notSparse, .description="Matrix that is not sparse") {
    int** M = initializeMatrix(4, 4, (int[]){1,0,2,0, 0,3,4,0, 5,6,7,0, 8,9,0,0});
    int** S_act = initializeMatrix(3, 4, (int[]){0,0,0,0,0,0,0,0,0,0,0,0});
    int ret_act = SparseMatrix(4, 4, M, S_act);
    int ret_exp = -1; 
    cr_expect_eq(ret_act, ret_exp, "Return value was %d, but it should have been %d.\n", ret_act, ret_exp);
    freeMatrix(4, M); freeMatrix(3, S_act);
}

Test(student_suite, SparseMatrix_single_row, .description="SparseMatrix with single row matrix") {
    int** M = initializeMatrix(1, 5, (int[]){0,0,7,0,9});
    int** S_act = initializeMatrix(3, 5, (int[]){0,0,0,0,0,0,0,0,0,0,0,0,0,0,0});
    int** S_exp = initializeMatrix(3, 5, (int[]){0,0,0,0,0, 2,4,0,0,0, 7,9,0,0,0});
    int ret_act = SparseMatrix(1, 5, M, S_act);
    int ret_exp = 2;  
    cr_expect_eq(ret_act, ret_exp,"Return value was %d, expected %d.\n", ret_act, ret_exp);
    cr_assert(areMatricesEqual(S_act, S_exp, 3, 5), "Contents of matrix incorrect. See student_tests.c for expected values.");
    freeMatrix(1, M);freeMatrix(3, S_act);freeMatrix(3, S_exp);
}

Test(student_suite, SparseMatrix_not_sparse_3x3, .description="3x3 matrix that is not sparse") {

    int** M = initializeMatrix(3, 3, (int[]){1,0,2, 0,3,0, 4,5,0});
    int** S_act = initializeMatrix(3, 3, (int[]){0,0,0,0,0,0,0,0,0});
    int ret_act = SparseMatrix(3, 3, M, S_act);
    int ret_exp = -1; 
    cr_expect_eq(ret_act, ret_exp, "Return value was %d, expected %d.\n", ret_act, ret_exp);
    freeMatrix(3, M);freeMatrix(3, S_act);
}


//---- addition function test ----
Test(student_suite, Addition_incompatible_too_small, .description="Incompatible matrices with A too small for full overlap") {
    int** M = initializeMatrix(3, 3, (int[]){1,2,3, 4,5,6, 7,8,9});
    int** N = initializeMatrix(2, 4, (int[]){9,8,7,6, 5,4,3,2});
    int** A_act = initializeMatrix(1, 2, (int[]){0,0});
    int** A_exp = initializeMatrix(1, 2, (int[]){10,10});
    int ret_act = Addition(3, 3, 2, 4, 1, 2, M, N, A_act);
    int ret_exp = -2;
    cr_expect_eq(ret_act, ret_exp, "Return value was %d, expected %d.\n", ret_act, ret_exp);
    cr_assert(areMatricesEqual(A_act, A_exp, 1, 2), "Contents of matrix incorrect. See student_tests.c for expected values.");
    freeMatrix(3, M);freeMatrix(2, N);freeMatrix(1, A_act);freeMatrix(1, A_exp);
}


Test(student_suite, Addition_compatible_oversized, .description="Compatible matrices with oversized result matrix A") {
    int** M = initializeMatrix(2, 2, (int[]){1,2, 3,4});
    int** N = initializeMatrix(2, 2, (int[]){5,6, 7,8});
    int** A_act = initializeMatrix(3, 3, (int[]){0,0,0, 0,0,0, 0,0,0});
    int** A_exp = initializeMatrix(3, 3, (int[]){6,8,0, 10,12,0, 0,0,0});
    int ret_act = Addition(2, 2, 2, 2, 3, 3, M, N, A_act);
    int ret_exp = 2;
    cr_expect_eq(ret_act, ret_exp, "Return value was %d, expected %d.\n", ret_act, ret_exp);
    cr_assert(areMatricesEqual(A_act, A_exp, 3, 3),"Contents of matrix incorrect. See student_tests.c for expected values.");
    freeMatrix(2, M);freeMatrix(2, N);freeMatrix(3, A_act);freeMatrix(3, A_exp);
}


//----multiplication function test----
Test(student_suite, multiplication_case_zero_dim, .description="Zero-dimension matrices should return 1") {
    int** M = initializeMatrix(0, 0, NULL);
    int** N = initializeMatrix(0, 0, NULL);
    int** A_act = initializeMatrix(0, 0, NULL);
    int D[6] = {0,0,0,0,0,0};
    int ret_act = Multiplication(D[0],D[1],D[2],D[3],D[4],D[5], M, N, A_act);
    int ret_exp = 1; 
    cr_expect_eq(ret_act, ret_exp,"Return value was %d, but it should have been %d.\n", ret_act, ret_exp);
    freeMatrix(0, M); freeMatrix(0, N); freeMatrix(0, A_act);
}


Test(student_suite, multiplication_case_single_cell, .description="1x1 matrices") {
    int** M = initializeMatrix(1, 1, (int[]){7});
    int** N = initializeMatrix(1, 1, (int[]){3});
    int** A_act = initializeMatrix(1, 1, (int[]){0});
    int** A_exp = initializeMatrix(1, 1, (int[]){21});

    int D[6] = {1,1,1,1,1,1};
    int ret_act = Multiplication(D[0],D[1],D[2],D[3],D[4],D[5], M, N, A_act);
    int ret_exp = 1;

    cr_expect_eq(ret_act, ret_exp, "Return value was %d, but it should have been %d.\n", ret_act, ret_exp);
    cr_assert(areMatricesEqual(A_act, A_exp, 1, 1), "Contents of matrix incorrect. See student_tests.c for expected values.");
    freeMatrix(1, M); freeMatrix(1, N); freeMatrix(1, A_act); freeMatrix(1, A_exp);
}


//---- transpose function test ----
Test(student_suite, transpose_case_oversized, .description="Transpose with oversized output matrix") {
    int** M = initializeMatrix(2, 2, (int[]){1, 2, 3, 4});
    int** A_act = initializeMatrix(3, 3, (int[]){0,0,0,0,0,0,0,0,0});
    int** A_exp = initializeMatrix(3, 3, (int[]){1,3,0,2,4,0,0,0,0});
    int D[4] = {2,2,3,3};
    int ret_act = Transpose(D[0],D[1],D[2],D[3],M,A_act);
    int ret_exp = 2;
    cr_expect_eq(ret_act, ret_exp,"Return value was %d, but it should have been %d.\n", ret_act, ret_exp);
    cr_assert(areMatricesEqual(A_act, A_exp, 3, 3),"Contents of matrix incorrect. See student_tests.c for expected values.");
    freeMatrix(2, M); freeMatrix(3, A_act); freeMatrix(3, A_exp);
}


Test(student_suite, transpose_case_zero_dim, .description="Transpose of zero-dimension matrix") {
    int** M = initializeMatrix(0, 3, NULL);  
    int** A_act = initializeMatrix(3, 0, NULL);
    int D[4] = {0,3,3,0};
    int ret_act = Transpose(D[0],D[1],D[2],D[3],M,A_act);
    int ret_exp = 1;
    cr_expect_eq(ret_act, ret_exp,"Return value was %d, but it should have been %d.\n", ret_act, ret_exp);
    freeMatrix(0, M); freeMatrix(3, A_act);
}









