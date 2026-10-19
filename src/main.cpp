#include <cstddef>
#include <iostream>
#include <limits>

#include "matrix_ops.h"

const std::size_t MAX_SIZE = 100;

bool read_int(const char* prompt, int& out) {
    while (true) {
        std::cout << prompt;
        if (std::cin >> out) {
            return true;
        }
        if (std::cin.eof()) {
            return false;
        }
        std::cout << "Ошибка: нужно целое число.\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

bool read_size(const char* prompt, std::size_t lo, std::size_t hi, std::size_t& out) {
    int value = 0;
    while (true) {
        if (!read_int(prompt, value)) {
            return false;
        }
        if (value >= 0 && (std::size_t)value >= lo && (std::size_t)value <= hi) {
            out = value;
            return true;
        }
        std::cout << "Ошибка: число должно быть от " << lo << " до " << hi << ".\n";
    }
}

bool no_matrix(int** m) {
    if (m == nullptr) {
        std::cout << "Матрица не создана. Выберите пункт 1.\n";
        return true;
    }
    return false;
}

bool create(int**& m, std::size_t& rows, std::size_t& cols) {
    std::size_t r = 0;
    std::size_t c = 0;
    if (!read_size("Число строк (1..100): ", 1, MAX_SIZE, r)) {
        return false;
    }
    if (!read_size("Число столбцов (1..100): ", 1, MAX_SIZE, c)) {
        return false;
    }

    matrix_delete(m, rows);
    m = matrix_create(r, c);
    rows = r;
    cols = c;

    std::cout << "Введите " << rows * cols << " элементов построчно:\n";
    for (std::size_t i = 0; i < rows; ++i) {
        for (std::size_t j = 0; j < cols; ++j) {
            if (!read_int("", m[i][j])) {
                return false;
            }
        }
    }
    std::cout << "Матрица " << rows << "x" << cols << ":\n";
    matrix_print(m, rows, cols);
    return true;
}

bool fill(int** m, std::size_t rows, std::size_t cols) {
    if (no_matrix(m)) {
        return true;
    }
    int value = 0;
    if (!read_int("Значение: ", value)) {
        return false;
    }
    matrix_fill(m, rows, cols, value);
    matrix_print(m, rows, cols);
    return true;
}

bool swap_menu(int** m, std::size_t rows, std::size_t cols) {
    if (no_matrix(m)) {
        return true;
    }
    std::cout << "1. Обменять строки\n2. Обменять столбцы\n";
    std::size_t choice = 0;
    if (!read_size("Выбор: ", 1, 2, choice)) {
        return false;
    }

    std::cout << "До:\n";
    matrix_print(m, rows, cols);

    std::size_t a = 0;
    std::size_t b = 0;
    if (choice == 1) {
        if (!read_size("Первая строка: ", 0, rows - 1, a) ||
            !read_size("Вторая строка: ", 0, rows - 1, b)) {
            return false;
        }
        matrix_row_swap(m, cols, a, b);
        std::cout << "После обмена строк " << a << " и " << b << ":\n";
    } else {
        if (!read_size("Первый столбец: ", 0, cols - 1, a) ||
            !read_size("Второй столбец: ", 0, cols - 1, b)) {
            return false;
        }
        matrix_col_swap(m, rows, a, b);
        std::cout << "После обмена столбцов " << a << " и " << b << ":\n";
    }
    matrix_print(m, rows, cols);
    return true;
}

bool find(int** m, std::size_t rows, std::size_t cols) {
    if (no_matrix(m)) {
        return true;
    }
    int target = 0;
    if (!read_int("Искомое значение: ", target)) {
        return false;
    }
    std::size_t row = 0;
    std::size_t col = 0;
    if (matrix_find(m, rows, cols, target, row, col)) {
        std::cout << "Найдено: m[" << row << "][" << col << "] = " << target << '\n';
    } else {
        std::cout << "Значение " << target << " не найдено.\n";
    }
    return true;
}

int main() {
    int** matrix = nullptr;
    std::size_t rows = 0;
    std::size_t cols = 0;

    bool running = true;
    while (running) {
        std::cout << "\n===== Вариант 16: матрицы =====\n"
                     "1. Создать матрицу\n"
                     "2. Заполнить значением\n"
                     "3. Напечатать\n"
                     "4. Алгоритм варианта (обмен строк / столбцов)\n"
                     "5. Поиск элемента\n"
                     "0. Выход\n";

        std::size_t choice = 0;
        if (!read_size("> ", 0, 5, choice)) {
            break;
        }

        switch (choice) {
            case 1:
                running = create(matrix, rows, cols);
                break;
            case 2:
                running = fill(matrix, rows, cols);
                break;
            case 3:
                if (!no_matrix(matrix)) {
                    matrix_print(matrix, rows, cols);
                }
                break;
            case 4:
                running = swap_menu(matrix, rows, cols);
                break;
            case 5:
                running = find(matrix, rows, cols);
                break;
            case 0:
                running = false;
                break;
        }
    }

    matrix_delete(matrix, rows);
    std::cout << "\nВыход.\n";
    return 0;
}
