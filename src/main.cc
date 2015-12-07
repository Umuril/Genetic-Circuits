#include <cairo.h>
#include <gtk/gtk.h>
#include <chrono>
#include <deque>
#include <iostream>
#include <set>
#include <thread>
#include <vector>
#include "thread.h"
#include "debug.h"
#include "utility.h"
#include "mutation.h"
#include "init.h"
#include "structs.h"

struct DataRef {
	std::vector<node> gate;
	std::vector<size_t> root;
	size_t input_lenght;
};

void drawGate(cairo_t *cr, int gate, double x, double y){
	if(gate < 0 || gate > 7)
		return;
	if((gate >> 1) % 2){
		cairo_move_to(cr,x,y+10);
		cairo_line_to(cr,x+12,y+10);
		cairo_move_to(cr,x,y+20);
		cairo_line_to(cr,x+12,y+20);
		cairo_move_to(cr,x+10,y);
		cairo_curve_to(cr,x+10,y,x+15,y+15,x+10,y+30);
	}
	if((gate >> 1) % 2 == 0 && gate > 0){
		cairo_move_to(cr,x,y+10);
		cairo_line_to(cr,x+10,y+10);
		cairo_move_to(cr,x,y+20);
		cairo_line_to(cr,x+10,y+20);
		cairo_move_to(cr,x+10,y);
		cairo_line_to(cr,x+10,y+30);
	}
	if(gate % 4 == 3){
		cairo_move_to(cr,x+5,y);
		cairo_curve_to(cr,x+5,y,x+10,y+15,x+5,y+30);
	}
	if(gate == 4){
		cairo_move_to(cr,x+10,y);
		cairo_line_to(cr,x+35,y+15);
		cairo_move_to(cr,x+10,y+30);
		cairo_line_to(cr,x+35,y+15);
	}
	if(gate % 4 == 1){
		cairo_move_to(cr,x+10,y+30);
		cairo_line_to(cr,x+20,y+30);
		cairo_move_to(cr,x+10,y);
		cairo_line_to(cr,x+20,y);
		cairo_arc(cr,x+20,y+15,15,3*G_PI/2,G_PI/2);
	}
	if((gate >> 1) % 2){
		cairo_move_to(cr,x+10,y);
		cairo_curve_to(cr,x+10,y,x+25,y,x+35,y+15);
		cairo_move_to(cr,x+10,y+30);
		cairo_curve_to(cr,x+10,y+30,x+25,y+30,x+35,y+15);
	}
	if(gate < 4){
		cairo_move_to(cr,x+35,y+15);
		cairo_line_to(cr,x+50,y+15);
	} else {
		cairo_move_to(cr,x+35,y+15);
		cairo_arc(cr,x+40,y+15,5,G_PI,3*G_PI);
		cairo_move_to(cr,x+45,y+15);
		cairo_line_to(cr,x+50,y+15);
	}
	return;
}

void connectGate(cairo_t *cr, double x1, double y1, double x2, double y2,bool first, double sizex1, double sizex2, double maxh){
	if(x2 <= x1)
		return;
	int xdist = (x2 - x1) / 90;
	if( xdist == 1 ){
		//std::cout << "x1: " << x1+50 << " Mx: " << x1+60+((x1-10)/40)*5/sizex1 << " x2: " << x2 << std::endl;
		//std::cout << "y1: " << y1+15 << " y2: " << y2+(first?10:20) << std::endl;
		cairo_move_to(cr,x1+50,y1+15);
		cairo_line_to(cr,x1+50+(((y1-10)/40)*10/sizex1)+5,y1+15);
		cairo_line_to(cr,x1+50+(((y1-10)/40)*10/sizex1)+5,y2+(first?10:20));
		cairo_line_to(cr,x2,y2+(first?10:20));
	} else {
		cairo_move_to(cr,x1+50,y1+15);
		cairo_line_to(cr,x1+50+(((y1-10)/40)*10/sizex1)+5,y1+15);
		cairo_line_to(cr,x1+50+(((y1-10)/40)*10/sizex1)+5,10+maxh*40+((y1-10)/40)*35/sizex1);
		cairo_line_to(cr,x2-20+(((y2-10)/40)*10/sizex2)+(first?10:0),10+maxh*40+((y1-10)/40)*35/sizex1);
		cairo_line_to(cr,x2-20+(((y2-10)/40)*10/sizex2)+(first?10:0),y2+(first?10:20));
		cairo_line_to(cr,x2,y2+(first?10:20));
		/*cairo_move_to(cr,x1+50,y1+15);	// Al contrario?
		cairo_line_to(cr,x1+60-(((y1-10)/40)*10/sizex1)+5,y1+15);
		cairo_line_to(cr,x1+60-(((y1-10)/40)*10/sizex1)+5,10+maxh*40+((y1-10)/40)*5/sizex1);
		cairo_line_to(cr,x2-20+(((y2-10)/40)*10/sizex2)+(first?0:10),10+maxh*40+((y1-10)/40)*5/sizex1);
		cairo_line_to(cr,x2-20+(((y2-10)/40)*10/sizex2)+(first?0:10),y2+(first?10:20));
		cairo_line_to(cr,x2,y2+(first?10:20));*/
	}
}

gboolean draw(GtkWidget *widget, cairo_t *cr, gpointer user_data){
	cairo_set_source_rgb(cr, 0, 0, 0);
	cairo_set_line_width(cr, 0.5);
	
	DataRef * dataref = (DataRef *)user_data;
	
	std::vector<unsigned int> levels(dataref->gate.size(),0);
	for(size_t i = dataref->input_lenght; i < levels.size(); i++){
		levels[i] = std::max(	levels[dataref->gate[i].a],levels[dataref->gate[i].b])+1;
	}
	int maxlevel = *(std::max_element(levels.begin(),levels.end()));
	
	std::vector< std::vector<node> > reordered_gate(maxlevel+1,std::vector<node>(0));
	std::vector<double> posX(levels.size()),posY(levels.size()); 
	
	
	
	
	
	
	for(size_t i = 0; i < levels.size(); i++){
		reordered_gate[levels[i]].emplace_back(dataref->gate[i]);
		posX[i] = 10+90*levels[i];
		posY[i] = 10+40*(reordered_gate[levels[i]].size()-1);
		drawGate(cr,dataref->gate[i].oper,posX[i],posY[i]);
	}
	
	unsigned int maxh;
	//std::cout << "LOOOOOP!" << std::endl;
	for(size_t i = dataref->input_lenght; i < levels.size(); i++){
		maxh = 0;
		for(size_t j = levels[dataref->gate[i].a]+1; j < levels[i]; j++)
			if(reordered_gate[j].size() > maxh)
				maxh = reordered_gate[j].size();
		/*std::cout << "x1: " << posX[dataref->gate[i].a] << std::endl;
		std::cout << "y1: " << posY[dataref->gate[i].a] << std::endl;
		std::cout << "x2: " << posX[i] << std::endl;
		std::cout << "y2: " << posY[i] << std::endl;
		std::cout << "first: " << true << std::endl;
		std::cout << "sizex1: " << reordered_gate[levels[dataref->gate[i].a]].size() << std::endl;
		std::cout << "sizex2: " << reordered_gate[levels[i]].size() << std::endl;
		std::cout << "maxh: " << maxh << std::endl;
		*/
		connectGate(cr,posX[dataref->gate[i].a],posY[dataref->gate[i].a],
						posX[i],posY[i],true,
						reordered_gate[levels[dataref->gate[i].a]].size(),
						reordered_gate[levels[i]].size(),maxh);
		maxh = 0;
		for(size_t j = levels[dataref->gate[i].b]+1; j < levels[i]; j++)
			if(reordered_gate[j].size() > maxh)
				maxh = reordered_gate[j].size();
				
		connectGate(cr,posX[dataref->gate[i].b],posY[dataref->gate[i].b],
						posX[i],posY[i],false,
						reordered_gate[levels[dataref->gate[i].b]].size(),
						reordered_gate[levels[i]].size(),maxh);
	}
	
	for(size_t i = 0; i < dataref->root.size(); i++){
		maxh = 0;
		for(size_t j = levels[dataref->root[i]]+1; j < reordered_gate.size(); j++)
			if(reordered_gate[j].size() > maxh)
				maxh = reordered_gate[j].size();
				
		connectGate(cr,posX[dataref->root[i]],posY[dataref->root[i]],
						10+reordered_gate.size()*90,10+40*i,true,
						reordered_gate[levels[dataref->root[i]]].size(),
						dataref->root.size(),maxh);
	}
	/*
	drawGate(cr,0,10,10);	//
	drawGate(cr,1,100,10);	// AND
	drawGate(cr,2,190,10);	// OR
	drawGate(cr,3,280,10);	// XOR
	drawGate(cr,4,10,50);	// NOT
	drawGate(cr,5,100,50);	// NAND
	drawGate(cr,6,190,50);	// NOR
	drawGate(cr,7,280,50);	// XNOR
	drawGate(cr,7,100,90);	// XNOR
	drawGate(cr,7,100,130);	// XNOR		
	
	connectGate(cr,10,10,190,10,true,2,2,4);
	connectGate(cr,10,50,190,10,false,2,2,4);
	connectGate(cr,100,50,280,10,true,4,2,2);
	connectGate(cr,100,130,280,10,false,4,2,2);
	*/
	cairo_stroke(cr);
	return TRUE;
}

int main(int argc, char *argv[]){

    GtkWidget * window;
    GtkWidget * darea;
    
    gtk_init (&argc, &argv);
    
    darea = gtk_drawing_area_new();
    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_container_add(GTK_CONTAINER(window), darea);
DataRef * dataref = new DataRef;
	g_signal_connect(darea, "draw", G_CALLBACK(draw), dataref); 
	g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
      
	
	
	
	srand(time(NULL));
	//size_t input_lenght; ///< we just need the lenght of the deque in order to generate it every time.
	std::vector< std::vector<bool> > output; 
	if(!read_output_from_file(output,dataref->input_lenght))
		return 1;
	
	std::vector<std::thread> threads;
	
	unsigned int best_fitness = 0;
	for(size_t i = 0; i < output.size(); i++)
		dataref->root.emplace_back(0);
	//std::vector<size_t> root(output.size(),0);
	//std::vector<node> gate;
	
	for(size_t i = 0; i < dataref->input_lenght; i++)
		dataref->gate.emplace_back(node{0,i,0});
	for(size_t i = 0; i < 80; i++)
		tryAdd(dataref->gate,dataref->input_lenght);
		//dataref->gate.emplace_back(node{1,0,0});
	//printData(dataref->gate,dataref->root,dataref->input_lenght,output);
	unsigned int generation = 0;
	/*
	dataref->gate.emplace_back(node{1,0,1});
	dataref->gate.emplace_back(node{2,1,2});	
	dataref->gate.emplace_back(node{3,3,4});
	dataref->gate.emplace_back(node{7,3,5});
*/
	do{
		thread_work(dataref->gate,dataref->root,dataref->input_lenght,output);
		//if(generation % 1000 == 0)
			//std::cout << "Generation: " << generation << " Best fitness: " << best_fitness/100+1 << std::endl;
		if(fitness(dataref->gate,dataref->root,dataref->input_lenght,output) > best_fitness){
			best_fitness = fitness(dataref->gate,dataref->root,dataref->input_lenght,output);
			system("clear");
			printData(dataref->gate,dataref->root,dataref->input_lenght,output);
			std::cout << "Generation: " << generation << " Best fitness: " << best_fitness << std::endl;
			//printGate(dataref->gate);
			//gtk_widget_queue_draw(darea);
		}
		//printGate(dataref->gate);
		generation++;

	}while(generation < 500000 && best_fitness < output.size()*(1<<dataref->input_lenght)*100-100);
	
	
	
	
	
	
	
	gtk_widget_queue_draw(darea);
	
	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
	gtk_window_set_default_size(GTK_WINDOW(window), 800, 600);
	gtk_window_maximize(GTK_WINDOW(window));
	
    gtk_widget_show_all(window);

    gtk_main ();
    
    return 0;
}

