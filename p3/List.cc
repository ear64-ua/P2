#include "List.h"
#include "Util.h"


List::List(string name)
{
   if (name.length()==0)
      throw ERR_EMPTY;
   else
      this->name=name;
}


unsigned List::getNumDone() const
{
   unsigned n = 0;
	
   for (unsigned i = 0; i < getNumTasks() ;i++) // recorremos el vector y si está hecho, se suma
   {                                            // 1 al contador
      if (tasks[i].getIsDone())
         n++;
   }

   return n;
}

int List::getTimeTasks() const
{
   int time = 0;
	
   for (unsigned i = 0; i < getNumTasks() ;i++)
   {
		
      time+=tasks[i].getTime();
   }
   
   return time;
}

int List::getTimeDone() const
{   
   int time = 0;

   for (unsigned i = 0; i < getNumTasks() ;i++)  // por cada tarea hecha, se le va sumando 
   {                                             // el tiempo de cada una
      if (tasks[i].getIsDone())
         time+=tasks[i].getTime();
   }

   return time;
}

int List::getPosTask(string name) const
{   

   for (unsigned i = 0; i < getNumTasks() ;i++)  // localizamos la posición en la que se encuentra 
   {                                             // la tarea
      if (tasks[i].getName()==name)
         return i;
   }

   return -1;
}

bool List::setName(string name)
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

void List::addTask(const Task& task)
{
   tasks.push_back(task);
}

bool List::deleteTask(string name)
{
   unsigned j;
   bool found = false;

   for(unsigned i = 0; i < getNumTasks(); i++) // según el nombre que se nos pase, eliminará dicha tarea
   {
      if (tasks[i].getName()==name)
      {
         j = i--;
         tasks.erase(tasks.begin()+j);
         found = true;
      }
   }

   if (found)
      return true;

   return false;
}


bool List::toggleTask(string name)
{

   bool found = false;
   for(unsigned i = 0; i < getNumTasks(); i++)
   {
      if (tasks[i].getName()==name)
      {
         tasks[i].toggle();
         found = true;
      }
   }

   if (found)
      return true;
   else
      return false;
}

ostream& operator<<(ostream& os, const List &list)
{
   
   os << list.getName() << endl;

   for (unsigned i = 0; i < list.getNumTasks(); i++)
   {
      if (!list.tasks[i].getIsDone())
         os << list.tasks[i];
   }

   for (unsigned i = 0; i < list.getNumTasks(); i++)
   {
      if (list.tasks[i].getIsDone())
         os << list.tasks[i];
   }

   return os;
}


















