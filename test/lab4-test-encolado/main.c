#include <msp430.h> 

#include "assert.h"
#include "queue.h"

static int test_num = 0;

void dummy_func() {}
void aumentar_num() {
	test_num++;
}
void mult2_num() {
	test_num = test_num*2;
}

void test_cola_llena() {
	int i;
	for (i = 0; i < QUEUE_MAX_LENGTH; i++) {
		enqueue(dummy_func);
	}
}

void test_cola_vacia() {
	dequeue();
}

void test_encolar() {
	enqueue(aumentar_num);
	enqueue(aumentar_num);
	enqueue(mult2_num);

	func_ptr_t f1 = dequeue();
	func_ptr_t f2 = dequeue();
	func_ptr_t f3 = dequeue();

	f1();
	f2();
	f3();

	ASSERT(test_num == 4);
}

int main(void) {
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer

	// test_cola_vacia();
	// test_cola_llena();
	test_encolar();

	return 0;
}
