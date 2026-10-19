#include <gtest/gtest.h>

#include <cstddef>
#include <sstream>

#include "matrix_ops.h"

int** make_matrix(std::size_t rows, std::size_t cols, const int* values) {
    int** m = matrix_create(rows, cols);
    for (std::size_t i = 0; i < rows; ++i) {
        for (std::size_t j = 0; j < cols; ++j) {
            m[i][j] = values[i * cols + j];
        }
    }
    return m;
}

void expect_matrix_eq(const int* const* m, std::size_t rows, std::size_t cols,
                      const int* expected) {
    for (std::size_t i = 0; i < rows; ++i) {
        for (std::size_t j = 0; j < cols; ++j) {
            EXPECT_EQ(m[i][j], expected[i * cols + j]) << "at [" << i << "][" << j << "]";
        }
    }
}

TEST(MatrixCreate, AllocatesZeroInitialized) {
    int** m = matrix_create(3, 4);
    ASSERT_NE(m, nullptr);
    for (std::size_t i = 0; i < 3; ++i) {
        ASSERT_NE(m[i], nullptr);
        for (std::size_t j = 0; j < 4; ++j) {
            EXPECT_EQ(m[i][j], 0);
        }
    }
    matrix_delete(m, 3);
}

TEST(MatrixCreate, ZeroSizeReturnsNull) {
    EXPECT_EQ(matrix_create(0, 5), nullptr);
    EXPECT_EQ(matrix_create(5, 0), nullptr);
}

TEST(MatrixDelete, NullsPointer) {
    int** m = matrix_create(2, 2);
    matrix_delete(m, 2);
    EXPECT_EQ(m, nullptr);
}

TEST(MatrixDelete, NullIsSafe) {
    int** m = nullptr;
    matrix_delete(m, 10);
    EXPECT_EQ(m, nullptr);
}

TEST(MatrixFill, SetsEveryElement) {
    int** m = matrix_create(2, 3);
    matrix_fill(m, 2, 3, 7);
    const int expected[] = {7, 7, 7, 7, 7, 7};
    expect_matrix_eq(m, 2, 3, expected);
    matrix_delete(m, 2);
}

TEST(MatrixPrint, PrintsRowsAndEmpty) {
    const int values[] = {1, 2, 3, 4};
    int** m = make_matrix(2, 2, values);
    std::ostringstream out;
    matrix_print(m, 2, 2, out);
    EXPECT_EQ(out.str(), "     1     2\n     3     4\n");
    matrix_delete(m, 2);

    std::ostringstream empty;
    matrix_print(nullptr, 0, 0, empty);
    EXPECT_EQ(empty.str(), "(пустая матрица)\n");
}

TEST(MatrixFind, FoundWritesOutParams) {
    const int values[] = {1, 2, 3, 4, 5, 6};
    int** m = make_matrix(3, 2, values);
    std::size_t row = 99;
    std::size_t col = 99;
    EXPECT_TRUE(matrix_find(m, 3, 2, 4, row, col));
    EXPECT_EQ(row, 1u);
    EXPECT_EQ(col, 1u);
    matrix_delete(m, 3);
}

TEST(MatrixFind, NotFoundAndEmptyReturnFalse) {
    const int values[] = {1, 2, 3, 4};
    int** m = make_matrix(2, 2, values);
    std::size_t row = 99;
    std::size_t col = 99;
    EXPECT_FALSE(matrix_find(m, 2, 2, 42, row, col));
    EXPECT_FALSE(matrix_find(nullptr, 0, 0, 1, row, col));
    EXPECT_EQ(row, 99u);
    EXPECT_EQ(col, 99u);
    matrix_delete(m, 2);
}

TEST(MatrixRowSwap, VariantExample) {
    const int values[] = {1, 2, 3, 4, 5, 6};
    int** m = make_matrix(3, 2, values);
    matrix_row_swap(m, 2, 0, 2);
    const int expected[] = {5, 6, 3, 4, 1, 2};
    expect_matrix_eq(m, 3, 2, expected);
    matrix_delete(m, 3);
}

TEST(MatrixRowSwap, SwapsPointersNotData) {
    int** m = matrix_create(3, 2);
    int* row0 = m[0];
    int* row2 = m[2];
    matrix_row_swap(m, 2, 0, 2);
    EXPECT_EQ(m[0], row2);
    EXPECT_EQ(m[2], row0);
    matrix_delete(m, 3);
}

TEST(MatrixRowSwap, SameRowAndNullAreNoop) {
    const int values[] = {1, 2, 3, 4};
    int** m = make_matrix(2, 2, values);
    matrix_row_swap(m, 2, 1, 1);
    expect_matrix_eq(m, 2, 2, values);
    matrix_row_swap(nullptr, 0, 0, 1);
    matrix_delete(m, 2);
}

TEST(MatrixColSwap, SwapsColumns) {
    const int values[] = {1, 2, 3, 4, 5, 6};
    int** m = make_matrix(2, 3, values);
    matrix_col_swap(m, 2, 0, 2);
    const int expected[] = {3, 2, 1, 6, 5, 4};
    expect_matrix_eq(m, 2, 3, expected);
    matrix_delete(m, 2);
}

TEST(MatrixColSwap, SameColumnAndNullAreNoop) {
    const int values[] = {1, 2, 3, 4};
    int** m = make_matrix(2, 2, values);
    matrix_col_swap(m, 2, 0, 0);
    expect_matrix_eq(m, 2, 2, values);
    matrix_col_swap(nullptr, 0, 0, 1);
    matrix_delete(m, 2);
}

TEST(MatrixSwap, RowThenColumnCombined) {
    const int values[] = {1, 2, 3, 4, 5, 6};
    int** m = make_matrix(3, 2, values);
    matrix_row_swap(m, 2, 0, 2);
    matrix_col_swap(m, 3, 0, 1);
    const int expected[] = {6, 5, 4, 3, 2, 1};
    expect_matrix_eq(m, 3, 2, expected);
    matrix_delete(m, 3);
}
