#pragma once

class ApplicationListener{
public:
	virtual ~ApplicationListener();

	virtual void update();

	virtual void dispose();

	ApplicationListener();

	friend bool operator==(const ApplicationListener& lhs, const ApplicationListener& rhs);

	friend bool operator!=(const ApplicationListener& lhs, const ApplicationListener& rhs);

	// ApplicationListener(const ApplicationListener& o) = delete;
	// ApplicationListener(ApplicationListener&& o) = delete;
	// ApplicationListener& operator=(const ApplicationListener& o) = delete;
	// ApplicationListener& operator=(ApplicationListener&& o) = delete;
};
