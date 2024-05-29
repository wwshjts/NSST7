#include <string>
#include <sstream>
#include <iomanip>
#include <memory>
#define DOT 2

class Expression {

public: 
    virtual std::shared_ptr<Expression> derivate(const std::string& var) = 0;

    virtual operator std::string() const = 0;
};

class Var : public Expression {
    std::string var_;

public:
    Var(const std::string& var);
    static std::shared_ptr<Var> make_var(const std::string& var) {
        return std::shared_ptr<Var> ( new Var { var } );
    }

    std::shared_ptr<Expression> derivate(const std::string& var);

    operator std::string() const;
    ~Var() = default;
};

class Val : public Expression {
    double val_;

public:
    Val(double val);    
    static std::shared_ptr<Expression> make_val(double val) {
        return std::shared_ptr<Val> ( new Val { val } );
    }
    std::shared_ptr<Expression> derivate(const std::string& var);

    operator std::string() const; 
    ~Val() = default;
};

class Binary : public Expression {
protected:
    std::shared_ptr<Expression> left_;
    std::shared_ptr<Expression> right_;

public:
    Binary(std::shared_ptr<Expression> left, std::shared_ptr<Expression> right);
    ~Binary() = default;
};

class Unary : public Expression {
protected:
    std::shared_ptr<Expression> expr_;
public:
    Unary(std::shared_ptr<Expression> expr);
    ~Unary() = default;
};

class Exp : public Unary, public std::enable_shared_from_this<Expression>{
public:
    Exp(std::shared_ptr<Expression> expr) : Unary { expr } {};
    std::shared_ptr<Expression> derivate(const std::string& var);

    static std::shared_ptr<Expression> make_exp(std::shared_ptr<Expression> arg) {
        return std::shared_ptr<Expression> { new Exp { arg } };
    }

    operator std::string() const; 
};

class Plus : public Binary {
public:
    Plus(std::shared_ptr<Expression> left, std::shared_ptr<Expression> right);
    static std::shared_ptr<Expression> make_plus(std::shared_ptr<Expression> left, std::shared_ptr<Expression> right) {
        return std::shared_ptr<Expression> { new Plus { left, right } };
    }
    std::shared_ptr<Expression> derivate(const std::string& var);

    operator std::string() const; 
};


class Sub : public Binary {
public:
    Sub(std::shared_ptr<Expression> l, std::shared_ptr<Expression> r);
    static std::shared_ptr<Expression> make_sub(std::shared_ptr<Expression> left, std::shared_ptr<Expression> right) {
        return std::shared_ptr<Expression> { new Sub { left, right } };
    }
    std::shared_ptr<Expression> derivate(const std::string& var);

    operator std::string() const; 
};

class Mult : public Binary {
public:
    Mult(std::shared_ptr<Expression> l, std::shared_ptr<Expression> r);
    static std::shared_ptr<Expression> make_mult(std::shared_ptr<Expression> left, std::shared_ptr<Expression> right) {
        return std::shared_ptr<Expression> { new Mult { left, right } };
    }
    std::shared_ptr<Expression> derivate(const std::string& var);

    operator std::string() const; 
};

class Div : public Binary {

public:
    Div(std::shared_ptr<Expression> l, std::shared_ptr<Expression> r);
    std::shared_ptr<Expression> derivate(const std::string& var);

    static std::shared_ptr<Expression> make_div(std::shared_ptr<Expression> left, std::shared_ptr<Expression> right) {
        return std::shared_ptr<Expression> { new Div { left, right } };
    }
     
    operator std::string() const; 
};
