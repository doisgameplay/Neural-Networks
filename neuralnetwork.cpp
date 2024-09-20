#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <random>
#include <utility>  
#include "module.h"

const int m = 2;
const int width = 60;
const float n = 2;
const float step = 1;


bool f1(int x, int y);
bool f1(int x, int y){
    x-=20;
    y-=20;
    return(x*x + y*y < 100);
}


bool f2(int x, int y);
bool f2(int x, int y){
    x -= 40;
    y -= 15;                  ; 
    return (x*x + y*y < 100);
}


void fillData(std::vector<std::vector<std::vector<float>>>& entradas, std::vector<std::vector<std::vector<float>>>& saidasEsperadas);
void fillData(std::vector<std::vector<std::vector<float>>>& entradas, std::vector<std::vector<std::vector<float>>>& saidasEsperadas){
    
    for(float x = 0.0 ; x < width; x+= step){
        for(float y = 0.0; y < width; y+= step){
            if(f1(x,y)){
                saidasEsperadas.push_back({{1}});
                entradas.push_back(matrixTranspose({{1,x,y}}));
            }else if(f2(x,y)){
                saidasEsperadas.push_back({{-1}});
                entradas.push_back(matrixTranspose({{1,x,y}}));
            }
        }       
    }
    
}   


int sinal(float v);
int sinal(float v){
    if(v <= 0){
        return(-1);
    }
    return 1;   
}


int main(){

    std::vector<std::vector<float>> v = matrixTranspose({{0,1,0,0,1,0}});
    std::vector<std::vector<std::vector<float>>> entradas;
    std::vector<std::vector<std::vector<float>>> saidasEsperadas;
    std::vector<std::vector<float>> W = matrixTranspose({std::vector<float>(m+1, 0)});
    fillData(entradas, saidasEsperadas); //This function will fill create some data using the funciotns f1 and f2
    
    std::vector<std::pair<std::vector<std::vector<float>>, std::vector<std::vector<float>>>> pares;                 
    for (size_t i = 0; i < entradas.size(); ++i) {
        pares.emplace_back(entradas[i], saidasEsperadas[i]);
    }

    std::random_device rd;
    std::mt19937 g(rd());

    // Embaralha o vetor de vetores
    std::shuffle(pares.begin(), pares.end(), g);

    for (size_t i = 0; i < pares.size(); ++i) {
        entradas[i] = pares[i].first;
        saidasEsperadas [i] = pares[i].second;
    }

    for(int tempo = 0; tempo < entradas.size(); tempo ++){
        float v = matrixMultiplication(matrixTranspose(W), entradas[tempo])[0][0];
        int y = sinal(v);
        W = matrixSum(W, matrixScalar(entradas[tempo], n*(saidasEsperadas[tempo][0][0] - y)));       
        
        //std::cout<<"W :: ";
        //showMatrix(matrixTranspose(W));
        //std::cout<<"passo: "<<tempo<<std::endl;
        //showMatrix(matrixMultiplication(matrixTranspose(W), entradas[tempo]));
        //std::cout<<"W :: ";
        //showMatrix(matrixTranspose(W));
        //std::cout<<"X :: ";
        //showMatrix(matrixTranspose(entradas[tempo]));
        //          std::cout<<"d  :: ";
        //          std::cout<<(saidasEsperadas[tempo][0][0])<<std::endl;
        //if(saidasEsperadas[tempo][0][0] != y){
        //    std::cout<<"W :: ";
        //    showMatrix(matrixTranspose(W));
        //}
        //std::cout<<std::endl<<std::endl;
    }   
    showMatrix(matrixTranspose(W)); 

    return 0;
}