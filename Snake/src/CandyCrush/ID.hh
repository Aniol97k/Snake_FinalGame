#pragma once
#include <iostream>

// Enum ID used to identify each Game Object in the Game
enum class ObjectID : const int {
	CELL_EMPTY, ARROW, BG_GAME, BG_CELL, SNAKE, APPLE, WALL, EMPTY_HEARTH, FULL_HEARTH, BG_DEATH,BG_WIN ,SNAKE_HEAD,// Cell IDs
	BG_00, BAR // Background IDs
};

inline std::ostream &operator<<(std::ostream &os, const ObjectID &id) { return os << int(id); };
inline std::istream &operator>>(std::istream &is, ObjectID &id) { return is >> reinterpret_cast<int&>(id); };

// Enum ID used to store each true type font for text rendering
enum class FontID : int { 
	ARIAL,
	CANDY,
	FACTORY, 
	MAX 
};