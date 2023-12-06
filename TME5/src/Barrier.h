#pragma once

#include <mutex>
#include <condition_variable>

namespace pr {

class Barrier {
	const int max;
	int counter;
	std::mutex m;
	std::condition_variable cv;
public:
	Barrier(int max):max(max),counter(0) {}

	void done() {
		std::unique_lock<std::mutex> lg(m);
		counter++;
		if(counter==max)
			cv.notify_all();
	}
	void waitFor(){
		std::unique_lock<std::mutex> lg(m);
		while(counter!=max)
			cv.wait(lg);
	}
};
}
