#ifndef SCENE_MENU_HPP
#define SCENE_MENU_HPP

class SceneMenu
{
	private:
		sf::RenderWindow* window;
		sf::Event* event;
		std::vector< sf::Font* >* ttt_fonts;
		sf::Font kenvector_future_thin, kenpixel_blocks;

		// Visual Elements
		sf::Text heading1, start_button, about_button;
		sf::RectangleShape mini_board;

	public:
		SceneMenu(sf::RenderWindow* xwindow, std::vector<sf::Font*>* xttt_fonts);
		void render();
		int handle(sf::Event* xevent);
		int handle_mouse_click(int click_X, int click_y);
};

#endif