/*****************************************************************************
 *
 * (Mushware file header version 1.0)
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.co.uk.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/


/*
 * $Id: SDLAppHandler.cpp,v 1.7 2002/07/08 14:22:02 southa Exp $
 * $Log: SDLAppHandler.cpp,v $
 * Revision 1.7  2002/07/08 14:22:02  southa
 * Rotated desks
 *
 * Revision 1.6  2002/07/07 13:44:18  southa
 * Screen size config variables
 *
 * Revision 1.5  2002/07/06 18:04:18  southa
 * More designer work
 *
 * Revision 1.4  2002/07/02 18:36:56  southa
 * Selection in designer, mouse buttons
 *
 * Revision 1.3  2002/06/27 12:36:06  southa
 * Build process fixes
 *
 * Revision 1.2  2002/06/23 10:42:33  southa
 * SDL input
 *
 * Revision 1.1  2002/06/21 18:50:16  southa
 * SDLAppHandler added
 *
 */

#include "SDLAppHandler.h"

#include "GLStandard.h"
#include "GLUtils.h"
#include "GLAppSignal.h"

#include "mushPlatform.h"
#include "mushMedia.h"


SDLAppHandler::SDLAppHandler():
    m_redisplay(false),
    m_visible(true),
    m_keyState(GLKeys::kNumberOfKeys),
    m_mouseX(0),
    m_mouseY(0),
    m_mouseXDelta(0),
    m_mouseYDelta(0)
{}

void
SDLAppHandler::Initialise(void)
{
    m_mouseX=0;
    m_mouseY=0;
    m_mouseXDelta=0;
    m_mouseYDelta=0;
}

void
SDLAppHandler::Idle(void)
{
    CoreAppHandler::Idle();
}

void
SDLAppHandler::Display(void)
{
}

void
SDLAppHandler::KeyboardSignal(const GLKeyboardSignal& inSignal)
{

    COREASSERT(inSignal.keyValue.ValueGet() < m_keyState.size());
    m_keyState[inSignal.keyValue.ValueGet()]=inSignal.keyDown;

    if (inSignal.keyValue.ValueGet() == 27 && inSignal.keyDown)
    {
        // Escape key pressed
        CoreAppHandler::Instance().Signal(CoreAppSignal(CoreAppSignal::kEscape));
    }
}

bool
SDLAppHandler::KeyStateGet(const GLKeys& inKey) const
{
    COREASSERT(inKey.ValueGet() < m_keyState.size());
    return m_keyState[inKey.ValueGet()];
}

void
SDLAppHandler::MousePositionGet(S32& outX, S32& outY) const
{
    // Return with origin at bottom left
    outX=m_mouseX;
    outY=m_height-m_mouseY-1;
}

void
SDLAppHandler::MouseDeltaGet(S32& outXDelta, S32& outYDelta)
{
    outXDelta=m_mouseXDelta;
    outYDelta=-m_mouseYDelta;
    m_mouseXDelta=0;
    m_mouseYDelta=0;
}

void
SDLAppHandler::EnterScreen(tInitType inType)
{
    MediaSDL::Instance().InitVideo();
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    m_width=640;
    m_height=480;
    m_bpp=32;
    
    switch (inType)
    {
        case kGame:
            CoreEnv::Instance().VariableGetIfExists(m_width, "FULLSCREEN_DISPLAY_WIDTH");
            CoreEnv::Instance().VariableGetIfExists(m_height, "FULLSCREEN_DISPLAY_HEIGHT");
            CoreEnv::Instance().VariableGetIfExists(m_bpp, "FULLSCREEN_DISPLAY_BPP");
            SDL_SetVideoMode(m_width, m_height, m_bpp, SDL_OPENGL|SDL_FULLSCREEN);
            break;

        case kWindow:
            CoreEnv::Instance().VariableGetIfExists(m_width, "WINDOW_DISPLAY_WIDTH");
            CoreEnv::Instance().VariableGetIfExists(m_height, "WINDOW_DISPLAY_HEIGHT");
            CoreEnv::Instance().VariableGetIfExists(m_bpp, "WINDOW_DISPLAY_BPP");
            SDL_SetVideoMode(m_width, m_height, m_bpp, SDL_OPENGL);
            break;

        default:
            throw(LogicFail("Bad value to SDLAppHandler::EnterScreen"));
    }
   
}

void
SDLAppHandler::PostRedisplay(void)
{
    m_redisplay=true;
}

void
SDLAppHandler::SwapBuffers(void)
{
    SDL_GL_SwapBuffers();
}

U32
SDLAppHandler::GetMilliseconds(void) const
{
    return SDL_GetTicks();
}

void
SDLAppHandler::SetCursorState(bool inValue)
{
    SDL_ShowCursor(inValue?SDL_ENABLE:SDL_DISABLE);
}

void
SDLAppHandler::Signal(const CoreAppSignal& inSignal)
{
    switch (inSignal.SigNumberGet())
    {
        case GLAppSignal::kDisplay:
            Display();
            break;

        case GLAppSignal::kVisible:
            m_visible=true;
            break;

        case GLAppSignal::kNotVisible:
            m_visible=false;
            break;

        case GLAppSignal::kKeyboard:
        {
            KeyboardSignal(dynamic_cast<const GLKeyboardSignal&>(inSignal));
        }
        break;

        default:
            if (inSignal.IsCoreAppSignal())
            {
                CoreAppHandler::Signal(inSignal);
            }
            else
            {
                cerr << "Unhandled SDLAppHandler signal 0x" << hex << inSignal.SigNumberGet() << dec << endl;
            }
            break;
    }
}    

void
SDLAppHandler::MainLoop(void)
{
    bool doQuit=false;
    while (!doQuit)
    {
        SDL_Event event;
        bool isEvent=SDL_PollEvent(&event);
        if (isEvent)
        {
            switch(event.type)
            {
                case SDL_KEYDOWN:
                case SDL_KEYUP:
                    Signal(GLKeyboardSignal((event.key.type==SDL_KEYDOWN), TranslateKey(&event.key), m_mouseX, m_mouseY));
                    break;

                case SDL_MOUSEMOTION:
                    m_mouseX=event.motion.x;
                    m_mouseY=event.motion.y;
                    m_mouseXDelta+=event.motion.xrel;
                    m_mouseYDelta+=event.motion.yrel;
                    break;

                case SDL_MOUSEBUTTONDOWN:
                case SDL_MOUSEBUTTONUP:
                {
                    U32 button=event.button.button-1;
                    if (event.button.button < 1 ||
                        button > (GLKeys::kKeyMouse5 - GLKeys::kKeyMouse1))
                    {
                        cerr << "Button index " << button << " ignored" << endl;
                        break;
                    }
                    m_mouseX=event.button.x;
                    m_mouseY=event.button.y;
                    Signal(GLKeyboardSignal((event.button.state == SDL_PRESSED),
                                       GLKeys(GLKeys::kKeyMouse1+button),
                                       event.button.x, event.button.y));
                }
                break;
                    
                case SDL_QUIT:
                    doQuit=true;
                    break;
            }
        }
        if (m_redisplay)
        {
            m_redisplay=false;
            Display();
        }
        if (!isEvent)
        {
            Idle();
        }
    }
}

GLKeys
SDLAppHandler::TranslateKey(void *inKeyEvent) const
{
    SDLKey keyValue=static_cast<SDL_KeyboardEvent *>(inKeyEvent)->keysym.sym;
    switch (keyValue)
    {
        case SDLK_F1:
            return GLKeys::kKeyF1;

        case SDLK_F2:
            return GLKeys::kKeyF2;

        case SDLK_F3:
            return GLKeys::kKeyF3;

        case SDLK_F4:
            return GLKeys::kKeyF4;

        case SDLK_F5:
            return GLKeys::kKeyF5;

        case SDLK_F6:
            return GLKeys::kKeyF6;

        case SDLK_F7:
            return GLKeys::kKeyF7;

        case SDLK_F8:
            return GLKeys::kKeyF8;

        case SDLK_F9:
            return GLKeys::kKeyF9;

        case SDLK_F10:
            return GLKeys::kKeyF10;

        case SDLK_F11:
            return GLKeys::kKeyF11;

        case SDLK_F12:
            return GLKeys::kKeyF12;

        case SDLK_LEFT:
            return GLKeys::kKeyLeft;

        case SDLK_UP:
            return GLKeys::kKeyUp;

        case SDLK_RIGHT:
            return GLKeys::kKeyRight;

        case SDLK_DOWN:
            return GLKeys::kKeyDown;

        case SDLK_PAGEUP:
            return GLKeys::kKeyPageUp;

        case SDLK_PAGEDOWN:
            return GLKeys::kKeyPageDown;

        case SDLK_HOME:
            return GLKeys::kKeyHome;

        case SDLK_END:
            return GLKeys::kKeyEnd;

        case SDLK_INSERT:
            return GLKeys::kKeyInsert;

        default:
            if (keyValue > 0 && keyValue < 0x100)
            {
                return keyValue;
            }
    }
    cerr << "Ignored SDL key " << keyValue << endl;
    return 0;
}

