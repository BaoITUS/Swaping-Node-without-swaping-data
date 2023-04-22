#include <iostream>

using namespace std;

struct task {
	task *prev = NULL;
	int code = 0;
	float executionTime = 0;
	int priority = 0;
	task *next = NULL;
};

struct queue {
	task *head = NULL;
	task *tail = NULL;
} list;

void createTask(task*& newTask) {
	char temp[128];
	cout << "Enter code: ";
	cin >> newTask->code;
	cout << "Enter execution time: ";
	cin >> newTask->executionTime;
	cout << "Enter priority (1 = Low, 2 = Medium, 3 = High): ";
	cin >> newTask->priority;
}

void enQueue(task *newTask) {
	if (list.tail == NULL)
		list.tail = list.head = newTask;
	else {
		newTask->prev = list.tail;
		list.tail = list.tail->next = newTask;
	}
}

void inputList() {
	int n;
	cout << "Enter n: ";
	cin >> n;
	for (int i = 0; i < n; i++) {
		task *newTask = new task;
		createTask(newTask);
		enQueue(newTask);
	}
}

void sort() {
	for (task *i = list.head; i != list.tail; i = i->next)
		for (task *j = i->next; j != NULL; j = j->next)
			if ((i->priority < j->priority) || (i->priority == j->priority && i->executionTime > j->executionTime)) {
				//change pointers in front of i, behind j, the list head and tail
				if (i != list.head)
					i->prev->next = j;
				else
					list.head = j;
				if (j != list.tail)
					j->next->prev = i;
				else
					list.tail = i;
				//swap i and j
				if (i->next == j) {
					i->next = j->next;
					j->prev = i->prev;
					i->prev = j;
					j->next = i;
				}
				else {
					task* temp = i;
					i->prev = j->prev;
					j->prev = temp->prev;
					j->prev->next = i;
					i->next->prev = j;
				}
				//update the correct i and j in the loop
				swap(i, j);
			}
}

void outputList() {
	for (task *i = list.head; i != NULL; i = i->next)
		cout << i->code << "\t"
		     << i->executionTime << "\t"
		     << i->priority << "\n";
	system("pause");
}

void deleteList() {
	if (list.head != list.tail)
		for (task* i = list.head->next; i != list.tail; i = i->next) {
			delete i->prev;
		}
	delete list.tail;
	list.head = list.tail = NULL;
}

int main() {
	inputList();
	sort();
	outputList();
	deleteList();
}