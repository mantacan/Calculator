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
 * @brief Sets up the callbacks for the calculator buttons.
 *
 * @param entry The entry widget where user input is displayed.
 * @param wp Pointer to a structure holding pointers to all widgets in the
 * calculator interface.
 */
void view::setup_callbacks(GtkWidget *entry, view::WidgetPointers *wp) {
  g_signal_connect(wp->button0, "clicked",
                   G_CALLBACK(on_button_clicked_wrapper), entry);
  g_signal_connect(wp->button1, "clicked",
                   G_CALLBACK(on_button_clicked_wrapper), entry);
  g_signal_connect(wp->button2, "clicked",
                   G_CALLBACK(on_button_clicked_wrapper), entry);
  g_signal_connect(wp->button3, "clicked",
                   G_CALLBACK(on_button_clicked_wrapper), entry);
  g_signal_connect(wp->button4, "clicked",
                   G_CALLBACK(on_button_clicked_wrapper), entry);
  g_signal_connect(wp->button5, "clicked",
                   G_CALLBACK(on_button_clicked_wrapper), entry);
  g_signal_connect(wp->button6, "clicked",
                   G_CALLBACK(on_button_clicked_wrapper), entry);
  g_signal_connect(wp->button7, "clicked",
                   G_CALLBACK(on_button_clicked_wrapper), entry);
  g_signal_connect(wp->button8, "clicked",
                   G_CALLBACK(on_button_clicked_wrapper), entry);
  g_signal_connect(wp->button9, "clicked",
                   G_CALLBACK(on_button_clicked_wrapper), entry);
  g_signal_connect(wp->buttonPlus, "clicked",
                   G_CALLBACK(on_button_clicked_wrapper), entry);
  g_signal_connect(wp->buttonMinus, "clicked",
                   G_CALLBACK(on_button_clicked_wrapper), entry);
  g_signal_connect(wp->buttonMultiply, "clicked",
                   G_CALLBACK(on_button_clicked_wrapper), entry);
  g_signal_connect(wp->buttonDivide, "clicked",
                   G_CALLBACK(on_button_clicked_wrapper), entry);
  g_signal_connect(wp->openingBracket, "clicked",
                   G_CALLBACK(on_button_clicked_wrapper), entry);
  g_signal_connect(wp->closedBracket, "clicked",
                   G_CALLBACK(on_button_clicked_wrapper), entry);
  g_signal_connect(wp->percent, "clicked",
                   G_CALLBACK(on_button_clicked_wrapper), entry);
  g_signal_connect(wp->buttonX, "clicked",
                   G_CALLBACK(on_button_clicked_wrapper), entry);
  g_signal_connect(wp->buttonRoot, "clicked",
                   G_CALLBACK(on_button_clicked_wrapper), entry);
  g_signal_connect(wp->buttonMod, "clicked",
                   G_CALLBACK(on_button_clicked_wrapper), entry);
  g_signal_connect(wp->buttonCos, "clicked",
                   G_CALLBACK(on_button_clicked_wrapper), entry);
  g_signal_connect(wp->buttonSin, "clicked",
                   G_CALLBACK(on_button_clicked_wrapper), entry);
  g_signal_connect(wp->buttonTan, "clicked",
                   G_CALLBACK(on_button_clicked_wrapper), entry);
  g_signal_connect(wp->buttonAcos, "clicked",
                   G_CALLBACK(on_button_clicked_wrapper), entry);
  g_signal_connect(wp->buttonAsin, "clicked",
                   G_CALLBACK(on_button_clicked_wrapper), entry);
  g_signal_connect(wp->buttonAtan, "clicked",
                   G_CALLBACK(on_button_clicked_wrapper), entry);
  g_signal_connect(wp->buttonSqrt, "clicked",
                   G_CALLBACK(on_button_clicked_wrapper), entry);
  g_signal_connect(wp->buttonLn, "clicked",
                   G_CALLBACK(on_button_clicked_wrapper), entry);
  g_signal_connect(wp->buttonLog, "clicked",
                   G_CALLBACK(on_button_clicked_wrapper), entry);
  g_signal_connect(wp->buttonDot, "clicked",
                   G_CALLBACK(on_button_clicked_wrapper), entry);
  g_signal_connect(wp->buttonPi, "clicked",
                   G_CALLBACK(on_button_clicked_wrapper), entry);

  g_signal_connect(wp->buttonEqual, "clicked",
                   G_CALLBACK(view::on_button_equal_clicked_wrapper), this);

  g_signal_connect(wp->WindowGraph, "clicked",
                   G_CALLBACK(view::openTheGraphWindow), this);

  g_signal_connect(wp->WindowCredit, "clicked",
                   G_CALLBACK(view::openTheCreditCalcWindow), this);

  g_signal_connect(wp->WindowDeposit, "clicked",
                   G_CALLBACK(view::openTheDepositCalcWindow), this);

  g_signal_connect(wp->buttonClear, "clicked",
                   G_CALLBACK(view::on_button_clear_clicked_wrapper), this);
}

/**
 * @brief Appends the clicked button's label to the text displayed in the entry
 * widget.
 *
 * @param button The button that was clicked.
 * @param user_data User data passed to the callback function (the entry
 * widget).
 */
void view::on_button_clicked(GtkButton *button, gpointer user_data) {
  GtkWidget *entry = static_cast<GtkWidget *>(user_data);
  if (!GTK_IS_ENTRY(entry)) {
    g_critical("Expected GtkEntry but got something else.");
    return;
  }
  const char *button_text = gtk_button_get_label(button);
  const char *current_text = gtk_entry_get_text(GTK_ENTRY(entry));
  std::string new_text = std::string(current_text) + button_text;
  gtk_entry_set_text(GTK_ENTRY(entry), new_text.c_str());
}
/**
 * @brief Clears the text displayed in the entry widget.
 *
 * @param button The "clear" button that was clicked.
 * @param user_data User data passed to the callback function (the view object).
 */
void view::on_button_clear_clicked(GtkButton *button, gpointer user_data) {
  view *self = static_cast<view *>(user_data);
  GtkWidget *entry = self->get_entry_widget();
  if (GTK_IS_ENTRY(entry)) {
    gtk_entry_set_text(GTK_ENTRY(entry), "");
  } else {
    g_critical("on_button_clear_clicked was called with non-GtkEntry widget");
  }
}
/**
 * @brief Processes the input data and displays the result in the entry widget.
 *
 * @param button The "equal" button that was clicked.
 * @param user_data User data passed to the callback function (the entry
 * widget).
 */
void view::on_button_equal_clicked(GtkButton *button, gpointer user_data) {
  GtkWidget *entry = (GtkWidget *)user_data;
  const char *input_text = gtk_entry_get_text(GTK_ENTRY(entry));
  const char *result = process_data(input_text);
  gtk_entry_set_text(GTK_ENTRY(entry), result);
}

/*
 *
 *
 *  CREDIT CALCULATOR
 *
 *
 */
/**
 * @brief Extracts input data for the credit calculator and performs the
 * calculation.
 *
 * @param button The "calculate" button that was clicked.
 * @param user_data User data passed to the callback function (unused).
 */
void view::extract_input_data(GtkWidget *button, gpointer user_data) {
  const char *totalAmountStr = gtk_entry_get_text(GTK_ENTRY(entryTotal));
  const char *termStr = gtk_entry_get_text(GTK_ENTRY(entryTerm));
  const char *rateStr = gtk_entry_get_text(GTK_ENTRY(entryRate));
  gboolean isAnnuitet =
      gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(radioAnn));

  calculate_credit(totalAmountStr, termStr, rateStr, isAnnuitet,
                   resultMonthlyPayment, resultOverpayment, resultTotalPayment);
}

/*
 *
 *
 *  DEPOSIT CALCULATOR
 *
 *
 */
/**
 * @brief Extracts input data for the deposit calculator and performs the
 * calculation.
 *
 * @param button The "calculate" button that was clicked.
 * @param user_data User data passed to the callback function (unused).
 */
void view::dep_extract_input_data(GtkWidget *button, gpointer user_data) {
  const char *totalAmountStr = gtk_entry_get_text(GTK_ENTRY(dep_entryTotal));
  const char *termStr = gtk_entry_get_text(GTK_ENTRY(dep_entryTerm));
  const char *rateStr = gtk_entry_get_text(GTK_ENTRY(dep_entryRate));
  const char *taxRateStr = gtk_entry_get_text(GTK_ENTRY(dep_entryTaxRate));
  const char *paymentFrequencyStr =
      gtk_entry_get_text(GTK_ENTRY(dep_entryPaymentFrequency));
  const char *depositAmountStr =
      gtk_entry_get_text(GTK_ENTRY(dep_entryDepositAmount));
  const char *withdrawalAmountStr =
      gtk_entry_get_text(GTK_ENTRY(dep_entryWithdrawalAmount));
  gboolean isCompounded =
      gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(dep_checkCompounded));

  calculate_deposit(totalAmountStr, termStr, rateStr, taxRateStr,
                    paymentFrequencyStr, depositAmountStr, withdrawalAmountStr,
                    isCompounded, dep_resultInterest, dep_resultTax,
                    dep_resultFinalBalance);
}

}  // namespace s21