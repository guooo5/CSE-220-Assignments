#include "global.h"



int SparseMatrix(int row, int col, int** M, int** S){
    //iterating through matrix M to get a counter of non-zero values
    int count = 0;
    for (int i = 0; i < row; i++){
        for (int j = 0; j < col; j++){
            if (*(*(M + i) + j) != 0){
                count++;
            }
        }
    }
    
    //get the max dimension 
    int m;
    if (row > col) m = row;
    else m = col;

    //if num of non-zero is greater than max dimension then not a sparse matrix
    if(count > m) return -1; 
    
    //filling in the sparse matrix 
    int index = 0;
    for (int i = 0; i < row; i++){
        for(int j = 0; j < col; j++){
            if (*(*(M + i) + j) != 0){
                *(*(S+0)+index) = i; //rows
                *(*(S+1)+index) = j; //columns
                *(*(S+2)+index) = *(*(M + i) + j); //values
                index++;

            }
        }
    }

    //number of non-zeros less than max dimension so add padding to remaining elements of sparse matrix 
    while (index < m) {
        *(*(S + 0) + index) = 0;
        *(*(S + 1) + index) = 0;
        *(*(S + 2) + index) = 0;
        index++;
    }

    return count;
    
}


int Addition(int RM, int CM, int RN, int CN, int RA, int CA, int** M, int** N, int** A) {
    //initialize matrix A to zeros
    for (int i = 0; i < RA; i++) {
        for (int j = 0; j < CA; j++) {
            *(*(A + i) + j) = 0;
        }
    }

    //checks that dimensions of M and N are compatible 
    if ((RM == RN) && (CM == CN)) {
        //checks that A has the same dimensions 
        if ((RA == RM) && (CA == CM)) {
            //first case: A is compatible so the result is stored in A
            for (int i = 0; i < RM; i++) {
                for (int j = 0; j < CM; j++) {
                    *(*(A + i) + j) = *(*(M + i) + j) + *(*(N + i) + j);
                }
            }
            return 1;

        } 
        else if ((RA >= RM) && (CA >= CM)) {
            //second case: A not compatible & oversized, so result is stored in A
            for (int i = 0; i < RM; i++) {
                for (int j = 0; j < CM; j++) {
                    *(*(A + i) + j) = *(*(M + i) + j) + *(*(N + i) + j);
                }
            }
            return 2;
        } 
        else {
            //third case: A not compatible & smaller, part of result is stored in A
            for (int i = 0; i < RA; i++) {
                for (int j = 0; j < CA; j++) {
                    *(*(A + i) + j) = *(*(M + i) + j) + *(*(N + i) + j);
                }
            }
            return -3;
        }
    } 
    else { //M and N are incompatible matrices

        //compute for the intersection of the matrices 
        int overlap_rows; 
        //find the smaller of both rows
        if (RM < RN) overlap_rows = RM;
        else overlap_rows = RN;

        int overlap_cols;
        //finds the smaller of both columns
        if (CM < CN) overlap_cols = CM;
        else overlap_cols = CN;


        if ((RA >= overlap_rows) && (CA >= overlap_cols)) {
            //fourth case: A is big enough to hold intersection
            for (int i = 0; i < overlap_rows; i++) {
                for (int j = 0; j < overlap_cols; j++) {
                    *(*(A + i) + j) = *(*(M + i) + j) + *(*(N + i) + j);
                }
            }
            return -1;
        } else {
            //fifth case: A is too small to hold so only hold what it can 
            for (int i = 0; i < RA; i++) {
                for (int j = 0; j < CA; j++) {
                    *(*(A + i) + j) = *(*(M + i) + j) + *(*(N + i) + j);
                }
            }
            return -2;
        }
    }
}


int Multiplication(int RM, int CM, int RN, int CN, int RA, int CA, int** M, int** N, int** A) {
    //initialize matrix A to zeros
    for (int i = 0; i < RA; i++) {
        for (int j = 0; j < CA; j++) {
            *(*(A + i) + j) = 0;
        }
    }

    //checks that dimensions of M and N are compatible (column of M = row of N)
    if (CM == RN) {
        //checks that A has the same dimensions 
        if ((RA == RM) && (CA == CN)) {
            //first case: A is compatible so the result is stored in A
            for (int i = 0; i < RM; i++) {
                for (int j = 0; j < CN; j++) {
                    int result = 0;
                    for (int k = 0; k < CM; k++) {
                        result += *(*(M + i) + k) * *(*(N + k) + j);
                    }
                    *(*(A + i) + j) = result;
                }
            }
            return 1;
        }
        else if ((RA >= RM) && (CA >= CN)) {
            //second case: A not compatible & oversized, so result is stored in A
            for (int i = 0; i < RM; i++) {
                for (int j = 0; j < CN; j++) {
                    int result = 0;
                    for (int k = 0; k < CM; k++) {
                        result += *(*(M + i) + k) * *(*(N + k) + j);
                    }
                    *(*(A + i) + j) = result;
                }
            }
            return 2;
        } 
        else {
            //third case: A not compatible & smaller, part of result is stored in A

            //finds the smaller row of M and A and use that as the intersection 
            int rows_to_compute;
            if (RA < RM) {
                rows_to_compute = RA;
            } else {
                rows_to_compute = RM;
            }

            //finds the smaller column of N and A and use that as intersection
            int cols_to_compute;
            if (CA < CN) {
                cols_to_compute = CA;
            } else {
                cols_to_compute = CN;
            }

            for (int i = 0; i < rows_to_compute; i++) {
                for (int j = 0; j < cols_to_compute; j++) {
                    int result = 0;
                    for (int k = 0; k < CM; k++) {
                        result += *(*(M + i) + k) * *(*(N + k) + j);
                    }
                    *(*(A + i) + j) = result;
                }
            }
            return -3;
        }
    } else {//M and N are incompatible matrices


        //find the smaller row between A and M to store computation
        int effective_rows;
        if (RA < RM) {
            effective_rows = RA;
        } else {
            effective_rows = RM;
        }

        //find the smaller column between A and N to store computation
        int effective_cols;
        if (CA < CN) {
            effective_cols = CA;
        } else {
            effective_cols = CN;
        }

        //goes over the rows and columns that are the intersections 
        for (int i = 0; i < effective_rows; i++) {
            for (int j = 0; j < effective_cols; j++) {
                //compute product 
                int result = 0;
                for (int k = 0; k < CM && k < RN; k++) { //since matrices are incompatible, we use k < CM and k < RN to say in bound
                    result += *(*(M + i) + k) * *(*(N + k) + j);
                }
                *(*(A + i) + j) = result; //store computed value in A[i][j]
            }
        }

        //determine the return code based on if A is smaller or bigger
        if (RA >= RM){
            if (CA >= CN){
                return -1;
            }else{
                return -2;
            }
        }
        else{
            return -2;
        }
    }
}



int Transpose(int RA, int RC, int RAT, int CAT, int** A, int** AT) {
    //initialize matrix AT to zeros
    for (int i = 0; i < RAT; i++) {
        for (int j = 0; j < CAT; j++) {
            *(*(AT + i) + j) = 0;
        }
    }

    //transpose top-left region
    for (int i = 0; i < RA; i++) {
        for (int j = 0; j < RC; j++) {
            if (j < RAT && i < CAT) {
                *(*(AT + j) + i) = *(*(A + i) + j);
            }
        }
    }

    //determine return code using nested if-else 
    if (RAT == RC) {
        if (CAT == RA) {
            return 1; //matrices are compatible 
        } else {
            if (CAT >= RA) {
                return 2; //not compatible, AT is oversized
            } else {
                return -1; //not compatible, AT holds intersection
            }
        }
    } else {
        if (RAT >= RC) {
            if (CAT >= RA) {
                return 2; //not compatible, AT is oversized
            } else {
                return -1; //not compatible, AT holds intersection
            }
        } else {
            return -1; //not compatible, AT holds intersection
        }
    }
}


// Helper functions for Testing
int** initializeMatrix(int n, int m, int* values){
    int** ret = (int**)malloc(n*sizeof(int*));
    for(int i=0; i<n; i++){
        ret[i] = (int*)malloc(m*sizeof(int));
    }
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            ret[i][j] = values[i*m+j];
        }
    }
    return ret;
}

void freeMatrix(int n, int** M){
    for(int i=0; i<n; i++){
        free(M[i]);
    }
    free(M);
}

#ifndef STUDENT_MAIN /* Do not remove this line*/
int main(int argc, char* argv[]){
    (void)argc;
	(void)argv;

    return 0;
}
#endif