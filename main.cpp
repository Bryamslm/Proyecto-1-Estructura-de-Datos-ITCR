#include <iostream>
using namespace std;

/*
 * Meeting management
 *      Luz Mora
 *      Bryam Lopez
 *      Estefania Perez Hidalgo
 */


//------ prototype section -----

void burnedData();
bool addAdmin(string, int, string);
struct Administrators*searchAdmin(string, int);

//------ end prototype section -----

struct Teachers{
    string fullName;
    int id;
    string gender;
    Teachers*next;
    Teachers*previous;

    Teachers(string fn, int i, string g){
        fullName=fn;
        id=i;
        gender=g;
        next=NULL;
        previous=NULL;
    }

}*firstTeacher;

struct Students{
    string fullName;
    int id;
    string gender;
    Students*next;

    Students(string fn, int i, string g){
        fullName=fn;
        id=i;
        gender=g;
        next=NULL;
    }

}*firstStudent;

struct Courses{

    string code;
}*firstCourse;

struct Administrators{

    string fullName;
    int id;
    string gender;

    Administrators*sig;
    Teachers*subListT;
    Students*subListS;
    Courses*subListC;

    Administrators(string fn, int i, string g){

        fullName=fn;
        id=i;
        gender=g;
        sig=NULL;
        subListT=firstTeacher;
        subListS=firstStudent;  //la sublista es igual a la lista general ya que es compartida
        subListC=firstCourse;

    }
}*firstAdmin;

Administrators*searchAdmin(string fullName, int id){//busca admin a ver si ya existe, retorna NULL si no está

    Administrators*temp=firstAdmin;

    while(temp != NULL){
        if(temp->fullName==fullName){//Lo busca por nombre
            cout<<"\nThe name is already part of the administrators\n"<<endl;
            return temp;
        }else if(temp->id==id){//Lo busca por ID
            cout<<"\nThe ID is already part of the administrators\n"<<endl;
            return temp;
        }
        temp=temp->sig;
    }
    return NULL; //if return NULL the admin is not

}

bool addAdmin(string fullName, int id, string gender){//función que agrega administadores a lista simple con inserción al inicio

    if(firstAdmin==NULL){//si lista de admins está vacía se agrega nuevo admin
        Administrators*nn = new Administrators(fullName, id, gender);
        firstAdmin=nn;
        return true;
    }else{
        Administrators*admin=searchAdmin(fullName, id);//si retorna  NULL el admin no existe, sino ya existe

        if(admin != NULL){//est esta el admin
            cout<<"Administrator could not be added"<<endl;

            return false;
        }else{
            Administrators*nn= new Administrators(fullName, id, gender);//crea al admin

            nn->sig=firstAdmin;
            firstAdmin=nn;      //hace inserción al inicio de lista simple

            return true;
        }
    }
}

Teachers*searchTeacher(string fullName, int id){//busca teacher a ver si ya existe, retorna NULL si no está

    Teachers*temp=firstTeacher;

    while(temp != NULL){
        if(temp->fullName==fullName){//Lo busca por nombre
            cout<<"\nThe name is already part of the teachers\n"<<endl;
            return temp;
        }else if(temp->id==id){//Lo busca por ID
            cout<<"\nThe ID is already part of the teachers\n"<<endl;
            return temp;
        }
        temp=temp->next;
    }
    return NULL; //if return NULL the teacher is not

}

bool addTeacher(string fullName, int id, string gender){//función que agrega aprofesor a lista doble con inserción al inicio

    if(firstTeacher==NULL){//si lista de profes está vacía se agrega nuevo profe
        Teachers*nn = new Teachers(fullName, id, gender);
        firstTeacher=nn;
        return true;
    }else{
        Teachers*teacher=searchTeacher(fullName, id);//si retorna  NULL el teacher no existe, sino ya existe

        if(teacher != NULL){//esta el teacher
            cout<<"Teacher could not be added"<<endl;

            return false;
        }else{
            Teachers*nn= new Teachers(fullName, id, gender);//crea al admin

            firstTeacher->previous=nn;
            nn->next=firstTeacher;
            firstTeacher=nn;

            return true;
        }
    }
}

Students*searchStudent(string fullName, int id){//busca student a ver si ya existe, retorna NULL si no está

    Students*temp=firstStudent;

    while(temp != NULL){//do while por si hay solo un elemnto en lista
        if (temp->fullName == fullName) {
            cout<<"\nThe name is already part of the students\n"<<endl;
            return temp;
        }
        if(temp->id == id){
            cout<<"\nThe ID is already part of the students\n"<<endl;
            return temp;
        }
        temp=temp->next;
    }
    return NULL;

}

bool addStudent(string fullName, int id, string gender){//función que agrega estudiante a lista circular con inserción ordenada

    if(firstStudent==NULL){//si lista de estudianes está vacía se agrega nuevo estudiante
        Students*nn = new Students(fullName, id, gender);
        firstStudent=nn;
        return true;
    }else{
        Students*student = searchStudent(fullName, id);//si retorna  NULL el estudiante no existe, sino ya existe

        if(student != NULL){//esta el estudiante
            cout<<"Student could not be added"<<endl;
            return false;

        }else{
            Students*nn= new Students(fullName, id, gender);//crea al estudiante

            Students*temp=firstStudent;

            while(temp != NULL){//compara el id del nn con el anterios temp y temp->next

                if(nn->id >=temp->id &&  temp->next == NULL){
                    temp->next = nn;
                    return true;
                }
                if(nn->id >=temp->id && nn->id <= temp->next->id){
                    nn->next = temp->next;
                    temp->next = nn;
                    return true;
                }

                temp = temp->next;
            }

            if(nn->id <= firstStudent->id){//si es mayor al primero
                nn->next=firstStudent;
                firstStudent=nn;
                return true;
            }

        }
    }
}

void imprime(){
    Students*temp=firstStudent;

    while(temp != NULL){
        cout<<temp->id<<endl;
        temp=temp->next;
    }
}

void updateTeachersList(){//Actializa en firstTeacher en cada admin
    /*
     * Cuando un profesor se agrega al inicio de lista profesores o se agrega por primera vez
     * la lista esta desactualizada por eso existe esta función para actualizar las sublista a
     * los datos exixtentes actualmente
     * Solo se llama en casos específicos y no siempre que se agregue un profesor
     */
    Administrators*temp=firstAdmin;

    while(temp != NULL){
        temp->subListT=firstTeacher;
        temp=temp->sig;
    }
}
void updateStudentsList(){//Actializa en firstStudent en cada admin
    /*
     * Cuando un estudiante se agrega al inicio de lista estudiantes o se agrega por primera vez
     * la lista esta desactualizada por eso existe esta función para actualizar las sublista a
     * los datos exixtentes actualmente
     * Solo se llama en casos específicos y no siempre que se agregue un estudiante
     */
    Administrators*temp=firstAdmin;

    while(temp != NULL){
        temp->subListS=firstStudent;
        temp=temp->sig;
    }
}

void burnedData(){

    //agergar admins

    addAdmin("Veronica Brenes", 1, "Female");
    addAdmin("Christian Gonzales", 2, "Male");
    addAdmin("Monica Speer", 3, "Female");
    addAdmin("Julio Cesar", 4, "Male");
    addAdmin("Sonia Rojas", 5, "Female");

    //agergar profes

    addTeacher("Lonera Picado", 1, "Female");
    addTeacher("Abel Mendez", 2, "Male");
    addTeacher("Rocio Aguilar", 3, "Female");
    addTeacher("Vera Gamboa", 4, "Female");
    addTeacher("Karina Gonzales", 5, "Female");

    //agregar estudiantes

    addStudent("Ovidio Martinez", 5, "Male");
    addStudent("Estefania Perez", 2, "Female");
    addStudent("Luz Mora", 3, "Female");
    addStudent("Bryam Lopez", 1, "Male");
    addStudent("Josue Orozco", 4, "Male");

}

int main(){

    burnedData();
    imprime();
    updateTeachersList();
    updateStudentsList();


    return 0;
}
