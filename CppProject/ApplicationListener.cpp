#include "ApplicationListener.h"
ApplicationListener::~ApplicationListener() = default;

void ApplicationListener::update(){
		
}

void ApplicationListener::dispose(){
		
}

ApplicationListener::ApplicationListener() = default;

bool operator==(const ApplicationListener& lhs, const ApplicationListener& rhs){
	return &lhs == & rhs;
}

bool operator!=(const ApplicationListener& lhs, const ApplicationListener& rhs){
	return !(lhs == rhs);
}
