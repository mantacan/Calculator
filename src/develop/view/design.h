#ifndef S21_SMARTCALC_DESIGN_H_
#define S21_SMARTCALC_DESIGN_H_

#include <gtk/gtk.h>

#include <iostream>
#include <vector>

namespace s21 {

/**
 * @brief Class responsible for the view of the application.
 */
class view {
 private:
  std::vector<double> x_values_view; /**< Vector to store x values for graph. */
  std::vector<double> y_values_view; /**< Vector to store y values for graph. */
  int R;                             /**< Variable for radius. */

 public:
  GtkWidget *entry_widget;
  static GtkWidget *window, *entryTotal, *entryTerm, *entryRate, *radioAnn,
      *radioDiff;
  static GtkWidget *dep_window, *dep_entryTotal, *dep_entryTerm, *dep_entryRate,
      *dep_radioAnn, *dep_radioDiff;
  static GtkWidget *resultMonthlyPayment, *resultOverpayment,
      *resultTotalPayment;
  static GtkWidget *dep_resultMonthlyPayment, *dep_resultOverpayment,
      *dep_resultTotalPayment;
  static GtkWidget *dep_entryTaxRate, *dep_entryPaymentFrequency,
      *dep_checkCompounded;
  static GtkWidget *dep_entryDepositAmount, *dep_entryWithdrawalAmount,
      *dep_resultInterest;
  static GtkWidget *dep_resultTax, *dep_resultFinalBalance;

  /**
   * @brief Structure to hold pointers to various buttons.
   */
  typedef struct {
    GtkWidget *button0;
    GtkWidget *button1;
    GtkWidget *button2;
    GtkWidget *button3;
    GtkWidget *button4;
    GtkWidget *button5;
    GtkWidget *button6;
    GtkWidget *button7;
    GtkWidget *button8;
    GtkWidget *button9;
    GtkWidget *buttonPlus;
    GtkWidget *buttonMinus;
    GtkWidget *buttonMultiply;
    GtkWidget *buttonDivide;
    GtkWidget *openingBracket;
    GtkWidget *closedBracket;
    GtkWidget *percent;
    GtkWidget *buttonX;
    GtkWidget *buttonRoot;
    GtkWidget *buttonMod;
    GtkWidget *buttonCos;
    GtkWidget *buttonSin;
    GtkWidget *buttonTan;
    GtkWidget *buttonAcos;
    GtkWidget *buttonAsin;
    GtkWidget *buttonAtan;
    GtkWidget *buttonSqrt;
    GtkWidget *buttonLn;
    GtkWidget *buttonLog;
    GtkWidget *buttonDot;
    GtkWidget *buttonPi;
    GtkWidget *WindowDeposit;
    GtkWidget *WindowGraph;
    GtkWidget *WindowCredit;
    GtkWidget *buttonEqual;
    GtkWidget *buttonClear;
    GtkWidget *entryTotal;
    GtkWidget *entryTerm;
    GtkWidget *entryRate;
    GtkWidget *radioAnn;
    GtkWidget *radioDiff;
    GtkWidget *resultMonthlyPayment;
    GtkWidget *resultOverpayment;
    GtkWidget *resultTotalPayment;
  } WidgetPointers;

  /**
   * @brief Constructor.
   */
  view() : x_values_view(), y_values_view() {}
  /**
   * @brief Destructor.
   */
  ~view() {}
  /**
   * @brief Renders the credit calculator window.
   *
   * @param button The button triggering the function call.
   */
  void renderingTheCreditCalcWindow(GtkButton *button);
  static void extract_input_data(GtkWidget *button, gpointer user_data);
  static void dep_extract_input_data(GtkWidget *button, gpointer user_data);

  void printVector(const std::vector<double> &vec);
  void setXValues(const std::vector<double> &values) { x_values_view = values; }
  void setYValues(const std::vector<double> &values) { y_values_view = values; }
  const std::vector<double> &getX() const { return x_values_view; }
  const std::vector<double> &getY() const { return y_values_view; }
  void on_button_graph_clicked(GtkButton *button);
  GtkWidget *get_entry_widget() const { return entry_widget; }
  static void calculate_credit(const char *totalAmountStr, const char *termStr,
                               const char *rateStr, gboolean isAnnuitet,
                               GtkWidget *resultMonthlyPayment,
                               GtkWidget *resultOverpayment,
                               GtkWidget *resultTotalPayment);

  static void openTheCreditCalcWindow(GtkButton *button, gpointer user_data);

  static void openTheDepositCalcWindow(GtkButton *button, gpointer user_data);

  void renderingTheDepositCalcWindow(GtkButton *button);
  static void depoz_extract_input_data(GtkWidget *button, gpointer user_data);
  static void calculate_deposit(const char *totalAmountStr, const char *termStr,
                                const char *rateStr, const char *taxRateStr,
                                const char *paymentFrequencyStr,
                                const char *depositAmountStr,
                                const char *withdrawalAmountStr,
                                gboolean isCompounded,
                                GtkWidget *resultInterest, GtkWidget *resultTax,
                                GtkWidget *resultFinalBalance);
  static void on_button_clicked_wrapper(GtkButton *button, gpointer entry);

  static void openTheGraphWindow(GtkButton *button, gpointer user_data);

  static void on_button_clear_clicked_wrapper(GtkButton *button,
                                              gpointer user_data);

  static void on_button_equal_clicked_wrapper(GtkButton *button,
                                              gpointer user_data);

  static gboolean on_draw_event_wrapper(GtkWidget *widget, cairo_t *cr,
                                        gpointer user_data);

  /**
   * @brief Callback function for button click event.
   *
   * @param button The button clicked.
   * @param user_data Pointer to user data.
   */
  void on_button_clicked(GtkButton *button, gpointer user_data);
  /**
   * @brief Callback function for clearing the entry widget.
   *
   * @param button The button clicked.
   * @param user_data Pointer to user data.
   */
  void on_button_clear_clicked(GtkButton *button, gpointer user_data);
  /**
   * @brief Processes the input data and returns the result as a C-style string.
   *
   * @param input The input expression to be processed.
   * @return A C-style string containing the result of the computation.
   */
  char *process_data(const char *input);
  void on_button_equal_clicked(GtkButton *button, gpointer user_data);
  /**
   * @brief Initializes the main window and grid.
   *
   * @param window Pointer to the main window.
   * @param grid Pointer to the grid widget.
   */
  void initialize_window(GtkWidget **window, GtkWidget **grid);
  /**
   * @brief Creates widgets and adds them to the grid.
   *
   * @param grid Pointer to the grid widget.
   * @param entry Pointer to the entry widget.
   * @param wp Pointer to the WidgetPointers structure.
   */
  void create_widgets(GtkWidget *grid, GtkWidget **entry, WidgetPointers *wp);
  /**
   * @brief Sets up signal callbacks for widgets.
   *
   * @param entry Pointer to the entry widget.
   * @param wp Pointer to the WidgetPointers structure.
   */
  void setup_callbacks(GtkWidget *entry, WidgetPointers *wp);
  /**
   * @brief Displays the window and starts the GTK main loop.
   *
   * @param window Pointer to the window widget.
   * @param grid Pointer to the grid widget.
   */
  void show_window_and_run(GtkWidget *window, GtkWidget *grid);
  /**
   * @brief Applies CSS styles to buttons.
   *
   * @param buttonEqual Pointer to the equal button widget.
   * @param buttons Array of button widgets.
   * @param num_buttons Number of buttons.
   */
  void apply_css_styles(GtkWidget *buttonEqual, GtkWidget *buttons[],
                        int num_buttons);
  /**
   * @brief Configures the grid layout.
   *
   * @param grid Pointer to the grid widget.
   * @param entry Pointer to the entry widget.
   * @param wp Pointer to the WidgetPointers structure.
   */
  void configure_grid(GtkWidget *grid, GtkWidget *entry, WidgetPointers *wp);
  gboolean on_draw_event(GtkWidget *widget, cairo_t *cr);
};
}  // namespace s21

#endif
