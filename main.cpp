#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

enum Priority { Low, Medium, High };

//Task class : Base

class Task {
private:
    string title;
    string description;
    bool isDone;
    string deadline;
    Priority priority;

public:
    Task(string, string, string, Priority);
    virtual ~Task() {}

    void toggleStatus() { isDone = !isDone; }
    virtual void display() const;
    bool getStatus() const { return isDone; }
    string getDeadline() const { return deadline; }
    Priority getPriority() const { return priority; }
    string getTitle() const { return title; }
};

Task::Task(string t, string d, string dl, Priority p): title(t), description(d), deadline(dl), priority(p), isDone(false) {}

void Task::display() const
{
    cout << "[" << (isDone ? "Done" : "Pending") << "] "
        << title << " | Priority: " << (priority == 2 ? "High" : (priority == 1 ? "Medium" : "Low"))
        << " | Deadline: " << deadline << endl;
    cout << "   Desc: " << description << endl;
}

//Todo class

class Todo : public Task {
public:
    Todo(string t, string d, string dl, Priority p) : Task(t, d, dl, p) {}

};

//Todo list class

class TodoList {
private:
    vector<Todo*> tasks;

public:
    ~TodoList();

    void addTask(string, string, string, int);
    void deleteTask(int);
    void showAll() const;
    void showByStatus(bool) const ;
    void sortByPriority();
    void changeStatus(int);
};

TodoList::~TodoList()
{
    for (auto t : tasks) delete t;
}

void TodoList::addTask(string t, string d, string dl, int p)
{
    tasks.push_back(new Todo(t, d, dl, static_cast<Priority>(p)));
}

void TodoList::deleteTask(int index)
{
        if (index >= 0 && index < tasks.size()) {
        delete tasks[index];
        tasks.erase(tasks.begin() + index);
    }
}

void TodoList::showAll() const
{
        for (size_t i = 0; i < tasks.size(); ++i) {
        cout << i + 1 << ". ";
        tasks[i]->display();
    }
}

void TodoList::showByStatus(bool done) const
{
        for (auto t : tasks) {
        if (t->getStatus() == done) t->display();
    }
}


void TodoList::sortByPriority()
{
    sort(tasks.begin(), tasks.end(), [](Todo* a, Todo* b) {
            return a->getPriority() > b->getPriority();
        });
}

void TodoList::changeStatus(int index)
{
    if (index >= 0 && index < tasks.size()) {
            tasks[index]->toggleStatus();
        }
}


//main


int main() {
    TodoList myTodo;
    int choice;

    while (true) {
        cout << "\n--- Todo List Menu ---\n";
        cout << "1. Add Task\n2. Show All\n3. Show Done/Pending\n4. Change Status\n5. Delete Task\n6. Sort by Priority\n7. Exit\n";
        cout << "Choice: ";
        cin >> choice;

        if (choice == 7) break;

        if (choice == 1) {
            string t, d, dl; int p;
            cout << "Title: "; cin.ignore(); getline(cin, t);
            cout << "Desc: "; getline(cin, d);
            cout << "Deadline (y/m/d): "; cin >> dl;
            cout << "Priority (0:Low, 1:Med, 2:High): "; cin >> p;
            myTodo.addTask(t, d, dl, p);
        } else if (choice == 2) {
            myTodo.showAll();
        } else if (choice == 4) {
            int idx; cout << "Enter task number: "; cin >> idx;
            myTodo.changeStatus(idx - 1);
        } else if (choice == 5) {
            int idx; cout << "Enter task number to delete: "; cin >> idx;
            myTodo.deleteTask(idx - 1);
        } else if (choice == 6) {
            myTodo.sortByPriority();
            cout << "Sorted by high priority!\n";
        }
    }
    return 0;
}
