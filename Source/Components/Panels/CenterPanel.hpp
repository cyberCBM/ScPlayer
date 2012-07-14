#ifndef hpp_CenterPanel_hpp
#define hpp_CenterPanel_hpp
// Juce related definitions go here
#include "../../../JuceLibraryCode/JuceHeader.h"
// custom LoolAndFeel and Grpahics info
#include "../../Common/LookAndFeel.hpp"

namespace GUI 
{
    class CenterPanel : public Component
    {
        // Members
    private:
        /** Boolean to initialise the class only once in resized method */
        bool firstCall;

        // Methods
    public:
        // Component interface
        /** This resize and set components on screen */
        void resized ();
        /** This paints graphical components */
        void paint (Graphics & g);

        // Constructor & Destructor
    public:
        /** Constructor 
            @param applicationData Reference about the data of the application        */
        CenterPanel ();
        /** Destructor */
        ~CenterPanel ();
    };
}

#endif  // hpp_CenterPanel_hpp