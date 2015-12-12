#ifndef DRAW_H
#define DRAW_H

#include <gtk/gtk.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include "structs.h"

void drawGate(cairo_t *cr, int gate, double x, double y);
void connectGate(cairo_t *cr, double x1, double y1, double x2, double y2,bool first, double sizex1, double sizex2, double maxh);
gboolean draw(GtkWidget *widget, cairo_t *cr, gpointer user_data);

#endif
