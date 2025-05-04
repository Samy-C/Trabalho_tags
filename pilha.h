#ifndef PILHA_H
#define PILHA_H

#include <string>
#include <iostream>
using namespace std;

class Pilha {
private:
    string pilha[1000]; 
    int topo;

public:
    Pilha() {
        topo = -1;
    } 

    bool vazia() {
        return topo == -1;
    }

    void empilhar(const string& tag) {
        if (topo >= 999) {
            cout << "Erro: muitas tags aninhadas (limite de 1000 atingido)." << endl;
            return;
        }
        pilha[++topo] = tag;
    }

    string desempilhar() {
        if (!vazia()) {
            return pilha[topo--];
        }
        return "";
    }

    string topoPilha() {
        if (!vazia()) {
            return pilha[topo];
        }
        return "";
    }
};

#endif 
