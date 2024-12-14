#pragma once

#include <CLI11.hpp>

#include <cppack/cppack.hpp>



class Command
{
protected:
	CLI::App* const app;

	CLI::App* thisCommand;

	const std::string name;
	const std::string description;


public:
	Project* const project;


	Command() = delete;

	Command(Project* project, CLI::App* app, const std::string& name, const std::string& description);


	CLI::App* get_app() const noexcept { return app; }

	const std::string& get_name() const noexcept { return name; }
	const std::string& get_description() const noexcept { return description; }


	virtual void run() = 0;
};
