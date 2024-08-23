#include "../smartcalc.h"

namespace s21 {

/**
 * @brief Default constructor for the controller class.
 *        Outputs an error message to standard output. This might indicate that
 *        this constructor should not be used for a valid instantiation.
 */
controller::controller() { std::cout << "ERROR" << std::endl; }

/**
 * @brief Constructor initializing with a mathematical expression.
 * @param str A pointer to a character array containing the mathematical
 * expression.
 */
controller::controller(const char *str) { expression = str; }
/**
 * @brief Constructor for credit calculation setup.
 * @param amount Total amount of the credit as a string.
 * @param term Duration of the credit term as a string (in months or years).
 * @param rate Annual interest rate of the credit as a string.
 * @param isAnnuitet Boolean indicating whether the payment type is annuitet
 * (true) or differential (false).
 */
controller::controller(const char *amount, const char *term, const char *rate,
                       gboolean isAnnuitet) {
  credit_amount = strtod(amount, nullptr);
  credit_term = strtol(term, nullptr, 10);
  credit_rate = strtod(rate, nullptr);
  credit_isAnnuitet = isAnnuitet;
  model models(credit_amount, credit_term, credit_rate, credit_isAnnuitet);

  credit_result_monthly = models.creditGetMonthlyPayment();
  credit_result_overpayment = models.creditGetLoanOverpayment();
  credit_result_total = models.creditGetTotalRepayment();
}

/**
 * @brief Constructor for deposit calculation setup.
 * @param totalAmountStr Initial deposit amount as a string.
 * @param termStr Deposit term in months as a string.
 * @param rateStr Annual interest rate as a string.
 * @param taxRateStr Tax rate applicable to the interest as a string.
 * @param paymentFrequencyStr Frequency of interest payments as a string.
 * @param depositAmountStr Total amount deposited over the period as a string.
 * @param withdrawalAmountStr Total amount withdrawn over the period as a
 * string.
 * @param isCompounded Boolean indicating if the interest is compounded.
 */
controller::controller(const char *totalAmountStr, const char *termStr,
                       const char *rateStr, const char *taxRateStr,
                       const char *paymentFrequencyStr,
                       const char *depositAmountStr,
                       const char *withdrawalAmountStr, gboolean isCompounded) {
  deposit_initialAmount = atof(totalAmountStr);
  deposit_placement_period_in_months = atoi(termStr);
  deposit_interestRate = atof(rateStr);
  deposit_taxRate = atof(taxRateStr);
  deposit_periodicity_of_payments = atoi(paymentFrequencyStr);
  deposit_isCompounded = isCompounded;
  deposit_amount_of_deposits = atof(depositAmountStr);
  deposit_withdrawal_amount = atof(withdrawalAmountStr);

  model models(deposit_initialAmount, deposit_placement_period_in_months,
               deposit_interestRate, deposit_taxRate,
               deposit_periodicity_of_payments, deposit_isCompounded,
               deposit_amount_of_deposits, deposit_withdrawal_amount);

  deposit_totalInterest = models.depositGetTotalInterest();
  deposit_totalTax = models.depositGetTotalTax();
  deposit_finalBalance = models.depositGetFinalBalance();
}

/**
 * @brief Destructor for the controller class.
 */
controller::~controller() {}

/**
 * @brief Retrieves the result from the model and converts it to a C-style
 * string.
 * @return A unique pointer to a character array containing the result.
 */
std::unique_ptr<char[]> controller::getResultFromModel() {
  model models(expression);
  std::string result = models.getResult();
  std::unique_ptr<char[]> cstr(new char[result.length() + 1]);
  std::strcpy(cstr.get(), result.c_str());

  setXValues(models.getXValues());
  setYValues(models.getYValues());

  return cstr;
}

/**
 * @brief Accessor for x-values used in graphing.
 * @return A constant reference to the vector of x-values.
 */
const std::vector<double> &controller::getXValues() const {
  return x_values_contrl;
}

/**
 * @brief Accessor for y-values used in graphing.
 * @return A constant reference to the vector of y-values.
 */
const std::vector<double> &controller::getYValues() const {
  return y_values_contrl;
}

};  // namespace s21