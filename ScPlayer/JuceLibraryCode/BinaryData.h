/* =========================================================================================

   This is an auto-generated file, created by The Introjucer 3.0.0
   Do not edit anything in this file!

*/

namespace BinaryData
{
    extern const char*   select_gif;
    const int            select_gifSize = 1961;

    extern const char*   unSelect_gif;
    const int            unSelect_gifSize = 1939;

    extern const char*   Kick_gif;
    const int            Kick_gifSize = 1839;

    extern const char*   about_gif;
    const int            about_gifSize = 2041;

    extern const char*   back_gif;
    const int            back_gifSize = 1874;

    extern const char*   clients_gif;
    const int            clients_gifSize = 1305;

    extern const char*   connect_gif;
    const int            connect_gifSize = 1332;

    extern const char*   disconnect_gif;
    const int            disconnect_gifSize = 1331;

    extern const char*   icon_gif;
    const int            icon_gifSize = 2038;

    extern const char*   lock_gif;
    const int            lock_gifSize = 2106;

    extern const char*   next_gif;
    const int            next_gifSize = 1876;

    extern const char*   open_gif;
    const int            open_gifSize = 1863;

    extern const char*   pause_gif;
    const int            pause_gifSize = 1865;

    extern const char*   play_gif;
    const int            play_gifSize = 1822;

    extern const char*   playlist_gif;
    const int            playlist_gifSize = 1733;

    extern const char*   save_gif;
    const int            save_gifSize = 2076;

    extern const char*   setting_gif;
    const int            setting_gifSize = 1683;

    extern const char*   startS_gif;
    const int            startS_gifSize = 1195;

    extern const char*   stop_gif;
    const int            stop_gifSize = 1745;

    extern const char*   stopS_gif;
    const int            stopS_gifSize = 1195;

    extern const char*   unlock_gif;
    const int            unlock_gifSize = 2094;

    // If you provide the name of one of the binary resource variables above, this function will
    // return the corresponding data and its size (or a null pointer if the name isn't found).
    const char* getNamedResource (const char* resourceNameUTF8, int& dataSizeInBytes) throw();

    //==============================================================================
    // This class acts as an ImageProvider that will access the BinaryData images
    class ImageProvider  : public juce::ComponentBuilder::ImageProvider
    {
    public:
        ImageProvider() noexcept {}

        juce::Image getImageForIdentifier (const juce::var& imageIdentifier)
        {
            int dataSize = 0;
            const char* const data = getNamedResource (imageIdentifier.toString().toUTF8(), dataSize);

            if (data != nullptr)
                return juce::ImageCache::getFromMemory (data, dataSize);

            return juce::Image();
        }

        juce::var getIdentifierForImage (const juce::Image&)  { return juce::var(); }
    };
}
