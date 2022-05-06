#pragma once
#include "ENUM.h"

// 설정값을 전역적으로 관리하는 역할을 합니다.
// 왠만하면 "컨트롤러" 클래스 끼리만 관여 가능하게 합니다.

class GameStaticData
{
public:
	static DAY curDay_;
	static DAY savedDay_;

	static int AICustomStartLevelBonnie_;
	static int AICustomStartLevelChica_;
	static int AICustomStartLevelFoxy_;
	static int AICustomStartLevelFreddy_;


	static std::vector<int> intVector_;
	static size_t size_;


	static void SaveDay();
	static void LoadDay();
};