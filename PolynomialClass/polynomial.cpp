//
//  polynomial.cpp
//  hw8-clone
//
//  Created by Noah LaPoint on 5/2/22.
//

#include "polynomial.h"

using namespace std;

namespace mathWorld{

    struct Node {
        Node(int data = 0, Node* next = nullptr) : data(data), next(next) {}
        int data;
        Node* next;
    };
    void doNothing(Polynomial temp) {}
    Polynomial operator+(const Polynomial& lhs, const Polynomial& rhs)
    {
        Polynomial temp = lhs;
        temp += rhs;
        return temp;
    }
    bool operator==(const Polynomial& lhs, const Polynomial& rhs)
    {
        if (lhs.degree != rhs.degree) return false;
        Node* headptr_1 = lhs.terms;
        Node* headptr_2 = rhs.terms;
        for(size_t x = 0; x < lhs.degree;x++)
        {
            if (headptr_1->data != headptr_2->data) return false;
            headptr_1 = headptr_1->next;
            headptr_2 =  headptr_2->next;
        }
        return true;
    }

    bool operator!=(const Polynomial& lhs, const Polynomial& rhs)
    {
        return !(lhs == rhs);
    }

    ostream& operator<<(ostream& os,const Polynomial& rhs)
    {
        Node* headptr = rhs.terms;
        for(size_t x = rhs.degree; x > 0; x--){
            if(headptr->data == 1) {os << "x^" << x << " + ";}
            else if (headptr->data != 0) {os << headptr->data << "x^" << x << " + ";}
            headptr = headptr->next;
        }
        os << headptr->data;
        return os;
    }
    Polynomial::Polynomial(const vector<int>& vals) : degree(vals.size() - 1),terms(new Node(vals[0]))
    {
        Node* headptr = terms;
        for(int x = 1; x < vals.size();x++)
        {
            headptr->next = new Node(vals[x]);
            headptr = headptr->next;
        }
    }
    Polynomial::Polynomial() : degree(0),terms(new Node(0)){}
    Polynomial::Polynomial(const Polynomial& rhs) : degree(rhs.degree),terms(new Node(rhs.terms->data))
    {
        Node* headptr = terms;
        Node* rhs_pointer = rhs.terms;
        rhs_pointer = rhs_pointer->next;
        for(int x = 0; x < degree;x++)
        {
            headptr->next = new Node(rhs_pointer->data);
            headptr = headptr->next;
            rhs_pointer = rhs_pointer->next;
        }
    }
    Polynomial::~Polynomial(){
        if(terms != nullptr)
        {
            while (terms) {
                Node* p = terms;
                terms = terms->next;
                delete p;
            }
        }
    }
    Polynomial& Polynomial::operator=(const Polynomial& rhs){
        if(this != &rhs)
        {
            degree =  rhs.degree;
            Node* remove = terms;
            while (remove != nullptr) {
                Node* p = remove;
                remove = remove->next;
                delete p;
            }
            Node* walker = rhs.terms;
            Node* add_terms = terms;
            while(walker!=nullptr)
            {
                add_terms->next = new Node(walker->data);
                walker = walker->next;
                add_terms = add_terms->next;
            }
        }
        return *this;
    }

    Polynomial Polynomial::operator+=(const Polynomial& rhs){
        if(this != &rhs)
        {
            if (degree == rhs.degree)
            {
                Node* headptr_2 = rhs.terms;
                Node* headptr_1 = terms;
                while(headptr_1 != nullptr)
                {
                    headptr_1->data += headptr_2->data;
                    headptr_1 = headptr_1->next;
                    headptr_2 = headptr_2->next;
                }
            }
            else if (degree < rhs.degree){
                Node* headptr_1 = terms;
                Node* headptr_2 = rhs.terms;
                for(size_t x = 0; x < rhs.degree - degree;x++)
                {
                    Node* new_node = new Node(headptr_2->data,terms);
                    terms = new_node;
                    headptr_2 = headptr_2->next;
                }
                while(headptr_1 != nullptr)
                {
                    headptr_1->data += headptr_2->data;
                    headptr_1 = headptr_1->next;
                    headptr_2 = headptr_2->next;
                }
            }
            else{
                Node* headptr_1 = terms;
                Node* headptr_2 = rhs.terms;
                for(size_t x = 0; x < degree - rhs.degree;x++)
                {
                    headptr_1 = headptr_1->next;
                }
                while(headptr_1 != nullptr)
                {
                    headptr_1->data += headptr_2->data;
                    headptr_1 = headptr_1->next;
                    headptr_2 = headptr_2->next;
                }
        }
        }
        return *this;
    }
    int Polynomial::evaluate(int n){ // using Horners method for linear runtime
        Node* headptr = terms;
        int sum = headptr->data;
        headptr = headptr->next;
        while(headptr)
        {
            sum = (sum*n) + headptr->data;
            headptr = headptr->next;
        }
        return sum;
    }
}


