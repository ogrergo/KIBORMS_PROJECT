#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

//define pour le fichier de conf peut etre a bouger plus tard
#define OGRE_CONFIGS_FILE "ogre_configs_file"
#define OGRE_PLUGINS_FILE "ogre_plugins_file"
#define OGRE_RESOURCES_FILE "ogre_resources_file"
#define OGRE_LOG_FILE "ogre_log_file"

#define FRAME_RATE "fps"
#define WINDOW_TITLE "window_title"
#define RESOLUTION_X "resolution_x"
#define RESOLUTION_Y "resolution_y"
#define FULLSCREEN_ENABLED "fullscreen"
#define FSAA "fsaa"
#define VSYNC "vsync"

//Ogre include
#include "OGRE/OgreRoot.h"
#include "OGRE/OgreRenderSystem.h"
#include "OGRE/OgreRenderWindow.h"
#include "OGRE/OgreConfigFile.h"
#include "OGRE/OgreWindowEventUtilities.h"
#include <OIS/OIS.h>

//macro
#include "utils/macro/debug_macro.h"

#include "utils/configuration/Config_file.h"


#ifdef _WIN32
    #include <windows.h>
#else
    #include <unistd.h>
#endif

using namespace Ogre;

class GameWindow
{
    public:
        GameWindow(Config_file const& config);
        virtual ~GameWindow();

        void start();
        void pause();


        void sleep(uint32_t millisec);
    protected:
    private:

        bool running;

        Config_file config_file;

        SceneManager* sceneMgr;
        Camera* camera;
        RenderWindow* render_window;
        Root* app_root;

        uint32_t load_ogre();
        void reset();
        void handle_event();
        void update();
        void render();
        void update_timer();

        //timer
        Timer* timer;
        double accum_time;
        double time_per_frame;
        int32_t accum_fps;
        int32_t framerate;
        int32_t fps;


};

#endif // GAMEWINDOW_H
