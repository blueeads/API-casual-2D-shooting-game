#pragma once

// Scene Type

enum SCENE_CREATE
{
	SC_CURRENT,
	SC_NEXT,
	SC_END
};

enum MOVE_DIR
{
	MD_BACK = -1,
	MD_NONE,
	MD_FRONT
};

//Collider Type
enum COLLIDER_TYPE
{
	CT_RECT,
	CT_SPHERE,
	CT_LINE,
	CT_POINT,
	CT_PIXEL,
	CT_END
};

// Collision State
enum COLLISION_STATE
{
	CS_ENTER,
	CS_STAY,
	CS_LEAVE,
	CS_END
};

// Animation Type
enum ANIMATION_TYPE
{
	AT_ATLAS,
	AT_FRAME,
	AT_END
};

// Animation Option
enum ANIMATION_OPTION
{
	AO_LOOP,
	AO_ONCE_RETURN, //�ѹ� ���� default ���
	AO_ONCE_DESTROY,
	AO_TIME_RETURN,
	AO_TIME_DESTROY
};

// Scene Change
enum SCENE_CHANGE
{
	SC_NONE,
	SC_CHANGE
};

enum ITEM_CHANGE
{
	IT_NONE,
	IT_SHANGE
};

enum TILE_OPTION
{
	TO_NONE,
	TO_NOMOVE
};

enum TILE_EDIT_MODE
{
	TEM_TEXTURE,
	TEM_OPTION
};

enum SetUP {
	Pause,
	Not
};

enum ITEM_STATE {
	SPEED,
	DAMAGE,
	HEAL
};

enum Stage_NumBer {
	First = 1,
	Second,
	Three
};