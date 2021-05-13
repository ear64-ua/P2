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

   for (unsigned i = 0; i < lists.size();i++){
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
   while (name.length()==0)
   {
      cout << P_NAME;
      getline(cin,name);

      if (name.length() == 0)
         Util::error(ERR_EMPTY);

      else 
         this->name=name;
         
   }

   if (description.length()==0)
   {
      cout << P_DESC;
      getline(cin,description);
   }
}

void Project::addList(string name)
{
   List list(name);

   while (name.length()==0)
   {
      cout << L_NAME;
      getline(cin,name);
      list.setName(name);
   }

   lists.push_back(list);
}

void Project::deleteList(string name)
{
   unsigned i,j;
   bool found = false;
   List list(name);

   while (name.length()==0)
   {
      cout << L_NAME;
      getline(cin,name);
      list.setName(name);
   }

   for(i = 0; i < lists.size(); i++)
   {
      if (this->lists[i].getName()==name)
      {
         j = i--;
         lists.erase(lists.begin()+j);
         found = true;
      }
   }
   
   if (!found)
      Util::error(ERR_LIST_NAME);

}


void Project::addTaskToList(string name)
{
   List list(name);
   string nameTask, date;
   int time = 0, i;
   bool found = false;
   unsigned j;

   while (name.length()==0)
   {
      cout << L_NAME;
      getline(cin,name);
   }

   for ( j = 0; j < lists.size();j++)
   {
      if (this->lists[j].getName()==name)
      {
         found = true;
         break;
      }
   }
   
   if (found)
   {
      i = getPosList(name);
      
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
      }

      if (task.setTime(time))
      {
         lists[j].addTask(task);
      }
   }

   else 
      Util::error(ERR_LIST_NAME);
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
         {
            countDone+=1;
   	     }
   	  }
   }

   sum << "(" << getId() << ") " << getName() << " [" << countDone << "/" << k << "]";
   return sum.str();
}

ostream& operator<<(ostream& os, const Project &p)
{

   cout << p.getName() << endl;
   if (p.getDescription().length()!=0)
      cout << p.getDescription() << endl;
   for (unsigned i = 0; i < p.lists.size(); i++)
   {
      cout << p.lists[i];
   }

   return os;
}


















