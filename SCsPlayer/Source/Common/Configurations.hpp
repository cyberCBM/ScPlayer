/*                                                                                  
*=====================================================================================
                    *CsPlayer - Simple Player (later It will be Server Player)                           |
*Music file player that works in Network                                             |
*Author: CsTeam                                                                      |
*Email: chaitanya.modi@gmail.com                                                     |
*Github: https://github.com/cyberCBM/CsPlayer.git                                    |
*                                                                                    |
                    *License: GNU2 License, Copyright (c) 2012 by CsTeam                                 |
* CsPlayer can be redistributed and/or modified under the terms of the GNU General   |
* Public License (Version 2).                                                        |
*It use JUCE and DrowAudio Libraries which holds GNU2                                |
*A copy of the license is included in the CsPlayer distribution, or can be found     |
* online at www.gnu.org/licenses.                                                    |
*=====================================================================================
*/

#ifndef hpp_Configurations_hpp
#define hpp_Configurations_hpp

// Juce related definitions go here
#include "../JuceLibraryCode/JuceHeader.h"

namespace Configurations
{
    struct ClientInfo
    {
        // Members
    public:
        String  clientName;
        String  clientIpAddress;
        bool    controlAccess;
        bool    isConnected;
        bool    hasLock;
        // Constructor
    public:
        ClientInfo() : controlAccess(false), isConnected(false), hasLock(false)
        {
        }
		/** read Cleint data from xml and copy to structure elements*/
		void fromXML(XmlElement * node)
		{
			clientIpAddress = node->getStringAttribute("ip");
			controlAccess = node->getBoolAttribute("access");
			clientName = node->getStringAttribute("name");
			hasLock = false;
			isConnected = false;
		}
		/** write Client data to xml  */
		void toXML(XmlElement * node)
		{
			node->setAttribute("ip", clientIpAddress);
			node->setAttribute("access",controlAccess);
			node->setAttribute("name", clientName);			
		}		
    };

    struct Media
    {
        // Members
    public:
        String filePath;
        double duration;
		// Methods
	public:
		void toXml (XmlElement & node)
		{
			node.addChildElement (new XmlElement ("Media"));
			node.getChildElement (node.getNumChildElements()-1)->setAttribute ("path", filePath);
			node.getChildElement (node.getNumChildElements()-1)->setAttribute ("duration", duration);
		}
		void fromXml (XmlElement * node)
		{
			filePath = node->getStringAttribute ("path");
			duration = node->getDoubleAttribute ("duration");
		}
        // Constructor
    public:
        Media()
        {
        }
	};

}

#endif // hpp_Configurations_hpp