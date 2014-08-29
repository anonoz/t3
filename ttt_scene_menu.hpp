#ifndef SCENE_MENU_HPP
#define SCENE_MENU_HPP

class SceneMenu
{
	public:
		SceneMenu(sf::RenderWindow& xwindow, std::vector<sf::Font*>& xttt_fonts);
		void render();
		void handle(sf::Event& event);
};

#endif