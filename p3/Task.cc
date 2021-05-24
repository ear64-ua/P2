#include "Task.h"
#include "Util.h"
#include <sstream> 

const int MAX_TIME = 180;
const int MIN_TIME = 1;
const int MIN_DAY = 1;
const int MAX_YEAR = 2100;
const int MIN_YEAR = 2000;

Task::Task(string name)
{
   this->name=name;

   deadline.day = 1;
   deadline.month = 1;
   deadline.year = 2000;
   isDone= false;
   time = 1;
}

void Task::setName(string name)
{
    this->name=name;
}

bool Task::setDeadline(string deadline)
{  
   int k = 0;
   Date date;
   int bisiesto = 28;
   string aux;
   date.day = date.month = date.year = 0;
   
   stringstream ss(deadline);
   while (getline(ss,aux,'/'))    // separamos cada valor de la fecha en sus correspondientes 
   {                             // variables
      k++;
      if (k==1)
         date.day=stoi(aux);
      if (k==2)
         date.month=stoi(aux);
      if (k==3)
         date.year=stoi(aux);
   }

   if((date.year % 4 == 0 && date.year % 100 != 0) || date.year % 400 == 0) 
      bisiesto = 29;

   if (date.year >= MIN_YEAR && date.year <= MAX_YEAR){
      if (date.month > 0 && date.month < 13){
         // meses del año con 31 o 30, y si es bisiesto febrero con 28 o 29 días
         if (date.day >= MIN_DAY && (((date.month == 1 || date.month == 3 || date.month == 5 || date.month == 7 
            || date.month == 8 || date.month == 10 || date.month == 12) && date.day <= 31)          
            || ((date.month == 4 || date.month == 6 || date.month == 9 || date.month == 11) && date.day <= 30) 
            || (date.month == 2 && date.day <= bisiesto))){
            
            this->deadline = date;
            return true;
          }
       }
   }

   
   Util::error(ERR_DATE);
   
   return false;

}

bool Task::setTime(int time)
{
   if (time >= MIN_TIME && time <= MAX_TIME)
   {
      this->time=time;
      return true;
   }

   else
   {
      Util::error(ERR_TIME);
      return false;
   }
}


void Task::toggle()
{
   isDone= !isDone;
}

ostream& operator<<(ostream& os, const Task &task)
{
   os << "[" << (task.isDone ? "X" : " ") << "] "
   << "(" << task.time << ") ";

   os << task.deadline.year << "-" << task.deadline.month << "-" << task.deadline.day
   << ":" << task.name << endl;

   return os;
}
