class FactoryMethod: public ScreenManager{
private:
	ScreenManager *sm;
	ScreenManager *sma[7];
	bool once;
	int section_now;
public:
	FactoryMethod(void);
	~FactoryMethod(void);
	void loadSection(void);
	void loadSection(int i);
	void showSection(InputManager<ALLEGRO_EVENT,ALLEGRO_KEYBOARD_STATE> &input,Maps<ALLEGRO_BITMAP> &m,Player<ALLEGRO_BITMAP> &p,bool st);
	void downloadMapPlayer(Maps<ALLEGRO_BITMAP> &m,Player<ALLEGRO_BITMAP> &p);
	void showCreatePlay(Maps<ALLEGRO_BITMAP> &m,Player<ALLEGRO_BITMAP> &p,InputManager<ALLEGRO_EVENT,ALLEGRO_KEYBOARD_STATE> &input);
	void setReadyPlayer(int p, bool c);
	void setNoAnimatePlay(bool c);
	void setButtonSelectMenu(int c);
	void setLoadMapPlayer(bool p);
	void setButtonSelectPause(int c);
	void setMap(int x, int y,char p);
	bool getLoadMapPlayer(void);
	bool getReadyPlayer(int p);
	bool readyPlayer(int p, InputManager<ALLEGRO_EVENT,ALLEGRO_KEYBOARD_STATE> &input);
	int  getButtonSelectMenu(void);
	int  getAvatarCodePlayer1(void);
	int  getAvatarCodePlayer2(void);
	int  getButtonSelectPause(void);
	char getMap(int x, int y);
	FILE* File(char *t);
};