#include <gtest/gtest.h>
#include <string>
#include "../sources/derivate.hpp"

TEST(repr_test, var) {
    auto e = Var::make_var("x");

    EXPECT_EQ(" x ", static_cast<std::string>(*e));
}
TEST(repr_test, Val) {
    auto e = Val::make_val(42.0);
    EXPECT_EQ(" 42.00 ", static_cast<std::string>(*e));
}
TEST(DifferentiationTest, Plus) {
    auto a = Val::make_val(42.0);
    auto b = Var::make_var("x");
    auto plus = Plus::make_plus(a, b);
    std::cout << "\n";
    std::cout << "expr:" << (std::string) *plus << std::endl; 
    std::cout << "dx (expr):" << (std::string) *plus->derivate("x") << std::endl; 
    std::cout << "dy (expr):" << (std::string) *plus->derivate("y") << std::endl; 
    std::cout << "\n";
}

TEST(DifferentiationTest, simple_mult) {
    auto mult = Mult::make_mult(Var::make_var("y"), Val::make_val(42.0));
    std::cout << "\n";
    std::cout << "expr: " << (std::string) *mult << std::endl; 
    std::cout << "dx (expr): " << (std::string) *mult->derivate("x") << std::endl; 
    std::cout << "dy (expr): " << (std::string) *mult->derivate("y") << std::endl; 
    std::cout << "\n";
}

TEST(DifferentiationTest, Sub) {
    auto a = Mult::make_mult(Var::make_var("y"), Val::make_val(42.0));
    auto b = Var::make_var("x");
    auto sub = Sub::make_sub(a, b);

    std::cout << "\n";
    std::cout << "expr: " << (std::string) *sub << std::endl; 
    std::cout << "dx (expr): " << (std::string) *sub->derivate("x") << std::endl; 
    std::cout << "dy (expr): " << (std::string) *sub->derivate("y") << std::endl; 
    std::cout << "\n";
}

TEST(DifferentiationTest, SimpleComposition) {
    auto a = Plus::make_plus(Var::make_var("x"), Val::make_val(42.0));
    auto b = Sub::make_sub(Val::make_val(24.0), Var::make_var ("y"));
    auto plus = Plus::make_plus(a, b);
    std::cout << "\n";
    std::cout << "expr: " << (std::string) *plus << std::endl; 
    std::cout << "dx (expr): " << (std::string) *plus->derivate("x") << std::endl; 
    std::cout << "dy (expr): " << (std::string) *plus->derivate("y") << std::endl; 
    std::cout << "\n";
}

TEST(DifferentiationTest, Mult) {
    auto a = Plus::make_plus(Var::make_var("x"), Val::make_val(42.0));
    auto b = Sub::make_sub(Val::make_val(24.0), Var::make_var("y"));
    auto mult = Mult::make_mult(a, b);
    std::cout << "\n";
    std::cout << "expr: " << (std::string) *mult << std::endl; 
    std::cout << "dx (expr): " << (std::string) *mult->derivate("x") << std::endl; 
    std::cout << "dy (expr): " << (std::string) *mult->derivate("y") << std::endl; 
    std::cout << "\n";
}

TEST(DifferentiationTest, Div) {
    auto a = Mult::make_mult(Var::make_var ( "x" ), Var::make_var ( "x" ));
    auto b = Sub::make_sub ( Val::make_val (24.0), Var::make_var ( "y" ) );
    auto div =  Div::make_div (a, b);
    std::cout << "\n";
    std::cout << "expr: " << (std::string) *div << std::endl; 
    std::cout << "dx (expr): " << (std::string) *div->derivate("x") << std::endl; 
    std::cout << "dy (expr): " << (std::string) *div->derivate("y") << std::endl; 
    std::cout << "\n";
}

TEST(DifferentiationTest, Exponent) {
    auto a = Mult::make_mult (Var::make_var("x"), Var::make_var ("x"));
    auto exp = Exp::make_exp(a);
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
