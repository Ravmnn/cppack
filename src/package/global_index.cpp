#include <package/global_index.hpp>

#include <cppack/cppack.hpp>
#include <project/project.hpp>
#include <project/project_exceptions.hpp>



static void copyPackageToGlobalPackageIndex(const Project& package)
{
	const fs::path packagePath = fs::absolute(package.getAbsoluteProjectPath());
	const fs::path targetPath = CPPack::cppackIndexDirectoryPath / package.getData().name;

	fs::create_directory(targetPath);

	fs::copy(packagePath, targetPath, fs::copy_options::recursive | fs::copy_options::overwrite_existing);
}



void GlobalPackageIndex::registerPackage(const Project& package)
{
	const ProjectData packageData = package.getData();

	InvalidPackageIndexHandling::throwIfRegistered(packageData.name);

	if (packageData.type == ProjectType::Executable)
		throw InvalidPackageIndexHandling("Cannot register a executable type package");

	copyPackageToGlobalPackageIndex(package);
}


void GlobalPackageIndex::unregisterPackage(const std::string& name)
{
	InvalidPackageIndexHandling::throwIfNotRegistered(name);

	fs::remove_all(CPPack::cppackIndexDirectoryPath / name);
}


bool GlobalPackageIndex::isPackageRegistered(const std::string& name) noexcept
{
	for (const auto& dir : fs::directory_iterator(CPPack::cppackIndexDirectoryPath))
		if (dir.path().stem().string() == name)
			return true;

	return false;
}



Project GlobalPackageIndex::getPackage(const std::string& name)
{
	InvalidPackageIndexHandling::throwIfNotRegistered(name);

	return Project(CPPack::cppackIndexDirectoryPath / name);
}
