/************ P R O J E C T ****************
Course : TCP1101 Programming Fundamentals
Session: Trimester 1, 2014/15
ID and Name #1 : 1131123100 Chong Hon Siong
Contacts #1 : 0173009142 honsiongchs@gmail.com
Lecture Section : TC101
Tutorial Section: TC201
********************************************/

#include "ttt_scene_battlefield.hpp"

// Calculation aids
// Board level
const float SceneBattlefield::TOP_LEFT_X = 147;
const float SceneBattlefield::TOP_LEFT_Y = 37;

const int SceneBattlefield::DELTA_BOARD_X = 173;
const int SceneBattlefield::DELTA_BOARD_Y = 183;

// Grid level
const int SceneBattlefield::TOP_LEFT_GRID_X = 25;
const int SceneBattlefield::TOP_LEFT_GRID_Y = 25;

const int SceneBattlefield::DELTA_GRID_X = 50;
const int SceneBattlefield::DELTA_GRID_Y = 50;

SceneBattlefield::SceneBattlefield(sf::RenderWindow* xwindow, std::vector<sf::Font*>* xttt_fonts, TTT_Instance* xinstance)
{
	window = xwindow;
	ttt_fonts = xttt_fonts;

	// Game instance got from director
	instance = xinstance;

	// Some RenderWindow calculations
	sf::Vector2f window_size_v2f(window->getSize());

	// Create board as background
	sf::Texture* battle_board_texture = TTTHelpers::load_texture("assets/images/battle-board.png");
	sf::Vector2u battle_board_texture_size = battle_board_texture->getSize();

	battle_board.setTexture(battle_board_texture);
	battle_board.setSize( sf::Vector2f(battle_board_texture_size.x, battle_board_texture_size.y) );
	battle_board.setPosition( (window_size_v2f.x / 2) - (battle_board_texture_size.x / 2), (window_size_v2f.y / 2) - (battle_board_texture_size.y / 2) );
	battle_board.setTextureRect( sf::IntRect(0, 0, battle_board_texture_size.x, battle_board_texture_size.y) );

	// Create marker textures and rectangle
	x_marker_texture = TTTHelpers::load_texture("assets/images/x-marker.png");
	sf::Vector2u x_marker_texture_size = x_marker_texture->getSize();

	x_marker.setTexture(x_marker_texture);
	x_marker.setSize( sf::Vector2f(x_marker_texture_size.x, x_marker_texture_size.y) );
	x_marker.setTextureRect( sf::IntRect(0, 0, x_marker_texture_size.x, x_marker_texture_size.y) );

	x_marker.setPosition(getGridCoordinates(8,8));

	o_marker_texture = TTTHelpers::load_texture("assets/images/o-marker.png");
	sf::Vector2u o_marker_texture_size = o_marker_texture->getSize();

	o_marker.setTexture(o_marker_texture);
	o_marker.setSize( sf::Vector2f(o_marker_texture_size.x, o_marker_texture_size.y) );
	o_marker.setTextureRect( sf::IntRect(0, 0, o_marker_texture_size.x, o_marker_texture_size.y) );

	// Create mouse cursors (the inactive textures too)
	x_marker_inactive_texture = TTTHelpers::load_texture("assets/images/x-marker-inactive.png");
	o_marker_inactive_texture = TTTHelpers::load_texture("assets/images/o-marker-inactive.png");

	mouse_cursor = x_marker;

	// Create active halos
	sf::Texture* x_active_halo_texture = TTTHelpers::load_texture("assets/images/x-active-halo-bg.png");
	sf::Texture* o_active_halo_texture = TTTHelpers::load_texture("assets/images/o-active-halo-bg.png");

	sf::Vector2u x_active_halo_texture_size = x_active_halo_texture->getSize();

	x_active_halo.setTexture(x_active_halo_texture);
	x_active_halo.setSize( sf::Vector2f(x_active_halo_texture_size.x, x_active_halo_texture_size.y) );
	x_active_halo.setTextureRect( sf::IntRect(0, 0, x_active_halo_texture_size.x, x_active_halo_texture_size.y) );

	o_active_halo = x_active_halo;
	o_active_halo.setTexture(o_active_halo_texture);

	// Create hinting halos
	sf::Texture* x_hint_halo_texture = TTTHelpers::load_texture("assets/images/x-hint-halo-bg.png");
	sf::Texture* o_hint_halo_texture = TTTHelpers::load_texture("assets/images/o-hint-halo-bg.png");

	sf::Vector2u x_hint_halo_texture_size = x_hint_halo_texture->getSize();

	x_hint_halo.setTexture(x_hint_halo_texture);
	x_hint_halo.setSize( sf::Vector2f(x_hint_halo_texture_size.x, x_hint_halo_texture_size.y) );
	x_hint_halo.setTextureRect( sf::IntRect(0, 0, x_hint_halo_texture_size.x, x_hint_halo_texture_size.y) );
	x_hint_halo.setPosition(1000,1000);

	o_hint_halo = x_hint_halo;
	o_hint_halo.setTexture(o_hint_halo_texture);

	// Create grid hitzones for event handling

	// Create winner mat
	sf::Texture* x_winner_mat_texture = TTTHelpers::load_texture("assets/images/x-winner-mat.png");
	sf::Texture* o_winner_mat_texture = TTTHelpers::load_texture("assets/images/o-winner-mat.png");
	sf::Texture* tie_mat_texture = TTTHelpers::load_texture("assets/images/tie-mat.png");

	sf::Vector2u winner_mat_texture_size = x_winner_mat_texture->getSize();

	x_winner_mat.setTexture(x_winner_mat_texture);
	x_winner_mat.setSize( sf::Vector2f(winner_mat_texture_size.x, winner_mat_texture_size.y) );
	x_winner_mat.setTextureRect( sf::IntRect(0, 0, winner_mat_texture_size.x, winner_mat_texture_size.y) );
	x_winner_mat.setPosition( (window_size_v2f.x / 2) - (winner_mat_texture_size.x / 2), (window_size_v2f.y / 2) - (winner_mat_texture_size.y / 2) );

	o_winner_mat = x_winner_mat;
	o_winner_mat.setTexture(o_winner_mat_texture);

	tie_mat = x_winner_mat;
	tie_mat.setTexture(tie_mat_texture);

	// Create winner mat textual notices
	x_winner_notice.setFont(*((*ttt_fonts)[4]));
	x_winner_notice.setColor(sf::Color::White);
	x_winner_notice.setStyle(sf::Text::Regular);
	x_winner_notice.setCharacterSize(80);
	x_winner_notice.setPosition(x_winner_mat.getPosition().x + x_winner_mat.getSize().x / 2, (x_winner_mat.getPosition().y + x_winner_mat.getSize().y / 2) - 60);
	TTTHelpers::set_text_string(x_winner_notice, "PLAYER X WON", "CT");

	o_winner_notice = x_winner_notice;
	TTTHelpers::set_text_string(o_winner_notice, "PLAYER O WON", "CT");

	you_won_notice = x_winner_notice;
	TTTHelpers::set_text_string(you_won_notice, "YOU WON", "CT");

	you_lost_notice = x_winner_notice;
	TTTHelpers::set_text_string(you_lost_notice, "YOU LOST", "CT");

	tie_notice = x_winner_notice;
	TTTHelpers::set_text_string(tie_notice, "TIE", "CT");	

	disconnected_notice = x_winner_notice;
	TTTHelpers::set_text_string(disconnected_notice, "DISCONNECTED", "CT");

	// Create winner mat play again inactive and active buttons
	sf::Texture* playagain_button_texture = TTTHelpers::load_texture("assets/images/playagain-button.png");
	sf::Vector2u playagain_button_texture_size = playagain_button_texture->getSize();

	playagain_button.setTexture(playagain_button_texture);
	playagain_button.setSize( sf::Vector2f(playagain_button_texture_size.x, playagain_button_texture_size.y));
	playagain_button.setTextureRect(sf::IntRect(0, 0, playagain_button_texture_size.x, playagain_button_texture_size.y));
	playagain_button.setPosition( (window_size_v2f.x / 2) - (playagain_button.getSize().x / 2) , (window_size_v2f.y / 2) - (playagain_button.getSize().y / 2) + 40);

	// Create the soundbytes
	placement_ok1_sound_buffer = *TTTHelpers::load_sound_buffer("assets/sounds/placement_1.ogg");
	placement_ok2_sound_buffer = *TTTHelpers::load_sound_buffer("assets/sounds/placement_2.ogg");
	placement_error_sound_buffer = *TTTHelpers::load_sound_buffer("assets/sounds/placement_error.ogg");
	winner_sound_buffer = *TTTHelpers::load_sound_buffer("assets/sounds/result_win.ogg");
	tie_sound_buffer = *TTTHelpers::load_sound_buffer("assets/sounds/result_tie.ogg");
	loser_sound_buffer = *TTTHelpers::load_sound_buffer("assets/sounds/result_lose.ogg");

	placement_ok1_sound.setBuffer(placement_ok1_sound_buffer);
	placement_ok2_sound.setBuffer(placement_ok2_sound_buffer);
	placement_error_sound.setBuffer(placement_error_sound_buffer);
	winner_sound.setBuffer(winner_sound_buffer);
	tie_sound.setBuffer(tie_sound_buffer);
	loser_sound.setBuffer(loser_sound_buffer);

}

void SceneBattlefield::reset()
{
	// Instance = game model. The truth. The source...
	instance->quitMultiplayer();
	instance->reset();
}