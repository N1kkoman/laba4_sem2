#include <iostream>
#include <istream>

template<typename T, size_t N, size_t M>
class Matrix {
private:
    T data[N][M];

public:
    // Конструктор по умолчанию
    Matrix() {
        for (size_t i = 0; i < N; ++i) {
            for (size_t j = 0; j < M; ++j) {
                data[i][j] = T();
            }
        }
    }

    // Конструктор копирования
    Matrix(const Matrix& other) {
        for (size_t i = 0; i < N; ++i) {
            for (size_t j = 0; j < M; ++j) {
                data[i][j] = other.data[i][j];
            }
        }
    }

    // Оператор присваивания копированием
    Matrix& operator=(const Matrix& other) {
        if (this == &other) {
            return *this;
        }
        for (size_t i = 0; i < N; ++i) {
            for (size_t j = 0; j < M; ++j) {
                data[i][j] = other.data[i][j];
            }
        }
        return *this;
    }

    // Оператор ввода
    friend std::istream& operator>>(std::istream& is, Matrix& m) {
        for (size_t i = 0; i < N; ++i) {
            for (size_t j = 0; j < M; ++j) {
                is >> m.data[i][j];
            }
        }
        return is;
    }

    // Оператор вывода
    friend std::ostream& operator<<(std::ostream& os, const Matrix& m) {
        for (size_t i = 0; i < N; ++i) {
            for (size_t j = 0; j < M; ++j) {
                os << m.data[i][j] << " ";
            }
            os << std::endl;
        }
        return os;
    }

    // Операторы +
    Matrix operator+(const Matrix& other) const {
        Matrix result;
        for (size_t i = 0; i < N; ++i) {
            for (size_t j = 0; j < M; ++j) {
                result.data[i][j] = data[i][j] + other.data[i][j];
            }
        }
        return result;
    }

    // Оператор +=
    Matrix& operator+=(const Matrix& other) {
        for (size_t i = 0; i < N; ++i) {
            for (size_t j = 0; j < M; ++j) {
                data[i][j] += other.data[i][j];
            }
        }
        return *this;
    }

    // Оператор *
    Matrix operator*(const Matrix& other) const {
        Matrix result;
        for (size_t i = 0; i < N; ++i) {
            for (size_t j = 0; j < M; ++j) {
                for (size_t k = 0; k < M; ++k) {
                    result.data[i][j] += data[i][k] * other.data[k][j];
                }
            }
        }
        return result;
    }

    // Оператор *=
    Matrix& operator*=(const Matrix& other) {
        *this = *this * other;
        return *this;
    }

    // Оператор ++
    Matrix& operator++() {
        for (size_t i = 0; i < N; ++i) {
            for (size_t j = 0; j < M; ++j) {
                ++data[i][j];
            }
        }
        return *this;
    }

    // Метод вычисления определителя
    T determinant() const {
        static_assert(N == M, "Matrix must be square");
        switch (N) {
        case 1:
            return data[0][0];
            break;
        case 2:
            return data[0][0] * data[1][1] - data[0][1] * data[1][0];
            break;
        case 3:
            return data[0][0] * data[1][1] * data[2][2]
                + data[0][1] * data[1][2] * data[2][0]
                + data[0][2] * data[1][0] * data[2][1]
                - data[0][2] * data[1][1] * data[2][0]
                - data[0][1] * data[1][0] * data[2][2]
                - data[0][0] * data[1][2] * data[2][1];
            break;
        default:
            std::cout << "Determinant is not implemented for matrices larger than 3x3";
            std::exit(1);
        }
    }
    
    // Метод получения или изменения элемента матрицы по индексу
    T& at(size_t firstIndex, size_t secondIndex) {
        if (firstIndex < N && secondIndex < M)
        {
            return data[firstIndex][secondIndex];
        }
        if (firstIndex > N || secondIndex > M)
        {
            std::abort();
        }

    }
};

int main() {
    // Создание и вывод матрицы
    Matrix<int, 3, 3> mat1;
    std::cout << "Enter a 3x3 matrix: " << std::endl;
    std::cin >> mat1;
    std::cout << "Matrix mat1:" << std::endl;
    std::cout << mat1;

    std::cout << "Matrix mat1 det:" << mat1.determinant() << std::endl;

    // Копирование матрицы
    Matrix<int, 3, 3> mat2 = mat1;
    std::cout << "Matrix mat2:" << std::endl;
    std::cout << mat2;

    // Изменение элемента матрицы
    mat2.at(0, 0) = 5;
    std::cout << "Matrix mat2 after changing element (0, 0):" << std::endl;
    std::cout << mat2;

    // Операции с матрицами
    Matrix<int, 3, 3> mat3 = mat1 + mat2;
    std::cout << "Matrix mat3 = mat1 + mat2:" << std::endl;
    std::cout << mat3;

    mat1 += mat2;
    std::cout << "Matrix mat1:" << std::endl;
    std::cout << mat1;

    Matrix<int, 3, 3> mat4 = mat1 * mat2;
    std::cout << "Matrix mat4 = mat1 * mat2:" << std::endl;
    std::cout << mat4;

    mat1 *= mat2;
    std::cout << "Matrix mat1 *= mat2:" << std::endl;
    std::cout << mat1;

    // Увеличение всех элементов матрицы на 1
    ++mat1;
    std::cout << "Matrix mat1 after ++:" << std::endl;
    std::cout << mat1;
    
    // Детерминант для матрицы 2 на 2
    Matrix<int, 2, 2> mat2x2;
    std::cout << "Enter a 2x2 matrix: " << std::endl;
    std::cin >> mat2x2;
    std::cout << "Matrix mat2x2:" << std::endl;
    std::cout << mat2x2;

    std::cout << "Matrix mat2x2 det:" << mat2x2.determinant() << std::endl;

    //std::cout << mat2x2 + mat1; // матрицы с разными размерностями не складываются

    return 0;
}
