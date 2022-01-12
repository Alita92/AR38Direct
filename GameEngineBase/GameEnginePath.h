#pragma once
// �з� :
// �뵵 :
// ���� :
class GameEnginePath
{
protected:	// member Var
	std::filesystem::path path_;

public:
	GameEnginePath(); // default constructer ����Ʈ ������
	GameEnginePath(std::filesystem::path _path);
	~GameEnginePath(); // default destructer ����Ʈ �Ҹ���

public:		// delete constructer
	GameEnginePath(const GameEnginePath& _other); // default Copy constructer ����Ʈ ���������
	GameEnginePath(GameEnginePath&& _other) noexcept; // default RValue Copy constructer ����Ʈ RValue ���������

public:		//delete operator
	GameEnginePath& operator=(const GameEnginePath& _other) = delete; // default Copy operator ����Ʈ ���� ������
	GameEnginePath& operator=(const GameEnginePath&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

public:
	static std::string GetFileName(std::string _Path);

public:		//member Func
	// ������ ����ΰ� �ƴѰ��� �Ǵ��ϴ� �Լ�.
	bool IsExist();

	std::string GetFullPath();

};
