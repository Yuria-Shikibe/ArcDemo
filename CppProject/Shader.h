#pragma once
#include <filesystem>
#include <functional>
#include <string>

#include "GL_Uniform.h"
#include "Graphic.h"
#include "Matrix3D.h"
#include "Vector2D.h"

class Shader{
protected:
	using SHADER_INDEX = unsigned int;

    std::unordered_map<std::string, GLint> locationMap;
	SHADER_INDEX shaderRef = 0;
    std::function<void(const Shader&)> drawer = [](const Shader&){};

	static std::string readFile(const std::string& name, const std::string& path = Graphic::getPath("shader\\"));

	static std::string shaderTypeStr(const unsigned int shaderType);

	template <size_t size>
	static unsigned int attachShaders(const unsigned int (& shaders)[size]);

	static unsigned int compile(const std::string& src, const unsigned int shaderType);

	[[nodiscard]] GLint getLocation(const std::string& uniform) const{
        return locationMap.at(uniform);
    }

public:
	explicit Shader(const std::string& vertName, const std::string& fragName);

	explicit Shader(const std::string& name);

    Shader& operator=(const Shader& other) = delete;
    Shader& operator=(Shader&& other) = delete;

	Shader(const Shader& tgt) = delete;
    Shader(Shader&& tgt) = delete;
    ~Shader();

	SHADER_INDEX operator*() const;

	void apply() const;

	void bind() const{
		glUseProgram(get());
	}

	void unbind() const {
		glUseProgram(0);
	}

    void registerUniform(const std::string& param) {
        locationMap.insert_or_assign(param, glGetUniformLocation(shaderRef, param.data()));
    }

    template <size_t size>
    void registerUniform(const std::string(& params)[size]) {
	    for(const auto & param : params){
            registerUniform(param);
	    }
	}

	void setUniformer(const std::function<void(const Shader&)>& run) {
		drawer = run;
	}

    void setColor(const std::string& name, const Color& color) const
    {
        uniformColor(getLocation(name), color);
    }

    void setBool(const std::string& name, const bool value) const
    {
        glUniform1i(getLocation(name), static_cast<int>(value));
    }
    // ------------------------------------------------------------------------
    void setInt(const std::string& name, const int value) const
    {
        glUniform1i(getLocation(name), value);
    }
    // ------------------------------------------------------------------------
    void setFloat(const std::string& name, const float value) const
    {
        glUniform1f(getLocation(name), value);
    }
    // ------------------------------------------------------------------------
    void setVec2(const std::string& name, const float x, const float y) const
    {
        glUniform2f(getLocation(name), x, y);
    }

    void setVec2(const std::string& name, const Geom::Vector2D& vector) const{
        setVec2(name, vector.getX(), vector.getY());
	}
   
    // ------------------------------------------------------------------------
    void setMat3(const std::string& name, const Geom::Matrix3D& mat) const
    {
        glUniformMatrix3fv(glGetUniformLocation(shaderRef, name.data()), 1, GL_FALSE, mat.getVal());
    }

    void setTexture2D(const std::string& name, const Texture2D& texture, const int offset = 0) const
    {
        texture.bind(true, offset);
        uniformTexture(glGetUniformLocation(shaderRef, name.data()), offset);
    }
   

	SHADER_INDEX get() const;  // NOLINT(modernize-use-nodiscard)
};

