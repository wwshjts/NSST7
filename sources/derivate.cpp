#include "derivate.hpp"

Var::Var(std::string var) : var_ { var } {}

ScopedPointer<Expression> Var::derivate(const std::string& var) {
    if (var != var_) {
        return ScopedPointer<Expression> { new Val { 0 } };
    }
    return ScopedPointer<Expression> { new Val { 1 } };
}

ScopedPointer<Expression> Exp::derivate(const std::string &var) {
    return ScopedPointer<Expression> { new Mult{ expr_->derivate(var), this->copy() } };
}

Expression* Exp::copy() const {
    return new Exp { expr_->copy() } ;
}

Exp::operator std::string() const {
    return " e ^ ( " + static_cast<std::string>(*expr_) + " ) ";
}

Var::operator std::string() const {
    return " " + var_ + " ";
}

Expression* Var::copy() const {
    return new Var { var_ };
}

Val::Val(double val) : val_ { val } {}

Val::operator std::string() const {
    std::stringstream stream;
    stream << std::fixed << std::setprecision(DOT) << val_;
    std::string format_str = stream.str();
    return " " + format_str + " ";
}

Expression* Val::copy() const {
    return new Val { val_ };
}

ScopedPointer<Expression> Val::derivate(const std::string& var) {
    return ScopedPointer<Expression> {new Val{ 0 } };
}

Binary::Binary(ScopedPointer<Expression> left, ScopedPointer<Expression> right) : left_ { left }, right_ { right } {}


Plus::Plus(ScopedPointer<Expression> left, ScopedPointer<Expression> right) : Binary(left, right) {}

Plus::operator std::string() const {
    return " (" + static_cast<std::string>(*left_) + " + " + static_cast<std::string>(*right_) + ") ";
}

Expression* Plus::copy() const {
    return new Plus { left_->copy(), right_->copy()};
}

ScopedPointer<Expression> Plus::derivate(const std::string& var) {
    return ScopedPointer<Expression> { new Plus(left_->derivate(var), right_->derivate(var)) };
}

Sub::Sub(ScopedPointer<Expression> l, ScopedPointer<Expression> r) : Binary {l, r} {}

ScopedPointer<Expression> Sub::derivate(const std::string& var) {
    return ScopedPointer<Expression> { new Sub(left_->derivate(var), right_->derivate(var)) };
}

Expression* Sub::copy() const {
    return new Sub { left_->copy(), right_->copy()};
}

Sub::operator std::string() const {
    return  " ( " + static_cast<std::string>(*left_) + "-" + static_cast<std::string>(*right_) + " ) ";
}

Mult::Mult(ScopedPointer<Expression> l, ScopedPointer<Expression> r) : Binary(l, r) {}

Expression* Mult::copy() const {
    return new Mult { left_->copy(), right_->copy()};
}

Mult::operator std::string() const {
    return  " ( " + static_cast<std::string>(*left_) + " * " + static_cast<std::string>(*right_) + " ) ";
}


ScopedPointer<Expression> Mult::derivate(const std::string& var) {
    ScopedPointer<Expression> dl = left_->derivate(var);
    ScopedPointer<Expression> dr = right_->derivate(var);
    return ScopedPointer<Expression> { new Plus( ScopedPointer<Expression> { new Mult(dl, right_) }, ScopedPointer<Expression> { new Mult(left_, dr) } ) };
}

Div::Div(ScopedPointer<Expression> l, ScopedPointer<Expression> r) : Binary{l, r} {}

ScopedPointer<Expression> Div::derivate(const std::string& var) {
    ScopedPointer<Expression> dl = left_->derivate(var);
    ScopedPointer<Expression> dr = right_->derivate(var);
    ScopedPointer<Expression> numerator = ScopedPointer<Expression> { new Sub( ScopedPointer<Expression> { new Mult(dl, right_) }, ScopedPointer<Expression> { new Mult(left_, dr) }) };
    ScopedPointer<Expression> denominator = ScopedPointer<Expression> { new Mult(right_, right_) };
    return ScopedPointer<Expression> { new Div(numerator, denominator) };
}

Div::operator std::string() const {
    return " ( " + static_cast<std::string>(*left_) + " / " + static_cast<std::string>(*right_) + " ) ";
}

Expression* Div::copy() const {
    return new Div { left_->copy(), right_->copy() };
}

Unary::Unary(ScopedPointer<Expression> expr) : expr_ { expr } {}
