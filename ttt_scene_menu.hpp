#ifndef SCENE_MENU_HPP
#define SCENE_MENU_HPP

class SceneMenu
{
	private:
		sf::RenderWindow* window;
		std::vector< sf::Font* >* ttt_fonts;
		sf::Font kenvector_future_thin, kenpixel_blocks;

		// Visual Elements
		sf::Text heading1, start_button, about_button;

	public:
		SceneMenu(sf::RenderWindow* xwindow, std::vector<sf::Font*>* xttt_fonts);
		void render();
		void handle(sf::Event& event);
};

#endif