#include <Test/RayRayTest.h>
#include <Tool/Vector2.h>
#include <Tool/Timer.h>
#include <string>
#include <cstdio>

static const std::string ArgvSelectionTag = "-rayraytest=";
static const std::string OutputFileName = "output";
static constexpr Tool::Vector2u OutputSize = {400, 225};
static constexpr size_t ScatterDepth = 50u;
static constexpr size_t SampleCount = 128u;
static constexpr size_t ThreadCount = 6u;
static constexpr float Gamma = 2.2f;
static constexpr float HDRExposure = 2.0f;
static constexpr size_t BloomSize = 5u;

static int GetArgvSelection(int argc, const char* argv[]);
static void RunSelection(size_t selection);
static void RunTestMenu();
static void PrintMenu(const std::vector<Test::RayRayTest::Spawner>& spawners);
static void RunMenuLoop(const std::vector<Test::RayRayTest::Spawner>& spawners);

int main(int argc, const char* argv[])
{
	int selection = GetArgvSelection(argc, argv);

	if(selection > 0)
	{
		RunSelection(static_cast<size_t>(selection));
	}
	else
	{
		RunTestMenu();
	}
	
	return 0;
}

static int GetArgvSelection(int argc, const char* argv[])
{
	int selection = -1;
	for( int i=0 ; i<argc ; ++i )
	{
		std::string argument = argv[i];
		size_t tagIndex = argument.find(ArgvSelectionTag);
		if(tagIndex != std::string::npos)
		{
			size_t selectionIndex = tagIndex + ArgvSelectionTag.size();
			auto selectionString = argument.substr(selectionIndex);

			selection = std::stoi(selectionString);
			break;
		}
	}

	return selection;
}

static void RunSelection(size_t selection)
{
	auto& spawners = Test::RayRayTest::GetSpawners();

	Test::RayRayTest* test = nullptr;
	for( auto& spawner : spawners )
	{
		if(spawner.Index == selection)
		{
			auto testSpawner = spawner.Function;
			test = testSpawner();
		}
	}

	if(test == nullptr)
	{
		std::printf("Test %zu not found!\n", selection);
		std::getchar();
	}
	else
	{
		auto output = test->Run(OutputSize, ScatterDepth, SampleCount, ThreadCount, Gamma, HDRExposure, BloomSize);
		output.Save(OutputFileName);

		delete test;
	}
}

static void RunTestMenu()
{
	auto& spawners = Test::RayRayTest::GetSpawners();

	PrintMenu(spawners);
	RunMenuLoop(spawners);
}

static void PrintMenu(const std::vector<Test::RayRayTest::Spawner>& spawners)
{
	std::printf("0 - Exit\n");
	for( auto& spawner : spawners )
	{
		std::printf("%zu - %s\n", spawner.Index, spawner.Name.c_str());
	}
}

static void RunMenuLoop(const std::vector<Test::RayRayTest::Spawner>& spawners)
{
	bool isRunning = true;
	while(isRunning)
	{
		int choice;
		std::printf("\nChoice = ");
		std::scanf("%d", &choice);

		if(choice > 0 && 
		   choice <= spawners.size())
		{
			auto testSpawner = spawners.at(choice-1).Function;
			auto test = testSpawner();

			Tool::ScopedTimer timer("Render completed in %time sec.\n");
			auto output = test->Run(OutputSize, ScatterDepth, SampleCount, ThreadCount, Gamma, HDRExposure, BloomSize);
			output.Save(OutputFileName);

			delete test;
		}
		else if(choice == 0)
		{
			isRunning = false;
		}
		else
		{
			std::printf("Index out of range!\n");
		}
	}
}
