template <class al_f>
class CreateResults:public ScreenManager{
	private:
		al_f *_font50;

	public:
		CreateResults(void);
		~CreateResults(void);

		void showSection(InputManager<ALLEGRO_EVENT,ALLEGRO_KEYBOARD_STATE> &input,Maps<ALLEGRO_BITMAP> &m,Player<ALLEGRO_BITMAP> &p,bool st);

};