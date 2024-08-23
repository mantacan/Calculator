#include "../smartcalc.h"

TEST(PostfixConversionTest, SimpleAddition) {
  s21::model model("3 + 4");
  EXPECT_EQ(model.getPostfixExpression(), "3 4 + ");
}

TEST(PostfixConversionTest, DivisionAndSubtraction) {
  s21::model model("8 / 4 - 2");
  EXPECT_EQ(model.getPostfixExpression(), "8 4 / 2 - ");
}

TEST(PostfixConversionTest, MultipleOperators) {
  s21::model model("3 ^ 4 + 5");
  EXPECT_EQ(model.getPostfixExpression(), "3 4 ^ 5 + ");
}

TEST(PostfixConversionTest, CosineFunction) {
  s21::model model("cos(45.4)");
  EXPECT_EQ(model.getPostfixExpression(), "45.4 cos ");
}

TEST(PostfixConversionTest, SineFunction) {
  s21::model model("sin(90)");
  EXPECT_EQ(model.getPostfixExpression(), "90 sin ");
}

TEST(PostfixConversionTest, TangentFunction) {
  s21::model model("tan(45)");
  EXPECT_EQ(model.getPostfixExpression(), "45 tan ");
}

TEST(PostfixConversionTest, ArccosFunction) {
  s21::model model("acos(0.5)");
  EXPECT_EQ(model.getPostfixExpression(), "0.5 acos ");
}

TEST(PostfixConversionTest, ArcsinFunction) {
  s21::model model("asin(0.5)");
  EXPECT_EQ(model.getPostfixExpression(), "0.5 asin ");
}

TEST(PostfixConversionTest, ArctanFunction) {
  s21::model model("atan(1)");
  EXPECT_EQ(model.getPostfixExpression(), "1 atan ");
}

TEST(PostfixConversionTest, SquareRootFunction) {
  s21::model model("sqrt(16)");
  EXPECT_EQ(model.getPostfixExpression(), "16 sqrt ");
}

TEST(PostfixConversionTest, NaturalLogarithm) {
  s21::model model("ln(2.718281828)");
  EXPECT_EQ(model.getPostfixExpression(), "2.718281828 ln ");
}

TEST(PostfixConversionTest, DecimalLogarithm) {
  s21::model model("log(10)");
  EXPECT_EQ(model.getPostfixExpression(), "10 log ");
}

/*
 *
 *
 * calculate
 *
 */

#include <gtest/gtest.h>

#include "../smartcalc.h"

TEST(ModelTest, DefaultConstructor) {
  s21::model defaultModel;
  EXPECT_TRUE(defaultModel.getExpression().empty());
  EXPECT_TRUE(defaultModel.getPostfixExpression().empty());
  EXPECT_TRUE(defaultModel.getXValues().empty());
  EXPECT_TRUE(defaultModel.getYValues().empty());
  EXPECT_EQ(defaultModel.getResult(), "");
}

TEST(ModelTest, HandleInvalidExpression) {
  s21::model modelWithInvalidExpression("1/0");
  EXPECT_EQ(modelWithInvalidExpression.getResult(), "division by zero");
}

TEST(ModelTest, FunctionHandling) {
  s21::model model("log(-1)");
  model.processExpression();
  EXPECT_FALSE(model.checkFunctions());
  EXPECT_EQ(model.getResult(), "NOT VALID EXPRESSION");

  s21::model model2("asin(2)");
  model2.processExpression();
  EXPECT_FALSE(model2.checkFunctions());
  EXPECT_EQ(model2.getResult(), "NOT VALID EXPRESSION");
}

TEST(ModelTest, ApplyFunctionEdgeCases) {
  s21::model model;
  EXPECT_EQ(model.applyFunction("sqrt", -1), 0);
  EXPECT_TRUE(model.getError());
  model.resetError();

  EXPECT_EQ(model.applyFunction("log", 0), 0);
  EXPECT_TRUE(model.getError());
}

TEST(ModelTest, OperatorPrecedence) {
  s21::model model;
  EXPECT_EQ(model.precedence("unknown_operator"), 0);
}

TEST(ModelTfawfest, FunctionApplication) {
  s21::model sinModel("sin(0)");
  double sinResult = std::stod(sinModel.getResult());
  EXPECT_DOUBLE_EQ(sinResult, 0);

  s21::model cosModel("cos(0)");
  double cosResult = std::stod(cosModel.getResult());
  EXPECT_DOUBLE_EQ(cosResult, 1);
}
TEST(ModelTgdfest, DefaultConstructor) {
  s21::model defaultModel;
  EXPECT_EQ(defaultModel.getExpression(), "");
  EXPECT_TRUE(defaultModel.getXValues().empty());
  EXPECT_TRUE(defaultModel.getYValues().empty());
  EXPECT_EQ(defaultModel.getResult(), "");
}

TEST(ModelTestfaw, FunctionApplication) {
  s21::model sinModel("sin(0)");
  EXPECT_EQ(sinModel.getResult(), "0.00");

  s21::model cosModel("cos(0)");
  EXPECT_EQ(cosModel.getResult(), "1.00");
}

TEST(CalculatePostfix, Baza) {
  s21::model model("4242 + 21442");
  std::string expected = "25684.00";

  EXPECT_EQ(model.getResult(), expected);
}

TEST(CalculatePostfix, Subtraction) {
  s21::model model("21442 - 4242");
  std::string expected = "17200.00";

  EXPECT_EQ(model.getResult(), expected);
}

TEST(CalculatePostfix, Multiplication) {
  s21::model model("100 * 2");
  std::string expected = "200.00";

  EXPECT_EQ(model.getResult(), expected);
}

TEST(CalculatePostfix, Division) {
  s21::model model("50 / 2");
  std::string expected = "25.00";

  EXPECT_EQ(model.getResult(), expected);
}

TEST(CalculatePostfix, Exponentiation) {
  s21::model model("3 ^ 4");
  std::string expected = "81.00";

  EXPECT_EQ(model.getResult(), expected);
}

TEST(CalculatePostfix, SinFunction) {
  s21::model model("sin(0)");
  std::string expected = "0.00";

  EXPECT_EQ(model.getResult(), expected);
}

TEST(CalculatePostfix, CosFunction) {
  s21::model model("cos(0)");
  std::string expected = "1.00";

  EXPECT_EQ(model.getResult(), expected);
}

TEST(CalculatePostfix, TanFunction) {
  s21::model model("tan(0)");
  std::string expected = "0.00";

  EXPECT_EQ(model.getResult(), expected);
}

TEST(CalculatePostfix, SqrtFunction) {
  s21::model model("sqrt(16)");
  std::string expected = "4.00";

  EXPECT_EQ(model.getResult(), expected);
}

TEST(CalculatePostfix, LnFunction) {
  s21::model model("ln(1)");
  std::string expected = "0.00";

  EXPECT_EQ(model.getResult(), expected);
}

TEST(CalculatePostfix, LogFunction) {
  s21::model model("log(100)");
  std::string expected = "2.00";

  EXPECT_EQ(model.getResult(), expected);
}

TEST(CalculatePostfix, ArcCosine) {
  s21::model model("acos(1)");

  std::string res = "0.00";
  EXPECT_EQ(model.getResult(), res);
}

TEST(CalculatePostfix, ArcSine) {
  s21::model model("asin(0)");

  std::string res = "0.00";
  EXPECT_EQ(model.getResult(), res);
}

TEST(CalculatePostfix, ArcTangent) {
  s21::model model("atan(0)");

  std::string res = "0.00";
  EXPECT_EQ(model.getResult(), res);
}

TEST(Calculate, Baza) {
  s21::model model("3589254242 + 423523908");

  std::string res = "4012778150.00";
  EXPECT_EQ(model.getResult(), res);
}

TEST(Calculate, CosinePlusSine) {
  s21::model model("cos(1) + sin(1)");
  std::string res = "1.38";

  EXPECT_EQ(model.getResult(), res);
}

TEST(Calculate, TangentOfSqrt) {
  s21::model model("tan(sqrt(2))");
  std::string res = "6.33";

  EXPECT_EQ(model.getResult(), res);
}

TEST(Calculate, LnOfCos) {
  s21::model model("ln(cos(1))");
  std::string res = "-0.62";

  EXPECT_EQ(model.getResult(), res);
}

TEST(Calculate, ComplexExpression) {
  s21::model model("sin(acos(0.5)) + log(100) * sqrt(16)");
  std::string res = "8.87";

  EXPECT_EQ(model.getResult(), res);
}

TEST(Calculate, MixedFunctionsAndNumbers) {
  s21::model model("asin(0.5) * 20 + atan(1)");
  std::string res = "11.26";

  EXPECT_EQ(model.getResult(), res);
}

TEST(Calculate, AtanOfExpression) {
  s21::model model("atan(2 + tan(0.5))");
  std::string res = "1.20";

  EXPECT_EQ(model.getResult(), res);
}

TEST(Calculate, SinCosFunctionWithVariable) {
  s21::model model("sin(x) * cos(x) | x = 45");
  std::string res = "0.45";

  EXPECT_EQ(model.getResult(), res);
}

TEST(Calculate, SqrtAndTanFunctionWithVariable) {
  s21::model model("sqrt(x) + tan(x) | x = 16");
  std::string res = "4.30";

  EXPECT_EQ(model.getResult(), res);
}

TEST(Calculate, NaturalLogFunctionWithVariable) {
  s21::model model("ln(x) | x = 2.71828182846");
  std::string res = "1.00";
  EXPECT_EQ(model.getResult(), res);
}

TEST(Calculate, ArcSinFunctionWithVariable) {
  s21::model model("asin(x) | x = 1");
  std::string res = "1.57";

  EXPECT_EQ(model.getResult(), res);
}

TEST(Calculate, ComplexExpressionWithVariable) {
  s21::model model("cos(x) * sin(x) + sqrt(x) | x = 30");
  std::string res = "5.32";

  EXPECT_EQ(model.getResult(), res);
}

TEST(Calculate, ErrSyntax) {
  s21::model model("c52352352");
  std::string result = "NOT VALID EXPRESSION";
  EXPECT_EQ(model.getResult(), result);
}

TEST(Calculate, ErrSyntaxInvalidCharacters) {
  s21::model model("c52352352");
  std::string result = "NOT VALID EXPRESSION";
  EXPECT_EQ(model.getResult(), result);
}

TEST(Calculate, ErrSyntaxMissingBracket) {
  s21::model model("sin(30");
  std::string result = "NOT VALID EXPRESSION";
  EXPECT_EQ(model.getResult(), result);
}

TEST(Calculate, ErrSyntaxExtraOperators) {
  s21::model model("5 + * 3");
  std::string result = "NOT VALID EXPRESSION";
  EXPECT_EQ(model.getResult(), result);
}

TEST(Calculate, ErrSyntaxMisusedPeriod) {
  s21::model model("3.14.159");
  std::string result = "NOT VALID EXPRESSION";
  EXPECT_EQ(model.getResult(), result);
}

TEST(Calculate, DivisionByZero) {
  s21::model model("10 / 0");
  std::string result = "division by zero";
  EXPECT_EQ(model.getResult(), result);
}

TEST(Calculate, MismatchedParentheses) {
  s21::model model("(3 + 2) * (4 - 3))");
  std::string result = "NOT VALID EXPRESSION";
  EXPECT_EQ(model.getResult(), result);
}

TEST(Calculate, UseOfUndefinedVariable) {
  s21::model model("x + 5 | y = 10");
  std::string result = "NOT VALID EXPRESSION";
  EXPECT_EQ(model.getResult(), result);
}

TEST(Calculate, InvalidFunctionUsage) {
  s21::model model("unknown_function(2)");
  std::string result = "NOT VALID EXPRESSION";
  EXPECT_EQ(model.getResult(), result);
}

TEST(Calculate, InvalidFunctionArgument) {
  s21::model model("sqrt(-1)");
  std::string result = "NOT VALID EXPRESSION";
  EXPECT_EQ(model.getResult(), result);
}

TEST(Calculate, MissingFunctionArgument) {
  s21::model model("sin()");
  std::string result = "NOT VALID EXPRESSION";
  EXPECT_EQ(model.getResult(), result);
}

TEST(Calculate, InvalidFunctionUsage2) {
  s21::model model("log10(100)");
  std::string result = "Invalid postfix expression.";
  EXPECT_EQ(model.getResult(), result);
}

TEST(Calculate, NegativeArgumentToLog) {
  s21::model model("log(-1)");
  std::string result = "NOT VALID EXPRESSION";
  EXPECT_EQ(model.getResult(), result);
}

TEST(Calculate, ZeroArgumentToSqrt) {
  s21::model model("sqrt(0)");
  std::string result = "0.00";
  EXPECT_EQ(model.getResult(), result);
}

TEST(Calculate, ArgumentOutOfRange) {
  s21::model model("sqrt(9999999999)");
  std::string result = "100000.00";
  EXPECT_EQ(model.getResult(), result);
}

/*
 *
 *
 * CREDIT CALC TESTS
 *
 *
 */
TEST(CreditModelTest, InvalidInputs) {
  s21::model creditModelInvalid1(-10000.0, 12, 6.0, true);
  s21::model creditModelInvalid2(10000.0, -12, 6.0, true);
  s21::model creditModelInvalid3(10000.0, 12, -6.0, true);

  EXPECT_TRUE(std::isnan(creditModelInvalid1.creditGetMonthlyPayment()));
  EXPECT_TRUE(std::isnan(creditModelInvalid1.creditGetTotalRepayment()));
  EXPECT_TRUE(std::isnan(creditModelInvalid1.creditGetLoanOverpayment()));

  EXPECT_TRUE(std::isnan(creditModelInvalid2.creditGetMonthlyPayment()));
  EXPECT_TRUE(std::isnan(creditModelInvalid2.creditGetTotalRepayment()));
  EXPECT_TRUE(std::isnan(creditModelInvalid2.creditGetLoanOverpayment()));

  EXPECT_TRUE(std::isnan(creditModelInvalid3.creditGetMonthlyPayment()));
  EXPECT_TRUE(std::isnan(creditModelInvalid3.creditGetTotalRepayment()));
  EXPECT_TRUE(std::isnan(creditModelInvalid3.creditGetLoanOverpayment()));
}
TEST(CreditModelTest, DifferentialPayment) {
  s21::model creditModelDifferential(10000.0, 12, 6.0, false);

  int expectedMonthlyPaymentApprox = 860;
  int expectedTotalRepaymentApprox = 10325;
  int expectedLoanOverpaymentApprox = 325;

  EXPECT_NEAR(creditModelDifferential.creditGetMonthlyPayment(),
              expectedMonthlyPaymentApprox, 1);
  EXPECT_NEAR(creditModelDifferential.creditGetTotalRepayment(),
              expectedTotalRepaymentApprox, 1);
  EXPECT_NEAR(creditModelDifferential.creditGetLoanOverpayment(),
              expectedLoanOverpaymentApprox, 1);
}

TEST(CreditModelTest, AnnuityPayment) {
  s21::model creditModel(10000.0, 12, 6.0, true);

  int expectedMonthlyPayment = 861;
  int expectedTotalRepayment = 10328;
  int expectedLoanOverpayment = 328;

  EXPECT_DOUBLE_EQ(creditModel.creditGetMonthlyPayment(),
                   expectedMonthlyPayment);
  EXPECT_DOUBLE_EQ(creditModel.creditGetTotalRepayment(),
                   expectedTotalRepayment);
  EXPECT_DOUBLE_EQ(creditModel.creditGetLoanOverpayment(),
                   expectedLoanOverpayment);
}

TEST(CreditModelTest, AnnuityPaymentF) {
  s21::model creditModel(10000.0, 12, 6.0, false);

  int expectedMonthlyPayment = 860;
  int expectedTotalRepayment = 10325;
  int expectedLoanOverpayment = 325;

  EXPECT_DOUBLE_EQ(creditModel.creditGetMonthlyPayment(),
                   expectedMonthlyPayment);
  EXPECT_DOUBLE_EQ(creditModel.creditGetTotalRepayment(),
                   expectedTotalRepayment);
  EXPECT_DOUBLE_EQ(creditModel.creditGetLoanOverpayment(),
                   expectedLoanOverpayment);
}

TEST(DepositModelTest, PeriodicDeposits) {
  s21::model depositModel(10000.0, 12, 5.0, 10.0, 1, false, 500.0, 0.0);
  double expectedFinalBalance = 10000;
  double monthlyDeposit = 500.0;
  for (int i = 1; i <= 12; ++i) {
    expectedFinalBalance += monthlyDeposit;
    double interest = expectedFinalBalance * (5.0 / 12 / 100);
    double tax = interest * 10.0 / 100;
    expectedFinalBalance += interest - tax;
  }
  EXPECT_NEAR(depositModel.depositGetFinalBalance(), expectedFinalBalance, 1.0);
}

TEST(DepositModelTest, PeriodicWithdrawals) {
  s21::model depositModel(10000.0, 12, 5.0, 10.0, 1, false, 0.0, 200.0);
  double expectedFinalBalance = 10000;
  double monthlyWithdrawal = 200.0;
  for (int i = 1; i <= 12; ++i) {
    expectedFinalBalance -= monthlyWithdrawal;
    double interest = expectedFinalBalance * (5.0 / 12 / 100);
    double tax = interest * 10.0 / 100;
    expectedFinalBalance += interest - tax;
  }
  EXPECT_NEAR(depositModel.depositGetFinalBalance(), expectedFinalBalance, 1.0);
}

TEST(DepositModelTest, CompoundingInterest) {
  s21::model depositModel(10000.0, 12, 5.0, 10.0, 1, true, 0.0, 0.0);
  double expectedFinalBalance = 10000;
  for (int i = 1; i <= 12; ++i) {
    double interest = expectedFinalBalance * (5.0 / 12 / 100);
    double tax = interest * 10.0 / 100;
    expectedFinalBalance += interest - tax;
  }
  EXPECT_NEAR(depositModel.depositGetFinalBalance(), expectedFinalBalance, 1.0);
}

TEST(DepositModelTest, InvalidInitialAmount) {
  s21::model depositModel(-10000.0, 12, 5.0, 10.0, 12, false, 100.0, 50.0);
  EXPECT_TRUE(std::isnan(depositModel.depositGetFinalBalance()));
}

TEST(DepositModelTest, InvalidPeriodMonths) {
  s21::model depositModel(10000.0, 0, 5.0, 10.0, 12, false, 100.0, 50.0);
  EXPECT_TRUE(std::isnan(depositModel.depositGetFinalBalance()));
}

TEST(DepositModelTest, NegativeInterestRate) {
  s21::model depositModel(10000.0, 12, -5.0, 10.0, 12, false, 100.0, 50.0);
  EXPECT_TRUE(std::isnan(depositModel.depositGetFinalBalance()));
}

TEST(DepositModelTest, NegativeTaxRate) {
  s21::model depositModel(10000.0, 12, 5.0, -10.0, 12, false, 100.0, 50.0);
  EXPECT_TRUE(std::isnan(depositModel.depositGetFinalBalance()));
}

TEST(DepositModelTest, NegativeDepositAmount) {
  s21::model depositModel(10000.0, 12, 5.0, 10.0, 12, false, -100.0, 50.0);
  EXPECT_TRUE(std::isnan(depositModel.depositGetFinalBalance()));
}

TEST(DepositModelTest, NegativeWithdrawalAmount) {
  s21::model depositModel(10000.0, 12, 5.0, 10.0, 12, false, 100.0, -50.0);
  EXPECT_TRUE(std::isnan(depositModel.depositGetFinalBalance()));
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}