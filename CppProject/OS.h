#pragma once
#include <functional>
#include <iostream>
#include <vector>

#include "ApplicationListener.h"
#include "Events.h"
#include "Renderer.h"

namespace OS{
    // extern inline int width, height;

	static Events::ApplicationMainLoop_Pre preEvent;
	static Events::ApplicationMainLoop_After afterEvent;

	inline float deltaTime = 0.0f;
	inline float globalTime = 0.0f;
	inline float globalTick = 0.0f;

    inline std::vector<ApplicationListener*> applicationListeners;

	inline std::vector<std::function<void()>> postTasks;

	inline void registerListener(ApplicationListener* listener){
		applicationListeners.push_back(listener);
		std::cout << "Registered Listener::" << typeid(*listener).name() << std::endl;
	}

	inline void removeListener(ApplicationListener* listener){
		std::erase(applicationListeners, listener);
	}

	inline void update(){
		for(const auto & postTask : postTasks){
			postTask();
		}

		postTasks.clear();

		Events::generalUpdateEvents.fire(preEvent);

		for(const auto & listener : applicationListeners){
			listener->update();
		}

		getRenderer().draw();

		Events::generalUpdateEvents.fire(afterEvent);
	}
}


