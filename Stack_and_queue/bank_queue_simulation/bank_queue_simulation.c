#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_QUEUE_SIZE 1000

typedef struct customer {
    int id;
    int service_time;
    int waiting_time;
} Customer;

int isFull(int Rear) {
    return Rear == MAX_QUEUE_SIZE - 1;
}

int isEmpty(int Rear, int Front) {
    return Front == Rear;
}

void enqueue(Customer *queue, int *Rear, Customer customer) {
    if (isFull(*Rear)) {
        printf("Queue is full.");
        return;
    }
    (*Rear)++;
    queue[*Rear] = customer;
}

void dequeue(Customer *queue, int *Front, int Rear) {
    if (isEmpty(Rear, *Front)) {
        return;
    }
    (*Front)++;
}

Customer init_customer(int id) {
    Customer customer;
    int service_time;
    scanf("%d", &service_time);
    customer.id = id;
    customer.service_time = service_time;
    customer.waiting_time = 0;
    return customer;
}

void update_windows(int *windows, int signal, int waiting_people) {
    if (signal == 1) {
        while (waiting_people / *windows >=7 && *windows < 5) {
            (*windows)++;
        }
    }
    else if (signal == 0) {
        while (waiting_people / *windows < 7 && *windows > 3) {
            (*windows)--;
        }
    }
    else {
        return;
    }
}

int main() {
    Customer customer_queue[MAX_QUEUE_SIZE];
    int windows_left_time[5];
    int windows = 3;
    memset(windows_left_time, 0, sizeof(windows_left_time));
    int Front = -1, Rear = -1;
    int n;
    scanf("%d", &n);
    int arrived_customers[100];
    for (int i = 0; i < n; i++) {
        scanf("%d", &arrived_customers[i]);
    }
    int id = 1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < arrived_customers[i]; j++) {
            Customer customer = init_customer(id++);
            enqueue(customer_queue, &Rear, customer);
        }
        update_windows(&windows, 1, Rear - Front);
        // only the open windows can serve the customers
        for (int k = 0; k < windows; k++) {
            if (windows_left_time[k] == 0 && !isEmpty(Rear, Front)) {
                windows_left_time[k] = customer_queue[Front + 1].service_time;
                dequeue(customer_queue, &Front, Rear);
            }
        }
        //as long as there are customers in the queue, we need to decrease the windows left time
        for (int k = 0; k < 5; k++) {
            if (windows_left_time[k] > 0) {
                windows_left_time[k]--;
            }
        }
        for (int m = Front + 1; m <= Rear; m++) {
            customer_queue[m].waiting_time++;
        }
        update_windows(&windows, 0, Rear - Front);
    }
    // after all customers have arrived,we need to continue to serve the customers in the queue
    while (!isEmpty(Rear, Front)) {
        for (int i = 0; i < windows; i++) {
            if (windows_left_time[i] == 0 && !isEmpty(Rear, Front)) {
                windows_left_time[i] = customer_queue[Front + 1].service_time;
                dequeue(customer_queue, &Front, Rear);
            }
        }
        for (int k = 0; k < 5; k++) {
            if (windows_left_time[k] > 0) {
                windows_left_time[k]--;
            }
        }
        for (int m = Front + 1; m <= Rear; m++) {
            customer_queue[m].waiting_time++;
        }
        update_windows(&windows, 0, Rear - Front);
    }
    // print the waiting time of each customer
    for (int i = 0; i < id - 1; i++) {
        printf("%d : %d\n", customer_queue[i].id, customer_queue[i].waiting_time);
    }
    return 0;
}