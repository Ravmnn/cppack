#pragma once

#include <commands/command.hpp>



class CommandPackageAdd : public Command
{
private:
	std::string _packageName;


public:
	CommandPackageAdd(CPPack* cppack, CLI::App* app);


	void run() override;
};



class CommandPackageRemove : public Command
{
private:
	std::string _packageName;


public:
	CommandPackageRemove(CPPack* cppack, CLI::App* app);


	void run() override;
};



class CommandPackageList : public Command
{
public:
	CommandPackageList(CPPack* cppack, CLI::App* app);


	void run() override;
};
