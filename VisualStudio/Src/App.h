#pragma once

class Scene;

class App
{
public:
	App();
	~App();
	bool init(int window_w, int window_h);
	void release();

	bool start();
	bool stop();

private:
	void loop();
	bool stopRequest_, running_; //loop control

	Scene* scene_;
};