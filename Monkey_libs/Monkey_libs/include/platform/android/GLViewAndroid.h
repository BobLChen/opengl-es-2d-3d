#include "platform/GLView.h"
#include "platform/PlatformMacros.h"

NS_MONKEY_BEGIN

class GLViewAndroid : public GLView {
	
public:
	
	GLViewAndroid();
	virtual ~GLViewAndroid();
	
    /**
     *  opengl是否准备好
     *  @return
     */
    virtual bool isOpenGLReady() override;
    /**
     *  swap buffer
     */
    virtual void swapBuffers() override;
    /**
     *  设置键盘状态
     *  @param bOpen
     */
    virtual void setIMEKeyboardState(bool bOpen) override;
};

NS_MONKEY_END

