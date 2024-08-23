#include "../smartcalc.h"

namespace s21 {

/**
 * @brief Constructs a model with initial deposit parameters.
 * @param deposit_initialAmount The initial amount deposited.
 * @param deposit_placement_period_in_months The duration of the deposit in
 * months.
 * @param deposit_interestRate Annual interest rate as a percentage.
 * @param deposit_taxRate Tax rate on the interest earned as a percentage.
 * @param deposit_periodicity_of_payments Frequency of interest application to
 * the deposit (in months).
 * @param deposit_isCompounded True if interest is compounded, false if interest
 * is applied at fixed periods.
 * @param deposit_amount_of_deposits Amount added to the deposit at each
 * interest application period.
 * @param deposit_withdrawal_amount Amount withdrawn from the deposit at each
 * interest application period.
 *
 * Initializes deposit parameters and validates them. If the inputs are valid,
 * it proceeds to calculate the final deposit balance including interest and tax
 * deductions.
 */
model::model(double deposit_initialAmount,
             int deposit_placement_period_in_months,
             double deposit_interestRate, double deposit_taxRate,
             int deposit_periodicity_of_payments, bool deposit_isCompounded,
             double deposit_amount_of_deposits,
             double deposit_withdrawal_amount)
    : initialAmount(deposit_initialAmount),
      periodMonths(deposit_placement_period_in_months),
      interestRate(deposit_interestRate / 100.0),
      taxRate(deposit_taxRate / 100.0),
      paymentFrequency(deposit_periodicity_of_payments),
      isCompounded(deposit_isCompounded),
      depositAmount(deposit_amount_of_deposits),
      withdrawalAmount(deposit_withdrawal_amount) {
  validateAndInit();
}

/**
 * @brief Validates the initial deposit parameters and initializes the
 * calculation.
 *
 * If any parameter is invalid (e.g., negative amounts, zero period), it sets
 * the final balance and tax calculations to NaN. Otherwise, it calls
 * `dep_calculate()` to compute the deposit's final balance and accrued interest
 * and tax.
 */
void model::validateAndInit() {
  if (initialAmount < 0 || periodMonths <= 0 || interestRate < 0 ||
      taxRate < 0 || depositAmount < 0 || withdrawalAmount < 0) {
    finalBalance = totalTax = totalInterest =
        std::numeric_limits<double>::quiet_NaN();
  } else {
    dep_calculate();
  }
}

/**
 * @brief Calculates the final balance, total interest, and tax for the deposit.
 *
 * Iteratively applies interest and tax deductions based on the deposit
 * parameters. Adjusts the balance for monthly deposits and withdrawals, and
 * applies interest according to the compounding settings and payment frequency.
 */
void model::dep_calculate() {
  float50 finalBalanceCalc = initialAmount;
  float50 totalTaxCalc = 0;
  float50 totalInterestCalc = 0;
  float50 monthlyInterestRate = interestRate / 12;

  for (int month = 1; month <= periodMonths; ++month) {
    finalBalanceCalc += depositAmount;
    finalBalanceCalc -= withdrawalAmount;

    float50 interest = finalBalanceCalc * monthlyInterestRate;
    float50 tax = interest * taxRate;
    totalTaxCalc += tax;

    if (isCompounded) {
      finalBalanceCalc += interest - tax;
    } else if (month % paymentFrequency == 0 || month == periodMonths) {
      finalBalanceCalc += interest - tax;
      totalInterestCalc += interest - tax;
    }
  }

  finalBalance = finalBalanceCalc.convert_to<double>();
  totalTax = totalTaxCalc.convert_to<double>();
  totalInterest = totalInterestCalc.convert_to<double>();
}

};  // namespace s21
