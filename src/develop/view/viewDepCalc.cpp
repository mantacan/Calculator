#include "../smartcalc.h"

namespace s21 {

/**
 * @brief Sets up and displays the deposit calculator window with GTK+ widgets.
 *
 * This method creates a new top-level GTK window tailored for deposit
 * calculations. It sets up a grid containing input fields for various deposit
 * parameters such as total amount, term, interest rate, tax rate, and others.
 * It also includes a button to initiate the calculation, and labels to display
 * the results. This method is designed to be called upon a button press event,
 * setting up everything necessary for the user to enter their data and compute
 * the results.
 *
 * @param button A pointer to the GtkButton that triggers the window rendering.
 * Unused in this function but required by the GTK+ callback signature.
 */
void view::renderingTheDepositCalcWindow(GtkButton *button) {
  dep_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  GtkWidget *grid = gtk_grid_new();
  gtk_container_add(GTK_CONTAINER(dep_window), grid);

  gtk_window_set_title(GTK_WINDOW(dep_window), "Deposit calculator");
  gtk_window_set_default_size(GTK_WINDOW(dep_window), 400, 300);

  dep_entryTotal = gtk_entry_new();
  dep_entryTerm = gtk_entry_new();
  dep_entryRate = gtk_entry_new();
  dep_entryTaxRate = gtk_entry_new();
  dep_entryPaymentFrequency = gtk_entry_new();
  dep_checkCompounded =
      gtk_check_button_new_with_label("Capitalization of interest");
  dep_entryDepositAmount = gtk_entry_new();
  dep_entryWithdrawalAmount = gtk_entry_new();

  gtk_grid_attach(GTK_GRID(grid), gtk_label_new("Deposit amount:"), 0, 0, 1, 1);
  gtk_grid_attach(GTK_GRID(grid), dep_entryTotal, 1, 0, 1, 1);
  gtk_grid_attach(GTK_GRID(grid), gtk_label_new("Deposit term (in months):"), 0,
                  1, 1, 1);
  gtk_grid_attach(GTK_GRID(grid), dep_entryTerm, 1, 1, 1, 1);
  gtk_grid_attach(GTK_GRID(grid), gtk_label_new("Interest rate(%):"), 0, 2, 1,
                  1);
  gtk_grid_attach(GTK_GRID(grid), dep_entryRate, 1, 2, 1, 1);
  gtk_grid_attach(GTK_GRID(grid), gtk_label_new("Tax rate (%):"), 0, 3, 1, 1);
  gtk_grid_attach(GTK_GRID(grid), dep_entryTaxRate, 1, 3, 1, 1);
  gtk_grid_attach(GTK_GRID(grid),
                  gtk_label_new("Periodicity of payments (in months):"), 0, 4,
                  1, 1);
  gtk_grid_attach(GTK_GRID(grid), dep_entryPaymentFrequency, 1, 4, 1, 1);
  gtk_grid_attach(GTK_GRID(grid), dep_checkCompounded, 0, 5, 2, 1);
  gtk_grid_attach(GTK_GRID(grid), gtk_label_new("Replenishments list:"), 0, 6,
                  1, 1);
  gtk_grid_attach(GTK_GRID(grid), dep_entryDepositAmount, 1, 6, 1, 1);
  gtk_grid_attach(GTK_GRID(grid), gtk_label_new("Partial withdrawals list:"), 0,
                  7, 1, 1);
  gtk_grid_attach(GTK_GRID(grid), dep_entryWithdrawalAmount, 1, 7, 1, 1);

  GtkWidget *buttonCalculate = gtk_button_new_with_label("Calculate");
  gtk_grid_attach(GTK_GRID(grid), buttonCalculate, 0, 8, 2, 1);
  g_signal_connect(buttonCalculate, "clicked",
                   G_CALLBACK(dep_extract_input_data), this);

  dep_resultInterest = gtk_label_new("");
  dep_resultTax = gtk_label_new("");
  dep_resultFinalBalance = gtk_label_new("");
  gtk_grid_attach(GTK_GRID(grid), gtk_label_new("Accrued interest:"), 0, 9, 1,
                  1);
  gtk_grid_attach(GTK_GRID(grid), dep_resultInterest, 1, 9, 1, 1);
  gtk_grid_attach(GTK_GRID(grid), gtk_label_new("Tax amount"), 0, 10, 1, 1);
  gtk_grid_attach(GTK_GRID(grid), dep_resultTax, 1, 10, 1, 1);
  gtk_grid_attach(GTK_GRID(grid),
                  gtk_label_new("Deposit amount by the end of the term:"), 0,
                  11, 1, 1);
  gtk_grid_attach(GTK_GRID(grid), dep_resultFinalBalance, 1, 11, 1, 1);

  gtk_widget_show_all(dep_window);
}

}  // namespace s21
