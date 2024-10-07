#include <iostream>
using namespace std;

struct Node
{
    int process_id;
    int execution_time;
    int remaining_time;
    Node *next;
};

class LinkedList
{
    Node *tail;
    Node *head;

public:
    LinkedList()
    {
        head = NULL;
        tail = NULL;
    }

    void insert(int process_id, int execution_time)
    {
        int remaining_time = execution_time;
        Node *newNode = new Node();
        newNode->process_id = process_id;
        newNode->execution_time = execution_time;
        newNode->remaining_time = remaining_time;

        if (!head)
        {
            newNode->next = newNode; 
            head = newNode;
            tail = newNode;
        }
        else
        {
            newNode->next = head;
            tail->next = newNode;
            tail = newNode;
        }
    }

    void display()
    {
        if (!head)
        {
            cout << "List is empty." << endl;
            return;
        }
        Node *temp = head;
        do
        {
            cout << "Process_Id: " << temp->process_id << " " << endl;
            cout << "Total Time: " << temp->execution_time << " " << endl;
            cout << "Remaining Time: " << temp->remaining_time << " " << endl;
            cout << endl;
            temp = temp->next;
        } while (temp != head);
        cout << endl;
    }

    void checkTime(Node *&temp, Node *&prev)
    {
        if (temp->remaining_time <= 0)
        {
            if (temp == head)
            {
                head = temp->next;
                tail->next = head; 
                delete temp;
                temp = head;
                prev = tail; 
            }
            else if (temp == tail)
            {
                tail = prev;
                tail->next = head;
                delete temp;
                temp = tail->next;
            }
            else
            {
                prev->next = temp->next;
                delete temp;
                temp = prev->next;
            }
        }
    }

    void cycle(int time)
    {
        if (!head) return;

        Node *temp = head;
        Node *prev = tail;
        do
        {
            temp->remaining_time -= time; // Subtract the time slice
            cout << "Process_Id: " << temp->process_id << endl;
            cout << "Total Time: " << temp->execution_time << endl;
            cout << "Remaining Time: " << temp->remaining_time << endl;
            cout << endl;

            checkTime(temp, prev);

            if (temp != head)  
                prev = prev->next;

        } while (temp != head);
    }

    void scheduler(int time)
    {
        int cycle_count = 0;
        while (size() > 1) 
        {
            cycle_count++;
            cout << "Cycle " << cycle_count << ":" << endl;
            cycle(time);
            display();

            if (cycle_count == 2) 
            {
                cout << "New process arrives: P6 (Remaining: 9)" << endl;
                insert(6, 9); 
            }
        }

        if (head)
        {
            cout << "Final Process_Id: " << head->process_id << " finished execution." << endl;
        }
    }

    int size()
    {
        if (!head)
            return 0;

        Node *temp = head;
        int count = 0;

        do
        {
            count++;
            temp = temp->next;
        } while (temp != head);

        return count;
    }
};

int main()
{
    LinkedList list = LinkedList();
    list.insert(1, 6);
    list.insert(2, 4);
    

    list.scheduler(2); // Time slice of 2
    return 0;
}
