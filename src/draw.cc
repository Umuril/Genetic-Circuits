#include "draw.h"
#include <assert.h>
/** @page draw
 * This page contains all drawing functions.
 *  
*/

/** Main drawing function of the drawing area
 *
 * @param[out] widget widget that called the draw fuction
 * @param[out] cr cairo to draw to
 * @param[in] user_data pointer pointer to all data needed by function
 * @return whether the signal emission should be aborted
 */
gboolean draw(GtkWidget * widget, cairo_t * cr, gpointer user_data){
	assert( user_data != NULL);
	cairo_scale(cr,1,1);
	cairo_set_source_rgb(cr, 0, 0, 0);
	cairo_set_line_width(cr, 0.5);
	
	Params * dataref = (Params *)user_data;
	if(dataref->input_lenght == 0)
		return TRUE;
	
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

	for(size_t i = dataref->input_lenght; i < levels.size(); i++){
		maxh = 0;
		for(size_t j = levels[dataref->gate[i].a]+1; j < levels[i]; j++)
			if(reordered_gate[j].size() > maxh)
				maxh = reordered_gate[j].size();

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
	
	cairo_stroke(cr);
	gtk_widget_queue_draw(widget);
	return TRUE;
}

/** Function that draws one logic gate
 *
 * @param[out] cr cairo to draw to
 * @param[in] gate type of logic gate to draw
 * @param[in] x coordinate x where to start to draw the gate
 * @param[in] y coordinate y where to start to draw the gate
 */
void drawGate(cairo_t *cr, const int gate, const double x,
					const double y){
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

/** Function that connects two logic gates
 *
 * @param[out] cr cairo to draw to
 * @param[in] x1 coordinate x of the output logic gate
 * @param[in] y1 coordinate y of the output logic gate
 * @param[in] x2 coordinate x of the input logic gate
 * @param[in] y2 coordinate y of the input logic gate
 * @param[in] first true if it's the first input of the gate
 * @param[in] sizex1 number of gates in the same line of output gate
 * @param[in] sizex2 number of gates in the same line of input gate
 * @param[in] maxh max number of gates between input and output gate
 */
void connectGate(cairo_t *cr, const double x1, const double y1,
					const double x2, const double y2, const bool first,
					const double sizex1, const double sizex2,
					const double maxh){
	if(x2 <= x1)
		return;
	int xdist = (x2 - x1) / 90;
	if( xdist == 1 ){
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
	}
}
