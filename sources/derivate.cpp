#include "derivate.hpp"
#include <iostream>
Var::Var(const std::string& var) : var_ { var } {}

std::shared_ptr<Expression> Var::derivate(const std::string& var) {
    if (var != var_) {
        return Val::make_val(0);
    }
    return Val::make_val(1);
}

std::shared_ptr<Expression> Exp::derivate(const std::string &var) {
    return Mult::make_mult(expr_->derivate(var), shared_from_this());
}

Exp::operator std::string() const {
    return " e ^ ( " + static_cast<std::string>(*expr_) + " ) ";
}

Var::operator std::string() const {
    return " " + var_ + " ";
}

Val::Val(double val) : val_ { val } {}

Val::operator std::string() const {
    std::stringstream stream;
    stream << std::fixed << std::setprecision(DOT) << val_;
    std::string format_str = stream.str();
    return " " + format_str + " ";
}

std::shared_ptr<Expression> Val::derivate(const std::string& var) {
    return std::shared_ptr<Expression> {new Val{ 0 } };
}

Binary::Binary(std::shared_ptr<Expression> left, std::shared_ptr<Expression> right) : left_ { left }, right_ { right } {}


Plus::Plus(std::shared_ptr<Expression> left, std::shared_ptr<Expression> right) : Binary(left, right) {}

Plus::operator std::string() const {
    return " (" + static_cast<std::string>(*left_) + " + " + static_cast<std::string>(*right_) + ") ";
}

std::shared_ptr<Expression> Plus::derivate(const std::string& var) {
    return std::shared_ptr<Expression> { new Plus(left_->derivate(var), right_->derivate(var)) };
}

Sub::Sub(std::shared_ptr<Expression> l, std::shared_ptr<Expression> r) : Binary {l, r} {}

std::shared_ptr<Expression> Sub::derivate(const std::string& var) {
    return std::shared_ptr<Expression> { new Sub(left_->derivate(var), right_->derivate(var)) };
}

Sub::operator std::string() const {
    return  " ( " + static_cast<std::string>(*left_) + "-" + static_cast<std::string>(*right_) + " ) ";
}

Mult::Mult(std::shared_ptr<Expression> l, std::shared_ptr<Expression> r) : Binary(l, r) {}

Mult::operator std::string() const {
    return  " ( " + static_cast<std::string>(*left_) + " * " + static_cast<std::string>(*right_) + " ) ";
}


std::shared_ptr<Expression> Mult::derivate(const std::string& var) {
    auto dl = left_->derivate(var);
    auto dr = right_->derivate(var);
    std::cout << (std::string) *left_ << std::endl;
    return  Plus::make_plus(Mult::make_mult(dl, right_), Mult::make_mult(left_, dr));
}

Div::Div(std::shared_ptr<Expression> l, std::shared_ptr<Expression> r) : Binary{l, r} {}

std::shared_ptr<Expression> Div::derivate(const std::string& var) {
    auto dl = left_->derivate(var);
    auto dr = right_->derivate(var);
    auto numerator = Sub::make_sub( Mult::make_mult(dl, right_), Mult::make_mult(left_, dr) ) ;
    auto denominator = std::shared_ptr<Expression> { new Mult(right_, right_) };
    return Div::make_div(numerator, denominator) ;
}

Div::operator std::string() const {
    return " ( " + static_cast<std::string>(*left_) + " / " + static_cast<std::string>(*right_) + " ) ";
}

Unary::Unary(std::shared_ptr<Expression> expr) : expr_ { expr } {}
