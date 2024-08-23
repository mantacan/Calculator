#include "../smartcalc.h"

namespace s21 {

/*
 *
 *
 *  DEFAULT CALCULATOR
 *
 *
 */

/**
 * @brief Processes the input data and returns the result as a C-style string.
 *
 * @param input The input expression to be processed.
 * @return A C-style string containing the result of the computation.
 */
char *view::process_data(const char *input) {
  controller controller(input);
  std::unique_ptr<char[]> resultModel = controller.getResultFromModel();
  char *cstr = new char[strlen(resultModel.get()) + 1];
  strcpy(cstr, resultModel.get());

  x_values_view = controller.getXValues();
  y_values_view = controller.getYValues();

  return cstr;
}

/*
 *
 *
 *  CREDIT CALCULATOR
 *
 *
 */

/**
 * @brief Calculates credit details based on user input and updates the GUI
 * elements accordingly.
 *
 * @param amountStr The total loan amount.
 * @param termStr The loan term in years.
 * @param rateStr The annual interest rate.
 * @param isAnnuitet Whether the loan is annuity-based or not.
 * @param resultMonthlyPayment The widget displaying the monthly payment result.
 * @param resultOverpayment The widget displaying the overpayment result.
 * @param resultTotalPayment The widget displaying the total payment result.
 */
void view::calculate_credit(const char *amountStr, const char *termStr,
                            const char *rateStr, gboolean isAnnuitet,
                            GtkWidget *resultMonthlyPayment,
                            GtkWidget *resultOverpayment,
                            GtkWidget *resultTotalPayment) {
  controller controller(amountStr, termStr, rateStr, isAnnuitet);

  auto monthlyPayment = controller.creditGetMonthly();
  auto overPayment = controller.creditGetOverpayment();
  auto totalPayment = controller.creditGetTotal();

  char buffer[256];
  sprintf(buffer, "%.2f", monthlyPayment);
  gtk_label_set_text(GTK_LABEL(resultMonthlyPayment), buffer);

  sprintf(buffer, "%.2f", overPayment);
  gtk_label_set_text(GTK_LABEL(resultOverpayment), buffer);

  sprintf(buffer, "%.2f", totalPayment);
  gtk_label_set_text(GTK_LABEL(resultTotalPayment), buffer);
}

/*
 *
 *
 *  DEPOSIT CALCULATOR
 *
 *
 */

/**
 * @brief Calculates deposit details based on user input and updates the GUI
 * elements accordingly.
 *
 * @param totalAmountStr The initial deposit amount.
 * @param termStr The deposit term in years.
 * @param rateStr The annual interest rate.
 * @param taxRateStr The tax rate.
 * @param paymentFrequencyStr The frequency of payments.
 * @param depositAmountStr The amount of each deposit payment.
 * @param withdrawalAmountStr The amount of each withdrawal payment.
 * @param isCompounded Whether the interest is compounded or not.
 * @param resultInterest The widget displaying the total interest result.
 * @param resultTax The widget displaying the total tax result.
 * @param resultFinalBalance The widget displaying the final balance result.
 */
void view::calculate_deposit(const char *totalAmountStr, const char *termStr,
                             const char *rateStr, const char *taxRateStr,
                             const char *paymentFrequencyStr,
                             const char *depositAmountStr,
                             const char *withdrawalAmountStr,
                             gboolean isCompounded, GtkWidget *resultInterest,
                             GtkWidget *resultTax,
                             GtkWidget *resultFinalBalance) {
  controller controller(totalAmountStr, termStr, rateStr, taxRateStr,
                        paymentFrequencyStr, depositAmountStr,
                        withdrawalAmountStr, isCompounded);

  auto total = controller.depositGetTotalInterest();
  auto totalTax = controller.depositGetTotalTax();
  auto finalBalance = controller.depositGetFinalBalance();
  char buffer[256];
  sprintf(buffer, "%.2f ₽", total);
  gtk_label_set_text(GTK_LABEL(resultInterest), buffer);

  sprintf(buffer, "%.2f ₽", totalTax);
  gtk_label_set_text(GTK_LABEL(resultTax), buffer);

  sprintf(buffer, "%.2f ₽", finalBalance);
  gtk_label_set_text(GTK_LABEL(resultFinalBalance), buffer);
}

}  // namespace s21