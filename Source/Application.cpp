#include <Test/RayRayTest.h>
#include <Tool/Vector2.h>
#include <string>
#include <cstdio>

static const std::string OutputFileName = "output";
static constexpr Tool::Vector2u OutputSize = {200, 100};
static constexpr size_t SampleCount = 128u;
static constexpr size_t ThreadCount = 6u;
static constexpr float Gamma = 2.2f;

static void RunTestMenu();
static void PrintMenu(const std::vector<Test::RayRayTest::Spawner>& spawners);
static void RunMenuLoop(const std::vector<Test::RayRayTest::Spawner>& spawners);

int main()
{
	RunTestMenu();

	return 0;
}

static void RunTestMenu()
{
	auto& spawners = Test::RayRayTest::GetSpawners();

	PrintMenu(spawners);
	RunMenuLoop(spawners);
}

static void PrintMenu(const std::vector<Test::RayRayTest::Spawner>& spawners)
{
	for( auto& spawner : spawners )
	{
		std::printf("%zu - %s\n", spawner.Index, spawner.Name.c_str());
	}

	std::printf("%zu - Exit\n", spawners.size()+1);
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

			auto output = test->Run(OutputSize, SampleCount, ThreadCount);
			output.Save(OutputFileName, Gamma);

			std::printf("Render complete\n");
			delete test;
		}
		else if(choice == spawners.size()+1)
		{
			isRunning = false;
		}
		else
		{
			std::printf("Index out of range!\n");
		}
	}
}
