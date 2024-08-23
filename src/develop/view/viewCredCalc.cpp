#include "../smartcalc.h"

namespace s21 {

/**
 * @brief Creates and displays the credit calculator window with all necessary
 * GTK+ widgets.
 *
 * This method initializes a new top-level GTK window and arranges all required
 * widgets inside a grid. It includes input fields for credit amount, term, and
 * interest rate, radio buttons for choosing between annuity and differentiated
 * payment methods, and a button to initiate credit calculation. Results of the
 * calculation such as monthly payment, overpayment, and total payment are
 * displayed in labeled fields. The setup is designed for easy user interaction
 * and clear display of information.
 *
 * @param button A pointer to the GtkButton that triggers the window rendering.
 * Unused directly, but necessary for GTK+ callback conventions.
 */
void view::renderingTheCreditCalcWindow(GtkButton *button) {
  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  GtkWidget *grid = gtk_grid_new();
  gtk_container_add(GTK_CONTAINER(window), grid);

  gtk_window_set_title(GTK_WINDOW(window), "Credit calculator");
  gtk_window_set_default_size(GTK_WINDOW(window), 350, 280);

  entryTotal = gtk_entry_new();
  entryTerm = gtk_entry_new();
  entryRate = gtk_entry_new();
  radioAnn = gtk_radio_button_new_with_label(NULL, "Annuity");
  radioDiff = gtk_radio_button_new_with_label_from_widget(
      GTK_RADIO_BUTTON(radioAnn), "Differentiated");

  gtk_grid_attach(GTK_GRID(grid), gtk_label_new("Total credit amount:"), 0, 0,
                  1, 1);
  gtk_grid_attach(GTK_GRID(grid), entryTotal, 1, 0, 1, 1);

  gtk_grid_attach(GTK_GRID(grid), gtk_label_new("Term (in months):"), 0, 1, 1,
                  1);
  gtk_grid_attach(GTK_GRID(grid), entryTerm, 1, 1, 1, 1);

  gtk_grid_attach(GTK_GRID(grid), gtk_label_new("Interest rate (%):"), 0, 2, 1,
                  1);
  gtk_grid_attach(GTK_GRID(grid), entryRate, 1, 2, 1, 1);

  gtk_grid_attach(GTK_GRID(grid), gtk_label_new("Type:"), 0, 3, 1, 1);
  gtk_grid_attach(GTK_GRID(grid), radioAnn, 1, 3, 1, 1);
  gtk_grid_attach(GTK_GRID(grid), radioDiff, 1, 4, 1, 1);

  GtkWidget *buttonCalculate = gtk_button_new_with_label("Calculate");
  gtk_grid_attach(GTK_GRID(grid), buttonCalculate, 0, 5, 1, 1);
  g_signal_connect(buttonCalculate, "clicked", G_CALLBACK(extract_input_data),
                   this);

  GtkWidget *buttonCancel = gtk_button_new_with_label("Abolition");
  gtk_grid_attach(GTK_GRID(grid), buttonCancel, 1, 5, 1, 1);

  resultMonthlyPayment = gtk_label_new("");
  resultOverpayment = gtk_label_new("");
  resultTotalPayment = gtk_label_new("");
  gtk_grid_attach(GTK_GRID(grid), gtk_label_new("Monthly payment:"), 0, 6, 1,
                  1);
  gtk_grid_attach(GTK_GRID(grid), resultMonthlyPayment, 1, 6, 1, 1);
  gtk_grid_attach(GTK_GRID(grid), gtk_label_new("Overpayment on credit:"), 0, 7,
                  1, 1);
  gtk_grid_attach(GTK_GRID(grid), resultOverpayment, 1, 7, 1, 1);
  gtk_grid_attach(GTK_GRID(grid), gtk_label_new("Total payment:"), 0, 8, 1, 1);
  gtk_grid_attach(GTK_GRID(grid), resultTotalPayment, 1, 8, 1, 1);

  gtk_widget_show_all(window);
}

}  // namespace s21
