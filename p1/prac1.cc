// Code by:	 Enrique Abma Romero
// NIE :	 X9853366M

#include <iostream>
#include <vector>
#include <cstdlib>
#include <sstream> 

using namespace std;

struct Date{
  int day;
  int month;
  int year;
};

struct Task{
  string name;
  Date deadline;
  bool isDone;
  int time;
};

struct List{
  string name;
  vector<Task> tasks;
};

struct Project{
  int id;
  string name;
  string description;
  vector<List> lists;
};

enum Error{
  ERR_OPTION,
  ERR_EMPTY,
  ERR_LIST_NAME,
  ERR_TASK_NAME,
  ERR_DATE,
  ERR_TIME
};

bool checkDate(int , int , int);
bool checkListName(List &);

void error(Error e){
  switch(e){
    case ERR_OPTION:
      cout << "ERROR: wrong menu option" << endl;
      break;
    case ERR_EMPTY:
      cout << "ERROR: empty string" << endl;
      break;
    case ERR_LIST_NAME:
      cout << "ERROR: wrong list name" << endl;
      break;
    case ERR_TASK_NAME:
      cout << "ERROR: wrong task name" << endl;
      break;
    case ERR_DATE:
      cout << "ERROR: wrong date" << endl;
      break;
    case ERR_TIME:
      cout << "ERROR: wrong expected time" << endl;
  }
}

void showMainMenu(){
  cout << "1- Edit project" << endl
       << "2- Add list" << endl
       << "3- Delete list" << endl 
       << "4- Add task" << endl
       << "5- Delete task" << endl
       << "6- Toggle task" << endl
       << "7- Report" << endl
       << "q- Quit" << endl
       << "Option: ";
}

void editProject(Project &toDoList){

	do{
		cout << "Enter project name: ";
		getline(cin,toDoList.name);

		if (toDoList.name.length() == 0){
			error(ERR_EMPTY);
		}
	}while(toDoList.name.length() == 0);
	cout << "Enter project description: ";
	getline(cin,toDoList.description);
}

void addList(Project &toDoList){

  List nameList;
  bool repeated = false;
  unsigned i;

   checkListName(nameList); 

   for ( i = 0; i < toDoList.lists.size(); i++){

        if (toDoList.lists[i].name == nameList.name)
        repeated = true;
    }

    if (repeated)
        error(ERR_LIST_NAME);

    else
        toDoList.lists.push_back(nameList);
}

void deleteList(Project &toDoList){

    List nameList;
    unsigned i, j;
    bool found = false;

    checkListName(nameList);
      
    for (i = 0 ; i < toDoList.lists.size(); i++){

      	if ( toDoList.lists[i].name == nameList.name){
        	j = i--;
          	toDoList.lists.erase(toDoList.lists.begin()+j);
          	found = true;
        }
    }

    if (!found)
    	error(ERR_LIST_NAME);
}

void addTask(Project &toDoList){

	Task vecTask;
	List nameList;
  	string date, aux;
  	bool ListFound = false;
  	int day, month, year, k = 0;

	if (checkListName(nameList)) {

		for (unsigned int i = 0; i < toDoList.lists.size(); i++)
	      	{
		        if (toDoList.lists[i].name == nameList.name){

		          	ListFound = true;
					cout << "Enter task name: " ;
			      	getline(cin,vecTask.name);
			      	cout << "Enter deadline: ";
					getline(cin,date);

					stringstream ss(date); 
						  
				    while (getline(ss, aux, '/')) { 
					k++;

		   		        if (k==1)
					       day = stoi(aux);

					if (k==2)
					       month = stoi(aux);
					   
				        if (k==3)
						year = stoi(aux);
					}

			      	if (checkDate(day, month, year)){
			      		vecTask.deadline.day = day;
			      		vecTask.deadline.month = month;
			      		vecTask.deadline.year = year; 
			      		cout << "Enter expected time: ";
			      		cin >> vecTask.time;
			      		vecTask.isDone = false;
			      		toDoList.lists[i].tasks.push_back(vecTask);
			        }

			        else
			        	error(ERR_DATE);
					
			        }
		        }
		    }

		if (!ListFound)
   	        error(ERR_LIST_NAME);
			
}
void deleteTask(Project &toDoList){

	int k;
	Task vecTask;
	List nameList;
  	bool ListEncontrado = false;
  	bool TaskEncontrado = false;
    
	if (checkListName(nameList)) {

		for (unsigned int i = 0; i < toDoList.lists.size(); i++)
	      	{
		        if (toDoList.lists[i].name == nameList.name){

		          	ListEncontrado = true;

				    cout << "Enter task name: ";
					getline(cin,vecTask.name);
							          	
				       	for (unsigned int j = 0 ; j < toDoList.lists[i].tasks.size(); j++){

			          		if ( toDoList.lists[i].tasks[j].name == vecTask.name){	
					      		TaskEncontrado = true;
				       			k = j--;
				   				toDoList.lists[i].tasks.erase(toDoList.lists[i].tasks.begin()+k);
		    				}
		          		}

				    if (!TaskEncontrado)
	   				 	error(ERR_TASK_NAME);
		        }
		    }
		if (!ListEncontrado)
   	        error(ERR_LIST_NAME);
	}
}

void toggleTask(Project &toDoList){

	unsigned i,j ;
	Task vecTask;
	List nameList;
  	bool ListEncontrado = false;
  	bool TaskEncontrado = false;

  	if (checkListName(nameList)) {

		for ( i = 0;  i < toDoList.lists.size(); i++)
	      	{
		        if (toDoList.lists[i].name == nameList.name){

		          	ListEncontrado = true;

				    cout << "Enter task name: ";
					getline(cin,vecTask.name);
							          	
					for ( j = 0 ; j < toDoList.lists[i].tasks.size(); j++){

				   		if ( toDoList.lists[i].tasks[j].name == vecTask.name){
					      		
				      		TaskEncontrado = true;
			       			if (toDoList.lists[i].tasks[j].isDone)
								toDoList.lists[i].tasks[j].isDone = false;

							else
								toDoList.lists[i].tasks[j].isDone = true;
			   			}
		       		}
	           	}
	        }

	    if (!TaskEncontrado)
	   			 	error(ERR_TASK_NAME);
    }

	if (!ListEncontrado)
        error(ERR_LIST_NAME);

}
void report(const Project &toDoList){

	int timeLeft = 0, timeDone = 0, countLeft= 0, countDone = 0;
	int PriorDay = 31 + 1 , PriorMonth = 12, PriorYear = 2100;
	string highestName;
	int currentDay, currentMonth, currentYear; 
	unsigned i, j;

	cout << "Name: "<< toDoList.name << endl;
	
	if (toDoList.description.length()!=0)
		cout << "Description: "<< toDoList.description << endl;
	
	for ( i = 0 ; i < toDoList.lists.size(); i++){

		cout << toDoList.lists[i].name << " " << endl;

		for ( j = 0 ; j < toDoList.lists[i].tasks.size(); j++){
			if (!toDoList.lists[i].tasks[j].isDone){
				
				cout << "[ ] ";
				timeLeft = timeLeft + toDoList.lists[i].tasks[j].time;
				countLeft++;
				cout << "(" << toDoList.lists[i].tasks[j].time << ") ";
				cout << toDoList.lists[i].tasks[j].deadline.year << "-";
				cout << toDoList.lists[i].tasks[j].deadline.month << "-";
				cout << toDoList.lists[i].tasks[j].deadline.day;

				currentYear = toDoList.lists[i].tasks[j].deadline.year;
				currentMonth = toDoList.lists[i].tasks[j].deadline.month;
				currentDay = toDoList.lists[i].tasks[j].deadline.day;

				if (PriorYear >= currentYear){
					
					if (PriorMonth > currentMonth){

						PriorDay = currentDay;
						PriorMonth = currentMonth;
						PriorYear = currentYear;
						highestName = toDoList.lists[i].tasks[j].name;
					}	
					else if (PriorMonth == currentMonth){

						if (PriorDay > currentDay){
							PriorDay = currentDay;
							PriorMonth = currentMonth;
							PriorYear = currentYear;
							highestName = toDoList.lists[i].tasks[j].name;
						}
					}
				}
				cout << " : " << toDoList.lists[i].tasks[j].name << endl;
			}

			else{

				cout << "[X] ";
				cout << "(" << toDoList.lists[i].tasks[j].time << ") ";
				timeDone = timeDone + toDoList.lists[i].tasks[j].time;
				countDone++;

				cout << toDoList.lists[i].tasks[j].deadline.year << "-";
				cout << toDoList.lists[i].tasks[j].deadline.month << "-";
				cout << toDoList.lists[i].tasks[j].deadline.day;

				cout << " : " << toDoList.lists[i].tasks[j].name << endl;
			}
		}
	}

	cout << "Total left: " << countLeft << " (" << timeLeft << " minutes)" << endl;
	cout << "Total done: "<< countDone << " (" << timeDone << " minutes)" << endl;
	if (PriorDay != 32){
		cout << "Highest priority: " << highestName << " (";
		cout << PriorYear << "-" << PriorMonth << "-" << PriorDay << ")" << endl;
	}
	cout << endl;
}


bool checkListName(List &nameList){

	do{
    	cout << "Enter list name: ";
    	getline(cin,nameList.name);

   		if (nameList.name.length() == 0)
     			error(ERR_EMPTY);

   	}while(nameList.name.length() == 0);

   	return true;

}

bool checkDate(int day, int month, int year){

	bool bisiesto = false;
	bool valido = false;

	if((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
		bisiesto = true;

	if (year > 1999 && year < 2101){
		if (month > 0 && month < 13){
			if (bisiesto && month == 2 && day > 0 && day <= 29)
				valido = true;

			else if (!bisiesto && month == 2 && day > 0 && day <= 28)
				valido = true;
		
			else if ((month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12 ) && day > 0 && day <= 31)
				valido = true;
	
			else if ((month == 4 || month == 6 || month == 9 || month == 11 ) && day > 0 && day <= 30)
				valido = true;
		}
	}
	else
		valido = false;

	return valido;
}

int main(){
  Project toDoList;
  toDoList.id=1;
  char option;
  
  do{
    showMainMenu();
    cin >> option;
    cin.get();
    
    switch(option){
      case '1': editProject(toDoList);
                break;
      case '2': addList(toDoList);
                break;
      case '3': deleteList(toDoList);
                break;
      case '4': addTask(toDoList);
                break;
      case '5': deleteTask(toDoList);
                break;
      case '6': toggleTask(toDoList);
                break;
      case '7': report(toDoList);
                break;
      case 'q': break;
      default: error(ERR_OPTION);
    }
  }while(option!='q');
  
  return 0;    
}
