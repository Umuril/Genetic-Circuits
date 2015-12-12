#include <cairo.h>
#include <gtk/gtk.h>
#include <chrono>
#include <deque>
#include <iostream>
#include <set>
#include <sstream>
#include <thread>
#include <vector>
#include <string.h>
#include "thread.h"
#include "debug.h"
#include "utility.h"
#include "mutation.h"
#include "init.h"
#include "structs.h"
#include "draw.h"

void main_quit(GtkWidget *widget, GdkEvent *event, gpointer callback_data){
	*((bool*)callback_data) = true;
}

void fop(GtkWidget * widget, gpointer data){
	GtkWidget *dialog;
	gint res;
	dialog = gtk_file_chooser_dialog_new ("Open File", GTK_WINDOW(gtk_widget_get_toplevel(widget)), GTK_FILE_CHOOSER_ACTION_OPEN,
                                      ("_Cancel"),
                                      GTK_RESPONSE_CANCEL,
                                      ("_Open"),
                                      GTK_RESPONSE_ACCEPT,
                                      NULL);

	res = gtk_dialog_run (GTK_DIALOG (dialog));
	
	if (res != GTK_RESPONSE_ACCEPT)
	    return;
	char *filename;   
	GtkFileChooser *chooser = GTK_FILE_CHOOSER (dialog);
	filename = gtk_file_chooser_get_filename (chooser);
	

	gtk_widget_destroy (dialog);
	std::vector< std::vector<bool> > output;
	size_t input_lenght;
	if(!read_output_from_file(filename,output,input_lenght)){
		std::cout << "OUT" << std::endl;
		return;
	}
	std::vector<size_t> root;
	std::vector<node> gate;
	for(size_t i = 0; i < output.size(); i++)
		root.emplace_back(0);
	for(size_t i = 0; i < input_lenght; i++)
		gate.emplace_back(node{0,i,0});
	((DataRef*)data)->input_lenght = input_lenght;
	((DataRef*)data)->output = std::move(output);
	((DataRef*)data)->root = std::move(root);
	((DataRef*)data)->gate = std::move(gate);
	((DataRef*)data)->best_fitness = 0;
	((DataRef*)data)->generation = 0;
}
void fsave(GtkWidget * widget, gpointer data){
	GtkWidget *dialog;
	GtkFileChooser *chooser;
	gint res;

	dialog = gtk_file_chooser_dialog_new ("Save File",
		                                  GTK_WINDOW(gtk_widget_get_toplevel(widget)),
		                                  GTK_FILE_CHOOSER_ACTION_SAVE,
		                                  ("_Cancel"),
		                                  GTK_RESPONSE_CANCEL,
		                                  ("_Save"),
		                                  GTK_RESPONSE_ACCEPT,
		                                  NULL);
	chooser = GTK_FILE_CHOOSER (dialog);

	gtk_file_chooser_set_do_overwrite_confirmation (chooser, TRUE);

	gtk_file_chooser_set_current_name (chooser,
		                                 ("Untitled document"));

	res = gtk_dialog_run (GTK_DIALOG (dialog));
	if (res == GTK_RESPONSE_ACCEPT){
		char *filename;

		filename = gtk_file_chooser_get_filename (chooser);
		std::ofstream fileout(filename);
		printGate(fileout,((DataRef*)data)->gate);
		printRoot(fileout,((DataRef*)data)->root);
		g_free (filename);
	  }

	gtk_widget_destroy (dialog);
	return;
}
void fquit(GtkWidget * widget, gpointer data){
	*((bool*)data) = true;
}
void fplay(GtkWidget * widget, gpointer data){
	*((bool*)data) = false;
}
void fpause(GtkWidget * widget, gpointer data){
	*((bool*)data) = true;
}
void fstop(GtkWidget * widget, gpointer data){
	std::vector<size_t> root;
	std::vector<node> gate;
	for(size_t i = 0; i < ((DataRef*)data)->output.size(); i++)
		root.emplace_back(0);
	for(size_t i = 0; i < ((DataRef*)data)->input_lenght; i++)
		gate.emplace_back(node{0,i,0});
	((DataRef*)data)->root = std::move(root);
	((DataRef*)data)->gate = std::move(gate);
	((DataRef*)data)->best_fitness = 0;
	((DataRef*)data)->generation = 0;
}

int main(int argc, char *argv[]){

	gtk_init (&argc, &argv);
	srand(time(NULL));
	
	DataRef * dataref = new DataRef;
	bool * end = new bool;
	*end = false;
	bool * pause = new bool;
	*pause = false;
	
    GtkWidget * window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    GtkWidget * darea = gtk_drawing_area_new();
	GtkWidget * box = gtk_box_new(GTK_ORIENTATION_VERTICAL,0);
	GtkWidget * label = gtk_label_new("");
	gtk_label_set_xalign(GTK_LABEL(label),0);
	
	
	GtkWidget * menubar = gtk_menu_bar_new();

    GtkWidget * file = gtk_menu_item_new_with_label("File");
    gtk_menu_shell_append(GTK_MENU_SHELL(menubar), file);
    
    GtkWidget * filemenu = gtk_menu_new();
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(file), filemenu);
    
       	GtkWidget * open = gtk_menu_item_new_with_label("Open");
    	gtk_menu_shell_append(GTK_MENU_SHELL(filemenu), open);
		g_signal_connect(G_OBJECT(open), "activate", G_CALLBACK(fop), dataref);
    	GtkWidget * save = gtk_menu_item_new_with_label("Save circuit");
    	gtk_menu_shell_append(GTK_MENU_SHELL(filemenu), save);
		g_signal_connect(G_OBJECT(save), "activate", G_CALLBACK(fsave), dataref);
    	GtkWidget * quit = gtk_menu_item_new_with_label("Exit");
		gtk_menu_shell_append(GTK_MENU_SHELL(filemenu), quit);
		g_signal_connect(G_OBJECT(quit), "activate", G_CALLBACK(fquit), end);
    
	
	GtkWidget * view = gtk_menu_item_new_with_label("Run");
    gtk_menu_shell_append(GTK_MENU_SHELL(menubar), view);
    
    GtkWidget * viewmenu = gtk_menu_new();
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(view), viewmenu);
    
       	GtkWidget * play = gtk_menu_item_new_with_label("Play");
    	gtk_menu_shell_append(GTK_MENU_SHELL(viewmenu), play);
    	g_signal_connect(G_OBJECT(play), "activate", G_CALLBACK(fplay), pause);
    	GtkWidget * bpause = gtk_menu_item_new_with_label("Pause");
		gtk_menu_shell_append(GTK_MENU_SHELL(viewmenu), bpause);
		g_signal_connect(G_OBJECT(bpause), "activate", G_CALLBACK(fpause), pause);
		GtkWidget * restart = gtk_menu_item_new_with_label("Restart");
		gtk_menu_shell_append(GTK_MENU_SHELL(viewmenu), restart);
		g_signal_connect(G_OBJECT(restart), "activate", G_CALLBACK(fstop), dataref);	
	
	
	
	
	gtk_box_pack_start(GTK_BOX(box),menubar,FALSE,TRUE,0);	
	gtk_box_pack_start(GTK_BOX(box),darea,TRUE,TRUE,0);
	gtk_box_pack_start(GTK_BOX(box),label,FALSE,TRUE,0);
    gtk_container_add(GTK_CONTAINER(window), box);
    
    
    
	g_signal_connect(darea, "draw", G_CALLBACK(draw), dataref);
	
	
	g_signal_connect(window, "delete-event", G_CALLBACK(main_quit), end);
	
	dataref->input_lenght = 0;
	
	dataref->generation = 0;
	unsigned int actual_fitness = 0;
	dataref->best_fitness = 0;
	char integer_string[1000];
	
	gtk_widget_queue_draw(darea);
	
	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
	gtk_widget_set_size_request(window, 800, 600);
	gtk_window_maximize(GTK_WINDOW(window));
	
    gtk_widget_show_all(window);
	
	while(true){
		if(dataref->input_lenght > 0 && !(*pause)){
			thread_work(dataref->gate,dataref->root,dataref->input_lenght,dataref->output);
			actual_fitness = fitness(dataref->gate,dataref->root,dataref->input_lenght,dataref->output);
			if(dataref->best_fitness < actual_fitness){
				dataref->best_fitness = actual_fitness;
				sprintf(integer_string, "Generation: %u Best fitness: %u %lu%%", dataref->generation, dataref->best_fitness,1+100*dataref->best_fitness/(dataref->output.size()*(1<<dataref->input_lenght)*100));
				gtk_label_set_text(GTK_LABEL(label),integer_string);
			}
			dataref->generation++;
		}
		if(*end)
			return 0;
		while(gtk_events_pending())
			gtk_main_iteration();
	}
}
