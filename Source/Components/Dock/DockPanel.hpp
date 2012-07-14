#ifndef hpp_DockPanel_hpp
#define hpp_DockPanel_hpp

// Juce related definitions go here
#include "../../../JuceLibraryCode/JuceHeader.h"
//We need DockManager
#include "DockManager.hpp"

namespace GUI 
{
    class DockPanel : public DockHolder
    {
        //Members
    private:
        friend class DockManager;
        friend class DockHolder;
        Component * content;

        //Methods
    public:
        // Component interface
        /** This resize and set components on screen */
        void resized ();
        /** This paints graphical components */
        void paint (Graphics & g);;

        //Constructor & Destructor
    public:
        /** Constructor 
            @param[in]  parent      Dock manager to manage the Panel
            @param[in]  content     Component
            @param      position    the Position whether Right/left/centre
        */
        DockPanel (DockManager * parent,Component * content,  const int position);
        /** Destructor */
        ~DockPanel ();

    };
}
#endif  // hpp_DockPanel_hpp
