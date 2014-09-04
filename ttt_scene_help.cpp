/************ P R O J E C T ****************
Course : TCP1101 Programming Fundamentals
Session: Trimester 1, 2014/15
ID and Name #1 : 1131123100 Chong Hon Siong
Contacts #1 : 0173009142 honsiongchs@gmail.com
Lecture Section : TC101
Tutorial Section: TC201
********************************************/

#include "ttt_scene_help.hpp"

SceneHelp::SceneHelp(sf::RenderWindow* xwindow, std::vector<sf::Font*>* xttt_fonts)
{
	window = xwindow;
	ttt_fonts = xttt_fonts;

	current_page = 1; 

	// Some RenderWindow calculations
	sf::Vector2f window_size_v2f(window->getSize());

	// Create the 5 pages
	sf::Texture* page1_texture = TTTHelpers::load_texture("assets/images/guide/guide.001.png");
	sf::Texture* page2_texture = TTTHelpers::load_texture("assets/images/guide/guide.002.png");
	sf::Texture* page3_texture = TTTHelpers::load_texture("assets/images/guide/guide.003.png");
	sf::Texture* page4_texture = TTTHelpers::load_texture("assets/images/guide/guide.004.png");
	sf::Texture* page5_texture = TTTHelpers::load_texture("assets/images/guide/guide.005.png");

	sf::Vector2u page1_texture_size = page1_texture->getSize();

	page1.setTexture(page1_texture);
	page1.setSize( sf::Vector2f(page1_texture_size.x, page1_texture_size.y) );
	page1.setPosition( (window_size_v2f.x / 2) - (page1_texture_size.x / 2), (window_size_v2f.y / 2) - (page1_texture_size.y / 2) );
	page1.setTextureRect( sf::IntRect(0, 0, page1_texture_size.x, page1_texture_size.y) );

	page2 = page1;
	page2.setTexture(page2_texture);

	page3 = page1;
	page3.setTexture(page3_texture);

	page4 = page1;
	page4.setTexture(page4_texture);

	page5 = page1;
	page5.setTexture(page5_texture);

	// Create quit button and its hovering state
	quit_button_normal_texture    = TTTHelpers::load_texture("assets/images/quit-inactive.png");
	quit_button_hover_texture     = TTTHelpers::load_texture("assets/images/quit-active.png");

	sf::Vector2u ingame_buttons_texture_size = quit_button_normal_texture->getSize();

	quit_button.setTexture(quit_button_normal_texture);
	quit_button.setSize( sf::Vector2f(ingame_buttons_texture_size.x, ingame_buttons_texture_size.y) );
	quit_button.setTextureRect(sf::IntRect(0, 0, ingame_buttons_texture_size.x, ingame_buttons_texture_size.y));
	quit_button.setPosition( 10 , 37 );

	// Create prev page, next page
	sf::Texture* prev_page_texture = TTTHelpers::load_texture("assets/images/prev-page.png");
	sf::Texture* next_page_texture = TTTHelpers::load_texture("assets/images/next-page.png");
	sf::Texture* ok_button_texture = TTTHelpers::load_texture("assets/images/guide-ok.png");

	sf::Vector2u guide_nav_buttons_texture_size = prev_page_texture->getSize();

	prev_page.setTexture(prev_page_texture);
	prev_page.setSize( sf::Vector2f(guide_nav_buttons_texture_size.x, guide_nav_buttons_texture_size.y) );
	prev_page.setTextureRect(sf::IntRect(0, 0, guide_nav_buttons_texture_size.x, guide_nav_buttons_texture_size.y));
	prev_page.setPosition( 20, 490 );

	next_page = prev_page;
	next_page.setTexture(next_page_texture);
	next_page.setPosition( window_size_v2f.x - 20 - guide_nav_buttons_texture_size.x, 490 );

	// Create Done tutorial "OK" button
	ok_button = next_page;
	ok_button.setTexture(ok_button_texture);
}

void SceneHelp::render()
{
	// Draw the manual pages
	switch (current_page)
	{
		case 1:
			window->draw(page1);
			break;
		case 2:
			window->draw(page2);
			break;
		case 3:
			window->draw(page3);
			break;
		case 4:
			window->draw(page4);
			break;
		case 5:
			window->draw(page5);
			break;
	}

	// Draw quit button and its hovering state
	window->draw(quit_button);

	// Draw prev, next and OK conditionally
	if (current_page > 1)
	{
		window->draw(prev_page);
	}
	
	if (current_page < 5)
	{
		window->draw(next_page);
	}

	if (current_page == 5)
	{
		window->draw(ok_button);
	}
}

int SceneHelp::handle(sf::Event* xevent)
{
	event = xevent;
	int new_scene = 3;

	switch (event->type)
	{
		case sf::Event::MouseMoved:
			handleMouseOver();
			break;

		case sf::Event::MouseButtonReleased:
			new_scene = handleMouseClick();
			break;

		case sf::Event::KeyPressed:
			new_scene = handleKeyPress(event->key.code);
			break;
	}

	return new_scene;
}

int SceneHelp::handleMouseOver()
{
	sf::Vector2f mouse_position( static_cast<sf::Vector2f>(sf::Mouse::getPosition(*window)) );

	// Toggle quit button hovering state
	if (quit_button.getGlobalBounds().contains(mouse_position))
	{
		quit_button.setTexture(quit_button_hover_texture);
	}
	else
	{
		quit_button.setTexture(quit_button_normal_texture);
	}

	return 3;
}

int SceneHelp::handleMouseClick()
{
	sf::Vector2f mouse_position( static_cast<sf::Vector2f>(sf::Mouse::getPosition(*window)) );

	// Quit button goes back to menu
	if (quit_button.getGlobalBounds().contains(mouse_position))
	{	
		current_page = 1;
		return 0;
	}

	// Short circuit: OK button handling when its at last page
	if (current_page == 5 && ok_button.getGlobalBounds().contains(mouse_position))
	{	
		current_page = 1;
		return 0;
	}

	// Prev page
	if (prev_page.getGlobalBounds().contains(mouse_position))
		prevPage();

	// Next page
	if (next_page.getGlobalBounds().contains(mouse_position))
		nextPage();

	return 3;
}

int SceneHelp::handleKeyPress(int keycode)
{
	switch (keycode)
	{
		case sf::Keyboard::Right:
			nextPage();
			break;

		case sf::Keyboard::Left:
			prevPage();
			break;

		case sf::Keyboard::Escape:
			return 0;
	}

	return 3;
}

void SceneHelp::nextPage()
{
	std::cout << "Next page to " << current_page + 1 << std::endl;
	if (current_page < 5)
	{
		current_page++;
	}
	return;
}

void SceneHelp::prevPage()
{
	std::cout << "Prev page to " << current_page - 1 << std::endl;
	if (current_page > 1)
	{
		current_page--;
	}
	return;
}