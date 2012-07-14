// We need our definitions
#include "DockManager.hpp"
// we need Dock buttons here
#include "DockButtons.hpp"
GUI::DockManager::DockManager () : 
top(0), left (0), center (0), right (0), leftButton (0), rightButton (0), lastMouseEvent (0)
{
    addAndMakeVisible (center = new DockHolder(this, 0, CENTER), ZORDER_CENTER);
    center->addComponentListener (this);
    addAndMakeVisible (left = new DockHolder(this, 0, LEFT), ZORDER_LEFT);
    left->addComponentListener (this);
    addAndMakeVisible (right = new DockHolder(this, 0, RIGHT), ZORDER_RIGHT);
    right->addComponentListener (this);
    addAndMakeVisible (top = new DockHolder(this, 0, TOP), ZORDER_TOP);
    top->addComponentListener (this);

    addAndMakeVisible (leftButton = GUI::getDockableButton (String("left"), LEFT), ZORDER_LEFT_BUTTON);
    leftButton->setToggleState (false, false);
    leftButton->setClickingTogglesState (true);
    leftButton->setBackgroundColours (Colours::black, Colours::black);
    leftButton->addMouseListener (this, true);
    leftButton->addListener (this);

    addAndMakeVisible (rightButton = GUI::getDockableButton (String("right"), RIGHT), ZORDER_RIGHT_BUTTON);
    rightButton->setToggleState (false, false);
    rightButton->setClickingTogglesState (true);
    rightButton->setBackgroundColours (Colours::black, Colours::black);
    rightButton->addMouseListener (this, true);
    rightButton->addListener (this);

}
GUI::DockManager::~DockManager ()
{
    deleteAllChildren ();
}
void GUI::DockManager::timerCallback ()
{
}

void GUI::DockManager::mousePropagation (const MouseEvent & e, const int position)
{
    if (position != TOP)	top->mouseExit (e);
    if (position != LEFT)	left->mouseExit (e);
    if (position != RIGHT)	right->mouseExit (e);
    if (position != CENTER) center->mouseExit (e);
}
bool GUI::DockManager::isDocked (const int position)
{
    switch (position)
    {
    case TOP:
        return top->isDocked ();
    case LEFT:
        return left->isDocked ();
    case RIGHT:
        return right->isDocked ();
    default:
        return false;
    }
}

void GUI::DockManager::setOpenWithoutAnimation (const int position, bool open)
{
    switch (position)
    {
    case TOP:
        top->setOpen (open);
        top->setDocked (open);
        top->setVisible (open);
        break;
    case LEFT:
        left->setOpen (open);
        left->setDocked (open);
        left->setVisible (open);
        leftButton->setToggleState (!open, false);
        break;
    case RIGHT:
        right->setOpen (open);
        right->setDocked (open);
        right->setVisible (open);
        rightButton->setToggleState (!open, false);
        break;
    default:
        break;
    }
}

void GUI::DockManager::lockAutomaticAnimationForPanel (const int positionPanel, bool lockAutomaticAnimation)
{
    switch (positionPanel)
    {
    case TOP:
        top->setLockAutomaticAnimation(lockAutomaticAnimation);
        break;
    case LEFT:
        left->setLockAutomaticAnimation(lockAutomaticAnimation);
        break;
    case RIGHT:
        right->setLockAutomaticAnimation(lockAutomaticAnimation);
        break;
    default:
        break;
    }
}

bool GUI::DockManager::isLockedAutomaticAnimationForPanel(const int positionPanel)
{
    switch (positionPanel)
    {
    case TOP:
        return top->getLockAutomaticAnimation();
    case LEFT:
        return left->getLockAutomaticAnimation();
    case RIGHT:
        return right->getLockAutomaticAnimation();
    default:
        break;
    }
    return false;
}

void GUI::DockManager::setOpenWithAnimation (const int positionPanel, bool lockAutomaticAnimation)
{
    Component * animate = 0;
    Component * child = 0;
    juce::Rectangle<int> position;
    int runningMs;

    switch (positionPanel)
    {
    case TOP:
        if (!animator.isAnimating (top) && !top->isVisible())
        {	
            top->setOpen (true);
            animate = top;
            child = dynamic_cast<DockPanel*>(top)->content;
            child->setAlpha (1.0f);
            position = animate->getBounds ();
            animate->setBounds (position.getX(), 
                position.getY() - position.getHeight(),
                position.getWidth(), 
                position.getHeight());
            top->setLockAutomaticAnimation(lockAutomaticAnimation);
        }
        break;
    case LEFT:
        if (!animator.isAnimating (left) && !left->isVisible())
        {	
            left->setOpen (true);
            animate = left;
            child = dynamic_cast<DockPanel*>(left)->content;
            child->setAlpha (1.0f);
            position = animate->getBounds ();
            animate->setBounds (position.getX() - position.getWidth(), 
                position.getY(),
                position.getWidth(), 
                position.getHeight());
            left->setLockAutomaticAnimation(lockAutomaticAnimation);
            leftButton->setToggleState(true, false);
        }
        break;
    case RIGHT:
        if (!animator.isAnimating (right) && !right->isVisible())
        {	
            right->setOpen (true);
            animate = right;
            child = dynamic_cast<DockPanel*>(right)->content;
            child->setAlpha (1.0f);
            position = animate->getBounds ();
            animate->setBounds (position.getX() + position.getWidth(), 
                position.getY(),
                position.getWidth(), 
                position.getHeight());
            right->setLockAutomaticAnimation(lockAutomaticAnimation);
            rightButton->setToggleState(true, false);
        }
        break;
    default:
        break;
    }
    if (animate)
    {
        if (!animator.isAnimating (animate) && !animate->isVisible())
        {	
            child->setVisible (true);
            animate->setVisible (true);
            runningMs= juce::roundDoubleToInt(juce::jlimit (0.0, 120.0, (position.getWidth() + position.getHeight()) * 0.25));
            animator.animateComponent (animate, position, 1.0, runningMs, true, 1.0, 0.0);
        }
    }
}
void GUI::DockManager::forceCloseWithAnimation (const int positionPanel, bool lockAutomaticAnimation)
{
    Component * topContent = dynamic_cast<DockPanel*>(top)->content;
    Component * leftContent = dynamic_cast<DockPanel*>(left)->content;
    Component * rightContent = dynamic_cast<DockPanel*>(right)->content;

    switch (positionPanel)
    {
    case TOP:
        animator.fadeOut (topContent, FADEOUTMS);
        animator.fadeOut (top, FADEOUTMS);
        top->setOpen (false);
        top->setLockAutomaticAnimation(lockAutomaticAnimation);
        break;
    case LEFT:
        animator.fadeOut (leftContent, FADEOUTMS);
        animator.fadeOut (left, FADEOUTMS);
        left->setOpen (false);
        left->setLockAutomaticAnimation(lockAutomaticAnimation);
        break;
    case RIGHT:
        animator.fadeOut (rightContent, FADEOUTMS);
        animator.fadeOut (right, FADEOUTMS);
        right->setOpen (false);
        right->setLockAutomaticAnimation(lockAutomaticAnimation);
        break;
    default:
        break;
    }
}
void GUI::DockManager::setPanelComponent (const int position, Component * component)
{
    switch (position)
    {
    case CENTER:
        {
            if (center)
                delete center;
            center = new DockPanel (this, component, CENTER);
            addAndMakeVisible (center, ZORDER_CENTER);
        }
        break;
    case LEFT:
        {
            if (left)
                delete left;
            left = new DockPanel (this, component, LEFT);
            left->addComponentListener (this);
            addAndMakeVisible (left, ZORDER_LEFT);
        }
        break;
    case RIGHT:
        {
            if (right)
                delete right;
            right = new DockPanel (this, component, RIGHT);
            right->addComponentListener (this);
            addAndMakeVisible (right, ZORDER_RIGHT);
        }
        break;
    case TOP:
        {
            if (top)
                delete top;
            top = new DockPanel (this, component, TOP);
            top->addComponentListener (this);
            addAndMakeVisible (top, ZORDER_TOP);
        }
        break;
    default:
        break;
    }
}
void GUI::DockManager::paint (Graphics & g)
{
    g.fillAll (Colours::black);
}
void GUI::DockManager::componentMovedOrResized (Component & component, bool wasMoved, bool wasResized)
{
    if (wasResized)
        resized ();
}
void GUI::DockManager::resized ()
{
    const int w = getWidth();
    const int h = getHeight();

    const int b = BUTTONSIZE;

    const int th = top->getBounds().getHeight();
    const int lw = left->getBounds().getWidth();
    const int rw = right->getBounds().getWidth();
    const int bh = 0;

    const bool td = top->isDocked();
    const bool ld = left->isDocked();
    const bool rd = right->isDocked();
    const bool bd = false;

    int cx, cy, cw, ch;
    cx = b + (ld ? lw : 0);
    cw = w - (ld ? lw : 0) 
        - (rd ? rw : 0) - (b*2);
    cy = b + (td ? th : 0);
    ch = h - (td ? th : 0) 
        - (bd ? bh : 0) - (b*2);

    top->setBounds (0, 0, w, th);

    left->setBounds (b, 
        b + (td ? th : 0) - 10, 
        lw, 
        h - (td ? th : 0) 
        - (bd ? bh : 0) - (b*3));

    center->setBounds (cx, cy - 10, cw, ch - b);

    right->setBounds (w - rw - b, 
        b + (td ? th : 0) - 10, 
        rw, 
        h - (td ? th : 0) 
        - (bd ? bh : 0) - (b*3));

    leftButton->setBounds (0, 
        b + (td ? th : 0), 
        b, 
        h - (td ? th : 0) 
        - (bd ? bh : 0) - (b*3));

    rightButton->setBounds (w - b, 
       b + (td ? th : 0), 
        b, 
        h - (td ? th : 0) 
        - (bd ? bh : 0) - (b*3));

}

bool GUI::DockManager::getToggleState(const int positionPanel)
{
    switch (positionPanel)
    {
    case CENTER:
        {
            return false;
        }
        break;
    case LEFT:
        {
            return leftButton->getToggleState();
        }
        break;
    case RIGHT:
        {
            return rightButton->getToggleState();
        }
        break;
    default:
        break;
    }
    return false;
}
void GUI::DockManager::buttonClicked (juce::Button * button)
{
    if (button == leftButton)
    {
        left->setOpen (!button->getToggleState());
        left->setDocked (!button->getToggleState());
        left->setVisible (!button->getToggleState());
        if(!button->getToggleState())
        {
            Component * leftContent = dynamic_cast<DockPanel*>(left)->content;
            animator.fadeIn (leftContent, 1);
            animator.fadeIn (left, 1);
        }
        left->resized();
    }
    else if (button == rightButton)
    {
        right->setOpen (!button->getToggleState());
        right->setDocked (!button->getToggleState());
        right->setVisible (!button->getToggleState());
        if(!button->getToggleState())
        {
            Component * rightContent = dynamic_cast<DockPanel*>(right)->content;
            animator.fadeIn (rightContent, 1);
            animator.fadeIn (right, 1);
        }
        right->resized();
    }
    resized ();
}
void GUI::DockManager::mouseEnter (const MouseEvent & e)
{
    if (e.eventComponent == leftButton)
    {
        if (!left->isDocked() && 
            !left->isOpen() && !left->getLockAutomaticAnimation())
        {
            setOpenWithAnimation(LEFT);
        }
    }
    else
        if (e.eventComponent == rightButton)
        {
            if (!right->isDocked() && 
                !right->isOpen() && !right->getLockAutomaticAnimation())
            {
                setOpenWithAnimation(RIGHT);
            }
        }


}
void GUI::DockManager::mouseExit (const MouseEvent & e)
{
    if(!left || !right)
        return;
    Component * leftContent = dynamic_cast<DockPanel*>(left)->content;
    Component * rightContent = dynamic_cast<DockPanel*>(right)->content;

    if (e.eventComponent == leftButton && !left->isDocked())
    {
        if (e.y < leftButton->getY() ||
            e.y > leftButton->getHeight() - BUTTONSIZE)
        {
            animator.fadeOut (leftContent, FADEOUTMS);
            animator.fadeOut (left, FADEOUTMS);
            left->setOpen (false);
        }
    }
    else
        if (e.eventComponent == rightButton && !right->isDocked())
        {
            if (e.y < rightButton->getY() ||
                e.y > rightButton->getHeight() - BUTTONSIZE)
            {
                animator.fadeOut (rightContent, FADEOUTMS);
                animator.fadeOut (right, FADEOUTMS);
                right->setOpen (false);
            }
        }
}