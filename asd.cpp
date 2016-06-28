//Allegro Inits
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

#include <vector>
#include <iostream>
using namespace std;

class FactoryMethod{
public:
};
class Juego:public FactoryMethod{
public:
};
class Juego1:public FactoryMethod{
public:
};
class Juego2:public FactoryMethod{
public:
};


class Controller{
private:
    int section;

    bool view;
    bool model;
public:
    Controller(void){
        this->section = 0;
        this->view = true;
        this->model = false;
    }
    void pressButton(ALLEGRO_KEYBOARD_STATE &key_state){
        bool st;
        if(al_key_down(&key_state, ALLEGRO_KEY_S))  {
            cout << "abajo"<<endl;
            st = true;
        }else if(al_key_down(&key_state, ALLEGRO_KEY_D))  {
            cout << "derecha"<<endl;
            st = true;
        }else{
            st = false;
        }
        if(st){
            this->model = true;
            this->view = false;
        }
    }
    bool enterView(void){ return this->view; }
    bool enterModel(void){ return this->model;}
    bool setView(bool b){ this->view = b; }
    bool setModel(bool b){ this->model = b; }

    int getSection(void){ return this->section; }
};

class Model{
private:
    vector<int> v;
    Controller c;
    FactoryMethod *fm;
public:
    Model(Controller &c){ this->c = c; }
    //~Model(void){ delete fm; }
    void Jugar(void){
        cout << "Jugando" << endl;
    }
    void loadFactory(int i){
        switch(i){
            case 0: fm = new Juego; break;
            case 1: fm = new Juego1; break;
            case 2: fm = new Juego2; break;
        }
    }
    void updateFactory(){
        
        
        //Actualizamos el Controlador
        c.setModel(0)
        c.setView(1);
    }
};

class View{
private:
    bool init;
    Controller c;
public:
    View(void){
        init = true;
    }

    View(Controller &c){ this->c = c; }
    void draw(Controller &c){
            cout << "Dibujando Basico..." << endl;
    }
};

int main(){
    if(!al_init()){
        cout << "Allegro no se pudo iniciar";
        return -1;
    }
    ALLEGRO_DISPLAY *display;
    display = al_create_display(500,500);
    /*Inserts libraries of Allegro*/
    al_install_keyboard();
    al_init_primitives_addon();

    ALLEGRO_KEYBOARD_STATE key_state;
    ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_display_event_source(display));

    Controller c;

    bool done = false;
    while(!done){
        ALLEGRO_EVENT events;
        al_wait_for_event(event_queue,&events);
        al_get_keyboard_state(&key_state);
        if(events.type == ALLEGRO_EVENT_DISPLAY_CLOSE)      { done = true; }
        
        //Esperando que presion un boton;
        c.pressButton(key_state);
        Model m(c); //Actualizamos el model
        View v(c);  //Actualizamos el view

        //Compuertas de conexion de control
        if(c.enterModel() && !c.enterView()){
            m.loadFactory(c.getSection());
            m.updateFactory();
        }else if(c.enterView() && c.enterModel()){
            cout << "puedo usar view" << endl;
        }else{
            cout << "Error con el controlador" << endl;
        }

        //Unico Metodo que no es controlado
        v.draw(c);
    }
    al_destroy_event_queue(event_queue);
}