template <class al_f, class f>
class Save:public ScreenManager{
	private:
	al_f *_font30;
	al_f *_font20;
	f *fp;
	int _file;
	vector<char *> name_files; 
	public:
	Save(void);
	~Save(void);
	f *File(char *t);
	void showSection(InputManager<ALLEGRO_EVENT,ALLEGRO_KEYBOARD_STATE> &input,Maps<ALLEGRO_BITMAP> &m,Player<ALLEGRO_BITMAP> &p,bool st);
};