#include <iostream>
#include "poly.h"

int main() {
    // Create polynomials
    polynomial p1({{2, 3}, {1, 2}, {0, 1}}); // 3x^2 + 2x + 1
    polynomial p2({{3, 1}, {1, -2}, {0, 3}}); // x^3 - 2x + 3
    
    // Print polynomials
    std::cout << "p1: ";
    p1.print();
    std::cout << "p2: ";
    p2.print();

    // Addition
    polynomial sum = p1 + p2;
    std::cout << "p1 + p2: ";
    sum.print();

    // Multiplication
    polynomial product = p1 * p2;
    std::cout << "p1 * p2: ";
    product.print();

    // Degree
    std::cout << "Degree of p1: " << p1.find_degree_of() << std::endl;

    // Canonical form
    std::vector<std::pair<power, coeff>> p1_canonical = p1.canonical_form();
    std::cout << "Canonical form of p1: ";
    for (const auto& term : p1_canonical) {
        std::cout << "(" << term.first << ", " << term.second << ") ";
    }
    std::cout << std::endl;

    return 0;
}
