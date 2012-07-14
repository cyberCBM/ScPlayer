#ifndef hpp_TopPanel_hpp
#define hpp_TopPanel_hpp

// Juce related definitions go here
#include "../../../JuceLibraryCode/JuceHeader.h"
// custom LoolAndFeel and Grpahics info
#include "../../Common/LookAndFeel.hpp"

namespace GUI 
{
    class TopPanel : public Component
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
        TopPanel ();
        /** Destructor */
        ~TopPanel ();
    };
}
#endif //hpp_TopPanel _hpp