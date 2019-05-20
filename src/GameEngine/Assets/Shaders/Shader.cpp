//
// Created by fuzuki on 05/04/19.
//

#include "Shader.h"

#include <iostream>


Shader& Shader::use() {
    glUseProgram(this->ID);
    return *this;
}

void Shader::compile(const char* vertexSource,
                     const char* fragmentSource,
                     const char* geometrySource) {
    GLuint sVertex, sFragment, sGeometry;

    // Vertex Shader
    sVertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(sVertex, 1, &vertexSource, nullptr);
    glCompileShader(sVertex);
    checkCompileErrors(sVertex, "VERTEX");

    // Fragment Shader
    sFragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(sFragment, 1, &fragmentSource, nullptr);
    glCompileShader(sFragment);
    checkCompileErrors(sFragment, "FRAGMENT");

    // Geometry Shader
    if (geometrySource != nullptr) {
        sGeometry = glCreateShader(GL_GEOMETRY_SHADER);
        glShaderSource(sGeometry, 1, &geometrySource, nullptr);
        glCompileShader(sGeometry);
        checkCompileErrors(sGeometry, "GEOMETRY");
    }

    // Shader Program
    this->ID = glCreateProgram();
    glAttachShader(this->ID, sVertex);
    glAttachShader(this->ID, sFragment);
    if (geometrySource != nullptr)
        glAttachShader(this->ID, sGeometry);
    glLinkProgram(this->ID);
    checkCompileErrors(this->ID, "PROGRAM");

    // Delete Shaders (already linked -> no more use)
    glDeleteShader(sVertex);
    glDeleteShader(sFragment);
    if (geometrySource != nullptr)
        glDeleteShader(sGeometry);
}

void Shader::setFloat(const GLchar* name,
                      GLfloat value,
                      GLboolean useShader) {
    if (useShader)
        this->use();
    glUniform1f(glGetUniformLocation(this->ID, name),
                value);
}

void Shader::setInteger(const GLchar* name,
                        GLint value,
                        GLboolean useShader) {
    if (useShader)
        this->use();
    glUniform1i(glGetUniformLocation(this->ID, name),
                value);
}

void Shader::setVector2f(const GLchar* name,
                         GLfloat x, GLfloat y,
                         GLboolean useShader) {
    if (useShader)
        this->use();
    glUniform2f(glGetUniformLocation(this->ID, name),
                x, y);
}

void Shader::setVector2f(const GLchar* name,
                         const glm::vec2& value,
                         GLboolean useShader) {
    if (useShader)
        this->use();
    glUniform2f(glGetUniformLocation(this->ID, name),
                value.x, value.y);
}

void Shader::setVector3f(const GLchar* name, GLfloat x, GLfloat y, GLfloat z,
                         GLboolean useShader) {
    if (useShader)
        this->use();
    glUniform3f(glGetUniformLocation(this->ID, name),
                x, y, z);
}

void Shader::setVector3f(const GLchar* name, const glm::vec3& value,
                         GLboolean useShader) {
    if (useShader)
        this->use();
    glUniform3f(glGetUniformLocation(this->ID, name),
                value.x, value.y, value.z);
}

void Shader::setVector4f(const GLchar* name,
                         GLfloat x, GLfloat y, GLfloat z, GLfloat w,
                         GLboolean useShader) {
    if (useShader)
        this->use();
    glUniform4f(glGetUniformLocation(this->ID, name),
                x, y, z, w);
}

void Shader::setVector4f(const GLchar* name,
                         const glm::vec4& value,
                         GLboolean useShader) {
    if (useShader)
        this->use();
    glUniform4f(glGetUniformLocation(this->ID, name),
                value.x, value.y, value.z, value.w);
}

void Shader::setMatrix4(const GLchar* name,
                        const glm::mat4& matrix,
                        GLboolean useShader) {
    if (useShader)
        this->use();
    glUniformMatrix4fv(glGetUniformLocation(this->ID, name), 1, GL_FALSE,
                       glm::value_ptr(matrix));
}

void Shader::checkCompileErrors(GLuint object, std::string type) {
    GLint success;
    GLchar infoLog[1024];

    if (type != "PROGRAM") {
        glGetShaderiv(object, GL_COMPILE_STATUS, &success);

        if (!success) {
            glGetShaderInfoLog(object, 1024, nullptr, infoLog);
            std::cerr << "ERROR::SHADER: compile-time error: "
                      << type
                      << std::endl
                      << infoLog
                      << "----------------------------------------"
                      << std::endl;
        }
    } else {
        glGetProgramiv(object, GL_LINK_STATUS, &success);

        if (!success) {
            glGetProgramInfoLog(object, 1024, nullptr, infoLog);
            std::cerr << "ERROR::SHADER: link-time error: "
                      << type
                      << std::endl
                      << infoLog
                      << std::endl
                      << "----------------------------------------"
                      << std::endl;
        }
    }
}
