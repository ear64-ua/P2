#include "ToDo.h"
#include "Util.h"
#include <sstream>

int ToDo::nextId = 1;


ToDo::ToDo(string name)
{

   if (name.length()==0)
      throw ERR_EMPTY;
   else
      this->name=name;
}

int ToDo::getPosProject(string name) const
{   

   for (unsigned i = 0; i < projects.size();i++)
   {
      if (projects[i]->getName()==name)
         return i;
   }

   return -1;
}

int ToDo::getPosProject(int id) const
{   

   for (unsigned i = 0; i < projects.size();i++)
   {
      if (projects[i]->getId()==id)
         return i;
   }

   return -1;
}

bool ToDo::setName(string name)
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

void ToDo::addProject(Project *project)
{

   if (name.length()!=0)
   {
      if (getPosProject(name)==-1)
      {
         project->setId(nextId);
         nextId++;
         projects.push_back(project);
      }
      else 
         throw ERR_PROJECT_NAME;
   }

   while (name.length()==0)
   {
      cout << P_NAME;
      getline(cin,name);
   
      if (getPosProject(name)==-1)
         projects.push_back(project);
         
      else 
         throw ERR_PROJECT_NAME;
   }

}

void ToDo::deleteProject(int id)
{
   int i,j;
   
   if (id == 0)
   {
      cout << P_ID;
      cin >> id;
   }

   i = getPosProject(id);
   
   if (i >= 0)
   {     
      j = i--;
      projects.erase(projects.begin()+j);
   }
   
   else
      Util::error(ERR_ID);

}

void ToDo::setProjectDescription(string name, string description)
{

   int i;

   i = getPosProject(name);

   if (i>=0)

      projects[i]->setDescription(description); 

   else 
      Util::error(ERR_PROJECT_NAME);

}

void ToDo::projectMenu(int id)
{

   int i;

   if (id == 0)
   {
      cout << P_ID;
      cin >> id;
      cin.get();
   }

   i = getPosProject(id);

   if (i >= 0)

      projects[i]->menu();

   else 
      Util::error(ERR_ID);

}


ostream& operator<<(ostream& os, const ToDo &toDo)
{

   for(unsigned i = 0; i < toDo.projects.size(); i++)
   {
      cout << toDo.projects[i]->summary();
   }

   return os;
}


















