/*
 * File:   mylib_test.c
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

#define F_NONE 0
#define F_EVENT_HANDLER 1
#define F_REDRAW 2

int calledFirst = 0;

void redraw(void){
	if(calledFirst == F_NONE)
		calledFirst = F_REDRAW;
}

void event_handler(int event){
	if(calledFirst == F_NONE)
		calledFirst = F_EVENT_HANDLER;
}

void test_func1() {
	window_t myWindow = {redraw, event_handler};

	window_delete();
	CU_ASSERT( window_getCurrentWindow() == NULL);

	window_init(&myWindow);
	CU_ASSERT( window_getCurrentWindow() == &myWindow);

	CU_ASSERT(calledFirst == F_EVENT_HANDLER);
}

int main() {
	CU_TestInfo test_array[] = {
		{"that windows can be added", test_func1},
		CU_TEST_INFO_NULL};

	CU_SuiteInfo suite_array[] = {
		{"window_manager_test", init_suite, clean_suite, 
			test_array},
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
	CU_basic_set_mode(CU_BRM_VERBOSE);
	CU_basic_run_tests();
	CU_cleanup_registry();
	return CU_get_error();
}
