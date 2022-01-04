#include "PreCompile.h"
#include "GameEngineDirectory.h"
#include <Windows.h>
#include <io.h>
#include "GameEngineFile.h"
// Static Var
// Static Func

// constructer destructer
GameEngineDirectory::GameEngineDirectory()
{
	// std::string
	// ³»ºÎ¿¡ char* = new char[256]
	path_.resize(256);

	for (size_t i = 0; i < path_.size(); i++)
	{
		path_[i] = '\0';
	}

	GetCurrentDirectoryA(static_cast<DWORD>(path_.size()), &path_[0]);
	size_t ZeroCount = path_.find('\0');
	path_ = path_.substr(0, ZeroCount);
	path_ += "\\";
}

GameEngineDirectory::GameEngineDirectory(const GameEngineDirectory& _other)
	: GameEnginePath(_other)
{

}

GameEngineDirectory::~GameEngineDirectory()
{
}

GameEngineDirectory::GameEngineDirectory(GameEngineDirectory&& _other) noexcept
{
}

//member Func

std::string GameEngineDirectory::DirectoryName()
{
	// reverseFind
	size_t Count = path_.rfind("\\");
	if (std::string::npos == Count)
	{
		return path_;
	}

	//       5     10                
	// "aaaaa//bbbbb//ccccc"
	size_t StartCount = path_.rfind("\\", Count - 1);

	std::string Name = path_.substr(StartCount, Count);
	Name = Name.substr(1, Name.size() - 2);
	return Name;

}

void GameEngineDirectory::MoveParent()
{
	size_t Count = path_.rfind("\\");
	if (std::string::npos == Count)
	{
		return;
	}

	// "aaaaa//bbbbb//ccccc//"
	// aaaaa//bbbbb//
	size_t StartCount = path_.rfind("\\", Count - 1);
	path_ = path_.substr(0, StartCount + 1);

}

bool GameEngineDirectory::IsRoot()
{
	int Count = 0;

	for (size_t i = 0; i < path_.size(); i++)
	{
		if (path_[i] == '\\')
		{
			++Count;
		}
	}

	if (1 >= Count)
	{
		return true;
	}

	return false;
}

bool GameEngineDirectory::MoveParent(const std::string& _DirName)
{
	// 
	GameEngineDirectory CheckDir = GameEngineDirectory(*this);

	while (true)
	{
		if (_DirName == CheckDir.DirectoryName())
		{
			break;
		}

		CheckDir.MoveParent();

		if (true == CheckDir.IsRoot())
		{
			return false;
		}
	}

	this->path_ = CheckDir.path_;

	return true;
}


bool GameEngineDirectory::MoveChild(const std::string& _DirName)
{
	if (0 == _DirName.size())
	{
		return false;
	}

	std::string CheckPath = _DirName;

	if (CheckPath[0] == '\\')
	{
		CheckPath = CheckPath.substr(1, _DirName.size());
	}

	if (CheckPath[CheckPath.size() - 1] == '\\')
	{
		CheckPath = CheckPath.substr(0, _DirName.size() - 1);
	}

	GameEngineDirectory NewDir;
	NewDir.path_ = this->path_ + _DirName + "\\";

	if (false == NewDir.IsExist())
	{
		return false;
	}

	this->path_ += CheckPath + "\\";
	return true;
}

std::string GameEngineDirectory::PathToPlusFileName(const std::string& _FileName)
{
	return path_ + _FileName;
}

GameEngineFile GameEngineDirectory::PathToCreateFile(const std::string& _FileName)
{
	GameEngineFile NewFile = GameEngineFile(PathToPlusFileName(_FileName), "wb");
	NewFile.Close();
	// NewFile.Open();
	return NewFile;
}

GameEngineFile GameEngineDirectory::PathToGetFile(const std::string& _FileName)
{
	return GameEngineFile(PathToPlusFileName(_FileName));
}