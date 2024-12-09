#pragma once

#include <commands/command.hpp>



class CommandProjectInit : public Command
{
private:
	std::string _projectType;
	std::string _projectName;


public:
	CommandProjectInit(CPPack* cppack, CLI::App* app);


	void run() override;
};



class CommandProjectInfo : public Command
{
public:
	CommandProjectInfo(CPPack* cppack, CLI::App* app);


	void run() override;
};



class CommandProjectBuild : public Command
{
public:
	CommandProjectBuild(CPPack* cppack, CLI::App* app);


	void run() override;
};



class CommandProjectRun : public Command
{
public:
	CommandProjectRun(CPPack* cppack, CLI::App* app);


	void run() override;
};



class CommandProjectClean : public Command
{
public:
	CommandProjectClean(CPPack* cppack, CLI::App* app);


	void run() override;
};
