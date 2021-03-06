#include "PreCompile.h"
#include "GameEngineSamplerManager.h"
#include "GameEngineSampler.h"

GameEngineSamplerManager* GameEngineSamplerManager::Inst = new GameEngineSamplerManager();

GameEngineSamplerManager::GameEngineSamplerManager() // default constructer 디폴트 생성자
{

}

GameEngineSamplerManager::~GameEngineSamplerManager() // default destructer 디폴트 소멸자
{
	for (const std::pair<std::string, GameEngineSampler*>& Res : ResourcesMap)
	{
		if (nullptr != Res.second)
		{
			delete Res.second;
		}
	}

	ResourcesMap.clear();
}

GameEngineSamplerManager::GameEngineSamplerManager(GameEngineSamplerManager&& _other) noexcept  // default RValue Copy constructer 디폴트 RValue 복사생성자
{

}



GameEngineSampler* GameEngineSamplerManager::Create(const std::string& _Name, const D3D11_SAMPLER_DESC& _Info)
{
	GameEngineSampler* FindRes = Find(_Name);

	if (nullptr != FindRes)
	{
		GameEngineDebug::MsgBoxError(_Name + " Is Overlap Create");
	}


	GameEngineSampler* NewRes = new GameEngineSampler();
	NewRes->SetName(_Name);
	NewRes->Create(_Info);

	// 그리고 뭘할거냐?

	ResourcesMap.insert(std::map<std::string, GameEngineSampler*>::value_type(_Name, NewRes));
	return NewRes;
}

GameEngineSampler* GameEngineSamplerManager::Find(const std::string& _Name)
{
	std::map<std::string, GameEngineSampler*>::iterator FindIter = ResourcesMap.find(_Name);

	if (FindIter != ResourcesMap.end())
	{
		return FindIter->second;
	}

	return nullptr;
}


GameEngineSampler* GameEngineSamplerManager::CreateAndFind(const std::string& _Name, const D3D11_SAMPLER_DESC& _Info)
{
	GameEngineSampler* FindRes = Find(_Name); // 찾아 주고...

	if (nullptr != FindRes) // 찾는게 있으면
	{
		return FindRes; // 그냥 그걸 리턴
	}

	// 찾는게 없다면? 바로 만들어준다..
	GameEngineSampler* NewRes = new GameEngineSampler();
	NewRes->SetName(_Name);
	NewRes->Create(_Info);

	ResourcesMap.insert(std::map<std::string, GameEngineSampler*>::value_type(_Name, NewRes)); // 만들어준걸 멤버 맵구조에 Insert

	return NewRes; // 리턴도 해 줄것
}