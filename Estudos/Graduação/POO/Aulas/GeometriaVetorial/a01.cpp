#include<stdexcept>
#include <iostream>



class Ponto{
    double _x, _y;
public:
    Ponto() : _x(0.0), _y(0.0){}
    Ponto(double x, double y) : _x(x), _y(y) {}
    double operator[] (int i) {
        if(i == 0) return _x;
        if(i == 1) return _y;
        throw std::out_of_range("Válido somente para 0 e 1!");
    }
    double operator[] (char c) {
        if(c == 'x') return _x;
        if(c == 'y') return _y;
        throw std::out_of_range("Válido somente para x e y!");
    } 
};

int main(){
    Ponto p1, p2[x:1, y:2];
    std::cout<< p1['x'] <<", "<<p1['y']<<std::endl;
    std::cout<< p2[0] <<", "<<p2[1]<<std::endl;
}