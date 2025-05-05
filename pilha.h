#ifndef PILHA_H
#define PILHA_H

#include <string>
#include <iostream>
using namespace std;

// Definição da pilha
class Pilha {
private:
    string pilha[1000];                         // Máximo de 1000 tags
    int topo;

public:
//Constructor de pilha
    Pilha() {
        topo = -1;
    } 

    bool vazia() {                               // Verifica se a pilha está vazia
        return topo == -1;                      //Cuando la pila está vacía (topo == -1), la función vazia() devuelve true. 
    }

    // Adiciona uma tag a o topo da pilha
    void empilhar(const string& tag) {
        if (topo >= 999) {                      //Revisa que o topo nao for maior ou igual que 999
            cout << "Erro: muitas tags aninhadas (limite de 1000 atingido)." << endl;
            return;
        }
        pilha[++topo] = tag;                    // Y si no es se incrementa el topo es decir de -1 pasa a pos 0
    }

    // Remove e retorna a tag do topo da pilha
    string desempilhar() {
        if (!vazia()) {                         //Verifica se a pilha nao estiver vazia 
            return pilha[topo--];               //accesa al valor del topo y lo decrementa se era 0 agr é -1
        }
        return "";                              // Se estiver vazias retorna uma cadena vcazia
    }

    // Verifica o nome da tag no topo da pilha
    string topoPilha() {
        if (!vazia()) {
            return pilha[topo];                 // só pega o nome mas nao retira 
        }
        return "";
    }
};

#endif//PILHA_H
