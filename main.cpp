#include <iostream>
#include <conio.h>
#include <string.h>
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
struct SublistAssistance;

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
    SublistAssistance*sublistAssistance;

    LinkStudent(int g){
        next=NULL;
        course=NULL;
        group=g;
        sublistAssistance=NULL;
    }

};

struct SublistAssistance{
    int id;
    SublistAssistance*next;

    SublistAssistance(int iD){
        id=iD;
        next=NULL;
    }
};

struct Meeting{

    Meeting*next;
    int id;
    int hour;
    int minute;
    int hourEnd;
    int minuteEnd;
    int day;
    int month;
    int year;
    string meetingTitle;

    Meeting(int iD, int hourr, int minutee, int hourEndd, int minuteEndd,int dayy, int monthh, int yearr, string title){

        id=iD;
        hour=hourr;
        minute=minutee;
        hourEnd=hourEndd;
        minuteEnd=minuteEndd;
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

            nn->next=firstTeacher;
            firstTeacher->previous=nn;
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

bool meetingTeacher(int idTeacher, string codeCourse, int idMeeting, int hour, int minute, int hourE, int minuteE,int day, int month, int year, string titleMeeting){

    if(hourE< hour){
        cout<<"\nThe end time must be greater than the start time"<<endl;
        return false;
    }else if(hourE== hour && minuteE < minute){
        cout<<"\nThe end time must be greater than the start time"<<endl;
        return false;
    }

    Teachers*teacher=searchTeacher(idTeacher);//si retorna  NULL el teacher no existe, sino ya existe

    if(teacher == NULL){//esta el teacher
        cout<<"Teacher not found"<<endl;

        return false;
    }

    Teachers*tempTeacher= firstTeacher;

    while(tempTeacher != NULL){


        /*
         * Ciclo para buscar que ID no este asignado a otra reunion
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

            Meeting*nn= new Meeting(idMeeting, hour, minute, hourE, minuteE, day, month, year, titleMeeting);

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

                    //comprueba que no se programe una reunionen el mismo tiempo que otra
                    if(temp2->year==nn->year && temp2->month == nn->month && temp2->day==nn->day && temp2->hour==nn->hour && temp2->minute==nn->minute){
                        cout<<"\nThe meeting cannot be assigned because this teacher already has a meeting at the same"<<
                        " time, day, month and year"<<endl;
                        return false;
                    }
                    //comprueba que no se programe una reunion cuando otra estará en curso
                   if(temp2->year==nn->year && temp2->month == nn->month && temp2->day==nn->day && temp2->hourEnd >= nn->hour && temp2->minuteEnd > nn->minute){
                       cout<<"\nYou cannot schedule the meeting because you will be in another meeting at that time"<<endl;
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


int anio=2021;
int mes=04;
int dia=04;
int hora=17;
int minuto=00;

bool meetingStudent(int idStudent, string codeCourse, int courseGroup, int idMeeting){
    Students*student=searchStudent(idStudent);
    if(student==NULL){
        cout<<"\nStudent not found"<<endl;
        return false;
    }
    LinkStudent*temp=student->link;
    while(temp != NULL){
        /*
         * Este ciclo busca el enlace que tiene el curso y grupo para registrar la asistencia
         */
        if(temp->course->code==codeCourse && temp->group==courseGroup){
            Teachers*temp2=firstTeacher;
            while(temp2 != NULL){
                /*
                 * Este ciclo recorre la lista de profesores
                 */
                LinkTeacher*temp3=temp2->link;
                while(temp3 != NULL){
                    /*
                     * este ciclo recorre la lista de enlace del profesor
                     */
                    Meeting*temp4=temp3->firstMeeting;
                    while(temp4 != NULL){
                        /*
                         * este ciclo recorre la lista de reuniones que está en cada enlace de cada profesor
                         */
                        if(temp4->id==idMeeting){
                            /*
                             * si el id de la reuion es igual al pasado por parametro sí se asistió
                             */
                            if(temp4->year > anio) {
                                cout << "1Attendance cannot be added because the meeting has not passed yet" << endl;
                                return false;
                            }
                            if(temp4->month > mes) {
                                cout << "2Attendance cannot be added because the meeting has not passed yet" << endl;
                                return false;
                            }
                            if(temp4->month == mes && temp4->day > dia) {
                                cout << "3Attendance cannot be added because the meeting has not passed yet" << endl;
                                return false;
                            }
                            if(temp4->day == dia && temp4->hour > hora) {
                                cout << "4Attendance cannot be added because the meeting has not passed yet" << endl;
                                return false;
                            }
                            if(temp4->hour == hora && temp4->minute > minuto) {
                                cout << "5Attendance cannot be added because the meeting has not passed yet" << endl;
                                return false;
                            }

                            SublistAssistance* nn=new SublistAssistance(idMeeting);
                            if(student->link->sublistAssistance==NULL){
                                student->link->sublistAssistance=nn;
                                return true;
                            }else{
                                SublistAssistance*temp5=student->link->sublistAssistance;

                                while(temp5->next != NULL){
                                    temp5=temp5->next;
                                }
                                temp5->next=nn;
                                return true;
                            }
                        }
                        temp4=temp4->next;
                    }
                    temp3=temp3->next;
                }
                temp2=temp2->next;
            }

        }
        temp=temp->next;
    }
    /*
     * si se llega hasta aquí es porque no se encontro un el id de reunion por lo tanto no se participó
     */
    cout<<"\nThe student did not attend the meeting"<<endl;
    return false;
}
void ModifyTeacher(int id){

    Teachers*teacher = searchTeacher(id);
    if(teacher==NULL){
        cout<<"\nTeacher not found"<<endl;
        return;
    }

    string option;
    cout<<"\nThis is the information of this teacher:"<<endl;

    cout<<"Full name: "<<teacher->fullName<<"\nGender: "<<teacher->gender<<"\nId: "<<teacher->id<<endl;

    cout<<"What do you want to modify?\n1- Full name\n2- Gender\n3- ID"<<endl;

    cout<<"Select an option: ";

    cin>>option;

    if(option=="1"){

        string name;
        cout<<"\nWrite new full name: ";


        teacher->fullName=name;

        cout<<"\nModification successful!"<<endl;
        return;
    }else if(option=="2"){
        string gender;
        cout<<"\nWrite new gender: ";
        cin>>gender;

        teacher->gender=gender;

        cout<<"\nModification successful!"<<endl;

        return;
    }else if(option=="3"){

        int newId;

        while(true) {
            //Miestras el ID no sea válido se pedirá
            cout << "\nWrite new ID: ";
            cin >> newId;
            Teachers *teacher2 = searchTeacher(newId);
            if (teacher2 == NULL) {
                teacher->id=newId;
                cout<<"\nModification successful!"<<endl;
                return;
            }
            cout << "\nThis ID is not available, please try another" << endl;
        }


    }
}
bool deleteTeacher(int id){
    Teachers*teacher= searchTeacher(id);
    if(teacher==NULL) {
        cout << "Teacher not found" << endl;
        return false;
    }
    if(firstTeacher==teacher){
        //Si el que se debe borrar es el primero de lista, solo se hace que el siguiente en previos apunte a NULL
        // y se redefine el firstTeacher como el segundo de la lista :)
        Teachers*temp=firstTeacher->next;
        temp->previous=NULL;
        firstTeacher=temp;
        cout<<"\nDelete successful! first"<<endl;
        return true;
    } else if(teacher->next==nullptr){//Con el NULL no sirve, CLion me lo autocorrigió puso nullptr y sirvió
        cout<<"\nend";
        //Si el que se debe borrar es el último de lista, solo se hace que el que está de penultimo apunte a NULL
        Teachers*temp2=teacher->previous;
        temp2->next=NULL;
        cout<<"\nDelete successful! first last"<<endl;
        return true;
    }else{
        //Si el que se debe borrar tiene anterior y siguiente diferentes de NULL, solo se hace que el anterior
        //apunte en next al que está apuntando el que se va a borrar en siguiente y ese siguinte en previous apunte
        //al que está antes del que se va a borrar, basicamente se deja de apuntar al que se va a borrar
        Teachers*temp3=teacher->previous;
        Teachers*temp4=teacher->next;
        temp3->next=temp4;
        temp4->previous=temp3;
        cout<<"\nDelete successful! first central"<<endl;
        return true;
    }
}
void ModifyStudent(int id){

    Students*student= searchStudent(id);

    if(student==NULL){
        cout<<"\nTeacher not found"<<endl;
        return;
    }

    string option;
    cout<<"\nThis is the information of this student:"<<endl;

    cout<<"Full name: "<<student->fullName<<"\nGender: "<<student->gender<<"\nId: "<<student->id<<endl;

    cout<<"What do you want to modify?\n1- Full name\n2- Gender\n3- ID"<<endl;

    cout<<"Select an option: ";

    cin>>option;

    if(option=="1"){
        string name;
        cout<<"\nWrite new full name: ";


        student->fullName=name;

        cout<<"\nModification successful!"<<endl;

        return;
    }else if(option=="2"){
        string gender;
        cout<<"\nWrite new gender: ";
        cin>>gender;

        student->gender=gender;

        cout<<"\nModification successful!"<<endl;

        return;
    }else if(option=="3"){

        int newId;

        while(true) {
            //Miestras el ID no sea válido se pedirá
            cout << "\nWrite new ID: ";
            cin >> newId;
            Teachers *teacher2 = searchTeacher(newId);
            if (teacher2 == NULL) {
                student->id=newId;
                cout<<"\nModification successful!"<<endl;
                return;
            }
            cout << "\nThis ID is not available, please try another" << endl;
        }


    }
}
bool deleteStudent(int id){

    Students*student=searchStudent(id);
    if(student==NULL){
        cout << "Student not found" << endl;
        return false;
    }

    if(student==firstStudent){
        firstStudent=firstStudent->next;
        cout<<"\nDelete successful!"<<endl;
        return true;
    }

    Students*temp=firstStudent;

    while(temp->next != student){
        temp=temp->next;
    }
    temp->next=student->next;

    cout<<"\nDelete successful!"<<endl;
    return true;
}

void imprime(){
    Students*temp=firstStudent;

    while(temp != NULL){
        cout<<temp->fullName<<endl;
        temp=temp->next;

    }
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

    meetingTeacher(5, "MA1226",1,  13, 10, 16, 55,29, 03, 2021,  "clase magistral");
    meetingTeacher(5, "MA1226",2,  16, 55, 18, 30,29, 03, 2021,  "clase magistral");
    meetingTeacher(5, "MA1226",7,  15, 10, 19, 30,02, 04, 2021,  "clase magistral");
    meetingTeacher(4, "CA1298",3,  7, 50, 11, 30, 29, 03, 2021,  "clase magistral");
    meetingTeacher(3, "CA1103",4,  7, 50, 11, 30, 29, 03, 2021,  "clase magistral");
    meetingTeacher(2, "CA1558",5,  7, 50, 11, 30, 29, 03, 2021,  "clase magistral");
    meetingTeacher(1, "CA1101",6,  7, 50, 11, 30, 29, 03, 2021,  "clase magistral");


    //Estudiantes indican reunion en la que participaron

    meetingStudent(5, "MA1226", 51, 1);
    meetingStudent(5, "MA1226", 51, 2);


    //----Modificar profesor------

    //ModifyTeacher(5);

    //------Delete teacher------

    //deleteTeacher(1);
    //deleteTeacher(3);

    //------Modificar estudiante------

    ModifyStudent(5);

    //------Borrar estudiante------
    deleteStudent(1);


    imprime();

}


//-----------------------
//ARRIBA DEL MÉTODO MEETINGSTUDENT ESTAN VARIABLES SIMULANDO UNA FECHA, PARA NO ESTAR INGRESANDO POR CONSOLA TANTO
//-------------------------
/*
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
*/

int main() {

    burnedData();

    //menu();

    /*
    updateTeachersList();
    updateStudentsList();
    */

    return 0;
}