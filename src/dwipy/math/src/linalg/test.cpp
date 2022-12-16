/*
#include "matrix.h"

using namespace linalg;

int main() {
    Matrix<double> id = Matrix<double>::getIdentity(5);
    Matrix<double> test(id.getData(), id.getWidth(), id.getHeight());
    test[0][3] = 2;
    std::cout << id << "\n\n" << test  << std::endl;
    return 0;
}
*/