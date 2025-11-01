#include <iostream>
#include <vector>
#include <string>
#include <concepts>
#include <functional>
#include <algorithm>
using namespace std;

template<typename T>
concept Sortable = requires(T a, T b) {
    { a < b } -> convertible_to<bool>;
};

template<Sortable T, typename Comp = less<T>>
void quickSort(vector<T>& vec, Comp comp = Comp{}) {
    if (vec.size() <= 1) return;

    auto pivot = vec[vec.size() / 2];
    vector<T> lessPart, equalPart, greaterPart;

    for (auto& x : vec) {
        if (comp(x, pivot))
            lessPart.push_back(x);
        else if (comp(pivot, x))
            greaterPart.push_back(x);
        else
            equalPart.push_back(x);
    }

    quickSort(lessPart, comp);
    quickSort(greaterPart, comp);

    vec.clear();
    vec.insert(vec.end(), lessPart.begin(), lessPart.end());
    vec.insert(vec.end(), equalPart.begin(), equalPart.end());
    vec.insert(vec.end(), greaterPart.begin(), greaterPart.end());
}

template<typename T>
struct Asc {
    bool operator()(const T& a, const T& b) const { return a < b; }
};

template<typename T>
struct Desc {
    bool operator()(const T& a, const T& b) const { return a > b; }
};

struct Produit {
    string nom;
    double prix;
    bool operator<(const Produit& other) const { return prix < other.prix; }
};

int main() {
    vector<int> v1 = {5, 3, 8, 1, 2};
    quickSort(v1, Asc<int>{});
    cout << "Tri croissant int : ";
    for (auto x : v1) cout << x << " ";
    cout << endl;

    quickSort(v1, Desc<int>{});
    cout << "Tri decroissant int : ";
    for (auto x : v1) cout << x << " ";
    cout << endl;

    vector<string> v2 = {"pomme", "banane", "orange", "kiwi"};
    quickSort(v2, Asc<string>{});
    cout << "Tri croissant string : ";
    for (auto& s : v2) cout << s << " ";
    cout << endl;

    vector<Produit> produits = {{"Stylo", 2.5}, {"Cahier", 10.0}, {"Gomme", 1.2}};
    quickSort(produits, Asc<Produit>{});
    cout << "Produits tries par prix croissant :\n";
    for (auto& p : produits)
        cout << " - " << p.nom << " : " << p.prix << " dhs\n";

    return 0;
}
