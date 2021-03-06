#pragma once

// 설명 : 
class GameEngineRenderTarget;
class GameEngineRenderTargetManager
{
private:
	static GameEngineRenderTargetManager* Inst;

public:
	static GameEngineRenderTargetManager& GetInst()
	{
		return *Inst;
	}

	static void Destroy()
	{
		if (nullptr != Inst)
		{
			delete Inst;
			Inst = nullptr;
		}
	}

private:	// member Var
	std::map<std::string, GameEngineRenderTarget*> ResourcesMap;

public:
	// 직접 만들수 있다.
	GameEngineRenderTarget* Create(const std::string& _Name, const std::string& _TextureName, float4 _Color);
	// 파일에서 로드
	GameEngineRenderTarget* Load(const std::string& _Path);
	// 이름 직접 지정
	GameEngineRenderTarget* Load(const std::string& _Name, const std::string& _Path);
	// 목록에서 찾는다.
	GameEngineRenderTarget* Find(const std::string& _Name);

private:
	GameEngineRenderTargetManager(); // default constructer 디폴트 생성자
	~GameEngineRenderTargetManager(); // default destructer 디폴트 소멸자

protected:		// delete constructer
	GameEngineRenderTargetManager(const GameEngineRenderTargetManager& _other) = delete; // default Copy constructer 디폴트 복사생성자
	GameEngineRenderTargetManager(GameEngineRenderTargetManager&& _other) noexcept; // default RValue Copy constructer 디폴트 RValue 복사생성자

private:		//delete operator
	GameEngineRenderTargetManager& operator=(const GameEngineRenderTargetManager& _other) = delete; // default Copy operator 디폴트 대입 연산자
	GameEngineRenderTargetManager& operator=(const GameEngineRenderTargetManager&& _other) = delete; // default RValue Copy operator 디폴트 RValue 대입연산자
};




