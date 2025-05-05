/*nomes: Mauricio Duarte Paliosa e Samy Haileen Chapaca Toapanta 
*/

#include <iostream>
#include <fstream>
#include <string>
#include "pilha.h"
using namespace std;


//Funcion tagFech: Identifica etiqueta de cierre
 bool tagFech(const string& tag) {
        return !tag.empty() && tag[0] == '/'; /* Devuelve true si:
                                               tag n está vazia e se seu primer carácter es /.
                                                tagFech("/Engine") → true */
    }
    
// Pega o nome do tag    
    string pegaNome(const string& tag) {
        string nome = tag;
        if (tagFech(nome)) {                    // Chama a função tagFech
            nome = nome.substr(1);              //Se é uma etiqueta de fechamento, remove o primer carácter (/)
                                                // e guarda o nome
        }
        size_t espaco = nome.find(' ');
        if (espaco != string::npos) {
            nome = nome.substr(0, espaco);
        }
        return nome;
    }
    
//Função para imprimir os atributos ex: manufacturer="Kia Motors" model="Sportage" year="2009" extras="XL" 
void imprimirAtributos(string atributos) {
    string atributosvet[100];                           //Salva até 100 atributos
    int conta = 0;                                      //Contador de atributos 

    size_t pos = 0;

    while (pos < atributos.length()) { 
        size_t igual = atributos.find('=', pos);        //Salva a pos quando encontrar um =
        if (igual == string::npos) break;               // Si no se encuentra un = termina el bucle

        size_t aspasInicio = atributos.find('"', igual);                                //Procura as aspas depois de o signo =
        size_t aspasFim = atributos.find('"', aspasInicio + 1);                         //Procura as outras aspas por isso coloco +1
        if (aspasInicio == string::npos || aspasFim == string::npos) break;             // N achei fechou o blucle

        string atributo = atributos.substr(pos, aspasFim - pos + 1);                    //Coloca tudo o q vai depois do igual ate as aspasFim ex: "Kia Motors"
        atributosvet[conta++] = atributo;                                               //Contador de atributos 

        pos = aspasFim + 2;                         //Actualiza a variavel pos para buscar o outro atributo 
    }

//Bubble Sort para ordenar em ordem alfabetica 
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
    string nomeArquivo = "001-valido.dcar"; //o espaço depois de "dcar " é nessesario porque o nome do arquivo com 
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

    while (getline(arquivo, linha)) {               //Ignora # já que só le quando tem < ou >
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
