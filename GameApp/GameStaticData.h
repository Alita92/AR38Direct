#pragma once
#include "ENUM.h"

// �������� ���������� �����ϴ� ������ �մϴ�.
// �ظ��ϸ� "��Ʈ�ѷ�" Ŭ���� ������ ���� �����ϰ� �մϴ�.

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