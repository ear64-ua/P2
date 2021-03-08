// Code by:	 Enrique Abma Romero
// NIE :	 X9853366M
#include <iostream>
#include <vector>
#include <cstdlib>
#include <sstream> 

using namespace std;

const string YES_NO = "Confirm [Y/N]?: ";
const string P_SAVE = "Save all projects [Y/N]?: ";
const string F_NAME = "Enter filename: ";
const string P_ID = "Enter project id: ";
const string P_NAME = "Enter project name: " ;
const string L_NAME = "Enter list name: " ;
const string T_NAME = "Enter task name: " ;
const string P_DESC = "Enter project description: ";
const string DEADLINE = "Enter deadline: ";
const string EXP_TIME = "Enter expected time: ";

const int KMAXNAME = 20;
const int KMAXDESC = 40;
const int MAX_TIME = 180;
const int MIN_TIME = 1;
const int MAX_DAY = 31;
const int MIN_DAY = 1;
const int MAX_MONTH = 12;
const int MAX_YEAR = 2100;
const int MIN_YEAR = 2000;

struct Date{
  int day;
  int month;
  int year;
};

struct BinTask{
  char name[KMAXNAME];
  Date deadline;
  bool isDone;
  int time;
};

struct BinList{
  char name[KMAXNAME];
  unsigned numTasks;
};

struct BinProject{
  char name[KMAXNAME];
  char description[KMAXDESC];
  unsigned numLists;
};

struct BinToDo{
  char name[KMAXNAME];
  unsigned numProjects;
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

struct ToDo{
  int nextId;
  string name;
  vector<Project> projects;
};

enum Error{
  ERR_OPTION,
  ERR_EMPTY,
  ERR_LIST_NAME,
  ERR_TASK_NAME,
  ERR_DATE,
  ERR_TIME,
  ERR_ID,
  ERR_PROJECT_NAME,
  ERR_FILE,
  ERR_ARGS
};

enum Months{
	JANUARY = 1,
	FEBRUARY,
	MARCH,
	APRIL,
	MAY,
	JUNE,
	JULY,
	AUGUST,
	SEPTEMBER,
	OCTOBER,
	NOVEMBER,
	DECEMBER
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
      break;
    case ERR_ID:
      cout << "ERROR: wrong project id" << endl;
      break;
    case ERR_PROJECT_NAME:
      cout << "ERROR: wrong project name" << endl;
      break;
    case ERR_FILE:
      cout << "ERROR: cannot open file" << endl;
      break;
    case ERR_ARGS:
      cout << "ERROR: wrong arguments" << endl;
  }
}


int daysPerMonth(int month, bool bisiesto){

   switch(month){
      case JANUARY:
      case MARCH:
      case MAY:
      case JULY:
      case AUGUST:
      case OCTOBER:
      case DECEMBER:
         return 31;

      case APRIL:
      case JUNE:
      case SEPTEMBER:
      case NOVEMBER:
         return 30;

      case FEBRUARY:
         if (bisiesto)
         	return 29;
         else 
         	return 28;

   }
   return 0;
}

void showMainMenu(){
 cout << "1- Proyect menu" << endl
       << "2- Add project" << endl
       << "3- Delete project" << endl 
       << "4- Import projects" << endl
       << "5- Export projects" << endl
       << "6- Load data" << endl
       << "7- Save data" << endl
       << "8- Summary"<< endl
       << "q- Quit" << endl
       << "Option: ";

}

void showProjectMenu(){
  cout << "1- Edit project" << endl
       << "2- Add list" << endl
       << "3- Delete list" << endl 
       << "4- Add task" << endl
       << "5- Delete task" << endl
       << "6- Toggle task" << endl
       << "7- Report" << endl
       << "b- Back to main menu" << endl
       << "Option: ";
}

string checkName(bool IsList){

   string name;

   do{
      if (IsList)
         cout << L_NAME;
      else 
         cout << P_NAME;

      getline(cin,name);

      if (name.length() == 0)
         error(ERR_EMPTY);

   }while(name.length() == 0);

   return name;
}

void editProject(Project &toDoList){
   
   bool IsList = false;

   toDoList.name = checkName(IsList);
   cout << P_DESC;
   getline(cin,toDoList.description);
}

void addList(Project &toDoList){

   List nameList;
   bool repeated = false, IsList = true;
   unsigned i;

   nameList.name = checkName(IsList);

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
   
   List nameList;
   unsigned i, j;
   bool found = false, IsList = true;

   nameList.name = checkName(IsList);
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

   nameList.name = checkName(IsList);

   for (i = 0; i < toDoList.lists.size(); i++){

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

   return valid;
}

void returnDate(string date,int &day,int &month,int &year){

   string aux;
   int k = 0;

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
}

bool checkDate(int day, int month, int year){

   bool bisiesto = false;
   bool valid = false;
   
   // comprobar si el año es bisiesto

   if((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) 
      bisiesto = true;

   if (year >= MIN_YEAR && year <= MAX_YEAR){
      if (month > 0 && month < 13){
         // meses del año con 31/30 o febrero con 28/29 días
         if (day >= MIN_DAY && day <= daysPerMonth(month, bisiesto))          
            valid = true;
       }
   }
   else
      valid = false;

   return valid;
}

void addTask(Project &toDoList){

   Task vecTask;
   List nameList;
   int day, month, year;
   unsigned i;
   string date;

   if (searchList(toDoList,vecTask,i)){ 
      cout << DEADLINE;
      getline(cin,date);
      returnDate(date,day,month,year);

      // comprobar si la fecha es correcta...
      if (checkDate(day, month, year)){

         vecTask.deadline.day = day;
         vecTask.deadline.month = month;
         vecTask.deadline.year = year;
         vecTask.isDone = false;

         cout << EXP_TIME;
         cin >> vecTask.time;

         if (vecTask.time >= MIN_TIME && vecTask.time <= MAX_TIME)
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
   bool TaskFound = false;
   Task vecTask;

   if (searchList(toDoList,vecTask,i)){          
      for ( j = 0 ; j < toDoList.lists[i].tasks.size(); j++){

         if ( toDoList.lists[i].tasks[j].name == vecTask.name){ 
            TaskFound = true;
            k = j--;
            toDoList.lists[i].tasks.erase(toDoList.lists[i].tasks.begin()+k);
         }
      }

   if (!TaskFound)
      error(ERR_TASK_NAME);
  }
}

void toggleTask(Project &toDoList){

   unsigned i,j ;
   Task vecTask;
   List nameList;
   bool TaskFound = false, ListFound;
   
   ListFound=searchList(toDoList, vecTask, i);

   if (ListFound) {                
      for ( j = 0 ; j < toDoList.lists[i].tasks.size(); j++){
         if ( toDoList.lists[i].tasks[j].name == vecTask.name){     
            
            TaskFound = true;

            if (toDoList.lists[i].tasks[j].isDone)
               toDoList.lists[i].tasks[j].isDone = false;
            else
               toDoList.lists[i].tasks[j].isDone = true;
         }
      }
   }

   if (!TaskFound && ListFound)
      error(ERR_TASK_NAME);
}

void priority(const Project &toDoList,int &PriorDay,int &PriorMonth, int &PriorYear, string &highestName, unsigned i , unsigned j){
   
   int currentDay, currentMonth, currentYear;

   currentYear = toDoList.lists[i].tasks[j].deadline.year;
   currentMonth = toDoList.lists[i].tasks[j].deadline.month;
   currentDay = toDoList.lists[i].tasks[j].deadline.day;

   // se guarda el valor de la fecha que tenga más prioridad
   
   if(PriorYear>currentYear){
      
      PriorDay = currentDay;
      PriorMonth = currentMonth;
      PriorYear = currentYear;
      highestName = toDoList.lists[i].tasks[j].name;

   }

   if (PriorYear == currentYear){

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

void print(const Project &toDoList, unsigned i, unsigned j){
   
   cout << "(" << toDoList.lists[i].tasks[j].time << ") ";
   cout << toDoList.lists[i].tasks[j].deadline.year << "-";
   cout << toDoList.lists[i].tasks[j].deadline.month << "-";
   cout << toDoList.lists[i].tasks[j].deadline.day;
}

void printDone(const Project &toDoList, unsigned i, int &countDone, int &timeDone){

   for ( unsigned j = 0 ; j < toDoList.lists[i].tasks.size(); j++){
      
      if (toDoList.lists[i].tasks[j].isDone){
         cout << "[X] ";
         print(toDoList, i, j);
         cout << " : " << toDoList.lists[i].tasks[j].name << endl;
         timeDone = timeDone + toDoList.lists[i].tasks[j].time;
         countDone++; 
      }
   }
}

void printLeft(const Project &toDoList, unsigned i, int &countLeft, int &timeLeft, int &PriorDay,int &PriorMonth, int &PriorYear, string &highestName){
   
   for ( unsigned j = 0 ; j < toDoList.lists[i].tasks.size(); j++){
      
      if (!toDoList.lists[i].tasks[j].isDone){
         cout << "[ ] ";
         timeLeft = timeLeft + toDoList.lists[i].tasks[j].time;
         countLeft++;
         print(toDoList, i, j);
         priority(toDoList, PriorDay,PriorMonth,PriorYear, highestName, i , j);
         cout << " : " << toDoList.lists[i].tasks[j].name << endl;
      }   
   }
}

void report(const Project &toDoList){

   int timeLeft = 0, timeDone = 0, countLeft= 0, countDone = 0;
   unsigned i;
   int PriorDay = MAX_DAY + 1, PriorMonth = MAX_MONTH, PriorYear = MAX_YEAR;
   string highestName;
   // se le añade uno a MAX_DAY al tener que inicializar el día con más prioridad que el 
   // el mayor número que puede ser introducido
   cout << "Name: "<< toDoList.name << endl;
  
   if (toDoList.description.length() != 0)
      cout << "Description: "<< toDoList.description << endl;
  
   for ( i = 0 ; i < toDoList.lists.size(); i++){
      // muestra primero las que no están hechas
      cout << toDoList.lists[i].name << " " << endl;
      printLeft(toDoList, i, countLeft, timeLeft,PriorDay, PriorMonth,  PriorYear, highestName);   
      printDone(toDoList, i, countDone, timeDone);
   }

   cout << "Total left: " << countLeft << " (" << timeLeft << " minutes)" << endl;
   cout << "Total done: "<< countDone << " (" << timeDone << " minutes)" << endl;

   if (PriorDay != MAX_DAY + 1 ){
     cout << "Highest priority: " << highestName << " (";
     cout << PriorYear << "-" << PriorMonth << "-" << PriorDay << ")" << endl;
  }
  cout << endl;
}

int projectMenu(){
   
  Project toDoList;
  char option;
  
  cout << P_ID;
  cin >> toDoList.id;
   do{
      showProjectMenu();
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
         case 'b': break;
         default: error(ERR_OPTION);
      }
   }while(option!='b');
  
  return 0;    

}

void addProject(){

}

void deleteProject(){

}

void importProject(){

}

void exportProject(){

}

void loadData(){

}

void saveData(){

}

void summary(){

}

int main(){
  Project toDoList;
  char option;
  
  do{
    showMainMenu();
    cin >> option;
    cin.get();
    
    switch(option){
      case '1': projectMenu();
                break;
      case '2': addProject();
                break;
      case '3': deleteProject();
                break;
      case '4': importProject();
                break;
      case '5': exportProject();
                break;
      case '6': loadData();
                break;
      case '7': saveData();
                break;
      case '8': summary();
                break;
      case 'q': break;
      default: error(ERR_OPTION);
    }
  }while(option!='q');
  
  return 0;    
}
