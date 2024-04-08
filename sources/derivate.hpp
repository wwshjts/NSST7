#include <string>
#include "ScopedPointer.hpp"

class Expression {

public: 
    virtual ScopedPointer<Expression> derivate(const std::string& var) = 0;
    virtual ~Expression() {};
    virtual operator std::string() const = 0;
    virtual Expression* copy() const = 0;
};

class Var : public Expression {
    std::string var_;

public:
    Var(std::string var);
    ~Var() = default;
    ScopedPointer<Expression> derivate(const std::string& var);
    operator std::string() const;
    Expression* copy() const;
};

class Val : public Expression {
    double val_;

public:
    Val(double val);    
    ~Val() = default;
    ScopedPointer<Expression> derivate(const std::string& var);
    operator std::string() const; 
    Expression* copy() const;
};

class Binary : public Expression {
protected:
    ScopedPointer<Expression> left_;
    ScopedPointer<Expression> right_;

public:
    Binary(ScopedPointer<Expression> left, ScopedPointer<Expression> right);
    ~Binary() = default;
};

class Unary : public Expression {
protected:
    ScopedPointer<Expression> expr_;
public:
    Unary(ScopedPointer<Expression> expr);
    ~Unary() = default;
};

class Exp : public Unary {
public:
    Exp(ScopedPointer<Expression> expr) : Unary { expr } {};
    ScopedPointer<Expression> derivate(const std::string& var);
    operator std::string() const; 
    Expression* copy() const;
};

class Plus : public Binary {
public:
    Plus(ScopedPointer<Expression> left, ScopedPointer<Expression> right);
    ScopedPointer<Expression> derivate(const std::string& var);
    operator std::string() const; 
    Expression* copy() const;
};


class Sub : public Binary {
public:
    Sub(ScopedPointer<Expression> l, ScopedPointer<Expression> r);
    
    ScopedPointer<Expression> derivate(const std::string& var);
    operator std::string() const; 
    Expression* copy() const;
};

class Mult : public Binary {
public:
    Mult(ScopedPointer<Expression> l, ScopedPointer<Expression> r);
    ScopedPointer<Expression> derivate(const std::string& var);
    operator std::string() const; 
    Expression* copy() const;
};

class Div : public Binary {

public:
    Div(ScopedPointer<Expression> l, ScopedPointer<Expression> r);
    
    ScopedPointer<Expression> derivate(const std::string& var);
    operator std::string() const; 
    Expression* copy() const;
};
