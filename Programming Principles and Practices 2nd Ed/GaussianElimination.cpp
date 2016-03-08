#include<iostream>
#include<stdexcept>
#include"Matrix11.h"
#include"MatrixIO11.h"
#include<cmath>

using Matrix = Numeric_lib::Matrix<double,2>;
using Vector = Numeric_lib::Matrix<double>;
using Index  = ssize_t;

void partial_pivoting(Matrix& A, Vector& b)
{
    const Index n = A.dim1();

    // Traverse each column, making zeros under the diagonal:
    for(Index j = 0; j<n; ++j){
        Index pivot_row = j;

        // Search suitable pivot:
        for(Index k = j+1; k<n; ++k)
            if(std::abs(A(k,j)) > std::abs(A(pivot_row,j))) pivot_row = k;

        // Swap rows if pivot found:
        if(pivot_row!=j){
            A.swap_rows(j,pivot_row);
            std::swap(b(j),b(pivot_row));
        }

        // Perform elimination:
        for(Index i = j+1; i<n; ++i){
            const double pivot = A(j,j);
            if(!pivot) throw std::runtime_error("The system doesn't have a unique solution");

            const double mult = A(i,j)/pivot;
            A[i].slice(j) = Numeric_lib::scale_and_add(A[j].slice(j),-mult,A[i].slice(j));
            b(i) -= mult*b(j);
        }
    }
}

Vector back_substitution(const Matrix& A, const Vector& b)
{
    const Index n = A.dim1();
    Vector x(n);

    for(Index i = n-1; i>=0; --i){
        double s = b(i)-Numeric_lib::dot_product(A[i].slice(i+1), x.slice(i+1));

        if(double m = A(i,i))
            x(i) = s/m;
        else
            throw std::runtime_error("Back substition failed.");
    }

    return x;
}

Vector gaussian_elimination(Matrix A, Vector b)
{
    partial_pivoting(A, b);
    return back_substitution(A, b);
}

int main(void)
{

    std::cout << "Insert the number of rows: ";
    ssize_t rows;
    std::cin >> rows;
    std::cout << "Insert the number of cols: ";
    ssize_t cols;
    std::cin >> cols;

    std::cout << "Insert the associated matrix: \n";
    Matrix A(rows,cols);
    std::cin >> A;
    std::cout << "Insert the constrained vector: \n";
    Vector b(rows);
    std::cin >> b;

    std::cout << "The unique solution is: ";
    std::cout << gaussian_elimination(A,b) << '\n';

    return 0;
}
