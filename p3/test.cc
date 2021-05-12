//Esta funcion es para probar las diferentes funciones de cada clase
#include <iostream>
#include <vector>
#include "Task.h"
#include "List.h"
#include "Project.h"

using namespace std;

int main(){
    
    string nombre;
    string nomblista;
    string isdone;
    vector <Task> t;

    cout <<"Introduzca nombre de lista: ";
    getline(cin,nomblista);
    List l1(nomblista);
    
    for(int i = 0; i<4;i++){
    cout << "Introduzca nombre de tarea: ";
    getline(cin,nombre);
    Task t1(nombre);
    l1.addTask(t1);
    }

    t = l1.getTasks();

   for(int i = 0; i<t.size();i++){
        cout << "El nombre de la tarea " << t[i].getName() << endl;
    }

    cout << "Introduzca el nombre de la tarea a cambiar a hecha/no hecha: " ;
    getline(cin,isdone);
    l1.toggleTask(isdone);
    cout << l1;

    //PROJECT:
    /*Project p1(nproy,"");
    cout << p1.getId()<<", "<<p1.getName()<<", "<<p1.getDescription()<<endl;
    cout <<"Introduzca nombre lista 2: ";
    getline(cin,nomblista);
    List l2(nomblista);
    cout<< l2.getName()<<endl;
    */

    return 0;
}