#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

int num_tasks = 0;

void afegir(){
    ofstream file ("tasques.txt", ios::app);
    string tasca = "";
    int prioritat = -1;
    while (tasca == "") {
        cout << "Entra el nom de la tasca (tot junt): ";
        cin >> tasca;
    }
    while (prioritat <= 0 or prioritat > 5) {
        cout << "Entra la prioritat (entre 1 i 5): ";
        cin >> prioritat;
    }
    if (file.is_open()){
        file << tasca << " " << prioritat << endl;
    }
    file.close();
}

void mostrar(){
    string line;
    ifstream file ("tasques.txt");
    cout << "***********************" << endl;
    if (file.is_open()){
        num_tasks = 0;
        while (getline(file,line)){
            cout << line << endl;
            num_tasks++;
        }
        file.close();
    }
    cout << "***********************" << endl;
}

void eliminar(){
    vector<string> v;
    string line;
    int pos = 0;
    ifstream file ("tasques.txt");
    if (file.is_open()){
        while (getline(file,line)){
            v.push_back(line);
            cout <<pos << ". " << line << endl;
            pos++;
        }
        file.close();
    }
    int elim;
    cout << "Selecciona la tasca a borrar: ";
    cin >> elim;

    ofstream file2 ("tasques.txt", ios::trunc);
    if (file2.is_open()){
        for (int i = 0; i < v.size(); i++) {
            if (i != elim)
                file2 << v[i] << endl;
        }
        file2.close();
    }
    mostrar();
}


void separate(string& line, string& task, int& prior){
    int i = 0;

    while (i < line.size()){
        char c = line[i];
        if (c == ' ') break;
        task.push_back(c);
        i++;
    }
    i++;
    char c = line[i++];
    prior = c - '0';
}

string ruleta(vector<string> v, int num){
    for (int i = 0; i < v.size(); i++){
        if (i == num) return v[i];
    }
}

void seleccionar(){
    vector<string> p1,p2,p3,p4,p5;
    string line;
    ifstream file ("tasques.txt");
    if (file.is_open()){
        num_tasks = 0;
        while (getline(file,line)){
            num_tasks++;
            string task;
            int prior;
            separate(line,task,prior);
            if (prior == 1) p1.push_back(task);
            if (prior == 2) p2.push_back(task);
            if (prior == 3) p3.push_back(task);
            if (prior == 4) p4.push_back(task);
            if (prior == 5) p5.push_back(task);
        }
        file.close();
    }

    string res = ruleta(p1, rand()%p1.size());
    if (res != " ") p2.push_back(res);
    res = ruleta(p2, rand()%p2.size());
    if (res != " ") p3.push_back(res);
    res = ruleta(p3, rand()%p3.size());
    if (res != " ") p4.push_back(res);
    res = ruleta(p4, rand()%p4.size());
    if (res != " ") p5.push_back(res);
    res = ruleta(p5, rand()%p5.size());
    cout << endl;
    cout << "-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-" << endl;
    cout << "Tasca seleccionada: " << res << endl;
    cout << "-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-" << endl;
    cout << endl;

}

int main (){
    srand (time(NULL));
    int opcio=1;
    while (opcio != -1) {
        switch (opcio) {
            case 0:
                opcio = -1;
                cout << "Fins aviat" << endl;
                break;
            case 1:
                mostrar();
                break;
            case 2:
                afegir();
                break;
            case 3:
                eliminar();
                break;
            case 4:
                seleccionar();
                break;
            default:
                cout << "Opció no vàlida:" << endl;
                opcio = 1;
        }

        cout << "+++++++++++++++++++++++++++++++++" << endl;
        cout << "   0 - Sortir" << endl;
        cout << "   1 - Mostrar tasques" << endl;
        cout << "   2 - Afegir tasca" << endl;
        cout << "   3 - Eliminar tasca" << endl;
        cout << "   4 - Seleccionar aleatoriament" << endl;
        cout << "+++++++++++++++++++++++++++++++++" << endl;

        if (opcio != -1){
            opcio = -1;
            cout << "Entra la opcio: ";
            cin >> opcio;
        }
    }
    return 0;
}