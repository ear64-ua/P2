#include "List.h"
#include "Util.h"


List::List(string name)
{
   if (name.lenght()==0)
      Util::error(ERR_EMPTY);
   else
      this->name=name;
}

unsigned List::getNumTasks()
{
   unsigned i;

   for ( i = 0; this->tasks.size() < i ;i++){}

   return i;
}

unsigned List::getNumDone()
{
   unsigned n = 0;
	
   for (unsigned i = 0; this->tasks.size() < i ;i++){
      if (tasks[i].isDone)
         n++;
   }

   return n;
}

int List::getTimeTasks()
{
   int time = 0;
	
   for (unsigned i = 0; this->tasks.size() < i ;i++){
		
      time+=tasks[i].time;
   }
   
   return time;
}

int List::getTimeTasks()
{   
   int time = 0;

   for (unsigned i = 0; this->tasks.size() < i ;i++){
      if (tasks[i].isDone)
         time+=tasks[i].time;
   }

   return time;
}

int List::getPosTask()
{   

   for (unsigned i = 0; this->tasks.size() < i ;i++){
      if (this->name=tasks[i].name)
         return i;
   }

   return -1;
}

bool List::setName(string name)
{
   if (name.lenght()==0)
   {
      Util::error(ERR_EMPTY);
      return false;
   }

   else 
      this->name=name;
}


















