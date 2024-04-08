#include <gtest/gtest.h>
#include <string>
#include "../sources/derivate.hpp"

TEST(DifferentiationTest, Var) {
    ScopedPointer<Expression> e = ScopedPointer<Expression> { new Var { "x" } };
    std::cout << "Var text repr" << (std::string) *e << std::endl; 
}

TEST(DifferentiationTest, Val) {
    ScopedPointer<Expression> e = ScopedPointer<Expression> { new Val { 42.0 } };
    std::cout << "Var text repr" << (std::string) *e << std::endl; 
}

TEST(DifferentiationTest, Plus) {
    ScopedPointer<Expression> a = ScopedPointer<Expression> { new Val { 42.0 } };
    ScopedPointer<Expression> b = ScopedPointer<Expression> { new Var { "x" } };
    ScopedPointer<Expression> plus = ScopedPointer<Expression> {new Plus {a, b} };
    std::cout << "Plus text repr" << (std::string) *plus << std::endl; 
    std::cout << "Derivative text repr" << (std::string) *plus->derivate("x") << std::endl; 
}

TEST(DifferentiationTest, Sub) {
    ScopedPointer<Expression> a = ScopedPointer<Expression> { new Val { 42.0 } };
    ScopedPointer<Expression> b = ScopedPointer<Expression> { new Var { "x" } };
    ScopedPointer<Expression> sub = ScopedPointer<Expression> {new Plus {a, b} };
    std::cout << "Sub text repr" << (std::string) *sub << std::endl; 
    std::cout << "Derivative text repr" << (std::string) *sub->derivate("x") << std::endl; 
}

TEST(DifferentiationTest, SimpleComposition) {
    ScopedPointer<Expression> a = new Plus { new Var { "x" }, new Val { 42.0 }};
    ScopedPointer<Expression> b = new Sub { new Val {24.0}, new Var { "y" } };
    ScopedPointer<Expression> plus = new Plus {a->copy(), b->copy()};
    std::cout << "Composition text repr" << (std::string) *plus << std::endl; 
    std::cout << "Derivative text repr" << (std::string) *plus->derivate("x") << std::endl; 
}

TEST(DifferentiationTest, Mult) {
    ScopedPointer<Expression> a = new Plus { new Var { "x" }, new Val { 42.0 }};
    ScopedPointer<Expression> b = new Sub { new Val {24.0}, new Var { "y" } };
    ScopedPointer<Expression> mult = new Mult {a->copy(), b->copy()};
    std::cout << "Mult text repr" << (std::string) *mult << std::endl; 
    std::cout << "Derivative text repr" << (std::string) *mult->derivate("x") << std::endl; 
}

TEST(DifferentiationTest, Div) {
    ScopedPointer<Expression> a = new Mult { new Var { "x" }, new Var { "x" }};
    ScopedPointer<Expression> b = new Sub { new Val {24.0}, new Var { "y" } };
    ScopedPointer<Expression> div = new Div {a, b};
    std::cout << "Div text repr" << (std::string) *div << std::endl; 
    std::cout << "Derivative text repr" << (std::string) *div->derivate("x") << std::endl; 
}

TEST(DifferentiationTest, Exponent) {
    ScopedPointer<Expression> a = new Mult { new Var { "x" }, new Var { "x" }};
    ScopedPointer<Expression> exp = new Exp {a};
    std::cout << "Exponent text repr" << (std::string) *exp << std::endl; 
    std::cout << "Derivative text repr" << (std::string) *exp->derivate("x") << std::endl; 
}
int main() {
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}