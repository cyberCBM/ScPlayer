//We need our basics class definitions 
#include "DockPanel.hpp"
//We need dock button's definitions 
#include "DockButtons.hpp"

GUI::DockPanel::DockPanel (DockManager * parent, Component * component, const int position)
:DockHolder (parent, this, position), content(component)
{
    content->addMouseListener (this, true);
    addAndMakeVisible (content);
}

GUI::DockPanel::~DockPanel ()
{
    deleteAllChildren ();
}

void GUI::DockPanel::resized ()
{
    content->setBounds (DockHolder::getContentBounds());
    DockHolder::resized ();
}
void GUI::DockPanel::paint (Graphics & g)
{
    DockHolder::paint (g);
}