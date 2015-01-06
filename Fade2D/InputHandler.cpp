#include "InputHandler.h"

#define CALL_MEMBER(object,ptrToMember) ((object).*(ptrToMember))

struct ClassKeyHandlerFunc {
    ClassKeyHandlerFunc(Fade2D* lib, ClassKeyHandler func) : lib(lib), func(func) { }
    Fade2D* lib;
    ClassKeyHandler func;
};

std::vector<ClassKeyHandlerFunc> classHandlerLookup;

void genericKeyHandler(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    for (auto &AclassHandler : classHandlerLookup)
    {
        if (AclassHandler.lib->window == window)
        {
            CALL_MEMBER(*AclassHandler.lib, AclassHandler.func)(key, action);
        }
    }
}

void addClassKeyHandler(Fade2D* lib)
{
    glfwSetKeyCallback(lib->window, genericKeyHandler);
    classHandlerLookup.push_back(ClassKeyHandlerFunc(lib, &Fade2D::classKeyHandler));
}
