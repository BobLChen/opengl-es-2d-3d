#include "core/material/GLSLProgram.h"
#include "core/utils/Log.h"

NS_MONKEY_BEGIN

const char *readFile(const char* filePath, long &length) {
    FILE *fb = fopen(filePath, "rb");
    if (!fb) {
        printf("Faild to open file:%s\n", filePath);
        return NULL;
    }
    fseek(fb, 0, SEEK_END);
    length = ftell(fb);
    fseek(fb, 0, SEEK_SET);
    char *data = new char[length + 1];
    fread(data, 1, length, fb);
    data[length] = '\0';
    fclose(fb);
    
    return data;
}

GLSLProgram::GLSLProgram() : m_program(0), m_strict(false) {
    
}

GLSLProgram::~GLSLProgram() {
    if (m_program) {
        glDeleteProgram(m_program);
    }
}

GLSLProgram* GLSLProgram::createFromFiles(const char *vertFilename, const char *fragFilename) {
    
    GLSLProgram *prog = new GLSLProgram();
    if (prog->setSourceFromFiles(vertFilename, fragFilename)) {
        return prog;
    } else {
        delete prog;
        return NULL;
    }
}

GLSLProgram* GLSLProgram::createFromStrings(const char *vertSrc, const char *fragSrc) {
    GLSLProgram *prog = new GLSLProgram();
    if (prog->setSourceFromStrings(vertSrc, fragSrc)) {
        return prog;
    } else {
        delete prog;
        return NULL;
    }
}

bool GLSLProgram::setSourceFromFiles(const char *vertFilename, const char *fragFilename) {
    long vertLengh = 0;
    const char *vertCode = readFile(vertFilename, vertLengh);
    const char *fragCode = readFile(fragFilename, vertLengh);
    if (!vertCode || !fragCode) {
        return false;
    }
    if (setSourceFromStrings(vertCode, fragCode)) {
        return true;
    }
    
    delete vertCode;
    delete fragCode;
    
    return false;
}

bool GLSLProgram::setSourceFromStrings(const char *vertSrc, const char *fragSrc) {
    if (m_program) {
        glDeleteProgram(m_program);
        m_program = 0;
    }
    m_program = compileProgram(vertSrc, fragSrc);
    return m_program != 0;
}

GLuint GLSLProgram::compileProgram(const char *vsource, const char *fsource) {
    
    GLuint vertShader = glCreateShader(GL_VERTEX_SHADER);  // create shader
    GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER); // create shader
    
    glShaderSource(vertShader, 1, &vsource, NULL);
    glShaderSource(fragShader, 1, &fsource, NULL);
    
    // compile vertex program
    glCompileShader(vertShader);
    if (!checkCompileError(vertShader, GL_VERTEX_SHADER)) {
        LOGI("Faild to compile Vertex Shader");
        return 0;
    }
    
    glCompileShader(fragShader);
    if (!checkCompileError(fragShader, GL_FRAGMENT_SHADER)) {
        LOGI("Faild to compile Fragment Shader");
        return 0;
    }
    
    GLuint program = glCreateProgram();
    // program attack shader
    glAttachShader(program, vertShader);
    glAttachShader(program, fragShader);
    
    // upload program
    glLinkProgram(program);
    
    GLint success = 0;
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    
    if (!success) {
        GLint bufLength = 0;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &bufLength);
        char *buf = new char[bufLength];
        glGetProgramInfoLog(program, bufLength, NULL, buf);
        LOGI("Cound not link program:\n%s\n", buf);
        delete [] buf;
    }
    
    // delete shader
    glDeleteShader(vertShader);
    glDeleteShader(fragShader);
    
    LOGI("Program Create Success");
    
    return program;
}

bool GLSLProgram::checkCompileError(GLuint shader, int32_t target) {
    GLint compiled = 0;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
    if (!compiled) {
        LOGE("Error compiling shader");
        GLint infoLen = 0;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);
        char *buf = new char[infoLen];
        glGetShaderInfoLog(shader, infoLen, NULL, buf);
        LOGI("Shader log:\n%s\n", buf);
        delete [] buf;
        return false;
    }
    return true;
}

void GLSLProgram::enable() {
    glUseProgram(m_program);
}

void GLSLProgram::disable() {
    glUseProgram(0);
}

bool GLSLProgram::relink() {
    glLinkProgram(m_program);
    GLint success = 0;
    glGetProgramiv(m_program, GL_LINK_STATUS, &success);
    if (!success) {
        GLint bufLength = 0;
        glGetProgramiv(m_program, GL_INFO_LOG_LENGTH, &bufLength);
        char *buf = new char[bufLength];
        glGetProgramInfoLog(m_program, bufLength, NULL, buf);
        LOGI("Count not link program:\n%s\b", buf);
        return false;
    }
    return true;
}

GLint GLSLProgram::getAttribLocation(const char *attribute) {
    GLint result = glGetAttribLocation(m_program, attribute);
    if (result == -1) {
        LOGI("Count not find attribute \"%s\" in program %d", attribute, m_program);
    }
    return result;
}

GLint GLSLProgram::getUniformLocation(const char *uniform) {
    GLint result = glGetUniformLocation(m_program, uniform);
    if (result == -1) {
        LOGI("Count not find uniform \"%s\" in program %d", uniform, m_program);
    }
    return result;
}

void GLSLProgram::bindTexture2D(const char *name, int32_t unit, GLuint tex) {
    GLint loc = getUniformLocation(name);
    if (loc >= 0) {
        glUniform1i(loc, unit);
        glActiveTexture(GL_TEXTURE0 + unit);
        glBindTexture(GL_TEXTURE_2D, tex);
    }
}

void GLSLProgram::bindTexture2D(GLint index, int32_t unit, GLuint tex) {
    glUniform1i(index, unit);
    glActiveTexture(GL_TEXTURE0 + unit);
    glBindTexture(GL_TEXTURE_2D, tex);
}

void GLSLProgram::setUniform1i(const char *name, int32_t value) {
    GLint loc = getUniformLocation(name);
    if (loc >= 0) {
        glUniform1i(loc, value);
    }
}

void GLSLProgram::setUniform1i(GLint index, int32_t value) {
    if (index >= 0) {
        glUniform1i(index, value);
    }
}

void GLSLProgram::setUniform2i(const char *name, int32_t x, int32_t y) {
    GLint loc = getUniformLocation(name);
    if (loc >= 0) {
        glUniform2i(loc, x, y);
    }
}

void GLSLProgram::setUniform2i(GLint index, int32_t x, int32_t y) {
    if (index >= 0) {
        glUniform2i(index, x, y);
    }
}

void GLSLProgram::setUniform3i(const char *name, int32_t x, int32_t y, int32_t z) {
    GLint loc = getUniformLocation(name);
    if (loc >= 0) {
        glUniform3i(loc, x, y, z);
    }
}

void GLSLProgram::setUniform3i(GLint index, int32_t x, int32_t y, int32_t z) {
    if (index >= 0) {
        glUniform3i(index, x, y, z);
    }
}

void GLSLProgram::setUniform1f(const char *name, float value) {
    GLint loc = getUniformLocation(name);
    if (loc >= 0) {
        glUniform1f(loc, value);
    }
}

void GLSLProgram::setUniform1f(GLint index, float value) {
    if (index >= 0) {
        glUniform1f(index, value);
    }
}

void GLSLProgram::setUniform2f(const char *name, float x, float y) {
    GLint loc = getUniformLocation(name);
    if (loc >= 0) {
        glUniform2f(loc, x, y);
    }
}

void GLSLProgram::setUniform2f(GLint index, float x, float y) {
    if (index >= 0) {
        glUniform2f(index, x, y);
    }
}

void GLSLProgram::setUniform3f(const char *name, float x, float y, float z) {
    GLint loc = getUniformLocation(name);
    if (loc >= 0) {
        glUniform3f(loc, x, y, z);
    }
}

void GLSLProgram::setUniform3f(GLint index, float x, float y, float z) {
    if (index >= 0) {
        glUniform3f(index, x, y, z);
    }
}

void GLSLProgram::setUniform4f(const char *name, float x, float y, float z, float w) {
    GLint loc = getUniformLocation(name);
    if (loc >= 0) {
        glUniform4f(loc, x, y, z, w);
    }
}

void GLSLProgram::setUniform4f(GLint index, float x, float y, float z, float w) {
    if (index >= 0) {
        glUniform4f(index, x, y, z, w);
    }
}

void GLSLProgram::setUniform3fv(const char *name, const float *value, int32_t count) {
    GLint loc = getUniformLocation(name);
    if (loc >= 0) {
        glUniform3fv(loc, count, value);
    }
    
}

void GLSLProgram::setUniform3fv(GLint index, const float *value, int32_t count) {
    if (index >= 0) {
        glUniform3fv(index, count, value);
    }
    
}

void GLSLProgram::setUniform4fv(const char *name, const float *value, int32_t count) {
    GLint loc = getUniformLocation(name);
    if (loc >= 0) {
        glUniform4fv(loc, count, value);
    }
}

void GLSLProgram::setUniform4fv(GLint index, const float *value, int32_t count) {
    if (index >= 0) {
        glUniform4fv(index, count, value);
    }
}

void GLSLProgram::setUniformMatrix4fv(const char *name, float *m, int32_t count, bool transpose) {
    GLint loc = getUniformLocation(name);
    if (loc >= 0) {
        glUniformMatrix4fv(loc, count, transpose, m);
    }
}

void GLSLProgram::setUniformMatrix4fv(GLint index, float *m, int32_t count, bool transpose) {
    if (index >= 0) {
        glUniformMatrix4fv(index, count, transpose, m);
    }
}

NS_MONKEY_END
