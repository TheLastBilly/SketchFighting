#include "engine/viewsManager.hpp"

register_logger();

using namespace engine;
using namespace graphics;

void viewsManager::registerView(const std::shared_ptr<view> &request)
{
    try
    {
        getChild<view>(request->getName());
        info("a view with the name \"" + request->getName() + "\" has already been registered");
    }
    catch(...)
    { }
    
    appendChild<view>(request);
    views.push_back(request);
}