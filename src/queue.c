static const uint8_t BUFFER_SIZE = 128;

static uint8_t buffer[BUFFER_SIZE];

// Inicializo tail y head al principio del buffer
static uint8_t *tail = buffer;
static uint8_t *head = buffer;

bool empty() {
	return tail == head;
}

bool full() {
	return tail + 1 == head;
}

void enqueue(uint8_t data) {
	if (full()) {
		// Advertencia de cola llena a traves de UART
		return;
	}
	*tail = data;
	tail++;

	if (tail == buffer + BUFFER_SIZE) {
		tail ==
	}
}

uint8_t dequeue() {
	if (empty()) {
		// Advertencia de cola vacia a traves de UART
		return;
	}

}
