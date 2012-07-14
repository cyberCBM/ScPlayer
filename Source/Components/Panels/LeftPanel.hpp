#ifndef hpp_BottomPanel_hpp
#define hpp_BottomPanel_hpp

// Juce related definitions go here
#include "../../../JuceLibraryCode/JuceHeader.h"
// custom LoolAndFeel and Grpahics info
#include "../../Common/LookAndFeel.hpp"

namespace GUI 
{
    class LeftPanel : public Component
    {
        // Members
    private:

        // Methods
    public:
        // Component interface
        /** This resize and set components on screen */
        void resized ();
        /** This paints graphical components */
        void paint (Graphics & g);
        
        // Constructor & Destructor
    public:
        /** Constructor */
        LeftPanel ();
        /** Destructor */
        ~LeftPanel ();
    };
}
#endif //hpp_BottomPanel _hpp