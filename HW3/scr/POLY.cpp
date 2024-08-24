#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;

class Polynomial; // 前向宣告

class Term {
    friend class Polynomial;
public:
    float coef; 
    int exp;    
};

class Polynomial {
private:
    Term* termArray; // 非零項的數組
    int capacity;    // termArray 的大小
    int terms;       // 非零項的數量

public:
    Polynomial(int cap = 10) : capacity(cap), terms(0) {
        termArray = new Term[capacity];
    }

    ~Polynomial() {
        delete[] termArray;
    }

    friend istream& operator>>(istream& input, Polynomial& p);
    friend ostream& operator<<(ostream& output, const Polynomial& p);
    
    Polynomial operator+(const Polynomial& other) const;
    Polynomial operator-(const Polynomial& other) const;
    Polynomial operator*(const Polynomial& other) const;
    void NewTerm(float theCoeff, int theExp);
    
    // 計算多項式在 x 值處的值
    float evaluate(float x) const;
};

istream& operator>>(istream& input, Polynomial& p) {
    int numTerms;
    cout << "輸入項數: ";
    input >> numTerms;

    for (int i = 0; i < numTerms; ++i) {
        float coef;
        int exp;
        cout << "輸入係數和指數: ";
        input >> coef >> exp;
        p.NewTerm(coef, exp);
    }

    sort(p.termArray, p.termArray + p.terms, [](const Term& a, const Term& b) {
        return a.exp > b.exp;
    });

    return input;
}

ostream& operator<<(ostream& output, const Polynomial& p) {
    for (int i = 0; i < p.terms; ++i) {
        output << p.termArray[i].coef << "x^" << p.termArray[i].exp;
        if (i != p.terms - 1) output << " + ";
    }
    return output;
}

void Polynomial::NewTerm(float theCoeff, int theExp) {
    for (int i = 0; i < terms; ++i) {
        if (termArray[i].exp == theExp) {
            termArray[i].coef += theCoeff;
            return;
        }
    }
    if (terms == capacity) {
        capacity *= 2;
        Term* newArray = new Term[capacity];
        copy(termArray, termArray + terms, newArray);
        delete[] termArray;
        termArray = newArray;
    }
    termArray[terms].coef = theCoeff;
    termArray[terms++].exp = theExp;
}

Polynomial Polynomial::operator+(const Polynomial& other) const {
    Polynomial c;
    int aPos = 0, bPos = 0;
    while (aPos < terms && bPos < other.terms) {
        if (termArray[aPos].exp == other.termArray[bPos].exp) {
            float t = termArray[aPos].coef + other.termArray[bPos].coef;
            if (t) c.NewTerm(t, termArray[aPos].exp);
            aPos++;
            bPos++;
        } else if (termArray[aPos].exp < other.termArray[bPos].exp) {
            c.NewTerm(other.termArray[bPos].coef, other.termArray[bPos].exp);
            bPos++;
        } else {
            c.NewTerm(termArray[aPos].coef, termArray[aPos].exp);
            aPos++;
        }
    }
    for (; aPos < terms; aPos++)
        c.NewTerm(termArray[aPos].coef, termArray[aPos].exp);
    for (; bPos < other.terms; bPos++)
        c.NewTerm(other.termArray[bPos].coef, other.termArray[bPos].exp);
    return c;
}

Polynomial Polynomial::operator-(const Polynomial& other) const {
    Polynomial c;
    int aPos = 0, bPos = 0;
    while (aPos < terms && bPos < other.terms) {
        if (termArray[aPos].exp == other.termArray[bPos].exp) {
            float t = termArray[aPos].coef - other.termArray[bPos].coef;
            if (t) c.NewTerm(t, termArray[aPos].exp);
            aPos++;
            bPos++;
        } else if (termArray[aPos].exp < other.termArray[bPos].exp) {
            c.NewTerm(-other.termArray[bPos].coef, other.termArray[bPos].exp);
            bPos++;
        } else {
            c.NewTerm(termArray[aPos].coef, termArray[aPos].exp);
            aPos++;
        }
    }
    for (; aPos < terms; aPos++)
        c.NewTerm(termArray[aPos].coef, termArray[aPos].exp);
    for (; bPos < other.terms; bPos++)
        c.NewTerm(-other.termArray[bPos].coef, other.termArray[bPos].exp);
    return c;
}

Polynomial Polynomial::operator*(const Polynomial& other) const {
    Polynomial c;
    for (int i = 0; i < terms; ++i) {
        for (int j = 0; j < other.terms; ++j) {
            float newCoef = termArray[i].coef * other.termArray[j].coef;
            int newExp = termArray[i].exp + other.termArray[j].exp;
            c.NewTerm(newCoef, newExp);
        }
    }
    return c;
}

float Polynomial::evaluate(float x) const {
    float result = 0.0;
    for (int i = 0; i < terms; ++i) {
        result += termArray[i].coef * pow(x, termArray[i].exp);
    }
    return result;
}

int main() {
    Polynomial p1, p2;

    cout << "輸入第一個多項式:\n";
    cin >> p1;
    cout << "輸入第二個多項式:\n";
    cin >> p2;

    cout << "多項式1: " << p1 << endl;
    cout << "多項式2: " << p2 << endl;

    Polynomial p3 = p1 + p2;
    Polynomial p4 = p1 - p2;
    Polynomial p5 = p1 * p2;

    cout << "多項式加法結果: (" << p1 << ") + (" << p2 << ") = " << p3 << endl;
    cout << "多項式減法結果: (" << p1 << ") - (" << p2 << ") = " << p4 << endl;
    cout << "多項式乘法結果: (" << p1 << ") * (" << p2 << ") = " << p5 << endl;

    return 0;
}
