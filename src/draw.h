#ifndef DRAW_H
#define DRAW_H

#include <gtk/gtk.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include "structs.h"

gboolean draw(GtkWidget *widget, cairo_t *cr, gpointer user_data);
void drawGate(cairo_t *cr, const int gate, const double x,
					const double y);
void connectGate(cairo_t *cr, const double x1, const double y1,
					const double x2, const double y2, const bool first,
					const double sizex1, const double sizex2,
					const double maxh);

#endif
