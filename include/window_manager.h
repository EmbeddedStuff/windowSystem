/* 
 * File:   window_manager.h
 * Author: eLimones <limonesu.me@gmail.com>
 *
 * Created on September 12, 2015, 1:38 AM
 */

#ifndef WINDOW_MANAGER_H
#define	WINDOW_MANAGER_H

#ifdef	__cplusplus
extern "C" {
#endif

	#define WINDOW_EVENT_ON_CREATE 0
	#define WINDOW_EVENT_ON_EXIT 1

	/**
	 * 
	 */
	typedef struct{
		void (*redraw)(void);
		void (*event_handler)(int event);
	} window_t;
	
	/**
	 * 
     * @param newWindow
     */
	void window_init(window_t* newWindow);

	/**
	 *
	 */
	void window_delete(void);
	
	/**
	 * 
     * @return 
     */
	window_t* window_getCurrentWindow(void);
	
	/**
	 * 
     * @param nextWindow
     */
	void window_chageWindow(window_t* nextWindow);

	/**
	 *
	 * @param event
	 */
	void window_postEvent(int event);
	
#ifdef	__cplusplus
}
#endif

#endif	/* WINDOW_MANAGER_H */

