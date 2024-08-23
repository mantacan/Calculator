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
 * @brief Initializes and places widgets into the GTK+ grid for the calculator
 * interface.
 *
 * This function creates and configures all necessary GUI elements (buttons,
 * entry fields, etc.) for the calculator's interface and adds them to the
 * specified grid. Each widget is created with a specific label representing its
 * function (numbers, operations, and additional features like trigonometric
 * functions and a graph window button).
 *
 * @param grid A pointer to the GtkWidget that represents the grid container for
 * placing all the widgets.
 * @param entry A double pointer to the GtkWidget that will represent the main
 * input/output text entry of the calculator.
 * @param wp A pointer to a struct containing pointers to all widgets used in
 * the calculator interface. This struct is used to maintain and manage the
 * state of the widgets throughout the application lifecycle.
 */
void view::create_widgets(GtkWidget *grid, GtkWidget **entry,
                          view::WidgetPointers *wp) {
  *entry = gtk_entry_new();
  entry_widget = *entry;
  this->entry_widget = *entry;

  wp->button0 = gtk_button_new_with_label("0");
  wp->button1 = gtk_button_new_with_label("1");
  wp->button2 = gtk_button_new_with_label("2");
  wp->button3 = gtk_button_new_with_label("3");
  wp->button4 = gtk_button_new_with_label("4");
  wp->button5 = gtk_button_new_with_label("5");
  wp->button6 = gtk_button_new_with_label("6");
  wp->button7 = gtk_button_new_with_label("7");
  wp->button8 = gtk_button_new_with_label("8");
  wp->button9 = gtk_button_new_with_label("9");
  wp->buttonClear = gtk_button_new_with_label("C");
  wp->buttonPlus = gtk_button_new_with_label("+");
  wp->buttonMinus = gtk_button_new_with_label("-");
  wp->buttonMultiply = gtk_button_new_with_label("*");
  wp->buttonDivide = gtk_button_new_with_label("/");
  wp->buttonEqual = gtk_button_new_with_label("=");
  wp->openingBracket = gtk_button_new_with_label("(");
  wp->closedBracket = gtk_button_new_with_label(")");
  wp->percent = gtk_button_new_with_label("%");
  wp->buttonX = gtk_button_new_with_label("x");
  wp->buttonRoot = gtk_button_new_with_label("√");
  wp->buttonMod = gtk_button_new_with_label("mod");
  wp->buttonCos = gtk_button_new_with_label("cos");
  wp->buttonSin = gtk_button_new_with_label("sin");
  wp->buttonTan = gtk_button_new_with_label("tan");
  wp->buttonAcos = gtk_button_new_with_label("acos");
  wp->buttonAsin = gtk_button_new_with_label("asin");
  wp->buttonAtan = gtk_button_new_with_label("atan");
  wp->buttonSqrt = gtk_button_new_with_label("sqrt");
  wp->buttonLn = gtk_button_new_with_label("ln");
  wp->buttonLog = gtk_button_new_with_label("log");
  wp->buttonDot = gtk_button_new_with_label(".");
  wp->buttonPi = gtk_button_new_with_label("𝜋");
  wp->WindowGraph = gtk_button_new_with_label("graph");
  wp->WindowCredit = gtk_button_new_with_label("credit");
  wp->WindowDeposit = gtk_button_new_with_label("deposit");
}

}  // namespace s21