#ifndef GUI_H
#define GUI_H

#include <gtk/gtk.h>
#include <iostream>
#include <vector>
#include <assert.h>
#include "structs.h"
#include "utility.h"
#include "debug.h"
#include "draw.h"

void initGUI(Params * & params, GtkWidget * & status_bar,bool * & end, bool * & pause);
void main_quit(GtkWidget *widget, GdkEvent *event, gpointer data);
void function_open(GtkWidget * widget, gpointer data);
void function_save(GtkWidget * widget, gpointer data);
void function_quit(GtkWidget * widget, gpointer data);
void function_play(GtkWidget * widget, gpointer data);
void function_pause(GtkWidget * widget, gpointer data);
void function_stop(GtkWidget * widget, gpointer data);

#endif
