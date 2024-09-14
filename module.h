#ifndef MODULE_H
#define MODULE_H

#include <vector>

std::vector<std::vector<float>> matrixSum(std::vector<std::vector<float>> A, std::vector<std::vector<float>> B);
std::vector<std::vector<float>> matrixScalar(std::vector<std::vector<float>> A, float scalar);
std::vector<std::vector<float>> createMemoryMatrix(std::vector<std::vector<std::vector<float>>> X, std::vector<std::vector<std::vector<float>>> Y);
float distanceBetweenVectors(std::vector<float> a, std::vector<float> b);
float EuclidianNorm(std::vector<float> v);
void showMatrix(std::vector<std::vector<float>> matrix);
std::vector<std::vector<float>> matrixMultiplication(std::vector<std::vector<float>> A, std::vector<std::vector<float>> B);
std::vector<std::vector<float>> matrixTranspose(std::vector<std::vector<float>> A);
std::vector<std::vector<float>> matrixOpposite(std::vector<std::vector<float>> A);

#endif 