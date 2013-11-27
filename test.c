void printInt(int i);
void printString(string s);
int readInt();
void* sbrk(int size);

int fib(int i) {
	if(i < 1) {
		return 0;
	} else if(i < 2) {
		return 1;
	}
	return fib(i-1) + fib(i-2);
}

int fib_iterative(int i) {
	int a = 0;
	int b = 1;
	if(i < 1) {
		return 0;
	} else {
		int j;
		for(j = 1; j < i; j++) {
			int c = a + b;
			a = b;
			b = c;
		}
		return b;
	}
}

int** makeMultiplicationTable(int size) {
	int** table = sbrk(sizeof(int*) * size);
	int i;
	for(i = 0; i < size; i++) {
		table[i] = sbrk(sizeof(int) * size);
		int j;
		for(j = 0; j < size; j++) {
			table[i][j] = (i + 1) * (j + 1);
		}
	}
	return table;
}

string s = "hello\nhello\n";

void askNums() {
	printString("Enter the number of integers you want to read in.\n");
	int num = readInt();
	int* myNums = sbrk(sizeof(int) * num);
	printString("Enter your numbers now.\n");
	int i;
	for(i = 0; i < num; i++) {
		*(myNums + i) = readInt();
	}
	int sum = 0;
	int product = 1;
	for(i = 0; i < num; i++) {
		int j = myNums[i];
		if(j == 0) {
			continue;
		}
		sum += myNums[i];
		product *= myNums[i];
	}
	printString("The sum of these numbers is ");
	printInt(sum);
	printString(".\n");
	
	printString("The product of these numbers is ");
	printInt(product);
	printString(".\n");
}

void incr(int* i) {
	(*i)++;
}

void incrTest() {
	int j = 0;
	int i[2];
	i[0] = 1;
	i[1] = 2;
	incr(&(j));
	incr(&(i[0]));
	incr(&(i[1]));
	
	printInt(j);
	printString("\n");
	
	printInt(i[0]);
	printString("\n");
	
	printInt(i[1]);
	printString("\n");
}

int trueFunc() {
	printString("true\n");
	return 100;
}

int falseFunc() {
	printString("false\n");
	return 0;
}

void printIntEndline(int i) {
	printInt(i);
	printString("\n");
}

void testShortCircuit() {
	int t1 = trueFunc() && falseFunc();
	printIntEndline(t1);
	int t2 = trueFunc() || falseFunc();
	printIntEndline(t2);
	int t3 = trueFunc() && trueFunc();
	printIntEndline(t3);
	int t4 = trueFunc() || trueFunc();
	printIntEndline(t4);
	int t5 = falseFunc() || trueFunc();
	printIntEndline(t5);
	int t6 = falseFunc() && trueFunc();
	printIntEndline(t6);
	
}

struct testStruct {
	int a;
	int b;
};

struct testStruct structTest() {
	struct testStruct myStruct;
	myStruct.a = 1;
	myStruct.b = 2;
	printIntEndline(myStruct.a);
	printIntEndline(myStruct.b);
	struct testStruct myStruct2;
	myStruct2.a = 3;
	myStruct2.b = 4;
	myStruct2 = myStruct;
	printIntEndline(myStruct2.a);
	return myStruct2;
}

void* NULL;

struct node_t;

struct node_t {
	int data;
	struct node_t* prev;
	struct node_t* next;
};

struct list_t {
	struct node_t* head;
	struct node_t* tail;
};

void insert_node_after( struct node_t * node, struct node_t * prev, struct list_t * mylist ) {
	if ( prev == NULL ) {
		node->next = mylist->head;
		if ( mylist->head != NULL ) {
			mylist->head->prev = node;
		}
		mylist->head = node;
		if ( mylist->tail == NULL ) {
			mylist->tail = node;
		}
	} else {
		if ( prev->next == NULL ) {
			mylist->tail = node;
		} else {
			node->next = prev->next;
			node->next->prev = node;
		}
		prev->next = node;
		node->prev = prev;
	}
}

void remove_element( struct node_t * node, struct list_t * mylist ) {
	
	if ( mylist->head == mylist->tail ) {
		mylist->head = mylist->tail = NULL;
	} else if ( node->prev == NULL ) {
		mylist->head = node->next;
		node->next->prev = NULL;
	} else if ( node->next == NULL ) {
		mylist->tail = node->prev;
		node->prev->next = NULL;
	} else {
		node->prev->next = node->next;
		node->next->prev = node->prev;
	}
	node->next = node->prev = NULL;
}

void sort_list(struct list_t * mylist) {
	if (mylist->head != mylist->tail) {
		struct node_t *smallest = mylist->head;
		struct node_t *trav;
		for (trav = smallest->next ; trav != NULL ; trav = trav->next) {
			if (trav->data < smallest->data) {
				smallest = trav;
			}
		}
		remove_element(smallest, mylist);
		sort_list(mylist);
		insert_node_after(smallest, NULL, mylist);
	}
}

void sortStructTest() {
	struct node_t nodes[20];
	nodes[0].prev = NULL;
	nodes[0].next = &(nodes[1]);
	nodes[19].next = NULL;
	nodes[19].prev = &(nodes[19]);
	int i;
	for(i = 1; i < 19; i++) {
		nodes[i].prev = &(nodes[i-1]);
		nodes[i].next = &(nodes[i+1]);
	}
	for(i = 0; i < 20; i++) {
		nodes[i].data = i % 7;
	}
	
	struct list_t list;
	list.head = &(nodes[0]);
	list.tail = &(nodes[19]);
	
	sort_list(&list);
	
	struct node_t* iter = list.head;
	while(iter != NULL) {
		printIntEndline(iter->data);
		iter = iter->next;
	}
}

int* i = 0x100;

int main() {
	sortStructTest();
}


