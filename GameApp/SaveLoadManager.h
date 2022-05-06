#pragma once
#include <stdio.h>
#include <vector>
#include <iostream>
// �з� : 
// �뵵 : 
// ���� : 
class SaveLoadManager
{
private:	// member Var
	static SaveLoadManager* Inst_;
	std::vector<int> intVector_;
	int size_;

public:
	static SaveLoadManager& GetInst()
	{
		return *Inst_;
	}


private:
	SaveLoadManager(); // default constructer ����Ʈ ������
	~SaveLoadManager(); // default destructer ����Ʈ �Ҹ���
	SaveLoadManager(const SaveLoadManager& _other) = delete; // default Copy constructer ����Ʈ ���������
	SaveLoadManager(SaveLoadManager&& _other) noexcept; // default RValue Copy constructer ����Ʈ RValue ���������
	SaveLoadManager& operator=(const SaveLoadManager& _other) = delete; // default Copy operator ����Ʈ ���� ������
	SaveLoadManager& operator=(const SaveLoadManager&& _other) noexcept = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

public:
	void SaveFile(const char* pFullPath);
	void LoadFile(const char* pFullPath);

};

