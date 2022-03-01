#pragma once

// 분류 : 
// 용도 : 
// 설명 : 
class CustomSettingBackground
{
private:	// member Var

public:
	CustomSettingBackground(); // default constructer 디폴트 생성자
	~CustomSettingBackground(); // default destructer 디폴트 소멸자

protected:		// delete constructer
	CustomSettingBackground(const CustomSettingBackground& _other) = delete; // default Copy constructer 디폴트 복사생성자
	CustomSettingBackground(CustomSettingBackground&& _other) noexcept; // default RValue Copy constructer 디폴트 RValue 복사생성자

private:		//delete operator
	CustomSettingBackground& operator=(const CustomSettingBackground& _other) = delete; // default Copy operator 디폴트 대입 연산자
	CustomSettingBackground& operator=(const CustomSettingBackground&& _other) = delete; // default RValue Copy operator 디폴트 RValue 대입연산자

public:
};

