#include <iostream>
#include <initializer_list>
using namespace std;

template<typename T, size_t N, size_t M>
class Matrice {
private:
    T data[N][M];

    template<typename, size_t, size_t> friend class Matrice;
    template<typename U, size_t X, size_t Y>
    friend ostream& operator<<(ostream&, const Matrice<U, X, Y>&);

public:
    Matrice() {
        for (size_t i = 0; i < N; ++i)
            for (size_t j = 0; j < M; ++j)
                data[i][j] = 0;
    }

    Matrice(initializer_list<initializer_list<T>> init) {
        size_t i = 0;
        for (auto& row : init) {
            size_t j = 0;
            for (auto& val : row) {
                if (i < N && j < M)
                    data[i][j] = val;
                ++j;
            }
            ++i;
        }
    }

    Matrice<T, N, M> operator+(const Matrice<T, N, M>& other) const {
        Matrice<T, N, M> result;
        for (size_t i = 0; i < N; ++i)
            for (size_t j = 0; j < M; ++j)
                result.data[i][j] = data[i][j] + other.data[i][j];
        return result;
    }

    Matrice<T, N, M> operator-(const Matrice<T, N, M>& other) const {
        Matrice<T, N, M> result;
        for (size_t i = 0; i < N; ++i)
            for (size_t j = 0; j < M; ++j)
                result.data[i][j] = data[i][j] - other.data[i][j];
        return result;
    }

    template<size_t P>
    Matrice<T, N, P> operator*(const Matrice<T, M, P>& other) const {
        Matrice<T, N, P> result;
        for (size_t i = 0; i < N; ++i)
            for (size_t j = 0; j < P; ++j) {
                result.data[i][j] = 0;
                for (size_t k = 0; k < M; ++k)
                    result.data[i][j] += data[i][k] * other.data[k][j];
            }
        return result;
    }

    friend ostream& operator<<(ostream& os, const Matrice<T, N, M>& mat) {
        for (size_t i = 0; i < N; ++i) {
            for (size_t j = 0; j < M; ++j)
                os << mat.data[i][j] << " ";
            os << "\n";
        }
        return os;
    }
};

int main() {
    Matrice<int, 2, 2> A{{{1, 2}, {3, 4}}};
    Matrice<int, 2, 2> B{{{5, 6}, {7, 8}}};
    Matrice<int, 2, 2> C = A + B;
    Matrice<int, 2, 2> D = A - B;
    Matrice<int, 2, 2> E = A * B;

    cout << "A + B =\n" << C;
    cout << "A - B =\n" << D;
    cout << "A * B =\n" << E;

    Matrice<double, 2, 3> X{{{1.1, 2.2, 3.3}, {4.4, 5.5, 6.6}}};
    Matrice<double, 3, 2> Y{{{1.0, 0.5}, {0.5, 1.0}, {1.5, 2.0}}};
    auto Z = X * Y;
    cout << "X * Y =\n" << Z;

    return 0;
}
