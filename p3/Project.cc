#include "Project.h"
#include "Util.h"
#include <sstream>


Project::Project(string name, string description)
{
   if (name.length()==0)
      throw ERR_EMPTY;
   else
      this->name=name;

   this->description=description;

   this->id=0;
}

int Project::getPosList(string name) const
{   

   for (unsigned i = 0; i < lists.size();i++)
   {
      if (lists[i].getName()==name)
         return i;
   }

   return -1;
}

bool Project::setId(int id)
{
   if (id>=0)
   {
      this->id=id;
      return true;
   }

   Util::error(ERR_ID);
   return false;
}

bool Project::setName(string name)
{
   if (name.length()==0)
   {
      Util::error(ERR_EMPTY);
      return false;
   }

   else 
      this->name=name;

   return true;
}

void Project::setDescription(string description)
{
   this->description=description;
}

void Project::edit(string name,string description)
{
   bool stop = false; 

   do
   {
      cout << P_NAME;
      getline(cin,name);

      stop = setName(name);
         
   }while (!stop);

   if (description.length()==0)
   {
      cout << P_DESC;
      getline(cin,description);
      setDescription(description);
   }
}

void Project::addList(string name)
{

   if (name.length()!=0)
   {
      List list(name);
      if (getPosList(name)==-1)
         lists.push_back(list);
      else 
            Util::error(ERR_LIST_NAME);
   }

   while (name.length()==0)
   {
      cout << L_NAME;
      getline(cin,name);
      try
      {
         List list(name);
         if (getPosList(name)==-1)
            lists.push_back(list);
         else 
            Util::error(ERR_LIST_NAME);
      }
      catch(Error err)
      {
         Util::error(err);
      }
   }

}

int Project::askForListName(string name)
{

   int i = 0;

   while (name.length()==0)
   {
      cout << L_NAME;
      getline(cin,name);

      if (name.length()==0)
         Util::error(ERR_EMPTY);
   }

   i = getPosList(name);

   return i;
}

void Project::deleteList(string name)
{
   int i,j;

   i = askForListName(name);
   
   if (i >= 0)
   {     
      j = i--;
      lists.erase(lists.begin()+j);
   }
   
   else
      Util::error(ERR_LIST_NAME);

}


void Project::addTaskToList(string name)
{
   string nameTask, date;
   int time = 0, i;

   i = askForListName(name);
   
   if (i>=0)
   {
      
      cout << T_NAME;
      getline(cin,nameTask);
      Task task(nameTask);
      
      cout << DEADLINE;
      getline(cin,date);
   
      if(task.setDeadline(date))
      { 
         cout << EXP_TIME;
         cin >> time;
         cin.get();

         if (task.setTime(time))
            lists[i].addTask(task);
      }
   }

   else 
      Util::error(ERR_LIST_NAME);
}

void Project::deleteTaskFromList(string name)
{
   string nameTask;
   int i;

   i = askForListName(name);
   
   if (i >= 0)
   {
      cout << T_NAME;
      getline(cin,nameTask);
      if (lists[i].getPosTask(nameTask) >= 0)
         lists[i].deleteTask(nameTask);
      else 
         Util::error(ERR_TASK_NAME);
   }

   else 
      Util::error(ERR_LIST_NAME);
}

void Project::toggleTaskFromList(string name)
{

   string nameTask;
   int i;

   i = askForListName(name);

   if (i >= 0)
   {
      cout << T_NAME;
      getline(cin,nameTask);
      if (lists[i].getPosTask(nameTask) >= 0)
         lists[i].toggleTask(nameTask);
      else 
         Util::error(ERR_TASK_NAME);
   }

   else 
      Util::error(ERR_LIST_NAME);

}

void Project::showMenu()
{
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

void Project::menu()
{

   string nameProject, description;
   char option;

   do
   {   
      showMenu();
      cin >> option;
      cin.get();

      switch(option)
      {

         case '1': edit();
                   break;
         case '2': addList();
                   break;
         case '3': deleteList();
                   break;
         case '4': addTaskToList();
                   break;
         case '5': deleteTaskFromList();
                   break;
         case '6': toggleTaskFromList();
                   break;
         case '7': cout << *this << endl;
                   break;
         case 'b': 
                   break;

         default:  Util::error(ERR_OPTION);
      }
   } while(option!='b');       
}

void Project::highestPriority(Date deadline,Date &priorDate, string taskName, string &priorName) const
{

   if(priorDate.year>deadline.year){

      priorDate.year = deadline.year;
      priorDate.month = deadline.month;
      priorDate.day = deadline.day;
      priorName = taskName;
   }

   if (priorDate.year == deadline.year){

      if (priorDate.month > deadline.month){
         priorDate.day = deadline.day;
         priorDate.month = deadline.month;
         priorDate.year = deadline.year;
         priorName = taskName;
      } 
      
      else if (priorDate.month == deadline.month){

         if (priorDate.day > deadline.day){
            priorDate.day = deadline.day;
            priorDate.month = deadline.month;
            priorDate.year = deadline.year;
            priorName = taskName;
         }
      }
   }

}

string Project::summary() const
{
   int countDone = 0;
   unsigned i, j;
   stringstream sum;
   int k=0;
   vector<Task> task;

   for ( i = 0; i < lists.size(); i++)
   {
      task = lists[i].getTasks();

      for (j = 0; j < task.size(); j++)
      {
         k+=1;
         if (task[j].getIsDone())
            countDone+=1;
      }
   }

   sum << "(" << getId() << ") " << getName() << " [" << countDone << "/" << k << "] \n";
   return sum.str();
}


ostream& operator<<(ostream& os, const Project &p)
{

   int timeDone = 0, totalTime = 0, numDone = 0, totalTasks = 0;
   Date priorDate;
   string priorName;
   vector <Task> task;

   priorDate.day = MAX_DAY + 1; 
   priorDate.month = MAX_MONTH;
   priorDate.year = MAX_YEAR;

   os << "Name: " << p.getName() << endl;
   if (p.getDescription()!="")
      os << "Description: " << p.getDescription() << endl;
   for (unsigned i = 0; i < p.lists.size(); i++)
   {
      os << p.lists[i];
      numDone += p.lists[i].getNumDone();
      totalTasks += p.lists[i].getNumTasks();
      timeDone += p.lists[i].getTimeDone();
      totalTime += p.lists[i].getTimeTasks();
   }

   os << "Total left: " << totalTasks - numDone
   << " ("<< totalTime - timeDone << " minutes)" << endl;

   os << "Total done: " << numDone << " ("
   << timeDone << " minutes)" << endl;

   for (unsigned i = 0; i < p.lists.size(); i++)
   {
      task = p.lists[i].getTasks();

      for (unsigned j = 0; j < task.size(); j++)
      {
         if(!task[j].getIsDone())
            p.highestPriority( task[j].getDeadline(), priorDate, task[j].getName() ,priorName); 
      }
   }

   if (priorName.length() != 0)
      {
         os << "Highest priority: " << priorName << " (" << priorDate.year << "-" 
         << priorDate.month << "-" << priorDate.day << ")" << endl;
      }
   return os;
}


















