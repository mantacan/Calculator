#include "../smartcalc.h"

/**
 * @brief Entry point of the application, sets up the GTK+ environment and main
 * window.
 *
 * This function initializes GTK+, sets up the main window and grid layout,
 * creates widgets, and configures events and styles. It then displays the
 * window and enters the GTK+ main event loop.
 *
 * @param argc The count of command-line arguments.
 * @param argv The array of command-line arguments.
 * @return Returns 0 upon exit of the application.
 */
int main(int argc, char *argv[]) {
  gtk_init(&argc, &argv);

  GtkWidget *window, *grid, *entry;
  s21::view::WidgetPointers wp;

  s21::view vi;

  vi.initialize_window(&window, &grid);
  vi.create_widgets(grid, &entry, &wp);
  vi.setup_callbacks(entry, &wp);

  GtkWidget *buttons[] = {wp.button0, wp.button1, wp.button2, wp.button3,
                          wp.button4, wp.button5, wp.button6, wp.button7,
                          wp.button8, wp.button9};
  vi.apply_css_styles(wp.buttonEqual, buttons, 10);
  vi.configure_grid(grid, entry, &wp);
  vi.show_window_and_run(window, grid);

  return 0;
}

namespace s21 {

GtkWidget *view::dep_window = nullptr;
GtkWidget *view::dep_entryTotal = nullptr;
GtkWidget *view::dep_entryTerm = nullptr;
GtkWidget *view::dep_entryRate = nullptr;
GtkWidget *view::dep_entryTaxRate = nullptr;
GtkWidget *view::dep_entryPaymentFrequency = nullptr;
GtkWidget *view::dep_checkCompounded = nullptr;
GtkWidget *view::dep_entryDepositAmount = nullptr;
GtkWidget *view::dep_entryWithdrawalAmount = nullptr;
GtkWidget *view::dep_resultInterest = nullptr;
GtkWidget *view::dep_resultTax = nullptr;
GtkWidget *view::dep_resultFinalBalance = nullptr;
GtkWidget *view::window = nullptr;
GtkWidget *view::entryTotal = nullptr;
GtkWidget *view::entryTerm = nullptr;
GtkWidget *view::entryRate = nullptr;
GtkWidget *view::radioAnn = nullptr;
GtkWidget *view::radioDiff = nullptr;
GtkWidget *view::resultMonthlyPayment = nullptr;
GtkWidget *view::resultOverpayment = nullptr;
GtkWidget *view::resultTotalPayment = nullptr;

void view::printVector(const std::vector<double> &vec) {
  for (double value : vec) {
    std::cout << value << " ";
  }
  std::cout << std::endl;
}

/**
 * @brief Shows the main window and runs the GTK+ main loop.
 *
 * This function adds the provided grid to the window, shows all widgets within
 * the window, and starts the GTK+ main loop to handle events.
 *
 * @param window Pointer to the main GTK+ window widget.
 * @param grid Pointer to the GTK+ grid widget containing all other widgets.
 */
void view::show_window_and_run(GtkWidget *window, GtkWidget *grid) {
  gtk_container_add(GTK_CONTAINER(window), grid);
  gtk_widget_show_all(window);
  gtk_main();

  gtk_container_add(GTK_CONTAINER(window), grid);

  gtk_widget_show_all(window);
  g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

  gtk_main();
}

/**
 * @brief Opens the credit calculator window when triggered by a button press.
 *
 * This function acts as a callback for a button event, initiating the display
 * of the credit calculation interface.
 *
 * @param button The GTK+ button that was pressed to trigger this event.
 * @param user_data Generic pointer to user-defined data, cast to the current
 * instance of `view`.
 */
void view::openTheCreditCalcWindow(GtkButton *button, gpointer user_data) {
  view *self = static_cast<view *>(user_data);
  self->renderingTheCreditCalcWindow(button);
}

void view::openTheDepositCalcWindow(GtkButton *button, gpointer user_data) {
  view *self = static_cast<view *>(user_data);
  self->renderingTheDepositCalcWindow(button);
}

/**
 * @brief Wrapper function to handle generic button click events and append the
 * button label to the entry widget's text.
 *
 * This function checks if the given GtkWidget is an entry, and appends the text
 * of the button to the text of the entry.
 *
 * @param button The GTK+ button that was pressed.
 * @param entry Generic pointer to the GTK+ entry widget where text will be
 * appended.
 */
void view::on_button_clicked_wrapper(GtkButton *button, gpointer entry) {
  if (!GTK_IS_ENTRY(entry)) {
    g_critical("Expected GtkEntry but got something else.");
    return;
  }
  const char *button_text = gtk_button_get_label(button);
  const char *current_text = gtk_entry_get_text(GTK_ENTRY(entry));
  std::string new_text = std::string(current_text) + button_text;
  gtk_entry_set_text(GTK_ENTRY(entry), new_text.c_str());
}
void view::openTheGraphWindow(GtkButton *button, gpointer user_data) {
  std::cout << "openTheGraphWindow" << std::endl;
  view *self = static_cast<view *>(user_data);
  self->on_button_graph_clicked(button);
}

void view::on_button_clear_clicked_wrapper(GtkButton *button,
                                           gpointer user_data) {
  view *self = static_cast<view *>(user_data);
  self->on_button_clear_clicked(button, user_data);
}

void view::on_button_equal_clicked_wrapper(GtkButton *button,
                                           gpointer user_data) {
  view *self = static_cast<view *>(user_data);
  if (!self) {
    g_critical("Self pointer in on_button_equal_clicked_wrapper is null");
    return;
  }
  GtkWidget *entry = self->get_entry_widget();
  if (!GTK_IS_ENTRY(entry)) {
    g_critical(
        "Expected GtkEntry but got something else in "
        "on_button_equal_clicked_wrapper");
    return;
  }
  self->on_button_equal_clicked(button, entry);
}
/**
 * @brief Handles the drawing event for a GTK+ widget using Cairo.
 *
 * This wrapper function is used to call the actual drawing function of the
 * class which renders graphical representations (e.g., plots) on a widget.
 *
 * @param widget The widget where the drawing occurs.
 * @param cr The Cairo context used for drawing.
 * @param user_data Generic pointer to user-defined data, typically an instance
 * of `view`.
 * @return Returns TRUE to stop further event handling, FALSE otherwise.
 */
gboolean view::on_draw_event_wrapper(GtkWidget *widget, cairo_t *cr,
                                     gpointer user_data) {
  std::cout << "on_draw_event_wrapper" << std::endl;

  view *self = static_cast<view *>(user_data);
  return self->on_draw_event(widget, cr);
}

}  // namespace s21
