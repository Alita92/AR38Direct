#pragma once
#include "GameEnginePath.h"
// 분류 :
// 용도 :
// 설명 :

class GameEngineFile;
class GameEngineDirectory : public GameEnginePath
{
public:
	GameEngineDirectory(); // default constructer 디폴트 생성자
	~GameEngineDirectory(); // default destructer 디폴트 소멸자

public:		// delete constructer
	GameEngineDirectory(const GameEngineDirectory& _other); // default Copy constructer 디폴트 복사생성자
	GameEngineDirectory(GameEngineDirectory&& _other) noexcept; // default RValue Copy constructer 디폴트 RValue 복사생성자

public:		//delete operator
	GameEngineDirectory& operator=(const GameEngineDirectory& _other) = delete; // default Copy operator 디폴트 대입 연산자
	GameEngineDirectory& operator=(const GameEngineDirectory&& _other) = delete; // default RValue Copy operator 디폴트 RValue 대입연산자

public:
	std::string DirectroyName();

public:		//member Func
	bool IsRoot();
	void MoveParent();
	bool MoveParent(const std::string& _DirName);
	bool MoveChild(const std::string& _DirName);

public:
	std::string PathToPlusFileName(const std::string& _DirName);
	GameEngineFile PathToCreateFile(const std::string& _FileName);
	GameEngineFile PathToGetFile(const std::string& _FileName);


	std::vector<GameEngineFile> GetAllFile();
};

