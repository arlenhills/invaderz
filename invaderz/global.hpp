#pragma once
#include <SFML\Graphics.hpp>
#include <SFML\Window.hpp>
#include <SFML\System.hpp>
#include <SFML\Audio.hpp>
#include <SFML\Network.hpp>
#include <cstdlib>
#include<Windows.h>
#include <iostream>
#include <sstream>
#include <chrono>
#include <thread>
#include <string>
#include <math.h>

using std::cout;
using std::endl;
using std::cin;
using namespace std::this_thread;
using namespace std::chrono_literals;

//Global Constants for pos stuff
constexpr int WINDOWX = 1024;
constexpr int WINDOWY = 768;

//If we divide 1 second by 60 frames (60 FPS), the duration of each frame will be 16.667 ms.
constexpr std::chrono::microseconds FRAME_DURATION(16667);

constexpr float PI = 3.141592653589793116f;
constexpr float DR = 0.01745329252f;

constexpr float FOV_H = 90.f;
constexpr float FOV_V = 74.f;
constexpr float maxRenderDistance = 224.f;
constexpr float WINDOWX_OFFSET = 256.f;

constexpr float PLAYER_ROTATION_SPEED = 2.5f;
constexpr float PLAYER_MOVE_SPEED = 0.75f;
constexpr float PLAYER_START_X = 48.f;
constexpr float PLAYER_START_Y = 48.f;
constexpr float CELL_SIZE = 32.f;
