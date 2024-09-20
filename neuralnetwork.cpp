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
    x -= 40;
    y -= 200;                  
    return (x*x + y*y < 1000);
}


bool f2(int x, int y);
bool f2(int x, int y){
    x -= 40;
    y -= 150;                  
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
    W[0][0] = width;
    
    std::vector<std::pair<std::vector<std::vector<float>>, std::vector<std::vector<float>>>> pares;                 
    for (size_t i = 0; i < entradas.size(); ++i) {
        pares.emplace_back(entradas[i], saidasEsperadas[i]);
    }

    std::random_device rd; // Seed
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

        

    int r = 2;
    sf::RenderWindow window(sf::VideoMode(width,width), "NEURAL NETWORK");
    sf::VertexArray vertex(sf::Quads, entradas.size()*4);
    for(int i = 0; i < entradas.size(); i++){
        //std::cout<<entradas[i][1][0]<<" - "<<entradas[i][2][0]<<std::endl;
        vertex[i*4 + 0].position = sf::Vector2f(entradas[i][1][0] - r, entradas[i][2][0] - r );
        vertex[i*4 + 1].position = sf::Vector2f(entradas[i][1][0] + r, entradas[i][2][0] - r );
        vertex[i*4 + 2].position = sf::Vector2f(entradas[i][1][0] + r, entradas[i][2][0] + r );
        vertex[i*4 + 3].position = sf::Vector2f(entradas[i][1][0] - r, entradas[i][2][0] + r );
        for(int j = 0; j < 4 ; j++){

        if(saidasEsperadas[i][0][0] == 1){vertex[4 * i + j].color = sf::Color(189, 210, 166);}else{vertex[4*i + j].color = sf::Color(255, 169, 135);}
        }
    }

    int tempo2 = 0;
    while(window.isOpen()){
        
        sf::Event event;

        while(window.pollEvent(event)){
            if(event.type == sf::Event::Closed){
                window.close();
            }
        }


        float a = W[1][0];
        float b = W[2][0];
        float c = W[0][0];
        
        int tempo = tempo2 % entradas.size();
        float v = matrixMultiplication(matrixTranspose(W), entradas[tempo])[0][0];
        int y = sinal(v);
        W = matrixSum(W, matrixScalar(entradas[tempo], n*(saidasEsperadas[tempo][0][0] - y)));  

        sf::Vertex line[] =
        {
        sf::Vertex(sf::Vector2f(0,-c/b)),
        sf::Vertex(sf::Vector2f(width, -(a * width + c)/b))
        };

        if(tempo2 % 50000 == 0){
            window.clear();
            window.draw(vertex);
            window.draw(line, 2, sf::Lines);
            window.display();
           // std::cout<<tempo2<<std::endl;
        }
     //   if(tempo2 > entradas.size()*loops){break;}
        tempo2 ++;
    }

    std::cout<<"W :: ";
    showMatrix(matrixTranspose(W));

    return 0;
}	