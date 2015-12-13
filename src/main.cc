/**
 * @mainpage Genetic Circuits
 *
 * The main objective is to find the optimal combinational circuit given n inputs and the desired output. <br/>
 * To do so, I decided to use a Genetic Algorithm.	
 * 
 * Logical Steps:<br />
 * 	Firstly, I generate a circuit which every output is taken from first input. Then I create many "fake" gates
 * 	as much the number of input. The ::gate vector contains a vector of nodes, every node is a logic binary gate 
 * 	with has a type, and the reference to the gates that's connected to. Then I modifiy randomly the actual best
 *  solution to find a better one.
 * 
 * Data structure:
 * - std::deque<bool> input
 *  	+ used to generate all possible inputs
 * - std::vector< std::vector<bool> > output
 * 	+ it contains the desired outputs
 * - std::vector<size_t> root 
 * 	+ it contains the index of the gates which will be taken to get the desired output
 * - std::vector<node> gate 
 * 	+ Contains all the circuit information
 * 
 * @author Eduard Rubio Cholbi
 */

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
#include "debug.h"
#include "utility.h"
#include "mutation.h"
#include "structs.h"
#include "draw.h"
#include "GUI.h"

#ifdef DEBUG_MODE
	unsigned int MASK = 3;
	#define DBG(A, B) {if ((A) & MASK) {B; } }
#else
	#define DBG(A, B)
#endif

#define D1(a) DBG(1, a)
#define D2(a) DBG(2, a)

int main(int argc, char *argv[]){

	gtk_init (&argc, &argv);
	srand(time(NULL));
	
	Params * params = new Params;
	bool * end = new bool;
	*end = false;
	bool * pause = new bool;
	*pause = false;
	
	GtkWidget * status_bar;
	initGUI(params,status_bar,end,pause);
	
	params->input_lenght = 0;
	params->generation = 0;
	params->best_fitness = 0;
	unsigned int actual_fitness = 0;
	char status_bar_string[1000];
	
	while(true){
		if(params->input_lenght > 0 && !(*pause)){
			evolve(params->gate,params->root,params->input_lenght,params->output);
			actual_fitness = fitness(params->gate,params->root,params->input_lenght,params->output);
			if(params->best_fitness < actual_fitness){
				params->best_fitness = actual_fitness;
				sprintf(status_bar_string,
					"Generation: %u Best fitness: %u %lu%%",
					params->generation,
					params->best_fitness,
					1+100*params->best_fitness/(params->output.size()*(1<<params->input_lenght)*100));
				gtk_label_set_text(GTK_LABEL(status_bar),status_bar_string);
			}
			params->generation++;
		}
		if(*end)
			return 0;
		while(gtk_events_pending())
			gtk_main_iteration();
	}
}
