#include <iostream>
#include "module.h"
#include <cmath>

std::vector<std::vector<float>> matrixSum(std::vector<std::vector<float>> A, std::vector<std::vector<float>> B);
std::vector<std::vector<float>> matrixSum(std::vector<std::vector<float>> A, std::vector<std::vector<float>> B){
    int numLines = A.size();
    int numColumns = B[0].size();
    std::vector<std::vector<float>> C(numLines, std::vector<float>(numColumns, 0.0f));

    for(int i = 0; i < numLines; i ++){
        for(int k = 0; k < numColumns; k++){
            C[i][k] = A[i][k] + B[i][k];
        }
    }

    return C;
}


std::vector<std::vector<float>> matrixOpposite(std::vector<std::vector<float>> A);
std::vector<std::vector<float>> matrixOpposite(std::vector<std::vector<float>> A){
    for(auto& line : A){
        for(auto& element : line){
            element *= -1;
        }
    }
    return A;
}


std::vector<std::vector<float>> matrixTranspose(std::vector<std::vector<float>> A);
std::vector<std::vector<float>> matrixTranspose(std::vector<std::vector<float>> A){
    int numLines = A.size();
    int numColumns = A[0].size();
    std::vector<std::vector<float>> B(numColumns, std::vector<float>(numLines, 0.0f));

    for(int line = 0; line < numLines; line++){
        for(int column = 0; column < numColumns; column++){
            B[column][line] = A[line][column];            
        }
    }

    return B;
}


std::vector<std::vector<float>> matrixMultiplication(std::vector<std::vector<float>> A, std::vector<std::vector<float>> B);
std::vector<std::vector<float>> matrixMultiplication(std::vector<std::vector<float>> A, std::vector<std::vector<float>> B){
    
    int numLines = A.size();
    int numColumns = B[0].size();
    int numMultiplication = A[0].size(); // This value will hold the 'n' of the matrix algorithm multiplication
    std::vector<std::vector<float>> C(numLines, std::vector<float>(numColumns, 0.0f));

    for(int i = 0;i < numLines; i ++){
        for(int k = 0; k < numLines; k++){
            for(int j = 0; j < numMultiplication; j++){
                C[i][k] += A[i][j]*B[j][k];
            }
        }
    }

    return C;
}


void showMatrix(std::vector<std::vector<float>> matrix);
void showMatrix(std::vector<std::vector<float>> matrix){
 
    for(auto line : matrix){
        for(auto value : line){
            std::cout<<value<<" ";
        }
        std::cout<<std::endl;
    }
}


float EuclidianNorm(std::vector<float> v);
float EuclidianNorm(std::vector<float> v){
    float norm = 0.0f;
    for(auto element : v ){
        element *= element;
        norm += element;
    }
    norm = sqrt(norm);
    
    return norm;
}


float distanceBetweenVectors(std::vector<float> a, std::vector<float> b);
float distanceBetweenVectors(std::vector<float> a, std::vector<float> b){
    float distance = 0.0f;
    distance = EuclidianNorm(matrixSum({a}, matrixOpposite({b}))[0]);
    return distance;
}


std::vector<std::vector<float>> createMemoryMatrix(std::vector<std::vector<std::vector<float>>> X, std::vector<std::vector<std::vector<float>>> Y);
std::vector<std::vector<float>> createMemoryMatrix(std::vector<std::vector<std::vector<float>>> X, std::vector<std::vector<std::vector<float>>> Y){
 
    //filling the memoryMatrix with zeros:
    int numLines = Y[0][0].size();
    int numColumns = matrixTranspose(X[0]).size();
    std::vector<std::vector<float>> memoryMatrix(numLines, std::vector<float>(numColumns, 0.0f));

    for(int operation = 0; operation < X.size(); operation++){
        memoryMatrix = matrixSum(matrixMultiplication(matrixTranspose(Y[operation]),X[operation]), memoryMatrix);
    }

    return memoryMatrix;
}


std::vector<std::vector<float>> matrixScalar(std::vector<std::vector<float>> A, float scalar);
std::vector<std::vector<float>> matrixScalar(std::vector<std::vector<float>> A, float scalar){
    for(auto& line: A){
        for(auto& element : line){
            element *= scalar;
        }
    }
    return A;
}
