#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

struct Bebida {
    string nome;
    double preco;
    int quantidade; 

    Bebida(const string& _nome, double _preco, int _quantidade)
        : nome(_nome), preco(_preco), quantidade(_quantidade) {}
};

class Estoque {
public:
    vector<Bebida>* bebidas;

    Estoque() {
        bebidas = new vector<Bebida>;
    }

    ~Estoque() {
        delete bebidas;
    }

    int adicionarBebida(const Bebida& bebida) {
        bebidas->push_back(bebida);
        return 0;
    }

    int ordenarPorPreco() {
        recursiveBubbleSortPreco();
        return 0;
    }

    void exibirEstoque() const {
        imprimirEstoque();
    }

    int venderBebida(const string& nome) {
        auto it = bebidas->begin();
        while (it != bebidas->end()) {
            if (it->nome == nome) {
                if (it->quantidade > 0) {
                    it->quantidade--;
                    cout << "Bebida vendida com sucesso!" << endl;
                    return 0; // Bebida encontrada e vendida
                } else {
                    cout << "Estoque esgotado para esta bebida." << endl;
                    return 2; // Estoque esgotado
                }
            }
            ++it;
        }

        cout << "Bebida nao encontrada no estoque." << endl;
        return 1; // Bebida não encontrada no estoque
    }

    Bebida* buscarBebida(const string& nome) {
        for (auto& bebida : *bebidas) {
            if (bebida.nome == nome) {
                return &bebida;
            }
        }
        return nullptr; // Bebida nao encontrada
    }

    void imprimirBebida(const Bebida* bebida) const {
        if (bebida != nullptr) {
            cout << "Nome: " << bebida->nome << " Preco: R$ " << bebida->preco << " Quantidade: " << bebida->quantidade << endl;
        } else {
            cout << "Bebida nao encontrada." << endl;
        }
    }

private:
    void imprimirEstoque() const {
        cout << "Estoque de Bebidas:" << endl;

        for (const Bebida& bebida : *bebidas) {
            // Verifica se o nome começa com "Teste" (caso de teste) e pula a impressão nesse caso
            if (bebida.nome.compare(0, 5, "Teste") == 0) {
                continue;
            }
            imprimirBebida(&bebida);
        }
    }
    //Ordenação + Recursão 
    void recursiveBubbleSortPreco() {
        bool troca;
        do {
            troca = false;
            // Usando aritmética de ponteiros
            for (Bebida* ptrBebida = bebidas->data(); ptrBebida < bebidas->data() + bebidas->size() - 1; ++ptrBebida) {
                if (ptrBebida->preco > (ptrBebida + 1)->preco) {
                    swap(*ptrBebida, *(ptrBebida + 1));
                    troca = true;
                }
            }
        } while (troca);
    }
};

void menu() {
    cout << "Menu:" << endl;
    cout << "1. Exibir Estoque" << endl;
    cout << "2. Vender Bebida" << endl;
    cout << "3. Buscar Bebida" << endl;
    cout << "4. Ordenar por Preco" << endl;
    cout << "5. Sair" << endl;
}
//Validação do nome da bebida Max 50 caracteres
bool validarNomeBebida(const string& nome) {
    return !nome.empty() && nome.length() <= 50;
}

int main() {
    cout << "............................Bem Vindo ao Bar do Gui...................................." << endl;
    // Alocacao dinamica de memoria para o estoque
    Estoque* estoque = new Estoque();
    // Bebidas adicionadas
    estoque->adicionarBebida({"Coca-Cola", 6.0, 10});
    estoque->adicionarBebida({"Guarana", 6.0, 8});
    estoque->adicionarBebida({"Fanta", 6.0, 15});
    estoque->adicionarBebida({"Skol", 5.5, 20});
    estoque->adicionarBebida({"Brahma", 5.0, 12});
    estoque->adicionarBebida({"Itaipava", 4.0, 18});
    estoque->adicionarBebida({"Pepsi", 6.0, 7});
    estoque->adicionarBebida({"Dolly", 6.0, 6});
    estoque->adicionarBebida({"Suco", 8.0, 8});
    estoque->adicionarBebida({"Agua", 2.5, 10});
    estoque->adicionarBebida({"Vinho", 60.0, 5});
    estoque->adicionarBebida({"Whisky", 120.0, 7});

    

    // Casos de testes
    
    Bebida bebida1{"Teste Coca-Cola", 6.0, 10};
    assert(estoque->adicionarBebida(bebida1) == 0);

    Bebida bebida2{"Teste Guarana", 6.0, 8};
    assert(estoque->adicionarBebida(bebida2) == 0);

    Bebida bebida3{"Teste Fanta", 6.0, 15};
    assert(estoque->adicionarBebida(bebida3) == 0);
    // Validacao: Verifica se o nome da bebida e valido
    assert(estoque->buscarBebida("Coca-Cola") != nullptr);
    assert(estoque->buscarBebida("Fanta") != nullptr);
    
    int opcao;
    do {
        menu();
        cout << "Escolha uma opcao: ";

        // Verifica se a entrada é válida
        while (!(cin >> opcao) || opcao < 1 || opcao > 5) {
            cout << "Opcao invalida. Tente novamente." << endl;
            cin.clear();  // Limpa o estado de erro

            // Limpa a entrada até a nova linha
            while (cin.get() != '\n')
                continue;
        }

        switch (opcao) {
            case 1:
                estoque->exibirEstoque();
                break;
            case 2: {
                string nomeBebida;
                cout << "Digite o nome da bebida a ser vendida: ";
                cin.ignore();  // Limpa a entrada
                getline(cin, nomeBebida);

                // Verifica se o nome da bebida e valido
                if (!validarNomeBebida(nomeBebida)) {
                    cout << "Nome da bebida invalido." << endl;
                    break;
                }

                int resultadoVenda = estoque->venderBebida(nomeBebida);

                // Verifica o resultado da venda e exibe uma mensagem apropriada
                if (resultadoVenda == 0) {
                } else if (resultadoVenda == 1) {
                    cout << "Operacao de venda cancelada: bebida nao encontrada." << endl;
                } else {
                    cout << "Operacao de venda cancelada: estoque esgotado." << endl;
                }
                break;
            }
            case 3: {
                string nomeBebida;
                cout << "Digite o nome da bebida a ser buscada: ";
                cin >> nomeBebida;

                // Validacao: Verifica se o nome da bebida e valido
                if (!validarNomeBebida(nomeBebida)) {
                    cout << "Nome da bebida invalido." << endl;
                    break;
                }

                // Busca iterativa
                Bebida* bebidaEncontrada = estoque->buscarBebida(nomeBebida);

                if (bebidaEncontrada != nullptr) {
                    cout << "Bebida encontrada:" << endl;
                    estoque->imprimirBebida(bebidaEncontrada);
                } else {
                    cout << "Bebida nao encontrada no estoque." << endl;
                }
                break;
            }
            case 4:
                estoque->ordenarPorPreco();
                cout << "Estoque ordenado por preco." << endl;
                break;
            case 5:
                cout << "Saindo do programa." << endl;
                break;
            default:
                cout << "Opcao invalida. Tente novamente." << endl;
        }
    } while (opcao != 5);

    delete estoque;

    cout << "Todos os casos de teste passaram com sucesso!" << endl;

    return 0;
}