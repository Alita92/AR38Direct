#pragma once
#include <string>

// �з� : �����
// �뵵 : �޸𸮰��� �޼��� ��� �α�
// ���� : ��� ����� ���� ����� ���⿡ ��Ƴ��´�.
class GameEngineDebug
{
private:	// member Var

public:
	static void LeakCheckOn();

protected:
	GameEngineDebug(); // default constructer ����Ʈ ������
	~GameEngineDebug(); // default destructer ����Ʈ �Ҹ���

protected:		// delete constructer
	GameEngineDebug(const GameEngineDebug& _other) = delete; // default Copy constructer ����Ʈ ���������
	GameEngineDebug(GameEngineDebug&& _other) noexcept; // default RValue Copy constructer ����Ʈ RValue ���������

private:		//delete operator
	GameEngineDebug& operator=(const GameEngineDebug& _other) = delete; // default Copy operator ����Ʈ ���� ������
	GameEngineDebug& operator=(const GameEngineDebug&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

public:		//member Func
	static void MsgBoxError(const std::string& _Text);
	static void AssertFalse();
	static void OutPutDebugString(const std::string& _Text);


};
