FactoryMethod::FactoryMethod(void){ 
	once = false;
	section_now = -1;
	for(int i = 0; i<6;i++){
		this->sma[i] = NULL;
	}
}
FactoryMethod::~FactoryMethod(void){ delete sm;}
void FactoryMethod::loadSection(void){
	ScreenManager *tmp = new ScreenManager;
	int section_tmp;

	if(this->isCreateMenu())				{ tmp = new Menu<ALLEGRO_BITMAP,ALLEGRO_FONT>; section_tmp = 0;}
	else if(this->isCreateSave())			{ tmp = new Save<ALLEGRO_FONT,FILE>; section_tmp = 1;}
	else if(this->isCreateChoosePlayer())	{ tmp = new ChoosePlayer<ALLEGRO_BITMAP, ALLEGRO_FONT>; section_tmp = 2;}
	else if(this->isCreateChooseMap())		{ tmp = new ChooseMap<ALLEGRO_BITMAP, ALLEGRO_FONT>; section_tmp = 3;}
	else if(this->isCreateBeginPlay())		{ tmp = new CreatePlay<ALLEGRO_BITMAP, ALLEGRO_FONT>; section_tmp = 4;}
	else if(this->isCreateShowPause())		{ tmp = new CreatePause<ALLEGRO_FONT>; section_tmp = 5;}
	else if(this->isCreateShowResults())	{ tmp = new CreateResults<ALLEGRO_FONT>; section_tmp = 6;}
	
	if(this->sma[section_tmp] == NULL){
		this->sma[section_tmp] = tmp;
			this->section_now = section_tmp;
	}/*else{
		if(section_tmp != this->section_now){
			this->sm = tmp;
			this->section_now = section_tmp;
		}
	}*/
	this->sm = this->sma[section_tmp];
}
void FactoryMethod::loadSection(int i){
	ScreenManager *tmp = new ScreenManager;

	if(i == 0)		{ tmp = new Menu<ALLEGRO_BITMAP,ALLEGRO_FONT>; }
	else if(i == 1)	{ tmp = new Save<ALLEGRO_FONT,FILE>; }
	else if(i == 2)	{ tmp = new ChoosePlayer<ALLEGRO_BITMAP, ALLEGRO_FONT>; }
	else if(i == 3)	{ tmp = new ChooseMap<ALLEGRO_BITMAP, ALLEGRO_FONT>; }
	else if(i == 4)	{ tmp = new CreatePlay<ALLEGRO_BITMAP, ALLEGRO_FONT>; }
	else if(i == 5)	{ tmp = new CreatePause<ALLEGRO_FONT>; }
	else if(i == 6)	{ tmp = new CreateResults<ALLEGRO_FONT>; }

	if(this->sma[i] == NULL){
		this->sma[i] = tmp;
	}
	this->sm = this->sma[i];
}
void FactoryMethod::showSection(InputManager<ALLEGRO_EVENT,ALLEGRO_KEYBOARD_STATE> &input,Maps<ALLEGRO_BITMAP> &m,Player<ALLEGRO_BITMAP> &p,bool st){ cout << this->section_now <<endl;this->sm->showSection(input,m,p,st); }
void FactoryMethod::downloadMapPlayer(Maps<ALLEGRO_BITMAP> &m,Player<ALLEGRO_BITMAP> &p){ this->sm->downloadMapPlayer(m,p); }
void FactoryMethod::showCreatePlay(Maps<ALLEGRO_BITMAP> &m,Player<ALLEGRO_BITMAP> &p,InputManager<ALLEGRO_EVENT,ALLEGRO_KEYBOARD_STATE> &input){ this->sm->showCreatePlay(m,p,input); }
void FactoryMethod::setReadyPlayer(int p, bool c){this->sm->setReadyPlayer(p,c);}
void FactoryMethod::setNoAnimatePlay(bool c){this->sm->setNoAnimatePlay(c);}
void FactoryMethod::setButtonSelectMenu(int c){this->sm->setButtonSelectMenu(c);}
void FactoryMethod::setLoadMapPlayer(bool p){this->sm->setLoadMapPlayer(p);}
void FactoryMethod::setButtonSelectPause(int c){this->sm->setButtonSelectPause(c);}
void FactoryMethod::setMap(int x, int y,char p){this->sm->setMap(x,y,p);}
bool FactoryMethod::getLoadMapPlayer(void){return this->sm->getLoadMapPlayer();}
bool FactoryMethod::getReadyPlayer(int p){return this->sm->getReadyPlayer(p);}
bool FactoryMethod::readyPlayer(int p, InputManager<ALLEGRO_EVENT,ALLEGRO_KEYBOARD_STATE> &input){return this->sm->readyPlayer(p,input);}
int  FactoryMethod::getButtonSelectMenu(void){return this->sm->getButtonSelectMenu();}
int  FactoryMethod::getAvatarCodePlayer1(void){return this->sm->getAvatarCodePlayer1();}
int  FactoryMethod::getAvatarCodePlayer2(void){return this->sm->getAvatarCodePlayer2();}
int  FactoryMethod::getButtonSelectPause(void){return this->sm->getButtonSelectPause();}
char FactoryMethod::getMap(int x, int y){ return this->sm->getMap(x,y); }
FILE* FactoryMethod::File(char *t){return this->sm->File(t);}
