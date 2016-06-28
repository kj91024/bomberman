template <class al_f>
class CreatePause:public ScreenManager{
	private:
		al_f *_font50;
		al_f *_font20;
		int _button;
	public:
		CreatePause(void);
		~CreatePause(void);

		int getButtonSelectPause(void);
		void setButtonSelectPause(int c);

		void showSection(InputManager<ALLEGRO_EVENT,ALLEGRO_KEYBOARD_STATE> &input,Maps<ALLEGRO_BITMAP> &m,Player<ALLEGRO_BITMAP> &p,bool st);
};