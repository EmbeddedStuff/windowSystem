/*
 * File:
 */

#include <stdio.h>
#include <stdlib.h>
#include <CUnit/Basic.h>
#include "window_manager.h"
/*
 * CUnit Test Suite
 */

int init_suite(){
	return 0;
}

int clean_suite(){
	return 0;
}

#define WINDOW_EVENT_BUTTON_A 2
#define WINDOW_EVENT_BUTTON_B 3
#define WINDOW_EVENT_BUTTON_C 4

void redraw1(void);
void redraw2(void);
void redraw3(void);

void eventHandler1(int event);
void eventHandler2(int event);
void eventHandler3(int event);


window_t window1 = {redraw1, eventHandler1};
window_t window2 = {redraw2, eventHandler2};
window_t window3 = {redraw3, eventHandler3};

void test_func1(){
	window_init(&window1);
	CU_ASSERT(window_getCurrentWindow() == &window1);

	window_postEvent(WINDOW_EVENT_BUTTON_A);
	CU_ASSERT(window_getCurrentWindow() == &window1);

	window_postEvent(WINDOW_EVENT_BUTTON_B);
	CU_ASSERT(window_getCurrentWindow() == &window2);

	window_postEvent(WINDOW_EVENT_BUTTON_B);
	CU_ASSERT(window_getCurrentWindow() == &window3);

	window_postEvent(WINDOW_EVENT_BUTTON_B);
	CU_ASSERT(window_getCurrentWindow() == &window3);

	window_postEvent(WINDOW_EVENT_BUTTON_A);
	CU_ASSERT(window_getCurrentWindow() == &window2);

	window_postEvent(WINDOW_EVENT_BUTTON_A);
	CU_ASSERT(window_getCurrentWindow() == &window1);

	window_postEvent(WINDOW_EVENT_BUTTON_A);
	CU_ASSERT(window_getCurrentWindow() == &window1);
}

void eventHandler1(int event){
	if(event == WINDOW_EVENT_ON_CREATE){
		printf("Initializing window 1\n");
	}
	else if(event == WINDOW_EVENT_ON_EXIT){
		printf("Exiting window 1\n");
	}
	else if(event == WINDOW_EVENT_BUTTON_A){
	}
	else if(event == WINDOW_EVENT_BUTTON_B){
		window_changeWindow(&window2);
	}
}

void eventHandler2(int event){
	if(event == WINDOW_EVENT_ON_CREATE){
		printf("Initializing window 2\n");
	}
	else if(event == WINDOW_EVENT_ON_EXIT){
		printf("Exiting window 2\n");
	}
	else if(event == WINDOW_EVENT_BUTTON_A){
		window_changeWindow(&window1);
	}
	else if(event == WINDOW_EVENT_BUTTON_B){
		window_changeWindow(&window3);
	}
}

void eventHandler3(int event){
	if(event == WINDOW_EVENT_ON_CREATE){
		printf("Initializing window 3\n");
	}
	else if(event == WINDOW_EVENT_ON_EXIT){
		printf("Exiting window 3\n");
	}
	else if(event == WINDOW_EVENT_BUTTON_A){
		window_changeWindow(&window2);
	}
	else if(event == WINDOW_EVENT_BUTTON_B){
	}
}

void redraw1(void){
	printf("Drawing window 1\n");
}
void redraw2(void){
	printf("Drawing window 2\n");
}
void redraw3(void){
	printf("Drawing window 3\n");
}

int main() {
	CU_TestInfo test_array[] = {
		{"testname1", test_func1},
		CU_TEST_INFO_NULL};

	CU_SuiteInfo suite_array[] = {
		{"window_manager_test", init_suite, clean_suite, test_array},
		CU_SUITE_INFO_NULL};

	/* Initialize the CUnit test registry */
	if (CUE_SUCCESS != CU_initialize_registry())
		return CU_get_error();

	/* Add a suite to the registry */
	if(CUE_SUCCESS != CU_register_suites(suite_array)){
		CU_cleanup_registry();
		return CU_get_error();
	}

	/* Run all tests using the CUnit Basic interface */
	CU_basic_set_mode(CU_BRM_SILENT);
	CU_basic_run_tests();
	CU_cleanup_registry();
	return CU_get_error();
}
