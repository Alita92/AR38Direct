#pragma once

// �з� : 
// �뵵 : 
// ���� : 
class CustomSettingBackground
{
private:	// member Var

public:
	CustomSettingBackground(); // default constructer ����Ʈ ������
	~CustomSettingBackground(); // default destructer ����Ʈ �Ҹ���

protected:		// delete constructer
	CustomSettingBackground(const CustomSettingBackground& _other) = delete; // default Copy constructer ����Ʈ ���������
	CustomSettingBackground(CustomSettingBackground&& _other) noexcept; // default RValue Copy constructer ����Ʈ RValue ���������

private:		//delete operator
	CustomSettingBackground& operator=(const CustomSettingBackground& _other) = delete; // default Copy operator ����Ʈ ���� ������
	CustomSettingBackground& operator=(const CustomSettingBackground&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

public:
};

