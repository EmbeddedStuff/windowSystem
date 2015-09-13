#include "window_manager.h"
#include "stdlib.h"

static window_t* current_window = NULL;

void window_init(window_t* newWindow){
	window_delete();
	if(newWindow != NULL){
		current_window = newWindow;
		current_window->event_handler(WINDOW_EVENT_ON_CREATE);
		current_window->redraw();
	}
}

void window_delete(void){
	current_window = NULL;
}

window_t* window_getCurrentWindow(void){
	return current_window;
}

void window_changeWindow(window_t* nextWindow){
	current_window = nextWindow;
}

void window_postEvent(int event){
	//get lock
	if(current_window != NULL){
		window_t* initialWindow = current_window;
		current_window->event_handler(event);
		if(initialWindow != current_window){
			initialWindow->event_handler(WINDOW_EVENT_ON_EXIT);
			current_window->event_handler(WINDOW_EVENT_ON_CREATE);
			current_window->redraw();
		}
	}
	//release lock
}

