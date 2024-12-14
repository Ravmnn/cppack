#pragma once

#include <commands/command.hpp>



class CommandIndexRegister : public Command
{
private:
	std::string _packagePath;


public:
	CommandIndexRegister(Project* project, CLI::App* app);


	void run() override;
};



class CommandIndexUnregister : public Command
{
private:
	std::string _packageName;


public:
	CommandIndexUnregister(Project* project, CLI::App* app);


	void run() override;
};



class CommandIndexList : public Command
{
public:
	CommandIndexList(Project* project, CLI::App* app);


	void run() override;
};
