//We need our Basic class definitions
#include "CenterPanel.hpp"

/** Dummy Component whose name is shown in title in panel */
class ZeroComponent : public Component
{
    // Methods
public:
    ZeroComponent (const String& name): Component (name)
    {
        // Null component which will be deleted later
    }
    void paint (Graphics & g)
    {
        // Paint the dummy components 
    }
};

GUI::CenterPanel::CenterPanel (): firstCall(true)
{
    
}
GUI::CenterPanel::~CenterPanel ()
{
    deleteAllChildren();
}
void GUI::CenterPanel::resized ()
{
    if(firstCall)
    {
        firstCall = false;
    }
}
void GUI::CenterPanel::paint (Graphics & g)
{
    g.fillAll (Colours::black);
}
