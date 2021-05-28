// NIE X9853366M ABMA ROMERO, ENRIQUE
#include <iostream>
#include <vector>
#include "Task.h"
#include "List.h"
#include "Project.h"
#include "Util.h"

using namespace std;

int main(){
    
    //string proyName;
    //string isdone;
    //vector <Task> t;

    // TASK 

    cout << "\n-----------Task------------" << endl;
    Task task1("t1");
    task1.setDeadline("3/4/2020");
    task1.setTime(130);
    task1.toggle();
    

    Task task2("t2");
    task2.setDeadline("1/7/2019");
    task2.setTime(50);

    Task task3("t3");
    task3.setDeadline("3/3/2021");
    task3.setTime(20);

    Task task4("t4");
    task4.setDeadline("1/7/2019");
    task4.setTime(50);  

    cout << task1 << task2 << task3 << task4;

    cout << "\n---------------------------" << endl;

    // LIST 

    cout << "\n-----------List------------" << endl;

    List l1("l1");
    
    l1.addTask(task1);
    l1.addTask(task2);
    l1.addTask(task3);
    l1.addTask(task4);

    l1.deleteTask("t4");

    l1.toggleTask("t2");

    cout << l1 << endl;
    try
    {
        List l2("");
    }

    catch(Error err)
    {
        Util::error(err); // ERROR EMPTY STRING
    }

    cout << "---------------------------" << endl;

    //PROJECT   
    
    cout << "\n---------Project------------" << endl;

    Project p1("project 1","project 1 description");
    p1.setId(4);
    p1.addList("l1");
    p1.addList("l2");
    //p1.addTaskToList("l1");
    //p1.addTaskToList("l1");
    cout << "**DELETE TASK**" << endl;
    //p1.deleteTaskFromList("l1");
    cout << "**TOGGLE TASK**" << endl;
    //p1.toggleTaskFromList("l1");
    p1.deleteList("l2");

    cout << p1 <<endl;

    Project p2("project 2","");
    cout << p2 <<endl;

    Project p3("project 3","");
    p3.setDescription("project 3 description");
    p3.setName("project 3 modified");
    cout << p3 <<endl;

    try
    {
        cout << "**EMPTY PROJECT NAME**" << endl;
        Project p4("","");
        cout << p4 <<endl;
    }

    catch(Error err)
    {
        Util::error(err);
    }



    return 0;
}