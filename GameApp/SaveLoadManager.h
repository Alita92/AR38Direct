#pragma once
#include <stdio.h>
#include <vector>
#include <iostream>
// 분류 : 
// 용도 : 
// 설명 : 
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
	SaveLoadManager(); // default constructer 디폴트 생성자
	~SaveLoadManager(); // default destructer 디폴트 소멸자
	SaveLoadManager(const SaveLoadManager& _other) = delete; // default Copy constructer 디폴트 복사생성자
	SaveLoadManager(SaveLoadManager&& _other) noexcept; // default RValue Copy constructer 디폴트 RValue 복사생성자
	SaveLoadManager& operator=(const SaveLoadManager& _other) = delete; // default Copy operator 디폴트 대입 연산자
	SaveLoadManager& operator=(const SaveLoadManager&& _other) noexcept = delete; // default RValue Copy operator 디폴트 RValue 대입연산자

public:
	void SaveFile(const char* pFullPath);
	void LoadFile(const char* pFullPath);

};

