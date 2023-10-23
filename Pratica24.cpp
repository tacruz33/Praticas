#include <iostream>
#include <vector>
#include <string>
#include <ctime>

using namespace std;

class Livro
{
public:
    Livro(string titulo, string autor, int numCopias)
        : titulo(titulo), autor(autor), numCopias(numCopias) {}

    string getTitulo() const
    {
        return titulo;
    }

    string getAutor() const
    {
        return autor;
    }

    int getNumCopias() const
    {
        return numCopias;
    }

    static void adicionarLivro(Livro livro)
    {
        livros.push_back(livro);
    }

    static void emprestarLivro(string titulo, string nomeUsuario)
    {
        for (Livro &livro : livros)
        {
            if (livro.getTitulo() == titulo && livro.getNumCopias() > 0)
            {
                livro.numCopias--;
                emprestimos.push_back(make_pair(titulo, nomeUsuario));
                cout << nomeUsuario << " pegou emprestado o livro '" << titulo << "'" << endl;
                return;
            }
        }
        cout << "Livro não disponível para empréstimo." << endl;
    }

    static void verificarDisponibilidade(string titulo)
    {
        for (const Livro &livro : livros)
        {
            if (livro.getTitulo() == titulo)
            {
                cout << "Livro '" << titulo << "' possui " << livro.getNumCopias() << " cópias disponíveis." << endl;
                return;
            }
        }
        cout << "Livro não encontrado na biblioteca." << std::endl;
    }

public:
    string titulo;
    string autor;
    int numCopias;
    static vector<Livro> livros;
    static vector<pair<string, string>> emprestimos;
};

vector<Livro> Livro::livros;
vector<pair<string, string>> Livro::emprestimos;

class Usuario
{
public:
    Usuario(string nome) : nome(nome) {}

    static void listarLivrosEmprestados(string nomeUsuario)
    {
        cout << "Livros emprestados para " << nomeUsuario << ":" << endl;
        for (const auto &emprestimo : Livro::emprestimos)
        {
            if (emprestimo.second == nomeUsuario)
            {
                cout << "- " << emprestimo.first << endl;
            }
        }
    }

private:
    string nome;
};

int main()
{
    Livro::adicionarLivro(Livro("Livro A", "Autor A", 3));
    Livro::adicionarLivro(Livro("Livro B", "Autor B", 2));
    Livro::adicionarLivro(Livro("Livro C", "Autor C", 1));

    Livro::verificarDisponibilidade("Livro A");
    Livro::emprestarLivro("Livro A", "Usuário 1");
    Livro::verificarDisponibilidade("Livro A");

    Livro::emprestarLivro("Livro A", "Usuário 2");

    Usuario usuario1("Usuário 1");
    usuario1.listarLivrosEmprestados("Usuário 1");

    return 0;
}