#pragma once

#include <commands/command.hpp>



class CommandInit : public Command
{
private:
	std::string _projectType;
	std::string _projectName;


public:
	CommandInit(CLI::App* app);


	void run() override;
};



class CommandInfo : public Command
{
public:
	CommandInfo(CLI::App* app);


	void run() override;
};



class CommandBuild : public Command
{
public:
	CommandBuild(CLI::App* app);


	void run() override;
};



class CommandRun : public Command
{
public:
	CommandRun(CLI::App* app);


	void run() override;
};



class CommandClean : public Command
{
public:
	CommandClean(CLI::App* app);


	void run() override;
};
