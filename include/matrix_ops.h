#pragma once

#include <cstddef>
#include <iostream>

int** matrix_create(std::size_t rows, std::size_t cols);
void matrix_delete(int**& m, std::size_t rows);
void matrix_fill(int** m, std::size_t rows, std::size_t cols, int value);
void matrix_print(const int* const* m, std::size_t rows, std::size_t cols,
                  std::ostream& out = std::cout);

bool matrix_find(const int* const* m, std::size_t rows, std::size_t cols, int target,
                 std::size_t& out_row, std::size_t& out_col);

void matrix_row_swap(int** m, std::size_t cols, std::size_t r1, std::size_t r2);
void matrix_col_swap(int** m, std::size_t rows, std::size_t c1, std::size_t c2);
