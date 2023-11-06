#pragma once

class AbstractKeyBind {
public:
	virtual ~AbstractKeyBind() = default;
	virtual bool activated(GLFWwindow* window) const {
		return false;
	}

	virtual int keyCode(){
		return GLFW_KEY_UNKNOWN;
	}

	AbstractKeyBind() = default;
};

class KeyBind final : public AbstractKeyBind {
protected:
	int key = 0;
	int statement = GLFW_PRESS;

public:
	KeyBind(const int key, const int statement) : AbstractKeyBind(),
		key(key),
		statement(statement) {
	}

	int keyCode() override{
		return key;
	}

	~KeyBind() override = default;

	KeyBind(const KeyBind& other)
	=
	default;

	KeyBind(KeyBind&& other) noexcept
		: AbstractKeyBind(other),
		  key(other.key),
		  statement(other.statement){
	}

	KeyBind& operator=(const KeyBind& other){
		if(this == &other) return *this;
		AbstractKeyBind::operator =(other);
		key = other.key;
		statement = other.statement;
		return *this;
	}

	KeyBind& operator=(KeyBind&& other) noexcept{
		if(this == &other) return *this;
		AbstractKeyBind::operator =(other);
		key = other.key;
		statement = other.statement;
		return *this;
	}

	bool activated(GLFWwindow* window) const override {
		return glfwGetKey(window, key) == statement;
	}
};

class KeyBindGroup final : public AbstractKeyBind {
protected:
	vector<KeyBind> binds;


public:
	// bool activated(GLFWwindow* window) const override{
	// 	return glfwGetKey(window, key) == statement;
	// }
};


struct KeyFunc {
	AbstractKeyBind* bind;
	std::function<void(const int)> func;
	std::function<void(const int)> elseFunc = nullptr;

	KeyFunc(const KeyFunc& other) = default;

	KeyFunc(KeyFunc&& other) noexcept
		: bind(other.bind),
		  func(std::move(other.func)),
		  elseFunc(std::move(other.elseFunc)){
	}

	KeyFunc& operator=(const KeyFunc& other){
		if(this == &other) return *this;
		bind = other.bind;
		func = other.func;
		elseFunc = other.elseFunc;
		return *this;
	}

	KeyFunc& operator=(KeyFunc&& other) noexcept{
		if(this == &other) return *this;
		bind = other.bind;
		func = std::move(other.func);
		elseFunc = std::move(other.elseFunc);
		return *this;
	}

	~KeyFunc() {
		// delete bind;
	}

	KeyFunc(AbstractKeyBind* b, const std::function<void(const int)>& func)
		: bind(b),
		func(func) {
	}

	KeyFunc(AbstractKeyBind* bind, const std::function<void(const int)>& func, const std::function<void(const int)>& elseFunc)
		: bind(bind),
		  func(func),
		  elseFunc(elseFunc){
	}
};