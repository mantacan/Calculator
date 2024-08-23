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
 * @brief Initializes the main window and grid layout.
 *
 * This method creates a new GTK+ top-level window and grid layout.
 * It sets the window's title, default size, and connects the "destroy" signal
 * to the GTK+ main_quit function to exit the application when the window is
 * closed.
 *
 * @param window Pointer to store the newly created GTK+ window.
 * @param grid Pointer to store the newly created GTK+ grid layout.
 */
void view::initialize_window(GtkWidget **window, GtkWidget **grid) {
  x_values_view = {0, 0, 0, 0, 0, 0};
  y_values_view = {0, 0, 0, 0, 0, 0};

  *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  *grid = gtk_grid_new();
  gtk_window_set_title(GTK_WINDOW(*window), "SmartCalculator");
  gtk_window_set_default_size(GTK_WINDOW(*window), 435, 265);
  g_signal_connect(*window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
}

/**
 * @brief Configures the grid layout with widgets.
 *
 * This method attaches various buttons and entry widget to the provided grid
 * layout. It arranges the widgets in a specified layout and order.
 *
 * @param grid Pointer to the GTK+ grid layout.
 * @param entry Pointer to the entry widget.
 * @param wp Pointer to a structure containing pointers to various button
 * widgets.
 */
void view::configure_grid(GtkWidget *grid, GtkWidget *entry,
                          view::WidgetPointers *wp) {
  gtk_grid_attach(GTK_GRID(grid), entry, 0, 0, 8, 1);
  gtk_grid_attach(GTK_GRID(grid), wp->buttonClear, 0, 1, 1, 1);
  gtk_grid_attach(GTK_GRID(grid), wp->openingBracket, 1, 1, 1, 1);
  gtk_grid_attach(GTK_GRID(grid), wp->closedBracket, 2, 1, 1, 1);
  gtk_grid_attach(GTK_GRID(grid), wp->buttonMod, 3, 1, 1, 1);
  gtk_grid_attach(GTK_GRID(grid), wp->button7, 0, 2, 1, 1);
  gtk_grid_attach(GTK_GRID(grid), wp->button8, 1, 2, 1, 1);
  gtk_grid_attach(GTK_GRID(grid), wp->button9, 2, 2, 1, 1);
  gtk_grid_attach(GTK_GRID(grid), wp->button4, 0, 3, 1, 1);
  gtk_grid_attach(GTK_GRID(grid), wp->button5, 1, 3, 1, 1);
  gtk_grid_attach(GTK_GRID(grid), wp->button6, 2, 3, 1, 1);
  gtk_grid_attach(GTK_GRID(grid), wp->button1, 0, 4, 1, 1);
  gtk_grid_attach(GTK_GRID(grid), wp->button2, 1, 4, 1, 1);
  gtk_grid_attach(GTK_GRID(grid), wp->button3, 2, 4, 1, 1);
  gtk_grid_attach(GTK_GRID(grid), wp->button0, 0, 5, 1, 1);
  gtk_grid_attach(GTK_GRID(grid), wp->buttonDot, 1, 5, 1, 1);
  gtk_grid_attach(GTK_GRID(grid), wp->percent, 2, 5, 1, 1);
  gtk_grid_attach(GTK_GRID(grid), wp->buttonPlus, 3, 5, 1, 1);
  gtk_grid_attach(GTK_GRID(grid), wp->buttonMinus, 3, 4, 1, 1);
  gtk_grid_attach(GTK_GRID(grid), wp->buttonMultiply, 3, 3, 1, 1);
  gtk_grid_attach(GTK_GRID(grid), wp->buttonDivide, 3, 2, 1, 1);
  gtk_grid_attach(GTK_GRID(grid), wp->buttonEqual, 4, 4, 1, 2);
  gtk_grid_attach(GTK_GRID(grid), wp->buttonX, 4, 3, 1, 1);
  gtk_grid_attach(GTK_GRID(grid), wp->buttonRoot, 4, 2, 1, 1);
  gtk_grid_attach(GTK_GRID(grid), wp->buttonPi, 4, 1, 1, 1);
  gtk_grid_attach(GTK_GRID(grid), wp->buttonCos, 5, 3, 1, 1);
  gtk_grid_attach(GTK_GRID(grid), wp->buttonSin, 5, 4, 1, 1);
  gtk_grid_attach(GTK_GRID(grid), wp->buttonTan, 5, 5, 1, 1);
  gtk_grid_attach(GTK_GRID(grid), wp->buttonAcos, 6, 3, 1, 1);
  gtk_grid_attach(GTK_GRID(grid), wp->buttonAsin, 6, 4, 1, 1);
  gtk_grid_attach(GTK_GRID(grid), wp->buttonAtan, 6, 5, 1, 1);
  gtk_grid_attach(GTK_GRID(grid), wp->buttonSqrt, 7, 3, 1, 1);
  gtk_grid_attach(GTK_GRID(grid), wp->buttonLn, 7, 4, 1, 1);
  gtk_grid_attach(GTK_GRID(grid), wp->buttonLog, 7, 5, 1, 1);
  gtk_grid_attach(GTK_GRID(grid), wp->WindowGraph, 8, 0, 1, 6);

  gtk_grid_attach(GTK_GRID(grid), wp->WindowCredit, 5, 1, 3, 1);
  gtk_grid_attach(GTK_GRID(grid), wp->WindowDeposit, 5, 2, 3, 1);
}
/**
 * @brief Applies CSS styles to buttons.
 *
 * This method creates and applies CSS styles to buttons and the equal button
 * using GTK+ CSS provider. It sets the minimum width, height, font size,
 * padding, margin, text color, and background color of the buttons.
 *
 * @param buttonEqual Pointer to the equal button widget.
 * @param buttons Array of pointers to other button widgets.
 * @param num_buttons Number of buttons in the array.
 */
void view::apply_css_styles(GtkWidget *buttonEqual, GtkWidget *buttons[],
                            int num_buttons) {
  GtkCssProvider *provider = gtk_css_provider_new();
  gtk_css_provider_load_from_data(provider,
                                  "button {"
                                  "   min-width: 30px;"
                                  "   min-height: 30px;"
                                  "   font-size: 16px;"
                                  "   padding: 5px;"
                                  "   margin: 2px;"
                                  "   color: white;"
                                  "   background-color: #333333;"
                                  "}",
                                  -1, NULL);

  gtk_style_context_add_provider_for_screen(
      gdk_screen_get_default(), GTK_STYLE_PROVIDER(provider),
      GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

  GtkCssProvider *equal_button_provider = gtk_css_provider_new();
  gtk_css_provider_load_from_data(equal_button_provider,
                                  "#buttonEqual {"
                                  "   background-color: #D2691E;"
                                  "   color: #FFFFFF;"
                                  "}",
                                  -1, NULL);
  gtk_style_context_add_provider(gtk_widget_get_style_context(buttonEqual),
                                 GTK_STYLE_PROVIDER(equal_button_provider),
                                 GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
  gtk_widget_set_name(buttonEqual, "buttonEqual");

  g_object_unref(provider);
  g_object_unref(equal_button_provider);
}

/*
 *
 *
 *  GRAPH
 *
 *
 */
/**
 * @brief Handles the graph button click event.
 *
 * This method creates a new GTK+ top-level window with a drawing area
 * and sets its size. It connects the "draw" signal of the drawing area
 * to the on_draw_event_wrapper method for drawing graphs.
 *
 * @param button Pointer to the graph button widget.
 */
void s21::view::on_button_graph_clicked(GtkButton *button) {
  std::cout << "on_button_graph_clicked" << std::endl;

  GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  GtkWidget *drawing_area = gtk_drawing_area_new();
  gtk_widget_set_size_request(drawing_area, 600, 400);
  gtk_container_add(GTK_CONTAINER(window), drawing_area);

  g_signal_connect(G_OBJECT(drawing_area), "draw",
                   G_CALLBACK(view::on_draw_event_wrapper), this);
  gtk_widget_show_all(window);
}

}  // namespace s21