#include "PreCompile.h"
#include "GameStaticData.h"

// �� ��ü�� �������� ���� �� �⺻���� �����͵��Դϴ�.
// GAMEAPP ������ "SaveData.txt" ���ϰ� �����˴ϴ�.


DAY GameStaticData::curDay_ = DAY::DAY1;
DAY GameStaticData::savedDay_ = DAY::MAX;

int GameStaticData::AICustomStartLevelBonnie_ = 0;
int GameStaticData::AICustomStartLevelChica_ = 0;
int GameStaticData::AICustomStartLevelFoxy_ = 0;
int GameStaticData::AICustomStartLevelFreddy_ = 0;

size_t GameStaticData::size_ = 0;
std::vector<int> GameStaticData::intVector_;

void GameStaticData::SaveDay()
{
	FILE* pFile = nullptr; // ���� ������ ��üȭ

	fopen_s(&pFile, "SaveData.txt", "rb"); // ���� ��� ��üȭ�� ���Ͽ� ������ ����

	if (!pFile) // ���� ������... �Ͷ߸���.
	{
		GameEngineDebug::MsgBoxError("���̺� ��� ���� ��ΰ� �߸��Ǿ��ų�, ������ �����ϴ�.");
		return;
	}

	size_ = intVector_.size();

	fwrite(&size_, sizeof(int), 1, pFile); // ���� �迭���ٰ� �ش� ������ ���ڵ��� ��� ������ ����δ�.

	for (int i = 0; i < size_; ++i)
	{
		fwrite(&intVector_[i], sizeof(int), 1, pFile);
	}

	fclose(pFile);

	intVector_.push_back(static_cast<int>(curDay_));
}

void GameStaticData::LoadDay()
{
	FILE* pFile = nullptr;

	fopen_s(&pFile, "SaveData.txt", "rt");

	if (!pFile)
	{
		GameEngineDebug::MsgBoxError("�ε� ��� ���� ��ΰ� �߸��Ǿ��ų�, ������ �����ϴ�.");
		return;
	}

	fread(&size_, sizeof(int), 1, pFile);
	intVector_.resize(size_);

	for (int i = 0; i < size_; ++i)
	{
		fread(&intVector_[i], sizeof(int), 1, pFile);
	}

	fclose(pFile);

	curDay_ = static_cast<DAY>(intVector_[0]);
}

