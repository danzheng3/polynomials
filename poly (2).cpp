#include "poly.h"
#include <iostream>
#include <algorithm>
#include <map>

polynomial::polynomial() {
    terms.emplace_back(0, 0);
}

polynomial::polynomial(const polynomial& other) : terms(other.get_terms()) {}

polynomial& polynomial::operator=(const polynomial& other) {
    terms = other.get_terms();
    return *this;
}

void polynomial::print() const {
    if (terms.empty() || (terms.size() == 1 && terms[0].second == 0)) {
        std::cout << "0";
    } else {
        bool first = true;
        for (const auto& term : terms) {
            if (!first && term.second > 0) std::cout << " + ";
            std::cout << term.second << "x^" << term.first;
            first = false;
        }
    }
    std::cout << std::endl;
}

size_t polynomial::find_degree_of() const {
    if (terms.empty()) {
        return 0;
    }

    return terms.front().first;
}


std::vector<std::pair<power, coeff>> polynomial::canonical_form() const {

    if (terms.empty() || (terms.size() == 1 && terms[0].second == 0)) {
        return {{0, 0}};
    }

    std::vector<std::pair<power, coeff>> cleaned_terms;
    for (const auto& term : terms) {
        if (term.second != 0) {
            cleaned_terms.push_back(term);
        }
    }

    return cleaned_terms;
}



// Addition of two polynomials
polynomial operator+(const polynomial& lhs, const polynomial& rhs) {
    polynomial result;
    for (const auto& term : lhs.get_terms()) {
        result.add_term(term.first, term.second);
    }
    for (const auto& term : rhs.get_terms()) {
        result.add_term(term.first, term.second);
    }
    return result;
}


// Addition of polynomial and integer
polynomial operator+(const polynomial& lhs, int rhs) {
    polynomial result(lhs);
    if (result.get_terms().empty() || result.get_terms().back().first != 0) {
        result.add_term(0, rhs);
    } else {
        result.add_term(0, rhs);
    }
    return result;
}


// Addition of integer and polynomial
polynomial operator+(int lhs, const polynomial& rhs) {
    return rhs + lhs;
}

// Multiplication of two polynomials
polynomial operator*(const polynomial& lhs, const polynomial& rhs) {
    polynomial result;
    std::map<power, coeff> product_terms;
    for (const auto& lterm : lhs.get_terms()) {
        for (const auto& rterm : rhs.get_terms()) {
            power combined_power = lterm.first + rterm.first;
            coeff combined_coeff = lterm.second * rterm.second;
            product_terms[combined_power] += combined_coeff;
        }
    }
    for (const auto& term : product_terms) {
        if (term.second != 0) {
            result.add_term(term.first, term.second);
        }
    }
    return result;
}



// Multiplication of polynomial by integer
polynomial operator*(const polynomial& lhs, int rhs) {
    polynomial result;
    for (const auto& term : lhs.get_terms()) {
        coeff new_coeff = term.second * rhs;
        if (new_coeff != 0) {
            result.add_term(term.first, new_coeff);
        }
    }
    return result;
}



// Multiplication of integer by polynomial
polynomial operator*(int lhs, const polynomial& rhs) {
    return rhs * lhs;
}

// Modulo operation between two polynomials
polynomial operator%(const polynomial& lhs, const polynomial& rhs) {
    polynomial result(lhs);
    polynomial temp;

    while (!result.get_terms().empty() && result.get_terms().front().first >= rhs.get_terms().front().first) {
        power degree_diff = result.get_terms().front().first - rhs.get_terms().front().first;
        coeff coeff_div = result.get_terms().front().second / rhs.get_terms().front().second;

        temp.clear_terms();
        temp.add_term(degree_diff, coeff_div);

        result = result - temp * rhs;
    }

    return result;
}



polynomial operator-(const polynomial& lhs, const polynomial& rhs) {
    polynomial result(lhs);
    for (const auto& term : rhs.get_terms()) {
        result.add_term(term.first, -term.second);
    }
    return result;
}


polynomial operator-(const polynomial& lhs, int rhs) {
    polynomial result(lhs);

    result.add_term(0, -rhs);
    return result;
}


polynomial operator-(int lhs, const polynomial& rhs) {
    polynomial result;

    for (const auto& term : rhs.get_terms()) {
        result.add_term(term.first, -term.second);
    }

    result.add_term(0, lhs);
    return result;
}



const std::vector<std::pair<power, coeff>>& polynomial::get_terms() const {
    return terms;
}


void polynomial::add_term(power pwr, coeff cff) {
    auto it = std::find_if(terms.begin(), terms.end(), [pwr](const std::pair<power, coeff>& term) { return term.first == pwr; });

    if (it != terms.end()) {
        it->second += cff;
        if (it->second == 0) {
            terms.erase(it);
        }
    } else {
        terms.emplace_back(pwr, cff);
        std::sort(terms.begin(), terms.end(), [](const std::pair<power, coeff>& a, const std::pair<power, coeff>& b) {
            return a.first > b.first;
        });
    }
}

void polynomial::clear_terms() {
    terms.clear();
}
