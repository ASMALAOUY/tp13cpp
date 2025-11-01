#include <iostream>
#include <stdexcept>
#include <string>
using namespace std;

template<typename T>
class ArrayDyn {
private:
    T* data;
    size_t capacite;
    size_t taille_courante;

public:
    ArrayDyn() : data(nullptr), capacite(0), taille_courante(0) {}
    ArrayDyn(size_t initial_capacity)
        : data(new T[initial_capacity]), capacite(initial_capacity), taille_courante(0) {}
    ArrayDyn(const ArrayDyn& other)
        : data(new T[other.capacite]), capacite(other.capacite), taille_courante(other.taille_courante)
    {
        for (size_t i = 0; i < taille_courante; ++i)
            data[i] = other.data[i];
    }
    ArrayDyn& operator=(const ArrayDyn& other) {
        if (this != &other) {
            delete[] data;
            capacite = other.capacite;
            taille_courante = other.taille_courante;
            data = new T[capacite];
            for (size_t i = 0; i < taille_courante; ++i)
                data[i] = other.data[i];
        }
        return *this;
    }
    ~ArrayDyn() {
        delete[] data;
    }
    void push_back(const T& value) {
        if (taille_courante == capacite)
            resize(capacite == 0 ? 1 : capacite * 2);
        data[taille_courante++] = value;
    }
    void pop_back() {
        if (taille_courante == 0)
            throw out_of_range("pop_back sur tableau vide");
        --taille_courante;
    }
    T& operator[](size_t index) {
        if (index >= taille_courante)
            throw out_of_range("Index hors limites");
        return data[index];
    }
    const T& operator[](size_t index) const {
        if (index >= taille_courante)
            throw out_of_range("Index hors limites");
        return data[index];
    }
    size_t size() const { return taille_courante; }
    size_t capacity() const { return capacite; }

private:
    void resize(size_t new_capacity) {
        T* new_data = new T[new_capacity];
        for (size_t i = 0; i < taille_courante; ++i)
            new_data[i] = data[i];
        delete[] data;
        data = new_data;
        capacite = new_capacity;
    }

public:
    class Iterator {
    private:
        T* ptr;
    public:
        Iterator(T* p = nullptr) : ptr(p) {}
        T& operator*() const { return *ptr; }
        Iterator& operator++() { ++ptr; return *this; }
        Iterator& operator--() { --ptr; return *this; }
        bool operator!=(const Iterator& other) const { return ptr != other.ptr; }
    };
    Iterator begin() { return Iterator(data); }
    Iterator end() { return Iterator(data + taille_courante); }
};

struct Produit {
    string nom;
    double prix;
};

int main() {
    ArrayDyn<int> tabInt;
    tabInt.push_back(10);
    tabInt.push_back(20);
    tabInt.push_back(30);
    cout << "Contenu tabInt : ";
    for (auto &x : tabInt) cout << x << " ";
    cout << endl;

    ArrayDyn<string> tabStr;
    tabStr.push_back("Bonjour");
    tabStr.push_back("le");
    tabStr.push_back("monde");
    cout << "Contenu tabStr : ";
    for (auto &s : tabStr) cout << s << " ";
    cout << endl;

    ArrayDyn<Produit> tabProd;
    tabProd.push_back({"Stylo", 2.5});
    tabProd.push_back({"Cahier", 10.0});
    tabProd.push_back({"Gomme", 1.2});
    cout << "Produits :" << endl;
    for (auto &p : tabProd)
        cout << " - " << p.nom << " : " << p.prix << " dhs" << endl;

    return 0;
}
