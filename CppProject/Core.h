#pragma once
// #include "Camera.h"
#include "Batch.h"
#include "Camera.h"
#include "InputCore.h"
#include "key.h"
#include "OS.h"
#include "SpriteBatch.h"

namespace Core{
	inline GLFWwindow* window = nullptr;
	inline InputCore* input = nullptr;
	inline Camera* camera = nullptr;
	inline Batch* batch = nullptr;

	inline void initCore(GLFWwindow* w){
		window = w;
		input = new InputCore(w);
		camera = new Camera();
		batch = new SpriteBatch();

		batch->setProjection(camera->worldToScreen);

		input->scrollListener.emplace_back([](float x, const float y) -> void {
			camera->setScale(camera->getScale() + y * OS::deltaTime * 5.0f);
		});

		// Events::generalUpdateEvents.on<Events::ApplicationMainLoop_Pre>([](const Events::ApplicationMainLoop_Pre& e){
		// 	cout << "Update... | " << OS::globalTime << endl;
		// });

		static float baseMoveSpeed = 50;

		input->keyBinds->push_back(
			KeyFunc{ new KeyBind(GLFW_KEY_LEFT_SHIFT, GLFW_PRESS),
				[&](const int k) {baseMoveSpeed = 200;},
				[&](const int k) {baseMoveSpeed = 50 ;},
			}
		);

		input->keyBinds->push_back(
		KeyFunc{ new KeyBind(GLFW_KEY_A, GLFW_PRESS),
			[&](const int k) -> void {
				camera->trans(-baseMoveSpeed * OS::deltaTime, 0);
			}
		});
			
		input->keyBinds->push_back(
			KeyFunc{ new KeyBind(GLFW_KEY_D, GLFW_PRESS),
				[&](const int k) -> void {
					camera->trans(baseMoveSpeed * OS::deltaTime, 0);
				}
			});
			
		input->keyBinds->push_back(
			KeyFunc{ new KeyBind(GLFW_KEY_W, GLFW_PRESS),
				[&](const int k) -> void {
					camera->trans(0, baseMoveSpeed * OS::deltaTime);
				}
			});
			
		input->keyBinds->push_back(
			KeyFunc{ new KeyBind(GLFW_KEY_S, GLFW_PRESS),
				[&](const int k) -> void {
					camera->trans(0, -baseMoveSpeed * OS::deltaTime);
				}
			});

		OS::registerListener(input);
	}

	inline void dispose(){
		delete input;
		delete camera;
		delete batch;

		// OS::removeListener(*input);
	}
}
