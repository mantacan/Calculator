#ifndef S21_SMARTCALC_MODEL_H_
#define S21_SMARTCALC_MODEL_H_

#include <boost/multiprecision/cpp_dec_float.hpp>
#include <cctype>
#include <cmath>
#include <cstring>
#include <iostream>
#include <limits>
#include <map>
#include <set>
#include <stack>
#include <stdexcept>
#include <string>
#include <unordered_set>
#include <vector>

using namespace boost::multiprecision;
using namespace std;
typedef cpp_dec_float_50 float50;

namespace s21 {

/**
 * @class model
 * @brief Represents the mathematical model for the SmartCalc application.
 *
 * This class handles parsing and evaluating mathematical expressions,
 * manages graph data generation, financial calculations like loans and
 * investments, and converts calculation results to string format for display.
 */
class model {
 private:
  std::string expression;  ///< Current mathematical expression as a string.
  std::string
      postfixExpression;  ///< Postfix notation of the current expression.
  std::vector<double> x_values;  ///< X-axis values for graph plotting.
  std::vector<double> y_values;  ///< Y-axis values for graph plotting.
  double x;                      ///< Current X value for expression evaluation.
  mu::Parser parser;             ///< Parser used for evaluating expressions.
  double x_start;                ///< Start X value for graph plotting.
  double x_end;                  ///< End X value for graph plotting.
  double x_step;                 ///< Step between X values for graph plotting.
  double result;                 ///< Result of the expression evaluation.

  std::string returnResult;  ///< Formatted string result for display.

  double credit_amount_mod;  ///< Credit amount for loan calculations.
  int credit_term_mod;       ///< Term (in months) of the credit.
  double credit_rate_mod;    ///< Interest rate of the credit.
  bool credit_type_mod;      ///< Type of credit calculation method (true for
                             ///< annuity).

  bool error;           ///< Flag indicating whether an error has occurred.
  std::string message;  ///< Error message description.

  struct Transaction {  ///< Transaction structure for recording financial
                        ///< movements.
    double amount;
  };

  double credit_monthly_payment;   ///< Monthly payment amount for credit.
  double credit_loan_overpayment;  ///< Total overpayment for the credit period.
  double credit_total_repayment;   ///< Total repayment amount including
                                   ///< principal and interest.

  double totalInterest;  ///< Total interest earned from deposits.
  double totalTax;       ///< Total tax paid on interest earnings.
  double finalBalance;   ///< Final balance of the deposit after the term ends.

  float50 initialAmount;        ///< Initial amount deposited.
  int periodMonths;             ///< Period of deposit in months.
  float50 interestRate;         ///< Annual interest rate of the deposit.
  float50 taxRate;              ///< Tax rate applied to the interest earned.
  int paymentFrequency;         ///< Frequency of deposit payments.
  bool isCompounded;            ///< Indicates if interest is compounded.
  float50 depositAmount;        ///< Total deposits made.
  float50 withdrawalAmount;     ///< Total withdrawals made.
  vector<float50> deposits;     ///< List of individual deposit transactions.
  vector<float50> withdrawals;  ///< List of individual withdrawal transactions.

  /**
   * @brief Determines if the given token is an operator.
   * @param token The string to check.
   * @return True if the token is an operator, otherwise false.
   */
  bool isOperator(const std::string &token);

  /**
   * @brief Checks if the operator is left associative.
   * @param op The operator to check.
   * @return True if the operator is left associative, otherwise false.
   */
  bool isLeftAssociative(const std::string &op);

  /**
   * @brief Converts the mathematical expression from infix to postfix notation.
   */
  void infixToPostfix();

  /**
   * @brief Replaces all instances of 'x' in the expression with the current
   * numerical value of x.
   */
  void replaceXWithNumber();

  /**
   * @brief Converts the result of the expression evaluation from double to
   * string format.
   */
  void fromDoubleToString();

  /**
   * @brief Sets an error message for the model.
   * @param errorsMessage The error message to be set.
   */
  void setErrors(std::string errorsMessage);

  /**
   * @brief Checks if all components are in order after processing and sets
   * results appropriately.
   */
  void everythingOkay();

  /**
   * @brief Calculates the monthly payment for a differential payment plan.
   */
  void calculateDifferentialPayment();

  /**
   * @brief Calculates the monthly payment for an annuity payment plan.
   */
  void calculateAnnuityPayment();

  /**
   * @brief Sets the type of credit calculation.
   */
  void credit_type();

  /**
   * @brief Calculates deposit growth over time, considering deposits and
   * withdrawals.
   */
  void dep_calculate();

  /**
   * @brief Validates the current expression for errors before processing.
   */
  void isValid();

  /**
   * @brief Replaces all instances of 'x' in the graph's expression with the
   * provided double value.
   * @param value The value to replace 'x' with.
   * @param expression The expression where replacements are made.
   */
  void GraphReplaceXWithNumber(double value, std::string &expression);

  /**
   * @brief Default constructor. Initializes an empty model.
   */
 public:
  model();

  /**
   * @brief Constructs a model with a specific mathematical expression.
   * @param str The mathematical expression to initialize the model.
   */
  explicit model(const std::string &str);

  /**
   * @brief Constructs a model for calculating credit with given parameters.
   * @param amount Loan amount.
   * @param term Loan term in months.
   * @param rate Interest rate per annum.
   * @param type Type of loan calculation: true for annuity, false for
   * differential.
   */
  model(double amount, int term, double rate, bool type);

  /**
   * @brief Constructs a model for deposit calculations.
   * @param deposit_initialAmount Initial amount of the deposit.
   * @param deposit_placement_period_in_months Term of the deposit in months.
   * @param deposit_interestRate Annual interest rate of the deposit.
   * @param deposit_taxRate Tax rate on the interest.
   * @param deposit_periodicity_of_payments Frequency of deposit payments.
   * @param deposit_isCompounded True if the interest is compounded.
   * @param deposit_amount_of_deposits Total amount of subsequent deposits.
   * @param deposit_withdrawal_amount Total amount of withdrawals.
   */
  model(double deposit_initialAmount, int deposit_placement_period_in_months,
        double deposit_interestRate, double deposit_taxRate,
        int deposit_periodicity_of_payments, bool deposit_isCompounded,
        double deposit_amount_of_deposits, double deposit_withdrawal_amount);

  /**
   * @brief Applies a specified mathematical function to an operand.
   * @param func The function name (e.g., "sin", "cos").
   * @param operand The number to apply the function on.
   * @return The result of the function application.
   */
  double applyFunction(const std::string &func, double operand);

  /**
   * @brief Processes the mathematical expression to prepare it for evaluation.
   */
  void processExpression();

  /**
   * @brief Destructor.
   */
  ~model();

  /**
   * @brief Calculates data for graph plotting based on the expression.
   */
  void calculateGraphData();

  /**
   * @brief Applies a binary operation between two operands.
   * @param first The first operand.
   * @param second The second operand.
   * @param op The operator (e.g., "+", "-", "*").
   * @return The result of the operation.
   */
  double applyOperation(double first, double second, const std::string &op);

  /**
   * @brief Checks for defined functions in the expression to validate them.
   * @return True if all functions are valid, otherwise false.
   */
  bool checkFunctions();

  /**
   * @brief Determines the precedence of an operator used in the expression.
   * @param op The operator to check.
   * @return The precedence level as an integer.
   */
  int precedence(const std::string &op);

  /**
   * @brief Retrieves the mathematical expression currently set in the model.
   * @return Current mathematical expression as a string.
   */
  std::string getExpression();

  /**
   * @brief Retrieves the postfix version of the mathematical expression.
   * @return Postfix mathematical expression as a string.
   */
  std::string getPostfixExpression();

  /**
   * @brief Gets the X values for graph plotting, typically used for the
   * horizontal axis.
   * @return A constant reference to a vector containing the X values.
   */
  const std::vector<double> &getXValues() const;

  /**
   * @brief Gets the Y values for graph plotting, typically used for the
   * vertical axis.
   * @return A constant reference to a vector containing the Y values.
   */
  const std::vector<double> &getYValues() const;

  /**
   * @brief Retrieves the string representation of the result from the last
   * calculation.
   * @return Result of the calculation as a string.
   */
  std::string getResult();

  /**
   * @brief Retrieves the monthly payment amount for a credit model.
   * @return Monthly payment amount as a double.
   */
  double creditGetMonthlyPayment() const { return credit_monthly_payment; }

  /**
   * @brief Retrieves the total repayment amount for the credit term, including
   * interest.
   * @return Total repayment amount as a double.
   */
  double creditGetTotalRepayment() const { return credit_total_repayment; }

  /**
   * @brief Retrieves the total overpayment for the credit, computed as the
   * difference between the total repayment and the credit amount.
   * @return Loan overpayment amount as a double.
   */
  double creditGetLoanOverpayment() const { return credit_loan_overpayment; }

  /**
   * @brief Validates all input parameters for correctness before proceeding
   * with calculations.
   * @return True if all inputs are valid, false otherwise.
   */
  bool validateInputs();

  /**
   * @brief Sets the results to a default or error state if the inputs are not
   * valid.
   */
  void setInvalidResults();

  /**
   * @brief Retrieves the total interest accumulated from the deposit over its
   * term.
   * @return Total interest earned as a double.
   */
  double depositGetTotalInterest() const { return totalInterest; }

  /**
   * @brief Retrieves the total tax paid on the interest earned from the
   * deposit.
   * @return Total tax paid as a double.
   */
  double depositGetTotalTax() const { return totalTax; }

  /**
   * @brief Retrieves the final balance of the deposit after the deposit term,
   * including interest and after tax deductions.
   * @return Final balance of the deposit as a double.
   */
  double depositGetFinalBalance() const { return finalBalance; }

  /**
   * @brief Resets any error states in the model.
   */
  void resetError() { error = false; }

  /**
   * @brief Checks if the model is currently in an error state.
   * @return True if there is an error, false otherwise.
   */
  bool getError() { return error; }

  /**
   * @brief Sets the error state of the model.
   * @param errors True to indicate an error has occurred, false otherwise.
   */
  void setError(bool errors) { error = errors; }

  /**
   * @brief Validates initial conditions and prepares the model for
   * calculations.
   */
  void validateAndInit();

  /**
   * @brief Performs all required calculations based on the current model state.
   */
  void calculate();
};

}  // namespace s21

#endif
