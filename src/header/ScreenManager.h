class ScreenManager{
	private:
		bool _Menu, _Save, _ChoosePlayer, _ChooseMap, _BeginPlay, _ShowPause, _ShowResults;
		ALLEGRO_FONT *_font20;
	public:
	ScreenManager(void);
	~ScreenManager(void);
	bool isCreateMenu(void);
	bool isCreateSave(void);
	bool isCreateChoosePlayer(void);
	bool isCreateChooseMap(void);
	bool isCreateBeginPlay(void);
	bool isCreateShowPause(void);
	bool isCreateShowResults(void);
	
	void setMenu(bool c);
	void setSave(bool c);
	void setChoosePlayer(bool c);
	void setChooseMap(bool c);
	void setBeginPlay(bool c);
	void setShowPause(bool c);
	void setShowResults(bool c);

	void drawButton(void);
	void restartInput(InputManager<ALLEGRO_EVENT,ALLEGRO_KEYBOARD_STATE> &input);
	
	virtual void showSection(InputManager<ALLEGRO_EVENT,ALLEGRO_KEYBOARD_STATE> &input,Maps<ALLEGRO_BITMAP> &m,Player<ALLEGRO_BITMAP> &p,bool st){cout <<"showSection sin Definir"<<endl;}
	virtual void downloadMapPlayer(Maps<ALLEGRO_BITMAP> &m,Player<ALLEGRO_BITMAP> &p){cout <<"downloadMapPlayer sin Definir"<<endl;}
	virtual void showCreatePlay(Maps<ALLEGRO_BITMAP> &m,Player<ALLEGRO_BITMAP> &p,InputManager<ALLEGRO_EVENT,ALLEGRO_KEYBOARD_STATE> &input){cout <<"showCreatePlay sin Definir"<<endl;}
	virtual void setReadyPlayer(int p, bool c){cout <<"setReadyPlayer sin Definir"<<endl;}
	virtual void setNoAnimatePlay(bool c){cout <<"setNoAnimatePlay sin Definir"<<endl;}
	virtual void setButtonSelectMenu(int c){cout <<"setButtonSelectMenu sin Definir"<<endl;}
	virtual void setLoadMapPlayer(bool p){cout <<"setLoadMapPlayer sin Definir"<<endl;}
	virtual void setButtonSelectPause(int c){cout << "setButtonSelectPause"<<endl;}
	virtual void setMap(int x, int y,char p){cout << "setMap"<<endl;}
	virtual bool getLoadMapPlayer(void){cout <<"getLoadMapPlayer sin Definir"<<endl;}
	virtual bool getReadyPlayer(int p){cout <<"getReadyPlayer sin Definir"<<endl;}
	virtual bool readyPlayer(int p, InputManager<ALLEGRO_EVENT,ALLEGRO_KEYBOARD_STATE> &input){cout << "readyPlayer sin Definir";}
	virtual int  getButtonSelectMenu(void){cout << "getButtonSelectMenu sin Definir"<<endl;}
	virtual int  getAvatarCodePlayer1(void){cout << "getAvatarCodePlayer1 sin Definir"<<endl;}
	virtual int  getAvatarCodePlayer2(void){cout << "getAvatarCodePlayer2 sin Definir"<<endl;}
	virtual int  getButtonSelectPause(void){cout << "getButtonSelectPause sin Definir"<<endl;}
	virtual char getMap(int x, int y){cout <<"getMap sin Definir"<<endl;}
	virtual FILE* File(char *t){cout << "File sin Definir"<<endl;}
};
