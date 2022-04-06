#pragma once
#include "ENUM.h"

// 설정값을 전역적으로 관리하는 역할을 합니다.
// 왠만하면 "컨트롤러" 클래스 끼리만 관여 가능하게 합니다.

class GameStaticData
{
public:
	static DAY curDay_;

	static int AIStartLevelBonnie_;
	static int AIStartLevelChica_;
	static int AIStartLevelFoxy_;
	static int AIStartLevelFreddy_;

public:
	void SetAIStartLevel(DAY _day)
	{
		switch (_day)
		{
		case DAY::DAY1:
		{
			AIStartLevelBonnie_ = 0;
			AIStartLevelChica_ = 0;
			AIStartLevelFoxy_ = 0;
			AIStartLevelFreddy_ = 0;
		}
			break;
		case DAY::DAY2:
		{
			AIStartLevelBonnie_ = 3;
			AIStartLevelChica_ = 1;
			AIStartLevelFoxy_ = 1;
			AIStartLevelFreddy_ = 0;
		}
			break;
		case DAY::DAY3:
		{
			AIStartLevelBonnie_ = 0;
			AIStartLevelChica_ = 5;
			AIStartLevelFoxy_ = 2;
			AIStartLevelFreddy_ = 1;
		}
			break;
		case DAY::DAY4:
		{
			AIStartLevelBonnie_ = 2;
			AIStartLevelChica_ = 4;
			AIStartLevelFoxy_ = 6;
			AIStartLevelFreddy_ = 2;
		}
			break;
		case DAY::DAY5:
		{
			AIStartLevelBonnie_ = 5;
			AIStartLevelChica_ = 7;
			AIStartLevelFoxy_ = 5;
			AIStartLevelFreddy_ = 3;
		}
			break;
		case DAY::DAY6:
		{

		}
			break;
		case DAY::CUSTOM:
			break;
		case DAY::MAX:
			break;
		default:
			break;
		}


	}
};