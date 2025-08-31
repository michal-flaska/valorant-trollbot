#pragma once
#include <vector>
#include <thread>
#include <atomic>
#include <functional>

class ThreadManager {
private:
	std::vector<std::thread> threads_;
	std::atomic<bool> running_{ true };

public:
	~ThreadManager() {
		shutdown();
	}

	void addThread(std::function<void()> task) {
		threads_.emplace_back(task);
	}

	void shutdown() {
		running_ = false;
		for (auto& thread : threads_) {
			if (thread.joinable()) {
				thread.join();
			}
		}
		threads_.clear();
	}

	bool isRunning() const {
		return running_.load();
	}

	void stop() {
		running_ = false;
	}
};
