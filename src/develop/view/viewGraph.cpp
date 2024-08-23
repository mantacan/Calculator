#include "../smartcalc.h"

/**
 * @brief Handles the drawing event for a GTK+ widget to plot a sine wave using
 * Cairo graphics.
 *
 * This function calculates the sine values for a range of x-coordinates, stores
 * them, and then plots these values on the given GTK+ widget. It sets up the
 * graph, calculates scaling factors based on the widget's size, and then draws
 * axes and the sine wave.
 *
 * @param widget A pointer to the GTK+ widget that the drawing is being
 * performed on.
 * @param cr A pointer to a cairo_t structure representing the Cairo drawing
 * context to be used.
 * @return Returns FALSE indicating that the drawing event should not propagate
 * further.
 */
gboolean s21::view::on_draw_event(GtkWidget *widget, cairo_t *cr) {
  printVector(x_values_view);
  printVector(y_values_view);
  std::cout << "N: " << R << std::endl;
  R++;

  GtkAllocation allocation;
  gtk_widget_get_allocation(widget, &allocation);
  int width = allocation.width;
  int height = allocation.height;

  cairo_set_source_rgb(cr, 1, 1, 1);
  cairo_paint(cr);

  cairo_set_source_rgb(cr, 0, 0, 0);
  cairo_set_line_width(cr, 2);
  cairo_move_to(cr, width / 2, 0);
  cairo_line_to(cr, width / 2, height);
  cairo_move_to(cr, 0, height / 2);
  cairo_line_to(cr, width, height / 2);
  cairo_stroke(cr);

  if (x_values_view.empty() || y_values_view.empty()) {
    return FALSE;
  }

  double x_diff = x_values_view.back() - x_values_view.front();
  double y_min = *std::min_element(y_values_view.begin(), y_values_view.end());
  double y_max = *std::max_element(y_values_view.begin(), y_values_view.end());
  double y_diff = y_max - y_min;

  double x_scale = (x_diff == 0 ? 1 : (width - 40) / x_diff);
  double y_scale = (y_diff == 0 ? 1 : (height - 40) / y_diff);

  cairo_set_source_rgb(cr, 1, 0, 0);
  cairo_set_line_width(cr, 1.5);

  bool first_point = true;
  for (size_t i = 0; i < x_values_view.size(); i++) {
    double x = x_values_view[i];
    double y = y_values_view[i];

    double dx = width / 2 + (x - x_values_view.front()) * x_scale;
    double dy = height / 2 - (y - y_min) * y_scale;

    std::cout << "Drawing Line from (" << dx << ", " << dy << ")" << std::endl;

    if (first_point) {
      cairo_move_to(cr, dx, dy);
      first_point = false;
    } else {
      cairo_line_to(cr, dx, dy);
    }
  }

  cairo_stroke(cr);
  return FALSE;
}