#pragma once

#include <commands/command.hpp>



class CommandPackageAdd : public Command
{
private:
	std::string _packageName;


public:
	CommandPackageAdd(Project* project, CLI::App* app);


	void run() override;
};



class CommandPackageRemove : public Command
{
private:
	std::string _packageName;


public:
	CommandPackageRemove(Project* project, CLI::App* app);


	void run() override;
};



class CommandPackageList : public Command
{
public:
	CommandPackageList(Project* project, CLI::App* app);


	void run() override;
};
