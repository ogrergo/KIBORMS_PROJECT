#include "GameWindow.h"

GameWindow::GameWindow(Config_file const& config): config_file(config)
{
    if(load_ogre()){
        ERR("Impossible de charger Ogre");
    }
    timer = new Timer();
}

GameWindow::~GameWindow()
{
    if(app_root) delete app_root;
    if(timer) delete timer;
}

void GameWindow::start()
{
    //reset the window
    reset();

    running = true;

    while(running){
        handle_event();
        update();
        render();
        update_timer();
    }
}

void GameWindow::reset()
{
    timer->reset();
    framerate = std::stol(config_file[FRAME_RATE]);
    time_per_frame = 1000000.0 / framerate;
	accum_time = 0;
	accum_fps = 0;
    fps = 0;
}

void GameWindow::handle_event()
{

}

void GameWindow::update()
{


}

void GameWindow::render()
{


}

void GameWindow::update_timer()
{
    double elapsed_time = timer->getMicroseconds() + accum_time;

	accum_fps++;

	if(elapsed_time  < time_per_frame*accum_fps){
		sleep((time_per_frame*accum_fps - elapsed_time)*0.001);
	}

	elapsed_time = timer->getMicroseconds();

	accum_time += elapsed_time;

	if(accum_time > 1000000 || accum_fps == framerate){
		accum_time -= 1000000;
		if(accum_time < 0){
			sleep(-accum_time);
			accum_time = 0.0;

		}

		fps = accum_fps;
		accum_fps = 0;
		MSG("fps: %d", fps);
	}

	timer->reset();
}

void GameWindow::pause()
{
    running = false;
}


uint32_t GameWindow::load_ogre()
{

        app_root = new Root(config_file[OGRE_PLUGINS_FILE],config_file[OGRE_CONFIGS_FILE],config_file[OGRE_LOG_FILE]);

        //if (!app_root->showConfigDialog())
         //   return -1;


        ConfigFile cf;
        cf.load(config_file[OGRE_RESOURCES_FILE]);

        ConfigFile::SectionIterator seci = cf.getSectionIterator();

        String secName, typeName, archName;

        while (seci.hasMoreElements())
        {
            secName = seci.peekNextKey();
            ConfigFile::SettingsMultiMap *settings = seci.getNext();
            ConfigFile::SettingsMultiMap::iterator i;
            for (i = settings->begin(); i != settings->end(); ++i)
            {
                typeName = i->first;
                archName = i->second;

                #if OGRE_PLATFORM == OGRE_PLATFORM_APPLE || OGRE_PLATFORM == OGRE_PLATFORM_IPHONE
                if (!StringUtil::startsWith(archName, "/", false)) // only adjust relative dirs
                    archName = String(macBundlePath() + "/" + archName);
                #endif

                ResourceGroupManager::getSingleton().addResourceLocation(archName, typeName, secName);
            }
        }
       // TextureManager::getSingleton().setDefaultNumMipmaps(5);
        ResourceGroupManager::getSingleton().initialiseAllResourceGroups();

        const RenderSystemList& lRenderSystemList = app_root->getAvailableRenderers();

        if( lRenderSystemList.size() == 0 )
		{
			LogManager::getSingleton().logMessage("Sorry, no rendersystem was found.");
			return 1;
		}

		RenderSystem *lRenderSystem = lRenderSystemList[0];
		app_root->setRenderSystem(lRenderSystem);

        app_root->initialise(false,"","");//on ne creer pas de fenetre automatiquement

        render_window = NULL;
		{
			String lWindowTitle = config_file[WINDOW_TITLE];
			unsigned int lSizeX = std::stoi(config_file[RESOLUTION_X]);
			unsigned int lSizeY = std::stoi(config_file[RESOLUTION_Y]);

			bool lFullscreen = std::stoi(config_file[FULLSCREEN_ENABLED]);

            NameValuePairList lParams;

			lParams["FSAA"] = config_file[FSAA];

			lParams["vsync"] = config_file[VSYNC];
			render_window = app_root->createRenderWindow(lWindowTitle, lSizeX, lSizeY, lFullscreen, &lParams);
		}

		sceneMgr = app_root->createSceneManager("DefaultSceneManager");
        camera = sceneMgr->createCamera("Camera");

        SceneNode* CamNode = sceneMgr->getRootSceneNode()->createChildSceneNode();
        CamNode->attachObject(camera);

        // Create one viewport, entire window
        Viewport* vp = render_window->addViewport(camera);
        vp->setBackgroundColour(ColourValue(0,1,0));

        // Alter the camera aspect ratio to match the viewport
        camera->setAspectRatio(Real(vp->getActualWidth()) / Real(vp->getActualHeight()));


        return SUCCESS;

}


#ifdef _WIN32
inline void GameWindow::sleep(uint32_t millisec)
{
    Sleep(millisec);
}
#else
inline void GameWindow::sleep(uint32_t millisec)
{
    usleep(millisec * 1000); // takes microseconds
}
#endif

