#ifndef __GLSLProgram__
#define __GLSLProgram__

#include "core/base/GLBase.h"
#include "platform/PlatformMacros.h"

NS_MONKEY_BEGIN

class GLSLProgram {
    
public:
    
    GLSLProgram();
    virtual ~GLSLProgram();
    
    struct ShaderSourceItem {
        const char *src;
        GLint type;
    };
    
    static GLSLProgram* createFromFiles(const char* vertFilename, const char* fragFilename);
    
    static GLSLProgram* createFromStrings(const char* vertSrc, const char* fragSrc);
    
    bool setSourceFromFiles(const char* vertFilename, const char* fragFilename);
    
    bool setSourceFromStrings(const char* vertSrc, const char* fragSrc);
    
    bool setSourceFromStrings(ShaderSourceItem* src, int32_t count);
    
    void enable();
    
    void disable();
    
    void bindTexture2D(const char *name, int32_t unit, GLuint tex);
    
    void bindTexture2D(GLint index, int32_t unit, GLuint tex);
    
    void setUniform1i(const char *name, int32_t value);
    void setUniform1f(const char *name, float value);
    
    void setUniform2i(const char *name, int32_t x, int32_t y);
    void setUniform2f(const char *name, float x, float y);
    
    void setUniform3i(const char *name, int32_t x, int32_t y, int32_t z);
    void setUniform3f(const char *name, float x, float y, float z);
    
    void setUniform4f(const char *name, float x, float y, float z, float w);
    
    void setUniform3fv(const char *name, const float *value, int32_t count=1);
    void setUniform4fv(const char *name, const float *value, int32_t count=1);
    
    void setUniform1i(GLint index, int32_t value);
    void setUniform1f(GLint index, float value);
    
    void setUniform2i(GLint index, int32_t x, int32_t y);
    void setUniform2f(GLint index, float x, float y);
    
    void setUniform3i(GLint index, int32_t x, int32_t y, int32_t z);
    void setUniform3f(GLint index, float x, float y, float z);
    
    void setUniform4f(GLint index, float x, float y, float z, float w);
    
    void setUniform3fv(GLint index, const float *value, int32_t count=1);
    void setUniform4fv(GLint index, const float *value, int32_t count=1);
    
    void setUniformMatrix4fv(const GLchar *name, GLfloat *m, int32_t count=1, bool transpose=false);

    void setUniformMatrix4fv(GLint index, GLfloat *m, int32_t count=1, bool transpose=false);
    
    GLint getAttribLocation(const char* attribute);
    
    GLint getUniformLocation(const char* uniform);
    
    GLuint getProgram() { return m_program; }
    
    bool relink();
    
    GLuint m_program;
    
protected:
    bool checkCompileError(GLuint object, int32_t target);
    GLuint compileProgram(const char *vsource, const char *fsource);
    GLuint compileProgram(ShaderSourceItem* src, int32_t count);
    
    bool m_strict;
    
};

NS_MONKEY_END

#endif