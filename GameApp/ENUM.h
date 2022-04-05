#pragma once
// 나에게 메모 : 헤더 걸지마라!!!


enum class InGameCollisonType
{
	MOUSEPOINTER,
	UI,
	GAMEACTOR,
	MAX
};

enum class RenderOrder
{
	FRONT,
	FILTER0,
	FILTER1,
	FILTER2,
	CCTV1,
	CCTV0,

	OBJECT0,
	OBJECT1,
	OBJECT2,

	BACKGROUND0,
	BACKGROUND1,
	BACKGROUND2,

	MAX = 999
};

enum class UIRenderOrder
{
	REAR = 0,

	UI2,
	UI1,
	UI0,

	FADE2,
	FADE1,
	FADE0,

	DAYPASS,
	
	FRONT = 999
};

enum class LOCATION
{
	OFFICE,
	LOFFICEDOOR,
	ROFFICEDOOR,
	SHOWSTAGE,
	KITCHEN,
	BACKSTAGE,
	DININGAREA,
	PIRATECOVE,
	EASTHALLA,
	EASTHALLB,
	WESTHALLA,
	WESTHALLB,
	RESTROOMS,
	SUPPLYCLOSET,
	NONE,
	MAX,
};

enum class PLAYERSTATUS
{
	OFFICE,
	CCTV,
	MAX
};

enum class FOXYLEVEL
{
	LV1,
	LV2,
	LV3,
	LV4,
	MAX
};

enum class DAY
{
	DAY1,
	DAY2,
	DAY3,
	DAY4,
	DAY5,
	DAY6,
	CUSTOM,

	MAX
};