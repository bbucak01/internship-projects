#include "Task.h"

using namespace std;


int main(int argc, char* argv[]) {

	
	

	
		

	TaskOne* one = new TaskOne;
	std::thread t1(&TaskOne::run, one); // Correct way to pass the member function to a thread

	TaskTwo* two = new TaskTwo;
	std::thread t2(&TaskTwo::run, two );

	TaskThree* three = new TaskThree;
	std::thread t3(&TaskThree::run, three);

	TaskFour* four = new TaskFour;
	std::thread t4(&TaskFour::run, four);

	TaskFive* five = new TaskFive;
	std::thread t5(&TaskFive::run, five);

	TaskSix* six = new TaskSix;
	std::thread t6(&TaskSix::run, six);

	
	while (1);

	return 0;
}