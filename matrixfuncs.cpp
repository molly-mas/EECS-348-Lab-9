#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>

static int size;


void deleteMatrix(int **matrix1, int size){
    for(int i= 0; i <size; i++){
        delete[] matrix1[i];
    }
    delete matrix1;
}

void read_file(std::string filename, int** matrixA, int** matrixB){
    std::ifstream theFile (filename);
    int size;
    if (!theFile){
        throw new std::runtime_error("this file cant be found");
    }

    theFile >> size;
    
    for(int i= 0; i < size; i++){
        for(int j = 0; j < size; j++){
            theFile >> matrixA[i][j];
        }
    }
    for(int i= 0; i < size; i++){
        for(int j = 0; j < size; j++){
            theFile >> matrixB[i][j];
        }
    }
    theFile.close();
}

int get_size(std::string filename){
    std::ifstream theFile(filename);
    if (!theFile.is_open()){
        std::cerr << "This file cant be found\n";
        throw std::exception();
    }
int size;
    theFile >> size;
    return size;
}

void print_matrix(int**matrix1, std::string name, int size){
    std::cout << name << ":\n";
    for(int i= 0; i < size; i++){
        for(int j = 0; j < size; j++){
            std::cout << matrix1[i][j] << "\t";
        }
        std::cout << "\n";
    }
    std::cout << "\n\n";
}

int **createMatrix(int size){
    int **matrix = new int*[size];
    for (int i= 0; i < size; i++){
        matrix[i] = new int[size];
    }
    return matrix;
}

void addMatrixs(int**matrix1, int**matrix2, int size){
    int** added = createMatrix(size);
    for(int i = 0; i <size; i++){
        for(int j = 0; j < size; j++){
            int val = matrix1[i][j] + matrix2[i][j];
            added[i][j] = val;
        }
    }
    print_matrix(added, "added", size);
    deleteMatrix(added, size);
}

void multMatrixs(int**matrix1, int**matrix2, int size){
    int** mult = createMatrix(size);
    int val = 0;
    for(int i = 0; i <size; i++){
        for(int j = 0; j < size; j++){
            for (int k = 0; k < size; k++){
                val = matrix1[i][k] * matrix2[k][j];
                val += val;
            }
            mult[i][j] = val;
            val = 0;
        }
    }
    print_matrix(mult, "mult", size);
    deleteMatrix(mult, size);
}

void get_diagSum(int**matrix1, int size, std::string name){
    int val = 0;
    for(int j = 0; j < size; j++){
        val += matrix1[j][j];
    }

    std::cout << name << "'s Sum of diagonal elements: " << val << "\n";
}

void swap_rows(int** matrix1, std::string name, int size, int index1, int index2){
    if (index1 >= size || index2 >= size || index1 < 0 || index2 < 0){
        std::cerr << "Invalid Index\n";
        throw std::exception();
    }
    int* temp1;
    temp1 = matrix1[index1];
    matrix1[index1] = matrix1[index2];
    matrix1[index2] = temp1;

    std::cout << "Swapped rows" << "\n";
    print_matrix(matrix1, name, size);
    matrix1[index2] = matrix1[index1];
    matrix1[index1] = temp1;
}

void swap_col(int** matrix1, std::string name, int size, int index1, int index2){
    if (index1 >= size || index2 >= size || index1 < 0 || index2 < 0){
        std::cerr << "Invalid Index\n";
        throw std::exception();
    }
    for(int i = 0; i < size; i++){
        int temp;
        temp = matrix1[i][index1];
        matrix1[i][index1] = matrix1[i][index2];
        matrix1[i][index2] = temp;
    }
    std::cout << "Swapped columns\n";
    print_matrix(matrix1, name, size);
    for(int i = 0; i < size; i++){
        int temp;
        temp = matrix1[i][index1];
        matrix1[i][index1] = matrix1[i][index2];
        matrix1[i][index2] = temp;
    }
}

void update_spot(int** matrix1, std::string name, int size, int index1, int index2, int value){
    if (index1 >= size || index2 >= size || index1 < 0 || index2 < 0){
         std::cerr << "Invalid Index\n";
        throw std::exception();
    }
    matrix1[index1][index2] = value;
        std::cout << "Updated: \n";
        print_matrix(matrix1, name, size);
}


//use std::cn >> var_name PUT A PRINT B4 this!


int main(){
    std::string file_name;
    std::cout << "Please enter the file name: ";
    std::cin >> file_name;
    std::cout << "\n";
    int n = get_size(file_name);
    int** matrixA = createMatrix(n);
    int** matrixB = createMatrix(n);
    read_file(file_name, matrixA, matrixB);
    print_matrix(matrixA, "matrixA", n );
    print_matrix(matrixB, "matrixB", n );
    addMatrixs(matrixA, matrixB, n);
    multMatrixs(matrixA, matrixB, n);
    get_diagSum(matrixA, n, "matrixA");
    get_diagSum(matrixB, n, "matrixB");
    int index1 =0;
    int index2 =0 ;
    int val =0;
    std::cout << "Please enter the first index to swap rows: ";
    std::cin >> index1;
    std::cout << "\n";
    std::cout << "Please enter the second index to swap rows: ";
    std::cin >> index2;
    std::cout << "\n";
    swap_rows(matrixA, "matrixA", n, index1, index2);
    std::cout << "Please enter the first index to swap rows: ";
    std::cin >> index1;
    std::cout << "\n";
    std::cout << "Please enter the first index to swap rows: ";
    std::cin >> index2;
    std::cout << "\n";
    swap_rows(matrixB, "matrixB", n, index1, index2);
    std::cout << "Please enter the first index to swap colums: ";
    std::cin >> index1;
    std::cout << "\n";
    std::cout << "Please enter the first index to swap colums: ";
    std::cin >> index2;
    std::cout << "\n";
    swap_col(matrixA, "matrixA", n, index1, index2);
    std::cout << "Please enter the first index to swap colums: ";
    std::cin >> index1;
    std::cout << "\n";
    std::cout << "Please enter the first index to swap colums: ";
    std::cin >> index2;
    std::cout << "\n";
    swap_col(matrixB, "matrixB", n, index1, index2);
    std::cout << "Please enter the first index to swap the item: ";
    std::cin >> index1;
    index1 = (int)index1;
    std::cout << "\n";
    std::cout << "Please enter the second index to swap the item: ";
    std::cin >> index2;
    index2 = (int)index2;
    std::cout << "\n";
    std::cout << "Please enter the value you want to be used to replace the index provided: ";
    std::cin >> val;
    std::cout << "\n";
    update_spot(matrixA, "matrixA",n,index1, index2, val);
    std::cout << "Please enter the first index to swap the item: ";
    std::cin >> index1;
    index1 = (int)index1;
    std::cout << "\n";
    std::cout << "Please enter the second index to swap the item: ";
    std::cin >> index2;
    std::cout << "\n";
    std::cout << "Please enter the value you want to be used to replace the index provided: ";
    std::cin >> val;
    std::cout << "\n";
    update_spot(matrixB, "matrixB",n,index1, index2, val);
    

}
