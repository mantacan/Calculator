#include <boost/multiprecision/cpp_dec_float.hpp>
#include <cmath>
#include <limits>

#include "../smartcalc.h"

using namespace boost::multiprecision;
using namespace std;

typedef cpp_dec_float_50 float50;

namespace s21 {

/**
 * @brief Constructs a model with initial credit parameters.
 * @param amount Initial amount of the credit.
 * @param term Duration of the credit in months.
 * @param rate Annual interest rate (percentage).
 * @param type Type of credit repayment: true for annuity, false for
 * differential.
 *
 * Initializes credit parameters and validates them. If the inputs are invalid,
 * sets the credit calculation results to NaN. Otherwise, proceeds to calculate
 * payment details based on the specified type.
 */
model::model(double amount, int term, double rate, bool type)
    : credit_amount_mod(amount),
      credit_term_mod(term),
      credit_rate_mod(rate / 1200.0),
      credit_type_mod(type) {
  if (!validateInputs()) {
    setInvalidResults();
  } else {
    credit_type();
  }
}

/**
 * @brief Validates the initial credit parameters.
 * @return True if all parameters are valid, False otherwise.
 *
 * Checks that the amount and term are positive, and the rate is between 0 and 1
 * (inclusive), which should be a valid fraction for monthly calculations.
 */
bool model::validateInputs() {
  return credit_amount_mod > 0 && credit_term_mod > 0 && credit_rate_mod >= 0 &&
         credit_rate_mod <= 1;
}

/**
 * @brief Sets invalid results for credit calculations.
 *
 * Assigns NaN (Not a Number) to all credit payment results to indicate invalid
 * or erroneous input parameters.
 */
void model::setInvalidResults() {
  credit_monthly_payment = std::numeric_limits<double>::quiet_NaN();
  credit_total_repayment = std::numeric_limits<double>::quiet_NaN();
  credit_loan_overpayment = std::numeric_limits<double>::quiet_NaN();
}

/**
 * @brief Determines the type of credit repayment calculation based on the user
 * input.
 *
 * Calls either `calculateAnnuityPayment()` or `calculateDifferentialPayment()`
 * depending on the type of credit repayment specified during initialization.
 */
void model::credit_type() {
  if (credit_type_mod) {
    calculateAnnuityPayment();
  } else {
    calculateDifferentialPayment();
  }
}

/**
 * @brief Calculates the differential payment schedule for a credit.
 *
 * Computes monthly payments decreasing over time as the principal amount is
 * paid down. Accumulates total payment and interest over the term.
 */
void model::calculateDifferentialPayment() {
  float50 totalInterest = 0;
  float50 totalPayment = 0;
  float50 remainingAmount = credit_amount_mod;

  for (int i = 0; i < credit_term_mod; i++) {
    float50 monthlyInterest = remainingAmount * credit_rate_mod;
    totalInterest += monthlyInterest;
    float50 monthlyPayment =
        (credit_amount_mod / credit_term_mod) + monthlyInterest;
    totalPayment += monthlyPayment;
    remainingAmount -= (credit_amount_mod / credit_term_mod);
  }

  credit_monthly_payment =
      static_cast<int>(totalPayment / credit_term_mod + 0.5);
  credit_total_repayment = static_cast<int>(totalPayment + 0.5);
  credit_loan_overpayment = static_cast<int>(totalInterest + 0.5);
}

/**
 * @brief Calculates the annuity payment schedule for a credit.
 *
 * Uses the annuity formula to compute equal monthly payments that include both
 * principal and interest, spread evenly over the term.
 */
void model::calculateAnnuityPayment() {
  float50 annuityCoefficient =
      (credit_rate_mod * pow((1 + credit_rate_mod), credit_term_mod)) /
      (pow((1 + credit_rate_mod), credit_term_mod) - 1);
  float50 monthlyPayment = credit_amount_mod * annuityCoefficient;

  credit_monthly_payment = static_cast<int>(monthlyPayment + 0.5);
  credit_total_repayment =
      static_cast<int>(monthlyPayment * credit_term_mod + 0.5);
  credit_loan_overpayment = static_cast<int>(
      (monthlyPayment * credit_term_mod - credit_amount_mod) + 0.5);
}

};  // namespace s21
