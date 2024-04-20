#include "queue.h"
#include "assert.h"

static func_ptr_t queue[QUEUE_MAX_LENGTH];
static func_ptr_t *head = queue;
static func_ptr_t *tail = queue;
static int queue_length = 0;

bool queue_empty() {
	return queue_length == 0;
}

bool queue_full() {
	return queue_length == QUEUE_MAX_LENGTH - 1;
}

void enqueue(func_ptr_t ptr) {
	ASSERT(!queue_full())

	*head = ptr;

	if (head == queue + QUEUE_MAX_LENGTH - 1) {
		head = queue;
	} else {
		head++;
	}
	queue_length++;
}

func_ptr_t dequeue() {
	ASSERT(!queue_empty())

	func_ptr_t ptr = *tail;

	if (tail == queue + QUEUE_MAX_LENGTH - 1) {
		tail = queue;
	} else {
		tail++;
	}
	queue_length--;

	return ptr;
}
