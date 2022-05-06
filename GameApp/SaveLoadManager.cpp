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
	FILE* pFile = nullptr; // ���� ������ ��üȭ

	fopen_s(&pFile, pFullPath, "wt"); // ���� ��� ��üȭ�� ���Ͽ� ������ ����

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
}

void SaveLoadManager::LoadFile(const char* pFullPath)
{
	FILE* pFile = nullptr;

	fopen_s(&pFile, pFullPath, "rb");

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
}
