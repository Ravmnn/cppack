#pragma once

#include <commands/command.hpp>



class CommandProjectInit : public Command
{
private:
	std::string _projectType;
	std::string _projectName;


public:
	CommandProjectInit(Project* project, CLI::App* app);


	void run() override;
};



class CommandProjectInfo : public Command
{
public:
	CommandProjectInfo(Project* project, CLI::App* app);


	void run() override;
};



class CommandProjectBuild : public Command
{
public:
	CommandProjectBuild(Project* project, CLI::App* app);


	void run() override;
};



class CommandProjectRun : public Command
{
public:
	CommandProjectRun(Project* project, CLI::App* app);


	void run() override;
};



class CommandProjectClean : public Command
{
public:
	CommandProjectClean(Project* project, CLI::App* app);


	void run() override;
};
