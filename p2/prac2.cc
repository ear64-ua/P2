// Code by:	 Enrique Abma Romero
// NIE :	 X9853366M
#include <iostream>
#include <vector>
#include <cstdlib>
#include <sstream> 
#include <fstream>
#include <cstring>

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
 cout << "1- Project menu" << endl
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
}

bool searchProject(ToDo &toDoProject, Project &toDoList, unsigned &position){
 
   bool found=false;

   cout << P_ID;
   cin >> toDoList.id;

   for (unsigned i = 0; i<toDoProject.projects.size(); i++){
      if (toDoList.id==toDoProject.projects[i].id){
      	 position = i;
         toDoList = toDoProject.projects[i];
         found = true;
       }
   }

   if (!found){
      error(ERR_ID);
      return false;
   }

   return true;
}

void saveProject(Project &toDoList, ToDo &toDoProject){

    for (unsigned i = 0; i < toDoProject.projects.size(); i++){
       if (toDoProject.projects[i].id == toDoList.id)
           toDoProject.projects[i] = toDoList;
     }
}

int projectMenu(ToDo &toDoProject){

   char option;
   Project toDoList;
   unsigned i;

   if (searchProject(toDoProject,toDoList, i)){

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
            case 'b': saveProject(toDoList,toDoProject);
                      break;
            default: error(ERR_OPTION);
         }
      }while(option!='b');
    }
  return 0;    
}

void addProject(ToDo &toDoProject){

   bool IsList = false, repeated = false;
   Project toDoList;

   toDoList.name = checkName(IsList);

   for (unsigned i = 0; i < toDoProject.projects.size(); i++){

      if (toDoProject.projects[i].name == toDoList.name)
         repeated = true;
   }

   // si está repetido, dará error
   if (repeated)
      error(ERR_PROJECT_NAME);

   else{
      cout << P_DESC;
      getline(cin,toDoList.description);
      toDoList.id = toDoProject.nextId;
      ++toDoProject.nextId;
      toDoProject.projects.push_back(toDoList);
   }
}

void deleteProject(ToDo &toDoProject){

   Project toDoList; 
   unsigned i,j;

   if (searchProject(toDoProject,toDoList, i)){
      j = i--;
      toDoProject.projects.erase(toDoProject.projects.begin()+j);
   }
}

void separateTaskData(string &s,string &name, string &date, string &boolean, int &time){
   
   int i=0, end=0, count = 0;

   while( end = s.find("|", i), end >= 0 ) // agarra la posición de donde termina cada '|' y se va guardando en cada variable
   {
      if (count == 0)
         name = s.substr(i, end - i);
      if (count == 1)
         date = s.substr(i, end - i);
      if (count == 2)
         boolean = s.substr(i, end - i);

      count++;
      i = end + 1;
   }

   if (count == 3) // después del último '|' corresponde al tiempo
      time = stoi(s.substr(i));

}

void isolateTask(string &s, List &listData){

   Task taskData;
   string name, date, boolean;
   int day, month, year, time=0;

   separateTaskData(s,name,date,boolean,time);
   returnDate(date,day,month,year);

   if(checkDate(day,month,year)){ // si la fecha es correcta se empiezan a asignar los datos de la tarea

      taskData.deadline.day = day;
      taskData.deadline.month = month;
      taskData.deadline.year = year;
      taskData.name = name;
      taskData.time = time;

      if (boolean == "F")
         taskData.isDone = false;

      else 
         taskData.isDone = true;

      if (time >= MIN_TIME && time <= MAX_TIME)
         listData.tasks.push_back(taskData);

      else
         error(ERR_TIME);
   }  

   else
      error(ERR_DATE);
}

bool checkProjectName(ToDo &toDoProject , string name){
// comprueba que ya existe un proyecto con ese nombre
   for (unsigned i = 0; i < toDoProject.projects.size(); i++){
      if (toDoProject.projects[i].name == name)
         return false;
   }

   return true;
}

void assignData(string s, Project &toDoList, ToDo &toDoProject,List &listData,bool searchProject, bool &isList, char chain[]){

   if ((chain[0]== '#') && !searchProject){ // si encuentra nombre
      s.replace(0,1,"");   // borra el primer elemento
      toDoList.name = s;
   }

   if (chain[0]== '*'){ // si es una descripcion
      s.replace(0,1,"");
      toDoList.description = s;
   }

   if (isList && chain[0] != '@' && (chain[0]!= '<' && chain[0]!= '>')){ // si estamos en una lista y no es un nombre de lista, ni < ó >,  es una tarea
      isolateTask(s,listData);
   }

   if (isList && chain[0]== '@'){ // si estamos en una lista y vuelve a ser una lista
      toDoList.lists.push_back(listData);
      listData.tasks.clear();
      isList = false;    // termina nuestra lista actual
   }

   if (!isList && chain[0]== '@') { // si no estamos en una lista y hay un nombre de lista 
      s.replace(0,1,"");
      listData.name=s;
      isList = true;
   }
}

void askFileName(string &filename){

   cout << F_NAME;
   getline(cin, filename);

}

void endsProject(ToDo &toDoProject,Project &toDoList, List &listData, bool &read, bool &searchProject, bool &isList ){

   toDoList.lists.push_back(listData); // empuja la última lista con tareas
   listData.tasks.clear();
   listData.name.erase();
   
   read = false; 
   searchProject = true;         
   isList = false;
   
   // borra el contenido de la estructura para seguir trabajando con él 
   if (checkProjectName(toDoProject , toDoList.name)){

      toDoList.id = toDoProject.nextId;
      ++toDoProject.nextId;
      toDoProject.projects.push_back(toDoList);
   }
   else 
      error(ERR_PROJECT_NAME);

   toDoList.lists.clear();
   toDoList.description="";
}

bool importProject(ToDo &toDoProject, string filename, bool askForFileName){
    
   List listData;
   Project toDoList;
   string data;
   bool read,searchProject, isList=false;
   int size;

   if (askForFileName) 
      askFileName(filename);

   ifstream fl(filename); 

   if(fl.is_open()){
      string s;
      while(getline(fl,s)){
         
         size = s.length();
         char chain[size];
         strcpy(chain,s.c_str());
	       // encuentra el < y asume que empieza un proyecto
         if (chain[0]== '<'){
            read=true;
            searchProject = false;
         }
         // termina el proyecto
         if (chain[0]== '>'){
            endsProject(toDoProject, toDoList, listData, read, searchProject, isList);
         }
         // ejecuta el proyecto
         if (read)
            assignData(s, toDoList, toDoProject, listData, searchProject, isList, chain);               
		}
		fl.close();
   }
   
   else {
      error(ERR_FILE);
      return false;   
   }

   return true;
}

void readProject(const ToDo &toDoProject, unsigned p, ofstream &fe){

   unsigned j, i;

   fe << "<" << endl;
   fe << "#" << toDoProject.projects[p].name << endl;
   if (toDoProject.projects[p].description.length() != 0)
      fe << "*" << toDoProject.projects[p].description << endl;

   for ( i = 0; i < toDoProject.projects[p].lists.size(); i++){
         
      if (toDoProject.projects[p].lists[i].name.length() != 0)
         fe << "@" << toDoProject.projects[p].lists[i].name << endl;

      for ( j = 0; j < toDoProject.projects[p].lists[i].tasks.size(); j++){

         fe << toDoProject.projects[p].lists[i].tasks[j].name << "|" << toDoProject.projects[p].lists[i].tasks[j].deadline.day;
         fe << "/" << toDoProject.projects[p].lists[i].tasks[j].deadline.month << "/" ;
         fe << toDoProject.projects[p].lists[i].tasks[j].deadline.year << "|";

         if (toDoProject.projects[p].lists[i].tasks[j].isDone == true)
            fe << "T";
         else 
            fe << "F";

         fe << "|" << toDoProject.projects[p].lists[i].tasks[j].time << endl;
      }
   }
      
   fe << ">" << endl;
}

bool confirm(bool isBin){

   string answer;

   do {

      if (isBin) // si es binario pide confirmación 
         cout << YES_NO;
      else if (!isBin)  // si no es binario se pide el num de proyectos 
         cout << P_SAVE; 
      
      getline(cin, answer);

  
   }while(answer != "y" && answer != "n" && answer != "Y" && answer != "N" );

   if ( answer == "y" ||  answer == "Y")
      return true;
   
   else 
      return false;
}

void exportProject(ToDo &toDoProject){

   string answer;
   string filename;
   unsigned p;
   Project toDoList;
   bool isBin = false;

   if (confirm(isBin)){
      
      askFileName(filename);
      ofstream fe(filename);

      if (fe.is_open()){ //si la respuesta es "y/Y" exporta todos los proyectos 
         for (unsigned i = 0; i < toDoProject.projects.size(); i++)
            readProject(toDoProject, i, fe);
         
         fe.close();
        }

      else 
         error(ERR_FILE);
   }

   else{

      if(searchProject( toDoProject,  toDoList,  p)){ // encuentra el proyecto con su correspondiente id
         
         cin.get();
         askFileName(filename);
         
         ofstream fe(filename);

         if (fe.is_open()){ // si la respuesta es "n/N" exporta un solo proyecto
            readProject(toDoProject, p, fe);
            fe.close();
         }
         else 
            error(ERR_FILE);
      }
   }
}

void loadList(ToDo &toDoProject, unsigned i, ifstream &file, unsigned projectSize){

   BinList binaryList;
   BinTask binaryTask;
   List pushList;
   Task pushTask;

   for (unsigned j = 0; j < projectSize ; j++ ){

      file.read((char * ) &binaryList, sizeof(BinList));

      pushList.name = binaryList.name;

      toDoProject.projects[i].lists.push_back(pushList);

      for (unsigned k = 0; k < binaryList.numTasks ; k++ ){

         file.read((char * ) &binaryTask, sizeof(BinTask));

         pushTask.name = binaryTask.name;
         pushTask.deadline.day = binaryTask.deadline.day;
         pushTask.deadline.month = binaryTask.deadline.month;
         pushTask.deadline.year = binaryTask.deadline.year;
         pushTask.isDone = binaryTask.isDone;
         pushTask.time = binaryTask.time;

         toDoProject.projects[i].lists[j].tasks.push_back(pushTask);
      }
   }
}

bool loadData(ToDo &toDoProject, string filename, bool askForFileName){
    
   BinToDo binaryToDo; 
   BinProject binaryProject;
   string answer;
   Project pushProj;

   bool isBin = true;

   if (askForFileName)
      askFileName(filename);
   
   ifstream file(filename, ios::in | ios::binary);

   if (file.is_open()){
      if (!askForFileName || confirm(isBin))
      {
         askForFileName = true;
         toDoProject.nextId = 1;
         toDoProject.projects.clear();
         file.read((char * ) &binaryToDo, sizeof(BinToDo));

         toDoProject.name = binaryToDo.name;
         	
         for (unsigned i = 0; i < binaryToDo.numProjects ; i++ ){

            file.read((char * ) &binaryProject, sizeof(BinProject));

            pushProj.name = binaryProject.name;
            pushProj.description = binaryProject.description;
            pushProj.id = toDoProject.nextId;
            toDoProject.nextId++;

            toDoProject.projects.push_back(pushProj);

            loadList(toDoProject, i , file, binaryProject.numLists);
         }
      }
      file.close(); 
   }

   else {
      error(ERR_FILE);
      return false;   
   }

   return true;
}

void saveList(ToDo &toDoProject, unsigned i, ofstream &file){

   BinList binaryList;
   BinTask binaryTask;

   for (unsigned j = 0; j < toDoProject.projects[i].lists.size(); j++){
            
      strncpy (binaryList.name, toDoProject.projects[i].lists[j].name.c_str(), KMAXNAME);
      binaryList.name[KMAXNAME-1]='\0';
      binaryList.numTasks = toDoProject.projects[i].lists[j].tasks.size();
      file.write((const char *)&binaryList, sizeof(BinList));   // para que se escriba la estructura List

      for (unsigned k = 0; k < toDoProject.projects[i].lists[j].tasks.size(); k++){

         strncpy (binaryTask.name, toDoProject.projects[i].lists[j].tasks[k].name.c_str(), KMAXNAME);
         binaryTask.name[KMAXNAME-1]='\0';

         binaryTask.deadline.day = toDoProject.projects[i].lists[j].tasks[k].deadline.day;
         binaryTask.deadline.month = toDoProject.projects[i].lists[j].tasks[k].deadline.month;
         binaryTask.deadline.year = toDoProject.projects[i].lists[j].tasks[k].deadline.year;

         binaryTask.isDone = toDoProject.projects[i].lists[j].tasks[k].isDone;

         binaryTask.time = toDoProject.projects[i].lists[j].tasks[k].time;
         file.write((const char *)&binaryTask, sizeof(BinTask));   // para que se escriba la estructura Task
      }
   }
}

void saveData(ToDo &toDoProject){

   string filename;
   BinToDo binaryToDo;
   BinProject binaryProject;
   
   askFileName(filename);
   ofstream file(filename, ios::out | ios::binary );

   if (file.is_open()){

      strncpy (binaryToDo.name,toDoProject.name.c_str(),KMAXNAME);
      binaryToDo.name[KMAXNAME-1]='\0';
      binaryToDo.numProjects = toDoProject.projects.size();
      file.write((const char *)&binaryToDo, sizeof(BinToDo));  // para que se esctiba la estructura ToDo

      for (unsigned i = 0; i < toDoProject.projects.size(); i++){
         
         strncpy (binaryProject.name, toDoProject.projects[i].name.c_str(), KMAXNAME);
         binaryProject.name[KMAXNAME-1]='\0';

         if (toDoProject.projects[i].name.length()!=0){
            strncpy (binaryProject.description, toDoProject.projects[i].description.c_str(), KMAXDESC);            
            binaryProject.description[KMAXDESC-1]='\0';
         }

         else 
         	strcpy(binaryProject.description,"");

         binaryProject.numLists = toDoProject.projects[i].lists.size();
         file.write((const char *)&binaryProject, sizeof(BinProject));   // para que se escriba la estructura Project

         saveList(toDoProject, i, file);

      }

      file.close();
   }

   else 
      error(ERR_FILE);

}

void summary(const ToDo &toDoProject){
   
   Project toDoList;
   unsigned i,j,k;
   int taskCounter, taskCountDone;
   
   for (j = 0; j < toDoProject.projects.size(); j++){
   
      toDoList = toDoProject.projects[j];
      taskCounter=0;
      taskCountDone=0;

      for ( i = 0 ; i < toDoList.lists.size(); i++){

         for (k = 0; k < toDoList.lists[i].tasks.size(); k++){

            if (toDoList.lists[i].tasks[k].isDone)
         	 	taskCountDone++;

         	taskCounter++;
          }
      }
      cout << "(" << toDoProject.projects[j].id << ") " << toDoProject.projects[j].name << "["<< taskCountDone << "/" << taskCounter << "]" << endl;
    }
}


void toDoMenu(ToDo &toDoProject,bool askForFileName){
   char option;
   string filename;  

   toDoProject.name = "My ToDo list";

  do{
    showMainMenu();
    cin >> option;
    cin.get();
    
    switch(option){
      case '1': projectMenu(toDoProject);
                break;
      case '2': addProject(toDoProject);
                break;
      case '3': deleteProject(toDoProject);
                break;
      case '4': importProject(toDoProject, filename, askForFileName);
                break;
      case '5': exportProject(toDoProject);
                break;
      case '6': loadData(toDoProject, filename, askForFileName);
                break;
      case '7': saveData(toDoProject);
                break;
      case '8': summary(toDoProject);
                break;
      case 'q': break;
      default: error(ERR_OPTION);
    }
  } while(option!='q');
}

int arguments(ToDo &toDoProject, int argc, vector<string> vecArguments, bool askForFileName){

   if (argc%2 == 0 || argc > 5 )
      return 1;

   if (argc == 5){
      if(vecArguments[1] == "-i" && vecArguments[3] == "-l"){
         if (!loadData(toDoProject, vecArguments[4], askForFileName) || !importProject(toDoProject, vecArguments[2], askForFileName))
            return 2;
      }
      else if (vecArguments[1] == "-l" && vecArguments[3] == "-i"){
         if (!loadData(toDoProject, vecArguments[2], askForFileName) || !importProject(toDoProject, vecArguments[4], askForFileName))
            return 2;
      }
      
      else 
         return 1;
   }
   
   else if (argc==3){
      
      if (vecArguments[1]=="-l"){
         if(!loadData(toDoProject, vecArguments[2], askForFileName))
            return 2;
      }
   
      else if (vecArguments[1]=="-i"){
         if(!importProject(toDoProject, vecArguments[2], askForFileName))
            return 2;
      }
      
      else
         return 1;
   }

   return 0;
}

int main(int argc, char *argv[]){
   
   vector<string> vecArguments;
   ToDo toDoProject;
   bool askForFileName = true;
   int value;

   toDoProject.nextId = 1;

   for (int i = 0; i < argc; i++)
      vecArguments.push_back(string(argv[i]));

   if (argc > 1)
      askForFileName = false;
   
   value = arguments(toDoProject, argc, vecArguments, askForFileName);

   if (value==0){
      askForFileName = true;
      toDoMenu(toDoProject, askForFileName);
   }

   else if (value == 1)
      error(ERR_ARGS);

   return 0;
}

