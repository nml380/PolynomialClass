//
//  polynomial.h
//  hw8-clone
//
//  Created by Noah LaPoint on 5/2/22.
//

#ifndef polynomial_h
#define polynomial_h

#include <iostream>
#include <vector>

namespace mathWorld{
    struct Node;
    class Polynomial{
        friend Polynomial operator+(const Polynomial& lhs, const Polynomial& rhs);
        friend bool operator==(const Polynomial& lhs, const Polynomial& rhs);
        friend bool operator!=(const Polynomial& lhs, const Polynomial& rhs);
        friend std::ostream& operator<<(std::ostream& os,const Polynomial& rhs);
    public:
        Polynomial(const std::vector<int>& vals);
        Polynomial();
        Polynomial(const Polynomial& rhs);
        ~Polynomial();
        Polynomial& operator=(const Polynomial& rhs);
        Polynomial operator+=(const Polynomial& rhs);
        int evaluate(int n);
    private:
        Node* terms;
        size_t degree;
    };
    Polynomial operator+(const Polynomial& lhs,const Polynomial& rhs);
    bool operator==(const Polynomial& lhs, const Polynomial& rhs);
    bool operator!=(const Polynomial& lhs, const Polynomial& rhs);
    void doNothing(Polynomial temp);
}


#endif /* polynomial_h */
