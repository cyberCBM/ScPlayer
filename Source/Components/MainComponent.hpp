#ifndef hpp_MainComponent_hpp
#define hpp_MainComponent_hpp

// Juce related definitions go here
#include "../../JuceLibraryCode/JuceHeader.h"
// ----- Docks -----
//We need Manager of panels : the smart component
#include "Dock/DockManager.hpp"
//We need Dock Panel 
#include "Dock/DockPanel.hpp"
//We need Dock Button 
#include "Dock/DockButtons.hpp"
// ----- Panels -----
//We need Right Panel
#include "Panels/RightPanel.hpp"
//We need Left Panel
#include "Panels/LeftPanel.hpp"
//We need Center Panel
#include "Panels/CenterPanel.hpp"
//We need Center Panel
#include "Panels/TopPanel.hpp"


namespace GUI 
{

// Used to sync (minimize,restore,close) Window
class MainAppWindow;

class MainComponent : public juce::Component
{
    //Members
private:
    /** Boolean to initialise the class only once in resized method */
    bool                            firstCall;
    /** Manager of panels : the smart component */
    ScopedPointer<DockManager>      manager;
    /** Center showing compontnes goes here (must be resizable - controls for player) */
    ScopedPointer<TopPanel>         topPanel;
    /** Center showing compontnes goes here (must be resizable - controls for player) */
    ScopedPointer<CenterPanel>      centerPanel;
    /** Right sided popup like panel might be having client lists and client related setting button */
    ScopedPointer<RightPanel>       rightPanel;
    /** Left sided popup like panel will have playList */
    ScopedPointer<LeftPanel>        leftPanel;

    //Methods
    public:
    // Component interface
    /** This resize and set components on screen */
    void resized ();

    // Static
    /** It applies different language according to selection either from 
        xml file or can be kept local fixed
        @param[in] language Language options to be used as parameter to file creation */
    static void applyTranslation(const String & language);

        // Constructor &  Destructor
    public:
        /** The constructor */
        MainComponent ();
        /** Destructor */
        ~MainComponent ();

    };
}
#endif //hpp_MainComponent_hpp