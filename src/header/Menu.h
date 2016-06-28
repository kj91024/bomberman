template <class al_b,class al_f>
class Menu:public ScreenManager{
	private:
		al_f *_font100;
		al_f *_font20;
		al_f *_font40;
		al_b *_icon;
		int _button;
		bool move;
	public:
		Menu(void);
		int getButtonSelectMenu(void);
		void setButtonSelectMenu(int c);
		void showSection(InputManager<ALLEGRO_EVENT,ALLEGRO_KEYBOARD_STATE> &input,Maps<al_b> &m,Player<al_b> &p,bool st);
		~Menu(void);
};