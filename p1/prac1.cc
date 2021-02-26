// Code by:	 Enrique Abma Romero
// NIE :	 X9853366M

#include <iostream>
#include <vector>
#include <cstdlib>
#include <sstream> 

using namespace std;

const string P_NAME = "Enter project name: " ;
const string L_NAME = "Enter list name: " ;
const string T_NAME = "Enter task name: " ;
const int MAX_DAY = 31 + 1;
const int MAX_MONTH = 12;
const int MAX_YEAR = 2100;

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

bool checkName(string &name, bool IsList){

   do{
      if (IsList)
         cout << L_NAME;
      else 
         cout << P_NAME;

      getline(cin,name);

      if (name.length() == 0)
         error(ERR_EMPTY);

   }while(name.length() == 0);

   return true;

}

void editProject(Project &toDoList){
   
   string name;
   bool IsList = false;

   checkName(name, IsList);
   toDoList.name = name;
   cout << "Enter project description: ";
   getline(cin,toDoList.description);
}

void addList(Project &toDoList){


   string name;
   List nameList;
   bool repeated = false, IsList = true;
   unsigned i;

   checkName(name, IsList);
   nameList.name = name; 

   for ( i = 0; i < toDoList.lists.size(); i++){

      if (toDoList.lists[i].name == nameList.name)
         repeated = true;
   }

   // si está repetido, dará error
   if (repeated)
      error(ERR_LIST_NAME);

   else
      toDoList.lists.push_back(nameList);
}

void deleteList(Project &toDoList){
   
   string name;
   List nameList;
   unsigned i, j;
   bool found = false, IsList = true;

   checkName(name, IsList);
   nameList.name = name;

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

bool searchList (Project &toDoList,Task &vecTask, unsigned &k){
   string name;
   unsigned i;
   List nameList;
   bool ListFound = false, IsList = true, valid = true;

   if (checkName(name, IsList)) {

   	  nameList.name = name;

      for (i = 0; i < toDoList.lists.size(); i++)
      {
         if (toDoList.lists[i].name == nameList.name){
            k = i;
            ListFound = true;
            cout << T_NAME;
            getline(cin,vecTask.name);
         }
      }
   
      if (!ListFound){
         error(ERR_LIST_NAME);
         valid = false;
      }
   }

   return valid;
}

bool checkDate(int day, int month, int year){

   bool bisiesto = false;
   bool valido = false;

   // comprobar si el año es bisiesto

   if((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) 
      bisiesto = true;

   if (year > 1999 && year < 2101){
      if (month > 0 && month < 13){

         // días de febrero según año 

         if (bisiesto && month == 2 && day > 0 && day <= 29)
            valido = true;

         else if (!bisiesto && month == 2 && day > 0 && day <= 28)
            valido = true;
    
        // meses del año con 31 días

         else if ((month == 1 || month == 3 || month == 5 || month == 7 || month == 8 
                   || month == 10 || month == 12 ) && day > 0 && day <= 31)          
            valido = true;
  
        // meses del año con 30 días

         else if ((month == 4 || month == 6 || month == 9 ||  
                    month == 11 ) && day > 0 && day <= 30)   
            valido = true;
         }
   }
   else
      valido = false;

   return valido;
}


void addTask(Project &toDoList){

   Task vecTask;
   List nameList;
   string date, aux;
   int day, month, year, k = 0;
   unsigned i;

   if (searchList(toDoList,vecTask,i)){ 
      cout << "Enter deadline: ";
      getline(cin,date);
      stringstream ss(date); 
      
      // bucle que guarda los caracteres en aux cada vez que se encuentra un '/'
        
      while (getline(ss, aux, '/')) { 
         k++;

         if (k==1)
            day = stoi(aux);

         if (k==2)
            month = stoi(aux);
             
         if (k==3)
            year = stoi(aux);
       }

      // si la fecha es correcta...
       
      if (checkDate(day, month, year)){

         vecTask.deadline.day = day;
         vecTask.deadline.month = month;
         vecTask.deadline.year = year;

         vecTask.isDone = false;

         cout << "Enter expected time: ";
         cin >> vecTask.time;

         if (vecTask.time >= 1 && vecTask.time <= 180)
         	toDoList.lists[i].tasks.push_back(vecTask);
         
         else
            error(ERR_TIME);
                      
      }
      else
         error(ERR_DATE);
  }   
}

void deleteTask(Project &toDoList){

   unsigned j, i;
   int k;
   bool TaskEncontrado = false;
   Task vecTask;
   if (searchList(toDoList,vecTask,i)){          
      for ( j = 0 ; j < toDoList.lists[i].tasks.size(); j++){

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

void toggleTask(Project &toDoList){

   unsigned i,j ;
   Task vecTask;
   List nameList;
   bool TaskEncontrado = false;

   if (searchList(toDoList, vecTask, i)) {                

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

   if (!TaskEncontrado)
      error(ERR_TASK_NAME);
}

void Priority(const Project &toDoList,int &PriorDay,int &PriorMonth, int &PriorYear, string &highestName, unsigned i , unsigned j){
   
   int currentDay, currentMonth, currentYear;

   currentYear = toDoList.lists[i].tasks[j].deadline.year;
   currentMonth = toDoList.lists[i].tasks[j].deadline.month;
   currentDay = toDoList.lists[i].tasks[j].deadline.day;

   // se guarda el valor de la fecha que tenga más prioridad
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
}

void Print(const Project &toDoList, unsigned i, unsigned j){
   
   cout << "(" << toDoList.lists[i].tasks[j].time << ") ";
   cout << toDoList.lists[i].tasks[j].deadline.year << "-";
   cout << toDoList.lists[i].tasks[j].deadline.month << "-";
   cout << toDoList.lists[i].tasks[j].deadline.day;
}

void PrintDone(const Project &toDoList, unsigned i, int &countDone, int &timeDone){

   for ( unsigned j = 0 ; j < toDoList.lists[i].tasks.size(); j++){
      
      if (toDoList.lists[i].tasks[j].isDone){
         cout << "[X] ";
         Print(toDoList, i, j);
         timeDone = timeDone + toDoList.lists[i].tasks[j].time;
         countDone++;
         
         cout << " : " << toDoList.lists[i].tasks[j].name << endl;
      }
   }
}

void PrintLeft(const Project &toDoList, unsigned i, int &countLeft, int &timeLeft, int &PriorDay,int &PriorMonth, int &PriorYear, string &highestName){
   
   for ( unsigned j = 0 ; j < toDoList.lists[i].tasks.size(); j++){
      
      if (!toDoList.lists[i].tasks[j].isDone){
         cout << "[ ] ";
         timeLeft = timeLeft + toDoList.lists[i].tasks[j].time;
         countLeft++;
         Print(toDoList, i, j);
         Priority(toDoList, PriorDay,PriorMonth,PriorYear, highestName, i , j);

         cout << " : " << toDoList.lists[i].tasks[j].name << endl;
      }   
   }
}

void report(const Project &toDoList){

   int timeLeft = 0, timeDone = 0, countLeft= 0, countDone = 0;
   unsigned i;
   int PriorDay= MAX_DAY, PriorMonth = MAX_MONTH, PriorYear = MAX_YEAR;
   string highestName;
   cout << "Name: "<< toDoList.name << endl;
  
   if (toDoList.description.length()!=0)
    cout << "Description: "<< toDoList.description << endl;
  
   for ( i = 0 ; i < toDoList.lists.size(); i++){
      
      // muestra primero las que no están hechas
      cout << toDoList.lists[i].name << " " << endl;
      PrintLeft(toDoList, i, countLeft, timeLeft,PriorDay, PriorMonth,  PriorYear, highestName);   
      PrintDone(toDoList, i, countDone, timeDone);
  }

  cout << "Total left: " << countLeft << " (" << timeLeft << " minutes)" << endl;
  cout << "Total done: "<< countDone << " (" << timeDone << " minutes)" << endl;

  if (PriorDay != MAX_DAY){
    cout << "Highest priority: " << highestName << " (";
    cout << PriorYear << "-" << PriorMonth << "-" << PriorDay << ")" << endl;
  }
  cout << endl;
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
