#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PROCESSES_NAME 20
// Process Control Block (PCB) struct
struct myPCB
{
    int proc_id;
    char proc_name[MAX_PROCESSES_NAME];
    char proc_state[10];
    int burst_t;
    int arrival_t;
    int pri;
    struct myPCB *next;
};

// Global variables for the FIFO queue
struct myPCB *head = NULL; // Pointer to the head of the queue
struct myPCB *tail = NULL; // Pointer to the tail of the queue
int Q_proc_count = 0;   // The number of processes in the queue

// Function to create a new process
struct myPCB *create_proc(int pid, char *name, int burst, int arrival, int priority)
{
    // Allocate memory for a new PCB
    struct myPCB *my_new_pcb = (struct myPCB *)malloc(sizeof(struct myPCB));
    
    // Set the values of the new PCB
    my_new_pcb->proc_id = pid;               // process ID
    strcpy(my_new_pcb->proc_name, name);     // process name
    strcpy(my_new_pcb->proc_state, "Ready"); // state
    my_new_pcb->burst_t = burst;             // burst time
    my_new_pcb->arrival_t = arrival;         // arrival time
    my_new_pcb->pri = priority;              // priority
    my_new_pcb->next = NULL;                 // Default the next pointer to NULL
    return my_new_pcb;                       // Return the new PCB
}

// Function to add a new process to the FIFO queue (Linked list Implemntation)
void Add_To_queue(struct myPCB *new_pcb)
{
    // Check if the Linked List is Empty
    if (head == NULL)
    {                         
        head = new_pcb;       // Set the head to the new PCB
        tail = new_pcb;       // Set the tail to the new PCB
        new_pcb->next = NULL; // Set the next pointer to NULL
    }
    else
    {   
    // If the queue (Linked List) is not empty

        tail->next = new_pcb; // Change the next pointer of the tail to the new PCB
        tail = new_pcb;       // Change the tail to the new PCB
        new_pcb->next = NULL; // Change the next pointer to NULL
    }
    Q_proc_count++; // Increment the number of processes  by 1 in the queue
}

void change_process_State(struct myPCB *pcb, char *new_state)
{
    strcpy(pcb->proc_state, new_state);
}

// Function to remove the first process from the FIFO queue
struct myPCB *dequeue()
{
    // Check if the Linked List is Empty
    if (head == NULL)
    {                
        return NULL; // Return NULL - DO Nothing
    }
    else
    {   
    // If the queue is not empty

        struct myPCB *my_removed_pcb = head; // Store a pointer to the new head PCB
        change_process_State(my_removed_pcb,"Terminated"); // Change State to Terminated
        head = head->next;              // Set the head to the next PCB
        // If the queue is empty
        if (head == NULL)
        {                
            tail = NULL; // Set the tail to NULL
        }
        Q_proc_count--;    // Decrement the number of processes by 1 in the queue
        return my_removed_pcb; // Return the removed PCB
    }
}

// Function to print information about a process
void print_process(struct myPCB *pcb)
{
    printf("Process ID: %d\n", pcb->proc_id);
    printf("Process Name: %s\n", pcb->proc_name);
    printf("State: %s\n", pcb->proc_state);
    printf("Burst Time: %d\n", pcb->burst_t);
    printf("Arrival Time: %d\n", pcb->arrival_t);
    printf("Priority: %d\n", pcb->pri);
    printf("\n");
}

int main()
{
    // Create some example PCBs 
    struct myPCB *pcb1 = create_proc(1, "A", 5, 10, 1);
    struct myPCB *pcb2 = create_proc(2, "B", 6, 2, 3);
    struct myPCB *pcb3 = create_proc(3, "C", 4, 4, 2);
    struct myPCB *pcb4 = create_proc(4, "D", 8, 7, 4);

    // Add the PCBs to the FIFO queue 
    Add_To_queue(pcb1);
    Add_To_queue(pcb2);
    Add_To_queue(pcb3);
    Add_To_queue(pcb4);

    // Print process information  in the queue
    struct myPCB *current_pcb = head;
    while (current_pcb != NULL)
    {
        print_process(current_pcb);
        current_pcb = current_pcb->next;
    }

    // Remove the first process from the queue using the dequeue function
    struct myPCB *removed_pcb = dequeue();
    printf("Removed Process:\n");
    print_process(removed_pcb);

    // Free memory allocated for the removed process
    free(removed_pcb);

    // Print information about the remaining processes in the queue
    current_pcb = head;
    while (current_pcb != NULL)
    {   
        change_process_State(current_pcb,"Running"); // Change State to Running
        print_process(current_pcb);
        current_pcb = current_pcb->next;
    }

    return 0;
}
