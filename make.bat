@echo off
COLOR 0a
echo Compiling the game right now...
g++ ttt_helpers.cpp ttt_scene_director.cpp ttt_scene_menu.cpp ttt_scene_battlefield.cpp ttt_scene_battlefield_render.cpp ttt_scene_battlefield_eventhandler.cpp ttt_scene_multiplayer.cpp ttt_instance.cpp ttt_instance_multiplayer.cpp main.cpp -I"c:\SFML-2.1\include" -L"c:\SFML-2.1\lib" -lsfml-system -lsfml-window -lopengl32 -lglu32 -lsfml-graphics -lsfml-main -lsfml-audio -lsfml-network -o t3.exe && start t3.exe && start t3.exe
COLOR 0f