#ifndef hpp_HeaderPanel_hpp
#define hpp_HeaderPanel_hpp
// Juce related definitions go here
#include "../../../JuceLibraryCode/JuceHeader.h"
// custom LoolAndFeel and Grpahics info
#include "../../Common/LookAndFeel.hpp"

namespace GUI 
{
    class RightPanel : public Component
    {
        // Member
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
        RightPanel ();
        /** Destructor */
        ~RightPanel ();
    };
}
#endif //hpp_HeaderPanel_hpp