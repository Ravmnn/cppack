#pragma once

#include <commands/command.hpp>



class CommandIndexRegister : public Command
{
private:
	std::string _packagePath;


public:
	CommandIndexRegister(CPPack* cppack, CLI::App* app);


	void run() override;
};



class CommandIndexUnregister : public Command
{
private:
	std::string _packageName;


public:
	CommandIndexUnregister(CPPack* cppack, CLI::App* app);


	void run() override;
};



class CommandIndexExist : public Command
{
private:
	std::string _packageName;


public:
	CommandIndexExist(CPPack* cppack, CLI::App* app);


	void run() override;
};



class CommandIndexList : public Command
{
public:
	CommandIndexList(CPPack* cppack, CLI::App* app);


	void run() override;
};
