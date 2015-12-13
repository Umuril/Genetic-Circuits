#include "GUI.h"

/** @page GUI
 * This page contains all GUI setup
 *  
*/

/** Function that handles GUI
 *
 * @param[out] params pointer to all circuit data
 * @param[out] status_bar pointer to the status bar
 * @param[out] end boolean that ends program when true
 * @param[out] pause boolean that pauses generation evolution
 */
void initGUI(Params * & params, GtkWidget * & status_bar, bool * & end, bool * & pause){
	assert(params!=NULL);
	assert(status_bar!=NULL);
	assert(end!=NULL);
	assert(pause!=NULL);
	GtkWidget * window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	GtkWidget * drawing_area = gtk_drawing_area_new();
	GtkWidget * vertical_container = gtk_box_new(GTK_ORIENTATION_VERTICAL,0);
	status_bar = gtk_label_new("");
	gtk_label_set_xalign(GTK_LABEL(status_bar),0);


	GtkWidget * menubar = gtk_menu_bar_new();

	GtkWidget * file = gtk_menu_item_new_with_label("File");
	gtk_menu_shell_append(GTK_MENU_SHELL(menubar), file);

	GtkWidget * filemenu = gtk_menu_new();
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(file), filemenu);

		GtkWidget * menu_open = gtk_menu_item_new_with_label("Open");
		gtk_menu_shell_append(GTK_MENU_SHELL(filemenu), menu_open);
		g_signal_connect(G_OBJECT(menu_open), "activate", G_CALLBACK(function_open), params);
		GtkWidget * menu_save = gtk_menu_item_new_with_label("Save circuit");
		gtk_menu_shell_append(GTK_MENU_SHELL(filemenu), menu_save);
		g_signal_connect(G_OBJECT(menu_save), "activate", G_CALLBACK(function_save), params);
		GtkWidget * menu_quit = gtk_menu_item_new_with_label("Exit");
		gtk_menu_shell_append(GTK_MENU_SHELL(filemenu), menu_quit);
		g_signal_connect(G_OBJECT(menu_quit), "activate", G_CALLBACK(function_quit), end);


	GtkWidget * run = gtk_menu_item_new_with_label("Run");
	gtk_menu_shell_append(GTK_MENU_SHELL(menubar), run);

	GtkWidget * runmenu = gtk_menu_new();
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(run), runmenu);

		GtkWidget * menu_play = gtk_menu_item_new_with_label("Play");
		gtk_menu_shell_append(GTK_MENU_SHELL(runmenu), menu_play);
		g_signal_connect(G_OBJECT(menu_play), "activate", G_CALLBACK(function_play), pause);
		GtkWidget * menu_pause = gtk_menu_item_new_with_label("Pause");
		gtk_menu_shell_append(GTK_MENU_SHELL(runmenu), menu_pause);
		g_signal_connect(G_OBJECT(menu_pause), "activate", G_CALLBACK(function_pause), pause);
		GtkWidget * menu_restart = gtk_menu_item_new_with_label("Restart");
		gtk_menu_shell_append(GTK_MENU_SHELL(runmenu), menu_restart);
		g_signal_connect(G_OBJECT(menu_restart), "activate", G_CALLBACK(function_stop), params);




	gtk_box_pack_start(GTK_BOX(vertical_container),menubar,FALSE,TRUE,0);
	gtk_box_pack_start(GTK_BOX(vertical_container),drawing_area,TRUE,TRUE,0);
	gtk_box_pack_start(GTK_BOX(vertical_container),status_bar,FALSE,TRUE,0);
	gtk_container_add(GTK_CONTAINER(window), vertical_container);



	g_signal_connect(drawing_area, "draw", G_CALLBACK(draw), params);
	g_signal_connect(window, "delete-event", G_CALLBACK(main_quit), end);

	gtk_widget_queue_draw(drawing_area);

	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
	gtk_widget_set_size_request(window, 800, 600);
	gtk_window_maximize(GTK_WINDOW(window));

	gtk_widget_show_all(window);
}

/** Function to end program
 *
 * @param[out] widget widget that called this fuction
 * @param event required by specs
 * @param[out] data boolean that ends program when true
 */
void main_quit(GtkWidget *widget, GdkEvent *event, gpointer data){
	assert(data!=NULL);
	*((bool*)data) = true;
}

/** Function to load new circuit
 *
 * @param[out] widget widget that called this fuction
 * @param[out] data pointer to all circuit data
 */
void function_open(GtkWidget * widget, gpointer data){
	assert(data!=NULL);
	GtkWidget *dialog;
	gint res;
	dialog = gtk_file_chooser_dialog_new ("Open File",
				GTK_WINDOW(gtk_widget_get_toplevel(widget)),
				GTK_FILE_CHOOSER_ACTION_OPEN,
				("_Cancel"), GTK_RESPONSE_CANCEL,
				("_Open"), GTK_RESPONSE_ACCEPT,
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
		return;
	}
	std::vector<size_t> root;
	std::vector<node> gate;
	for(size_t i = 0; i < output.size(); i++)
		root.emplace_back(0);
	for(size_t i = 0; i < input_lenght; i++)
		gate.emplace_back(node{0,i,0});
	((Params*)data)->input_lenght = input_lenght;
	((Params*)data)->output = std::move(output);
	((Params*)data)->root = std::move(root); // Delete before
	((Params*)data)->gate = std::move(gate);
	((Params*)data)->best_fitness = 0;
	((Params*)data)->generation = 0;
}

/** Function to save circuit
 *
 * @param[out] widget widget that called this fuction
 * @param[out] data pointer to all circuit data
 */
void function_save(GtkWidget * widget, gpointer data){
	assert(data!=NULL);
	GtkWidget *dialog;
	GtkFileChooser *chooser;
	gint res;

	dialog = gtk_file_chooser_dialog_new ("Save File",
				GTK_WINDOW(gtk_widget_get_toplevel(widget)),
				GTK_FILE_CHOOSER_ACTION_SAVE,
				("_Cancel"), GTK_RESPONSE_CANCEL,
				("_Save"), GTK_RESPONSE_ACCEPT,
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
		printGate(fileout,((Params*)data)->gate);
		printRoot(fileout,((Params*)data)->root);
		g_free (filename);
	  }

	gtk_widget_destroy (dialog);
	return;
}

/** Function to end program
 *
 * @param[out] widget widget that called this fuction
 * @param[out] data boolean that ends program when true
 */
void function_quit(GtkWidget * widget, gpointer data){
	assert(data!=NULL);
	*((bool*)data) = true;
}

/** Function that resumes program
 *
 * @param[out] widget widget that called this fuction
 * @param[out] data boolean that pauses program when true
 */
void function_play(GtkWidget * widget, gpointer data){
	assert(data!=NULL);
	*((bool*)data) = false;
}

/** Function that pauses program
 *
 * @param[out] widget widget that called this fuction
 * @param[out] data boolean that pauses program when true
 */
void function_pause(GtkWidget * widget, gpointer data){
	assert(data!=NULL);
	*((bool*)data) = true;
}

/** Function that restart program with same input
 *
 * @param[out] widget widget that called this fuction
 * @param[out] data pointer to all circuit data
 */
void function_stop(GtkWidget * widget, gpointer data){
	assert(data!=NULL);
	std::vector<size_t> root;
	std::vector<node> gate;
	for(size_t i = 0; i < ((Params*)data)->output.size(); i++)
		root.emplace_back(0);
	for(size_t i = 0; i < ((Params*)data)->input_lenght; i++)
		gate.emplace_back(node{0,i,0});
	((Params*)data)->root = std::move(root); // Delete before
	((Params*)data)->gate = std::move(gate);
	((Params*)data)->best_fitness = 0;
	((Params*)data)->generation = 0;
}
