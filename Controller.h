#pragma once

class Controller : public Component
{
public:
	Controller();
	Controller(string s) { cout << s; }
	~Controller();
	void Update();
	int s = 0;
};



Controller::Controller()
{

}


Controller::~Controller()
{
}

void Controller::Update()
{
	
}
