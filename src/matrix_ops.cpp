#include "matrix_ops.h"

#include <iomanip>

int** matrix_create(std::size_t rows, std::size_t cols) {
    if (rows == 0 || cols == 0) {
        return nullptr;
    }
    int** m = new int*[rows];
    for (std::size_t i = 0; i < rows; ++i) {
        m[i] = new int[cols]{};
    }
    return m;
}

void matrix_delete(int**& m, std::size_t rows) {
    if (m == nullptr) {
        return;
    }
    for (std::size_t i = 0; i < rows; ++i) {
        delete[] m[i];
    }
    delete[] m;
    m = nullptr;
}

void matrix_fill(int** m, std::size_t rows, std::size_t cols, int value) {
    if (m == nullptr) {
        return;
    }
    for (std::size_t i = 0; i < rows; ++i) {
        for (std::size_t j = 0; j < cols; ++j) {
            m[i][j] = value;
        }
    }
}

void matrix_print(const int* const* m, std::size_t rows, std::size_t cols, std::ostream& out) {
    if (m == nullptr || rows == 0 || cols == 0) {
        out << "(пустая матрица)\n";
        return;
    }
    for (std::size_t i = 0; i < rows; ++i) {
        for (std::size_t j = 0; j < cols; ++j) {
            out << std::setw(6) << m[i][j];
        }
        out << '\n';
    }
}

bool matrix_find(const int* const* m, std::size_t rows, std::size_t cols, int target,
                 std::size_t& out_row, std::size_t& out_col) {
    if (m == nullptr) {
        return false;
    }
    for (std::size_t i = 0; i < rows; ++i) {
        for (std::size_t j = 0; j < cols; ++j) {
            if (m[i][j] == target) {
                out_row = i;
                out_col = j;
                return true;
            }
        }
    }
    return false;
}

void matrix_row_swap(int** m, std::size_t, std::size_t r1, std::size_t r2) {
    if (m == nullptr || r1 == r2) {
        return;
    }
    int* tmp = m[r1];
    m[r1] = m[r2];
    m[r2] = tmp;
}

void matrix_col_swap(int** m, std::size_t rows, std::size_t c1, std::size_t c2) {
    if (m == nullptr || c1 == c2) {
        return;
    }
    for (std::size_t i = 0; i < rows; ++i) {
        int tmp = m[i][c1];
        m[i][c1] = m[i][c2];
        m[i][c2] = tmp;
    }
}
