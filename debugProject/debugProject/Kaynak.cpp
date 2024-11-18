/*#pragma once
class Calculator
{
public:
	void Add(float a, float b, float* c) {
		*c = a + b;
	}
	void Substract(float a, float b, float* c) {
		*c = a - b;
	}
	void Multiply(float a, float b, float* c) {
		*c = a * b;
	}
	void Divide(float a, float b, float* c) {
		*c = a * b;
	}

};

//Gorev2

/*
	ornek:
	//Gercek kod degildir
	thread th1 = Thread(TaskOne::run);
	th1.start();


	//
	TaskONe* t1 = new TaskOne();
	TaskOne()->Start();

	//


*/

class TaskOne : public Task {
	virtual void run() {

		//handshake code 

		while (1) {
			Thread::sleep(100);
			//pinging code


		}
	}


};

class TaskTwo : public Task {
	virtual void run() {

	}


};


class TaskThree : public Task {
	virtual void run() {

	}


};


class TaskFour : public Task {
	virtual void run() {

	}


};


class Task {

public:

	bool enableTrace;

	virtual void run() = 0;

	virtual void initialize() = 0;

	virtual void startTimer() = 0;

	virtual void stopTimer() = 0;


	void traceChange(bool traceChange) {
		enableTrace = traceChange;
		checkTrace();
	}

private:
	void checkTrace() {
		if (enableTrace) {
			// timerlarý baþlat ve loglarý tutmak için verileri topla
		}
		else {
			// timerlarý sustur
		}
	}


};

//Gorev2


/*
	Calculator* calculator = new Calculator();
	float b = 0;
	calculator->Add(2, 6, &b); // b = 8 olmalý
	//Add, Substact, Multiply, Divide -> hepsinin return valuesu void


	*/