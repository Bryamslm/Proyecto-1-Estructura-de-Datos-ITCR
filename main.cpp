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
struct Teachers*searchTeacher(string, int);
bool addTeacher(string, int, string);
struct Students*searchStudent(string, int);
bool addStudent(string, int, string);
struct Courses*searchCourse(string);
bool addCourse(string, string, int);
void updateTeachersList();
void updateStudentsList();
void imprime();
struct LinkTeacher;
struct Students;
struct Courses;
struct Administrators;
struct LinkTeacher;
struct LinkStudent;
struct Meeting;

//------ end prototype section -----


struct Teachers{
    string fullName;
    int id;
    string gender;
    Teachers*next;
    Teachers*previous;
    LinkTeacher*link;

    Teachers(string fn, int i, string g){
        fullName=fn;
        id=i;
        gender=g;
        next=NULL;
        previous=NULL;
        link=NULL;
    }

}*firstTeacher;

struct Students{
    string fullName;
    int id;
    string gender;
    Students*next;
    LinkStudent*link;

    Students(string fn, int i, string g){
        fullName=fn;
        id=i;
        gender=g;
        next=NULL;
        link=NULL;
    }

}*firstStudent;

struct Courses{
    string name;
    string code;
    int credits;
    Courses*next;

    Courses(string n, string c, int cred) {

        name=n;
        code=c;
        credits=cred;
        next=NULL;
    }
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

struct LinkTeacher{

    LinkTeacher*next;
    Courses*course;
    int group;
    Meeting*firstMeeting;

    LinkTeacher(int g){
        next=NULL;
        course=NULL;
        group=g;
        firstMeeting=NULL;
    }

};
struct LinkStudent{

    LinkStudent*next;
    Courses*course;
    int group;

    LinkStudent(int g){
        next=NULL;
        course=NULL;
        group=g;
    }

};

struct Meeting{

    Meeting*next;
    int id;
    int hour;
    int minute;
    int day;
    int month;
    int year;
    string meetingTitle;

    Meeting(int iD, int hourr, int minutee, int dayy, int monthh, int yearr, string title){

        id=iD;
        hour=hourr;
        minute=minutee;
        day=dayy;
        month=monthh;
        year=yearr;
        meetingTitle=title;
        next=NULL;

    }

};

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

Teachers*searchTeacher(int id){//busca teacher a ver si ya existe, retorna NULL si no está

    Teachers*temp=firstTeacher;

    while(temp != NULL){
        if(temp->id==id){//Lo busca por ID
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
        Teachers*teacher=searchTeacher(id);//si retorna  NULL el teacher no existe, sino ya existe

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

Students*searchStudent(int id){//busca student a ver si ya existe, retorna NULL si no está

    Students*temp=firstStudent;

    while(temp != NULL){//do while por si hay solo un elemnto en lista
        if(temp->id == id){
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
        Students*student = searchStudent(id);//si retorna  NULL el estudiante no existe, sino ya existe

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

Courses*searchCourse(string code){//busca teacher a ver si ya existe, retorna NULL si no está

    Courses*temp=firstCourse;

    do{
        if(temp->code == code){
            return temp;
        }
        temp=temp->next;
    } while(temp != firstCourse);

    return NULL;
}

bool addCourse(string name, string code, int credits){//función que agrega aprofesor a lista doble con inserción al inicio

    if(firstCourse==NULL){//si lista de profes está vacía se agrega nuevo profe
        Courses*nn = new Courses(name, code, credits);
        firstCourse=nn;
        firstCourse->next=firstCourse; //se hace la lista circular
        return true;
    }else{
        Courses*course=searchCourse(code);//si retorna  NULL el teacher no existe, sino ya existe

        if(course != NULL){//esta el teacher
            cout<<"Course could not be added"<<endl;

            return false;
        }else{
            Courses*nn= new Courses(name, code, credits);//crea al admin

            Courses*temp= firstCourse;

            while(temp->next != firstCourse){
                temp=temp->next;
            }
            temp->next=nn;
            nn->next=firstCourse;
            return true;
        }
    }
}

void imprime(){
    Courses*temp=firstCourse;

    do{
        cout<<temp->name<<endl;
        temp=temp->next;
    }while(temp != firstCourse);
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

bool relateTeacherCourse(int idTeacher, string codeCourse, int group){
    Teachers*teacher=searchTeacher(idTeacher);
    if(teacher==NULL){
        cout<<"\nThe teacher is not in the list, the link cannot be made"<<endl;
        return false;
    }
    Courses*course=searchCourse(codeCourse);
    if(course==NULL){
        cout<<"\nThe course is not in the list, the link cannot be made"<<endl;
        return false;
    }

    LinkTeacher*nn=new LinkTeacher(group);
    nn->course=course;

    LinkTeacher*temp=teacher->link;
    if(temp==NULL){
        teacher->link=nn;
        return true;
    }else{
       do{
           /*
            * Este ciclo al mismo tiempo que busca posicionarse en la ultima posición de la lista para agregar el
            * nuevo curso al profesor también comprueba que el curso y grupo no se metan de manera repetida al
            * mismo profesor, por eso es un ciclo do while
            */
            if(temp->course->code == nn->course->code && temp->group == nn->group){
                cout<<"This teacher has already assigned this group and course"<<endl;
                return false;
            }
            if(temp->next==NULL){
                break;
            }
            temp=temp->next;
        } while(temp != NULL);
        temp->next=nn;

        return true;
    }
}

bool relateStudentCourse(int idStudent, string codeCourse, int group){
    Students*student=searchStudent(idStudent);//se busca a estudiante en lista
    if(student==NULL){
        cout<<"\nThe student is not in the list, the link cannot be made"<<endl;
        return false;
    }
    Courses*course=searchCourse(codeCourse);//se busca curso en lista
    if(course==NULL){
        cout<<"\nThe course is not in the list, the link cannot be made"<<endl;
        return false;
    }

    bool courseFoud=false;//variable para comprobar si el curso está siendo impartido

    Teachers*tempT=firstTeacher;
    while(tempT != NULL){
        /*
         * Este ciclo comprueba que el curso esté siendo impartido por un profesor para poder asignarselo a un estudiante
         * si el curso sí está siendo impartido la variable courseFound cambia a true, si no cambia al terminar todo
         * el ciclo while el curso no está siendo impartido, aunque esté en la lista de curso
         */
        LinkTeacher*tempL=tempT->link;
        while(tempL != NULL){
            if(tempL->course == course && tempL->group == group){
                courseFoud=true;
                break;
            }
            tempL=tempL->next;
        }
        if(courseFoud){
            break;
        }
        tempT=tempT->next;

    }
    if(courseFoud==false){
        cout<<"\nThe course cannot be added because no teacher is teaching it"<<endl;
        return false;
    }

    LinkStudent*nn=new LinkStudent(group);
    nn->course=course;

    LinkStudent*temp=student->link;
    if(temp==NULL){
        student->link=nn;
        return true;
    }else{
        do{
            /*
             * Este ciclo al mismo tiempo que busca posicionarse en la ultima posición de la lista para agregar el
             * nuevo curso al estudiante también comprueba que el curso y grupo no se metan de manera repetida al
             * mismo estudiante, por eso es un ciclo do while
             */
            if(temp->course->code == nn->course->code && temp->group == nn->group){
                cout<<"This student has already assigned this group and course"<<endl;
                return false;
            }
            if(temp->next==NULL){
                break;
            }
            temp=temp->next;
        } while(temp != NULL);
        temp->next=nn;

        return true;
    }
}

bool meetingTeacher(int idTeacher, string codeCourse, int idMeeting, int hour, int minute, int day, int month, int year, string titleMeeting){

    Teachers*teacher=searchTeacher(idTeacher);//si retorna  NULL el teacher no existe, sino ya existe

    if(teacher == NULL){//esta el teacher
        cout<<"Teacher not found"<<endl;

        return false;
    }

    Teachers*tempTeacher= firstTeacher;
    while(tempTeacher != NULL){

        /*
         * Este ciclo recorre cada profesor de la lista
         */

        LinkTeacher*tempLink=tempTeacher->link;
        while(tempLink != NULL){

            /*
             * Este ciclo recorre cada enlace a curso de profesor
             */

            Meeting*tempMeeting=tempLink->firstMeeting;
            while(tempMeeting != NULL){
                /*
                 * Este ciclo recorre cada reunion de de cada enlace de curso de profesor
                 */

                if(tempMeeting->id == idMeeting){

                    /*
                     * si el ID de la reunion es igual al ID que se quiere usar, es una restricción por tanto retorna false
                     * no se asigna la reuinión
                     */
                    cout<<"\nThere is another meeting with this ID assigned"<<endl;
                    return false;
                }
                tempMeeting=tempMeeting->next;
            }
            tempLink=tempLink->next;
        }
        tempTeacher=tempTeacher->next;
    }

    LinkTeacher*temp= teacher->link;
    while(temp != NULL){

        /*
         * este ciclo recorre cada enlace de curso en busca del curso donde de debe asignar la reunion, sino encuentra
         * el enlace del curso es porque el curso no esta siendo impartido, por lo tanto no se puede asignar la reunion
         */

        if(temp->course->code == codeCourse){

            Meeting*nn= new Meeting(idMeeting, hour, minute, day, month, year, titleMeeting);

            if(temp->firstMeeting==NULL){
                teacher->link->firstMeeting=nn;
                return true;
            }else{
                Meeting*temp2=temp->firstMeeting;
               do{
                    /*
                     * Este ciclo a parte de recorrer los enlaces de cursos verifica que el profesor no tenga otra
                     * reunión a la misma hora, el mismo día, mes y año
                     */
                    if(temp2->year==nn->year && temp2->month == nn->month && temp2->day==nn->day && temp2->hour==nn->hour && temp2->minute==nn->minute){
                        cout<<"\nThe meeting cannot be assigned because this teacher already has a meeting at the same"<<
                        " time, day, month and year"<<endl;
                        return false;
                    }
                    if(temp2->next==NULL){
                        break;
                    }
                    temp2=temp2->next;
                }while(temp2 != NULL);
                temp2->next=nn;
                return true;
            }
        }
        temp=temp->next;
    }
    cout<<"The meeting cannot be assigned to this course because the teacher does not teach the course"<<endl;
    return false;
}

void burnedData(){

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

    //agregar cursos

    addCourse("Estructuta de Datos", "CA1101", 3);
    addCourse("Programacion Orientada a Objetos", "CA1298", 3);
    addCourse("Calculo Diferencial e Integral", "MA1226", 4);
    addCourse("Matematicas Discretas", "MA7878", 4);
    addCourse("Arquitectura de Computadores", "CA1103", 4);
    addCourse("Introduccion a la Programacion", "CA1558", 3);

    //agergar admins

    addAdmin("Veronica Brenes", 1, "Female");
    addAdmin("Christian Gonzales", 2, "Male");
    addAdmin("Monica Speer", 3, "Female");
    addAdmin("Julio Cesar", 4, "Male");
    addAdmin("Sonia Rojas", 5, "Female");

    //Relacionar profesor con curso

    relateTeacherCourse(5, "MA1226", 51);
    relateTeacherCourse(5, "MA7878", 53);
    relateTeacherCourse(2, "CA1558", 50);
    relateTeacherCourse(1, "CA1101", 51);
    relateTeacherCourse(3, "CA1103", 52);
    relateTeacherCourse(4, "CA1298", 52);

    //Relacionar estudiante con curso

    relateStudentCourse(5, "MA1226", 51);
    relateStudentCourse(2, "MA7878", 53);
    relateStudentCourse(3, "CA1558", 50);
    relateStudentCourse(4, "CA1101", 51);
    relateStudentCourse(1, "CA1103", 52);
    relateStudentCourse(1, "CA1298", 52);

    //Asignar reuinión a un profesor

    meetingTeacher(5, "MA1226",1,  13, 10, 29, 03, 2020,  "clase magistral");
    meetingTeacher(5, "MA1226",2,  7, 50, 29, 03, 2020,  "clase magistral");
    meetingTeacher(4, "CA1298",3,  7, 50, 29, 03, 2020,  "clase magistral");
    meetingTeacher(3, "CA1103",4,  7, 50, 29, 03, 2020,  "clase magistral");
    meetingTeacher(2, "CA1558",5,  7, 50, 29, 03, 2020,  "clase magistral");
    meetingTeacher(1, "CA1101",6,  7, 50, 29, 03, 2020,  "clase magistral");

}


void menu(){
    int hora=0;
    char c;
    int minutos=0;
    char d;
    int dia = 0;
    int mes = 0;
    int anio = 0;
    char a;
    char b;
    while(true) {
        cout<<"Ingrese la hora actual (ejemplo: 15:20/29/03/2021): " ;
        cin >> hora >> c >> minutos >> d >> dia >> a >> mes >> b >> anio;

        if (hora >= 0 && hora <= 23 && c == ':' && minutos >= 0 && minutos <= 59 && d == '/' && dia > 0 && dia < 32 &&
            a == '/' && mes > 0 && mes < 13 && b == '/' && anio > 2020 && anio < 2022) {

            cout << "\nLa fecha es correcta" << endl;
            break;

        }else{
            cout << "Incorrecto el formato: HHHH/DD/MM/AAAA";
        }
    }
}


int main() {

    burnedData();

    //menu();

    /*
    updateTeachersList();
    updateStudentsList();
    */

    return 0;
}