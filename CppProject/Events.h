#pragma once

#include <functional>
#include <typeindex>
#include <unordered_map>

namespace Events {
    struct EventType {};

    struct Draw_After final : EventType {};
    struct Draw final : EventType {};
    struct Draw_Prepare final : EventType {};
    struct AssertLoad_Prepare final : EventType {};
    struct AssertLoad_Completed final : EventType {};
    struct ApplicationMainLoop_Pre final : EventType {};
    struct ApplicationMainLoop_After final : EventType {};

    template <typename T>
    concept Event = std::is_base_of_v<EventType, T>;

    class EventManager {
    protected:
        std::unordered_map<std::type_index, std::vector<std::function<void(const void*)>>> events;

    public:
        template <Event T>
        void fire(const T& event){
	        for (const auto eventType = std::type_index(typeid(T)); const auto& listener : events[eventType]) {
                listener(&event);
            }
        }

        template <Event T>
        void on(const std::function<void(const T&)>& func) {
            const auto eventType = std::type_index(typeid(T));
            events[eventType].emplace_back([func](const void* event) {
                func(*static_cast<const T*>(event));
            });
        }
    };

    inline EventManager generalCheckEvents{};
    inline EventManager generalUpdateEvents{};
}
