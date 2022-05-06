#include "PreCompile.h"
#include "SaveLoadManager.h"



SaveLoadManager::SaveLoadManager() 
	: size_(0), intVector_(0)
{

}

SaveLoadManager::~SaveLoadManager() 
{

}

void SaveLoadManager::SaveFile(const char* pFullPath)
{
	FILE* pFile = nullptr; // 파일 포인터 객체화

	fopen_s(&pFile, pFullPath, "wt"); // 파일 열어서 객체화된 파일에 가져다 놓기

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
}

void SaveLoadManager::LoadFile(const char* pFullPath)
{
	FILE* pFile = nullptr;

	fopen_s(&pFile, pFullPath, "rb");

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
}
