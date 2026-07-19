#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <sstream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <chrono>
#include <thread>
#include <algorithm>
#include <limits>
using namespace std;
string lucro = "";
bool modelo_salvo = false;
string dados[6];
string modelo_planilha = "";
int j = 0;
//descreve todas as características de um material (cabeçalho)
struct materiais_ {
    string nome = "";
    int quantidade = 0;
    string quantidade_de_manobra = "";
    float preco = 0.00f;
    float preco_unitario = 0.00f;
    float preco_impresso = 0.00f;
    string fornecedor = "";

    float media_preco = 0.000f;
    float media_preco_unitario = 0.000f;
    float media_preco_impresso = 0.00f;

    double soma_preco_ = 0.00;
    double soma_preco_unitario_ = 0.00;
    double soma_preco_impresso_ = 0.00;

//os preços em forma de texto, por causa do símbolo de reais,
//que não pode ser lido como um número.
    string preco_de_manobra = "";
    string preco_unitario_de_manobra = "";
    string preco_impresso_de_manobra = "";
};

struct materiais_de_save {
    char nome_[50] = "";
    int quantidade = 0;
    float preco = 0.00f;
    float preco_unitario = 0.00f;
    float preco_impresso = 0.00f;
    char fornecedor[50] = "";

    float media_preco = 0.000f;
    float media_preco_unitario = 0.000f;
    float media_preco_impresso = 0.00f;

    double soma_preco_ = 0.00;
    double soma_preco_unitario_ = 0.00;
    double soma_preco_impresso_ = 0.00;

};

materiais_de_save ms[30];

vector<materiais_> materiais = vector<materiais_>(30);
//formato do cadastro do cliente
struct cadastro {
    string nome_pessoa = "não há cadastro";
    float total_gasto = 0;
    string manobra = "";
    string endereco_pessoa = "não há endereço salvo";
    string cpf = "não há CPF salvo";

};

      vector<cadastro> cliente = vector<cadastro>(50);

//variáveis de média e soma
float media_preco = 0.000000f;
float media_preco_unitario = 0.000000f;
float media_preco_impresso = 0.000000f;

double soma_preco = 0.00;
double soma_preco_unitario = 0.00;
double soma_preco_impresso = 0.00;

void microplan() {
//verifica se tu já tem um arquivo de modelo para planilhas
    ifstream modelo_de_planilha_("modelo_de_planilha.txt");

    if(modelo_de_planilha_.is_open()) {
        modelo_salvo = true;

        for(int wx = 0; wx < 6; wx++) {
            getline(modelo_de_planilha_, dados[wx], ' ');
        }
        modelo_de_planilha_.close();
        return;
    }

    cout << "por favor, insira a ordem de leitura de cada campo da planilha (exemplo preço preço impresso fornecedor preço unitario etc SEM USAR VIRGULA)" << endl;
    string passar_dados = "";

    for(int ww = 0; ww < 6; ww++) {
        getline(cin, dados[ww], ' ');

        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        system("clear");
    }
    passar_dados += dados[0];
    passar_dados += ' ';
    passar_dados += dados[1];
    passar_dados += ' ';
    passar_dados += dados[2];
    passar_dados += ' ';
    passar_dados += dados[3];
    passar_dados += ' ';
    passar_dados += dados[4];
    passar_dados += ' ';
    passar_dados += dados[5];
    modelo_salvo = true;

    ofstream dado_("modelo_de_planilha.txt");
    dado_ << passar_dados;
}

//lê o arquivo
void ler_arquivos() {
    //nome do arquivo
    string nome_do_arquivo = "";

    cout << "digite o nome do arquivo: " << endl;
    cin >> nome_do_arquivo;

    ifstream arquivo(nome_do_arquivo);

    //executa a leitura conforme o teu modelo
    if(modelo_salvo == true) {
        using ponteiro_membro = string materiais_::*;

        unordered_map<string, ponteiro_membro> escolha;

        escolha["produto"] = &materiais_::nome;
        escolha["Produto"] = &materiais_::nome;
        escolha["valor"] = &materiais_::preco_de_manobra;
        escolha["Valor"] = &materiais_::preco_de_manobra;
        escolha["valor unitário"] = &materiais_::preco_unitario_de_manobra;
        escolha["Valor unitário"] = &materiais_::preco_unitario_de_manobra;
        escolha["valor impresso"] = &materiais_::preco_impresso_de_manobra;
        escolha["Valor impresso"] = &materiais_::preco_impresso_de_manobra;
        escolha["quantidade"] = &materiais_::quantidade_de_manobra;
        escolha["Quantidade"] = &materiais_::quantidade_de_manobra;


        ponteiro_membro p1 = escolha[dados[0]];
        ponteiro_membro p2 = escolha[dados[1]];
        ponteiro_membro p3 = escolha[dados[2]];
        ponteiro_membro p4 = escolha[dados[3]];
        ponteiro_membro p5 = escolha[dados[4]];
        ponteiro_membro p6 = escolha[dados[5]];

        while(j < 30 && arquivo.good()) {

            getline(arquivo, materiais[j].*p1, ',');
            getline(arquivo, materiais[j].*p2, ',');
            getline(arquivo, materiais[j].*p3, ',');
            getline(arquivo, materiais[j].*p4, ',');
            getline(arquivo, materiais[j].*p5, ',');
            getline(arquivo, materiais[j].*p6, '\n');


            materiais[j].preco_de_manobra = (materiais[j].preco_de_manobra).erase(0, 3);
            materiais[j].preco = stoi(materiais[j].preco_de_manobra);

            materiais[j].preco_unitario_de_manobra = (materiais[j].preco_unitario_de_manobra).erase(0, 3);
            materiais[j].preco_unitario = stoi(materiais[j].preco_unitario_de_manobra);

            materiais[j].preco_impresso_de_manobra = (materiais[j].preco_impresso_de_manobra).erase(0, 3);
            materiais[j].preco_impresso = stoi(materiais[j].preco_impresso_de_manobra);

            materiais[j].quantidade = stoi(materiais[j].quantidade_de_manobra);
            j++;
        }
    }
    arquivo.close();
}


//funçao que calcula a média e o preço de tudo
void media_() {

    for(int i = 0; i < 20; i++) {
        media_preco += materiais[i].preco;
        if(materiais[i].preco == 0.00) {
            media_preco = media_preco/(i - 1);
            break;
        }

        media_preco_unitario += materiais[i].preco;
        if(materiais[i].preco_unitario == 0.00) {
            media_preco_unitario = media_preco_unitario/(i - 1);
            break;
        }

        media_preco_impresso += materiais[i].preco;
        if(materiais[i].preco_impresso == 0.00) {
            media_preco_impresso = media_preco_impresso/(i - 1);
            break;
        }

    }

    soma_preco = media_preco;
    soma_preco_unitario = media_preco_unitario;
    soma_preco_impresso = media_preco_impresso;

    for(int h = 0; h < 30; h++) {

        materiais[h].soma_preco_ = soma_preco;
        materiais[h].soma_preco_unitario_ = soma_preco_unitario;
        materiais[h].soma_preco_impresso_ = soma_preco_impresso;


    }
    media_preco = media_preco/19;
    media_preco_unitario = media_preco_unitario/19;
    media_preco_impresso = media_preco_impresso/19;

label:
    string escolha_modo = "";
    cout << "qual média você quer escolher?\n\npreço\npreço unitário\n preço impresso\n\n" << endl;
    cin >> escolha_modo;

    if(escolha_modo == "preço") {
        cout << "a média dos preços é: " << media_preco << "com soma total de: " << soma_preco << endl;
    }
    else if(escolha_modo == "preço unitario") {
        cout << "a média dos preços unitarios é: " << media_preco_unitario << "com soma total de: " << soma_preco_unitario << endl;
    }
    else if(escolha_modo == "preço impresso") {
        cout << "a média dos preços impressos é: " << media_preco_impresso << "com soma total de: " << soma_preco_impresso << endl;
    }

    else {
        goto label;
    }
}
string modelo = "";


int main() {
usuario:

    cout << "você quer ler um novo arquivo ou trabalhar comos arquivos que você já tem?" << endl;
    string io;

    cin >> io;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if(io == "ler um novo arquivo") {

        system("clear");

        ler_arquivos();
        system("clear");

//opções do usuario
        while(true){
        cout << "1 - calcular media de custos\n" << endl;
        cout << "2 - inserir lucro\n" << endl;
        cout << "3 - criar novo modelo de planilha\n" << endl;
        cout << "4 - ver todos os itens já comprados" << endl;
        cout << "5 - adicionar cadastro de cliente" << endl;
        cout << "6 - inserir margem de lucro" << endl;

        int escolha = 8;
        cin >> escolha;

        if(escolha == 1) {
            media_();
            break;
        }
        else if(escolha == 2) {
            cin >> lucro;
            ofstream lucro_arquivo("lucro.txt", ios::app);
            if(!lucro_arquivo.is_open()) {
                cerr << "erro ao abrir arquivo";
            }

            lucro_arquivo << lucro << '\n';
            lucro_arquivo.close();
            break;
        }
        else if(escolha == 3) {
            cout << "digite a ordem dos dados: " << endl;
            string ordem_dos_dados = "";
            cin >> ordem_dos_dados;

            cout << "dê um nome para seu modelo de planilha" << endl;
            string modelo_planilha = "sem nome";
            cin >> modelo_planilha;

            ofstream molde(modelo_planilha);

            molde << ordem_dos_dados;
        } else if(escolha == 4) {
            for(int z = 0; z < 30; z++) {
                int soma_total = 0;
                soma_total += materiais[z].quantidade;
                break;
            }
        }
        else if(escolha == 5) {
            ofstream cadastros_("cadastros.txt");
            cout << "quantos cadastros você deseja fazer agora?" << endl;
            int numero_de_cadastros = 0;
            cin >> numero_de_cadastros;

            for(int loooooop = 0; loooooop < numero_de_cadastros; loooooop++) {

                cout << "\n\nadicione o nome do cliente: " << endl;
                cin >> cliente[loooooop].nome_pessoa;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                cout << "\n\nadicione o total gasto pelo cliente: " << endl;
                cin >> cliente[loooooop].total_gasto;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                cout << "\n\nadicione o endereço do cliente: " << endl;
                cin >> cliente[loooooop].endereco_pessoa;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                cout << "\n\nadicione o CPF do cliente:" << endl;
                cin >> cliente[loooooop].cpf;
                system("clear");

                cadastros_ << cliente[loooooop].nome_pessoa << ';' << cliente[loooooop].total_gasto << ';' << cliente[loooooop].endereco_pessoa << ';' << cliente[loooooop].cpf << '\n';
                break;
            }
            cadastros_.close();
        }

        else if(escolha == 67) {
            cout << "\n\nSIX SEVEN! sabia que tu ia tentar kkkkkkk" << endl;
            break;
        }

        else if(escolha == 6) {

            cout << "qual margem de lucro você quer?" << endl;
            string margem_de_lucro = "";
            cin >> margem_de_lucro;
            margem_de_lucro.pop_back();

            int margemL = stoi(margem_de_lucro);

            if(margemL < 100) {
                margemL = 1 + margemL - 100;
                cout << "o preço do produto deve ser: " << soma_preco * margemL << endl;
            } else {
                margemL = margemL/100;
                cout << "o preço do produto deve ser: "<< soma_preco * margemL << endl;
                break;
            }
        }

        else {
            cout << "erro 404: entrada desconhecida, por favor, tente novamente" << endl;
            this_thread::sleep_for(chrono::seconds(6));
            system("clear");
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        for(int RTX = 0; RTX < 30; RTX++) {

            strncpy(ms[RTX].fornecedor, (materiais[RTX].fornecedor).c_str(), sizeof(ms[RTX]) - 1);
                    strncpy(ms[RTX].fornecedor, (materiais[RTX].fornecedor).c_str(), sizeof(ms[RTX]) - 1);

                            ms[RTX].preco = materiais[RTX].preco;
                            ms[RTX].preco_unitario = materiais[RTX].preco_unitario;
                            ms[RTX].preco_impresso = materiais[RTX].preco_impresso;

                            ms[RTX].soma_preco_ = materiais[RTX].soma_preco_;
                            ms[RTX].soma_preco_unitario_ = materiais[RTX].soma_preco_unitario_;
                            ms[RTX].soma_preco_impresso_ = materiais[RTX].soma_preco_impresso_;

                            ms[RTX].media_preco = materiais[RTX].media_preco;
                            ms[RTX].media_preco_unitario = materiais[RTX].media_preco_unitario;
                            ms[RTX].media_preco_impresso = materiais[RTX].media_preco_impresso;

                            ms[RTX].quantidade = materiais[RTX].quantidade;
        }}}else if(io == "trabalhar os arquivos que já tenho") {

        system("clear");

        ofstream dados_output("dados.bin", ios::binary | ios::app);

        if(dados_output.is_open()) {
            dados_output.write(reinterpret_cast<char*>(ms), sizeof(materiais_de_save) * 29);
        } else {
            cerr << "erro ao abrir arquivo";
        }
        dados_output.close();

        ifstream dados_input("dados.bin", ios::binary);

        if(!dados_output.is_open()) {
            cerr << "erro ao abrir arquivo";
        }

        streamsize tamanho_do_arquivo = dados_input.tellg();
        size_t tamanho_dos_arrays = sizeof(materiais_de_save) * 30;
        size_t quantidade_de_arrays = tamanho_do_arquivo/tamanho_dos_arrays;
        size_t quantidade_de_structs = quantidade_de_arrays * 30;

        vector<materiais_de_save> importacao(quantidade_de_structs);

        dados_input.seekg(0, ios::beg);

        dados_input.read(reinterpret_cast<char*>(importacao.data()), tamanho_do_arquivo),

                         dados_input.close();

        cout << "dados lidos com sucesso! o que quer fazer com eles?\n\n" << endl;

        cout << "1 - comparar lucros\n" << endl;
        cout << "2 - comparar gastos\n" << endl;
        cout << "3 - ver o total de itens comprados\n" << endl;
        cout << "4 - conferir os maiores fornecedores\n" << endl;
        cout << "5 - vizualizar os melhores cadastros" << endl;
        cout << "6 - adicionar quantidade de vendas para cada arquivo" << endl;

        int escolha_modo_de_dados = 0;

        cin >> escolha_modo_de_dados;

        if(escolha_modo_de_dados == 1) {
            string lucros_texto[50];
            int lucros[50];

            ifstream lucro_arquivoinput("lucro.txt");
            int Randeon = 0;

            while(true){

                getline(lucro_arquivoinput, lucros_texto[Randeon]);
            if(lucros_texto[Randeon].empty()) {
                break;
            }
            lucros[Randeon] = stoi(lucros_texto[Randeon]);
            Randeon++;

            cout << "lucro " << Randeon + 1 << ": " << lucros[Randeon] << endl;
        }}

        else if(escolha_modo_de_dados == 2) {

            int quantia_de_quebra = 0;
            float quantidade_do_array[50];
            quantidade_do_array[0] = 0.00f;

            while(quantia_de_quebra <= quantidade_de_structs) {
                int selecao = 0;
                int comparacao = 0;

                quantidade_do_array[comparacao] += importacao[selecao].preco;

                if(selecao != 0 && selecao % 30 == 0) {

                    cout << "quantidade total de produtos comprados: " << quantidade_do_array[comparacao] << '\n' << endl;

                    comparacao++;
                }
                selecao++;

            }


        }
        else if(escolha_modo_de_dados == 3) {

            int quantia_de_quebra_ = 0;
            int quantidade_do_array_[50];
            quantidade_do_array_[0] = 0;

            while(quantia_de_quebra_ <= quantidade_de_structs) {
                int selecao_ = 0;
                int comparacao_ = 0;

                quantidade_do_array_[comparacao_] += importacao[selecao_].quantidade;

                if(selecao_ != 0 && selecao_ % 30 == 0) {

                    cout << "quantidade total de produtos comprados: " << quantidade_do_array_[comparacao_] << '\n' << endl;

                    comparacao_++;
                    
                }
                selecao_++;
            }
        }

        else if(escolha_modo_de_dados == 4) {

            string fornecedor_mais_frequente = "";
            int contagem = 0;

            unordered_map <string, int> ferramenta;

            for(const materiais_de_save& c : importacao) {

                ferramenta[c.fornecedor]++;

                if(ferramenta[c.fornecedor] > contagem) {

                    contagem = ferramenta[c.fornecedor];
                    fornecedor_mais_frequente = c.fornecedor;
                }
            }
            cout << "o seu maior fornecedor é: " <<  fornecedor_mais_frequente << endl;

        }

        else if(escolha_modo_de_dados == 5) {

            ifstream cadastro__("cadastros.txt");
            if(!cadastro__.is_open()) {
                cerr << "erro ao abrir arquivo";
            }
            
            int rs = 0;
            while(true) {
                getline(cadastro__, cliente[rs].nome_pessoa, ';');
                getline(cadastro__, cliente[rs].manobra, ';');
                cliente[rs].total_gasto = stof(cliente[rs].manobra);
                getline(cadastro__, cliente[rs].endereco_pessoa, ';');
                getline(cadastro__, cliente[rs].cpf, '\n');
                
                if((cliente[rs].nome_pessoa).empty()){break;}
                
                sort(cliente.begin(), cliente.end(),[](const cadastro& a, const cadastro& b) {return a.total_gasto > b.total_gasto; });
            
            cout << "aqui estão os 3 maiores compradores:\n\n" << cliente[0].nome_pessoa << ": " << cliente[0].total_gasto << '\n' << cliente[1].nome_pessoa << ": " << cliente[1].total_gasto << '\n' << cliente[2].nome_pessoa << ": " << cliente[2].total_gasto << '\n' << cliente[3].nome_pessoa << ": " << cliente[3].total_gasto << endl;
        }}
        else if(escolha_modo_de_dados == 6){
            int quantia_de_quebra__ = 0;
            int quantidade_de_vendas[50];

            ofstream vendas("vendas.txt");
            while(quantia_de_quebra__ <= quantidade_de_structs) {
                int selecao__ = 0;
                int comparacao__ = 0;

                if(selecao__ != 0 && selecao__ % 30 == 0) {
                    cout << "arquivo " << comparacao__ + 1 << ": " << endl;

                    cin >> quantidade_de_vendas[comparacao__];
                    vendas << "arquivo " << comparacao__ + 1 << ": " << quantidade_de_vendas[comparacao__];
                    
                    comparacao__++;
                }
                selecao__++;
                vendas.close();}
                }
                else if(escolha_modo_de_dados == 67){cout << "SIIIIIIX SEEEEEVEEEEN!! aqui também tem viu?" << endl;}

        else {
            cout << "opçao inválida, por favor, leia as opções e digite corretamente." << endl;
            this_thread::sleep_for(chrono::seconds(6));
            system("clear");
            goto usuario;
        }}
        string encerrar = "";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "aperte ENTER para encerrar o programa!" << endl;
        cin >> encerrar;
        return 0;
}
