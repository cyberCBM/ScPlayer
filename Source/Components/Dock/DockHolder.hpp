#ifndef hpp_DockHolder_hpp
#define hpp_DockHolder_hpp
// Juce related definitions go here
#include "../../../JuceLibraryCode/JuceHeader.h"

namespace GUI 
{
    class DockManager;
    class DockPanel;
    /** This class holds other dock component using DockManager and DockPanel
        Dock component's like (Center, Left, Right, Bottom, Top) 
    */ 
    class DockHolder : public Component
    {
        // Type definitions
    public:
        /** Inject used Juce's classes here */
        typedef juce::BorderSize<int> BorderSizeInt;
        typedef juce::Rectangle<int> RectangleInt;

        // Members
    private:
        ComponentAnimator animator;
        DockManager * manager;
        DockPanel * panel;
        int orientation;
        int size;
        bool docked;
        bool inside;
        bool open;
        int button;		// default: 15
        int padding;	// default: 3
        void initConstrainer ();
        friend class DockPanel;
        ResizableBorderComponent * resizable;
        ComponentBoundsConstrainer * constrainer;
        /** Member to avoid the automatic animation for some holder*/
        bool lockAutomaticAnimation;

        // Helper
    protected:
        friend class DockManager;

        // Methods
    protected:
        // Component interface
        /** This resize and set components on screen */
        void resized ();
        /** This paints graphical components */
        void paint (Graphics & g);
        void mouseEnter (const MouseEvent & e);
        void mouseMove (const MouseEvent & e);
        void mouseExit (const MouseEvent & e);

        // Class Methods
        /** This method returns true when mouse is inside DockHolder Bounds 
            @return inside  True when inside Bounds    */
        bool isMouseInside ()				{ return inside; }
        /** This method return true when Dock is open
            @return open    True when dock is open    */
        bool isOpen ()						{ return open; }
        /** This method set open/close status of dock
            @param[in] status  whether panel is open or close ?    */
        void setOpen (bool status)			{ open = status; }
        /** This method return returns true or false for panel's dock status
            @return docked  When insider dock panel is docked     */
        bool isDocked ()					{ return docked; }
        /** This method set Dock status of insider panel for Dock
            @param[in] status whether dock panel is docked or not ?    */
        void setDocked (bool status)		{ docked = status; }
        /** This method set animation status
            @param[in] status whether automatic animation must to be stopped or not ? */
        void setLockAutomaticAnimation(bool status) {lockAutomaticAnimation = status;}
        /** This method get animation status
            @return status whether automatic animation is stopped or not ? */
        bool getLockAutomaticAnimation() {return lockAutomaticAnimation;}

        // Methods
    public:
        /** It returns bound of dock
            @return Rectangle    */
        const Rectangle<int> getContentBounds ();
        /** Gives current size of DockHolder
            @return Size    */
        inline const int getCurrentSize ()			{ return size; }
        /** used to check memory leaks */
        juce_UseDebuggingNewOperator

        // Constructor & Destructor
    public:
        /** Constructor 
            @param [in] parent
            @param [in] panel
            @param type     */
        DockHolder (DockManager * parent, DockPanel * panel, const int type);
        /** Destructor */
        ~DockHolder ();

    };
}
#endif // hpp_DockHolder_hpp