#include "PreCompile.h"
#include "GameStaticData.h"

// 씬 전체에 전역으로 가져 갈 기본적인 데이터들입니다.
// GAMEAPP 폴더의 "SaveData.txt" 파일과 연동됩니다.


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
	FILE* pFile = nullptr; // 파일 포인터 객체화

	fopen_s(&pFile, "SaveData.txt", "rb"); // 파일 열어서 객체화된 파일에 가져다 놓기

	if (!pFile) // 파일 없으면... 터뜨린다.
	{
		GameEngineDebug::MsgBoxError("세이브 대상 파일 경로가 잘못되었거나, 파일이 없습니다.");
		return;
	}

	size_ = intVector_.size();

	fwrite(&size_, sizeof(int), 1, pFile); // 벡터 배열에다가 해당 파일의 글자들을 모두 복사해 써붙인다.

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
		GameEngineDebug::MsgBoxError("로드 대상 파일 경로가 잘못되었거나, 파일이 없습니다.");
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

