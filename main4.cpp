/*nomes: Mauricio Duarte Paliosa e Samy Haileen Chapaca Toapanta 
*/

#include <iostream>
#include <fstream>
#include <string>
#include "pilha.h"
using namespace std;

bool tagFech(const string& tag) {
    return !tag.empty() && tag[0] == '/';
}

string pegaNome(const string& tag) {
    string nome = tag;
    if (tagFech(nome)) {
        nome = nome.substr(1); 
    }
    size_t espaco = nome.find(' ');
    if (espaco != string::npos) {
        nome = nome.substr(0, espaco);
    }
    return nome;
}

void imprimirAtributos(string atributos) {
    string atributosvet[100]; 
    int conta = 0; 

    size_t pos = 0;

    while (pos < atributos.length()) {
        size_t igual = atributos.find('=', pos);
        if (igual == string::npos) break; 

        size_t aspasInicio = atributos.find('"', igual);
        size_t aspasFim = atributos.find('"', aspasInicio + 1);
        if (aspasInicio == string::npos || aspasFim == string::npos) break; 

        string atributo = atributos.substr(pos, aspasFim - pos + 1);
        atributosvet[conta++] = atributo; 

        pos = aspasFim + 2;
    }

    for (int i = 0; i < conta - 1; i++) {
        for (int j = 0; j < conta - 1 - i; j++) {
            if (atributosvet[j] > atributosvet[j + 1]) {
                string temp = atributosvet[j];
                atributosvet[j] = atributosvet[j + 1];
                atributosvet[j + 1] = temp;
            }
        }
    }

    for (int i = 0; i < conta; i++) {
        cout << " " << atributosvet[i];
    }
}

int main() {
    string nomeArquivo = "001-valido.dcar "; //o espaço depois de "dcar " é nessesario porque o nome do arquivo com 
                                             //as informações do carro so é salvo como ( <> ) se tiver um espaço no final. "dificuldade no meu computador"
    //string nomeArquivo = "002-invalido.dcar ";
    //string nomeArquivo = "003-invalido.dcar ";

    ifstream arquivo(nomeArquivo);

    if (!arquivo.is_open()) {
        cout << "Não foi possível abrir o arquivo: " << nomeArquivo << endl;
        return 1;
    }

    Pilha pilha;

    string linha;
    int linhaAtual = 0;
    bool falha = false;

    while (getline(arquivo, linha)) {
        linhaAtual++;
        size_t pos = linha.find('<');
        while (pos != string::npos) {
            size_t fim = linha.find('>', pos);
            if (fim == string::npos) break; 

            string tag = linha.substr(pos + 1, fim - pos - 1);
            string nomeTag = pegaNome(tag);

            if (!tagFech(tag)) {
                pilha.empilhar(nomeTag);

                cout << "\n" << "Tag encontrada: <" << nomeTag << ">";

                size_t espaco = tag.find(' ');
                if (espaco != string::npos) {
                    string atributos = tag.substr(espaco + 1);
                    imprimirAtributos(atributos);
                }
            } else {
                if (pilha.vazia() || pilha.topoPilha() != nomeTag) {
                    cout << "\n" << "falha na linha " << linhaAtual << ": tag de fechamento </" << nomeTag << "> fechou na hora errada." << endl;
                    falha = true;
                    break;
                }
                pilha.desempilhar();
            }

            pos = linha.find('<', fim + 1);
        }

        if (falha) break;
    }

    if (!falha && !pilha.vazia()) {
        cout << "\n" << "falha: tag <" << pilha.topoPilha() << "> sem fechamento correspondente." << endl;
        falha = true;
    }

    if (!falha) {
        cout << "\n" <<"Arquivo válido: todas as tags estão fechadas corretamentes." << endl;
    }

    arquivo.close();
    return 0;
}
