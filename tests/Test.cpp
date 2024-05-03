#include <gtest/gtest.h>
#include <string>
#include "../sources/derivate.hpp"

TEST(repr_test, var) {
    ScopedPointer<Expression> e = ScopedPointer<Expression> { new Var { "x" } };
    EXPECT_EQ(" x ", static_cast<std::string>(*e));
}

TEST(DifferentiationTest, Val) {
    ScopedPointer<Expression> e = ScopedPointer<Expression> { new Val { 42.0 } };
    EXPECT_EQ(" 42.00 ", static_cast<std::string>(*e));
}

TEST(DifferentiationTest, Plus) {
    ScopedPointer<Expression> a = ScopedPointer<Expression> { new Val { 42.0 } };
    ScopedPointer<Expression> b = ScopedPointer<Expression> { new Var { "x" } };
    ScopedPointer<Expression> plus = ScopedPointer<Expression> {new Plus {a, b} };
    std::cout << "\n";
    std::cout << "expr:" << (std::string) *plus << std::endl; 
    std::cout << "dx (expr):" << (std::string) *plus->derivate("x") << std::endl; 
    std::cout << "dy (expr):" << (std::string) *plus->derivate("y") << std::endl; 
    std::cout << "\n";
}

TEST(DifferentiationTest, Sub) {
    ScopedPointer<Expression> a = ScopedPointer<Expression> { new Mult { new Var { " y " }, new Val { 42.0 } }};
    ScopedPointer<Expression> b = ScopedPointer<Expression> { new Var { "x" } };
    ScopedPointer<Expression> sub = ScopedPointer<Expression> {new Sub {a, b} };

    std::cout << "\n";
    std::cout << "expr: " << (std::string) *sub << std::endl; 
    std::cout << "dx (expr): " << (std::string) *sub->derivate("x") << std::endl; 
    std::cout << "dy (expr): " << (std::string) *sub->derivate("y") << std::endl; 
    std::cout << "\n";
}

TEST(DifferentiationTest, SimpleComposition) {
    ScopedPointer<Expression> a = new Plus { new Var { "x" }, new Val { 42.0 }};
    ScopedPointer<Expression> b = new Sub { new Val {24.0}, new Var { "y" } };
    ScopedPointer<Expression> plus = new Plus {a->copy(), b->copy()};
    std::cout << "\n";
    std::cout << "expr: " << (std::string) *plus << std::endl; 
    std::cout << "dx (expr): " << (std::string) *plus->derivate("x") << std::endl; 
    std::cout << "dy (expr): " << (std::string) *plus->derivate("y") << std::endl; 
    std::cout << "\n";
}

TEST(DifferentiationTest, Mult) {
    ScopedPointer<Expression> a = new Plus { new Var { "x" }, new Val { 42.0 }};
    ScopedPointer<Expression> b = new Sub { new Val {24.0}, new Var { "y" } };
    ScopedPointer<Expression> mult = new Mult {a->copy(), b->copy()};
    std::cout << "\n";
    std::cout << "expr: " << (std::string) *mult << std::endl; 
    std::cout << "dx (expr): " << (std::string) *mult->derivate("x") << std::endl; 
    std::cout << "dy (expr): " << (std::string) *mult->derivate("y") << std::endl; 
    std::cout << "\n";
}

TEST(DifferentiationTest, Div) {
    ScopedPointer<Expression> a = new Mult { new Var { "x" }, new Var { "x" }};
    ScopedPointer<Expression> b = new Sub { new Val {24.0}, new Var { "y" } };
    ScopedPointer<Expression> div = new Div {a, b};
    std::cout << "\n";
    std::cout << "expr: " << (std::string) *div << std::endl; 
    std::cout << "dx (expr): " << (std::string) *div->derivate("x") << std::endl; 
    std::cout << "dy (expr): " << (std::string) *div->derivate("y") << std::endl; 
    std::cout << "\n";
}

TEST(DifferentiationTest, Exponent) {
    ScopedPointer<Expression> a = new Mult { new Var { "x" }, new Var { "x" }};
    ScopedPointer<Expression> exp = new Exp {a};
    std::cout << "\n";
    std::cout << "expr: " << (std::string) *exp << std::endl; 
    std::cout << "dx (expr): " << (std::string) *exp->derivate("x") << std::endl; 
    std::cout << "dy (expr): " << (std::string) *exp->derivate("y") << std::endl; 
    std::cout << "\n";
}

int main() {
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}
