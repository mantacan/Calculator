#ifndef S21_SMARTCALC_CONTROLLER_H_
#define S21_SMARTCALC_CONTROLLER_H_

namespace s21 {

/**
 * @class controller
 * @brief Manages the logic for financial calculations including credits and
 * deposits.
 *
 * This class provides interfaces to perform calculations for credit payments
 * and deposit growth, and stores the results of these calculations along with
 * input parameters.
 */
class controller {
 private:
  const char
      *expression;  ///< Stores the mathematical expression to be evaluated.

  std::vector<double> x_values_contrl;  ///< X values for plotting graphs.
  std::vector<double>
      y_values_contrl;  ///< Y values corresponding to the X values for graphs.

  // Credit related members
  double credit_amount;    ///< Total amount of the credit.
  int credit_term;         ///< Duration of the credit in terms (months/years).
  double credit_rate;      ///< Annual interest rate of the credit.
  bool credit_isAnnuitet;  ///< Flag to determine if the credit is annuitet or
                           ///< differential.

  double credit_result_monthly;  ///< Monthly payment result for credit.
  double
      credit_result_total;  ///< Total amount payable by the end of credit term.
  double credit_result_overpayment;  ///< Total interest overpayment over the
                                     ///< credit term.

  // Deposit related members
  double deposit_initialAmount;            ///< Initial deposit amount.
  int deposit_placement_period_in_months;  ///< Duration of the deposit in
                                           ///< months.
  double deposit_interestRate;  ///< Annual interest rate of the deposit.
  double deposit_taxRate;       ///< Tax rate applicable to the interest earned.
  int deposit_periodicity_of_payments;  ///< Frequency of interest payments
                                        ///< (e.g., monthly, quarterly).
  bool deposit_isCompounded;  ///< Flag to check if the interest is compounded.
  double
      deposit_amount_of_deposits;  ///< Total amount deposited over the period.
  double
      deposit_withdrawal_amount;  ///< Total amount withdrawn over the period.

  double deposit_totalInterest;  ///< Total interest earned on the deposit.
  double deposit_totalTax;       ///< Total tax paid on the interest.
  double deposit_finalBalance;  ///< Final balance of the deposit after the term
                                ///< ends.

 public:
  controller();                 ///< Default constructor.
  controller(const char *str);  ///< Constructor for expressions.
  controller(const char *amount, const char *term, const char *rate,
             gboolean isAnnuitet);  ///< Constructor for credit calculations.
  controller(const char *totalAmountStr, const char *termStr,
             const char *rateStr, const char *taxRateStr,
             const char *paymentFrequencyStr, const char *depositAmountStr,
             const char *withdrawalAmountStr,
             gboolean isCompounded);  ///< Constructor for deposit calculations.
  ~controller();                      ///< Destructor.

  std::unique_ptr<char[]>
  getResultFromModel();  ///< Retrieves results from the model.

  const std::vector<double> &getXValues()
      const;  ///< Returns the x-values for graphing purposes.
  const std::vector<double> &getYValues()
      const;  ///< Returns the y-values for graphing purposes.

  double creditGetMonthly() const {
    return credit_result_monthly;
  }  ///< Retrieves the monthly payment for the credit.
  double creditGetTotal() const {
    return credit_result_total;
  }  ///< Retrieves the total payment amount including interest for the credit.
  double creditGetOverpayment() const {
    return credit_result_overpayment;
  }  ///< Retrieves the total overpayment in interest for the credit.
  double depositGetTotalInterest() const {
    return deposit_totalInterest;
  }  ///< Retrieves the total interest earned from the deposit.
  double depositGetTotalTax() const {
    return deposit_totalTax;
  }  ///< Retrieves the total tax paid on the interest from the deposit.
  double depositGetFinalBalance() const {
    return deposit_finalBalance;
  }  ///< Retrieves the final balance of the deposit.

  void setXValues(const std::vector<double>
                      &values) {  ///< Sets the x-values for graphing purposes.
    x_values_contrl = values;
  }
  void setYValues(const std::vector<double>
                      &values) {  ///< Sets the y-values for graphing purposes.
    y_values_contrl = values;
  }
};
}  // namespace s21

#endif
