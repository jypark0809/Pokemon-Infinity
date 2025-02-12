#pragma once

enum class PEN_TYPE
{
	RED,
	GREEN,
	BLUE,
	GRAY,
	YELLOW,

	COUNT,
};

enum class BRUSH_TYPE
{
	RED,
	GREEN,
	BLUE,
	WHITE,
	GRAY,
	DARKGRAY,
	EMERALD,
	HOLLOW,

	COUNT,
};


enum class LayerType
{
	DEFAULT,
	MAP,
	TILE,
	PLAYER,
	MONSTER,
	

	UI = 31,
	COUNT = 32
};


enum class ComponentType
{
	TRANSFORM,
	CAMERA,
	COLLIDER,
	FLIPBOOK_PLAYER,
	RIGIDBODY,
	STATE_MACHINE,
	TILEMAP,
	TILEMAPRENDERER,
	GRID,
	SCRIPT
};

enum class AssetType
{
	TEXTURE,
	SPRITE,
	FLIPBOOK,
	SOUND,
};


enum class TASK_TYPE
{
	CREATE_OBJECT, // Param0 : Object, Param1 : Layer
	DELETE_OBJECT, // Param0 : Object
	CHANGE_LEVEL,  // Param0 : LevelType

	COUNT,
};

enum POSTPROC
{
	FADE_IN,
	FADE_OUT,

	HURT,
	NIGHT,

	PS_NONE,
};

enum LevelType
{
	TITLE,
	GAME,
	SPRITE_EDITOR,
	FLIPBOOK_EDITOR,
	TILEMAP_EDITOR,

	COUNT,
};

enum class Dir
{
	DOWN,
	LEFT,
	RIGHT,
	UP,

	COUNT,
	NONE
};