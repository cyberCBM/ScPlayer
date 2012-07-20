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

#include "Client.hpp"

Client::Client() : serverResponse(false)
{
    
}

Client::~Client()
{

}

void Client::connectToServer()
{
    serverResponse = connectToSocket("192.168.0.17",80,100000);
    if(!serverResponse)
    {
        int error = 0;
    }
}

void Client::connectionMade ()
{
    
}
void Client::connectionLost ()
{
    int k =0;
}
void Client::messageReceived (const MemoryBlock &message)
{

}