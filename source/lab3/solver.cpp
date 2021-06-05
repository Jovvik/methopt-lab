#include <lab2/vector.h>
#include <lab3/solver.h>

#include <fstream>
#include <string>

using namespace lab3;

lab2::Vector Solver::solve(const lab2::Matrix& A, const lab2::Vector& b) {
    std::ofstream A_of("data/A.txt");
    A_of << A;
    A_of.close();
    std::ofstream b_of("data/b.txt");
    b_of << b;
    b_of.close();
    std::string command = "java -cp build-gradle/classes/java/main matrix.Solver " + std::to_string(A.size());
    std::system(command.c_str());
    std::ifstream x_if("data/x.txt");
    lab2::Vector x(x_if);
    x_if.close();
    return x;
}
