#include <iostream>
#include <vector>


void showMatrix(std::vector<std::vector<float>> A);
void showMatrix(std::vector<std::vector<float>> A){
    for(auto a : A){
        for(auto b : a){
            std::cout<<b<<" ";
        }
        std::cout<<std::endl;
    }
}


std::vector<std::vector<float>> matrixMultiplication(std::vector<std::vector<float>> A, std::vector<std::vector<float>> B);
std::vector<std::vector<float>> matrixMultiplication(std::vector<std::vector<float>> A, std::vector<std::vector<float>> B){
    
    int numLines = A.size();
    int numColums = B[0].size();
    int numMultiplication = A[0].size(); // This value will hold the 'n' of the matrix algorithm multiplication
    std::vector<std::vector<float>> C(numLines, std::vector<float>(numColums, 0.0f));

    for(int i = 0;i < numLines; i ++){
        for(int k = 0; k < numLines; k++){
            for(int j = 0; j < numMultiplication; j++){
                C[i][k] += A[i][j]*B[j][k];
            }
        }
    }

    return C;
}



int main(){
    std::vector<std::vector<float>> A = {
        {1.0, 2.0, 3.0},
        {4.0, 5.0, 6.0}
    };

    std::vector<std::vector<float>> B = {
        {7.0, 8.0},
        {9.0, 10.0},
        {11.0, 12.0}
    };


    return 0;
}