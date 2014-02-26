#include "OGRE/OgreRoot.h"
#include "OGRE/OgreRenderSystem.h"
#include "OGRE/OgreRenderWindow.h"
#include "OGRE/OgreWindowEventUtilities.h"

// I will use std::auto_ptr so I need to include 'memory'.
// If you don't know std::auto_ptr, you should check some C++ tutorials/lesson on this matter.
#include <memory>
// I will check for std::exception. If you don't know what exception/try/catch means, you should learn C++ first.
#include <exception>

int main()
{

	// This try/catch will catch potential exception launched by ogre or by my program.
	// Ogre can launch 'Ogre::Exception' for example.
	try
	{
		// STEP 1/ First, we will need to create the Ogre::Root object.
		// It is an object that must be created to use ogre correctly, and delete once we are finished using Ogre.

		// This is the name of an optionnal textual configuration file for the rendersystem.
		// I won't use it.
		Ogre::String lConfigFileName = "";
		// This is the name of an optionnal textual configuration file, which lists the available plugins.
		// I won't use it.
		Ogre::String lPluginsFileName = "";
		// This is the name of the log file. A log file is a file in which you can write things during the program execution.
		// Ogre use it to display general informations about the rendersystem.
		// You are not obliged to generate one, and ogre can even transmit the log data to you own class if you want.
		// Here we only ask the root to create the file.
		Ogre::String lLogFileName = "Tutorial_Ogre.LOG";

		// I create the root and I wrap it in an auto_ptr so that it will be automatically released.
		// Now I can even do "throw std::bad_alloc("bad alloc");", the program will release the root smoothly.
		std::auto_ptr<Ogre::Root> lRoot(
			new Ogre::Root(lConfigFileName, lPluginsFileName, lLogFileName));

		// STEP 2/ Then we need to load plugins. It means that there are functions that are stored inside dynamic libraries.
		// These libraries are .dll or .so files. Most projects Ogre Project do not need all functions to be usable.
		// That way, only a subset of all function can be loaded. It also means you can create your own plugins if you want.
		// If you want to know more on the subject, you 'll need to dig into a C++ tutorial.
		// Anyway, for our use, we will need to load at least a 'RenderSystem' plugin, which means something to drive opengl or directx.
		// The basic plugins you are the most likely to use are the RenderSystems, the particle FX and the Cgprogram.
		{
			// Ogre uses Ogre::String (which is a typedef) to represent strings.
			// Here I use a typedef. If you don't know what it means, you should learn C++ basics first.
			// Same if you don't know what std::vector is.
			typedef std::vector<Ogre::String> Strings;
			// Here I list all the plugins I want to load.
			// I let those I don't want to use in comments.
			// Opengl rendersystem is supposed to work everywhere.
			// But in reality a rendersystem may fail on your computer.
			// It is likely do to bad/old graphic card driver/installation,
			// or too old directx version on windows (try update).
			// Often, when one rendersystem fail, the other at least kind-a-work.
			// I put them in a std::vector, because then I can factorise operations and calls (do a 'for').
			Strings lPluginNames;
			lPluginNames.push_back("RenderSystem_GL");
			//lPluginNames.push_back("RenderSystem_Direct3D9");
			lPluginNames.push_back("Plugin_ParticleFX");
			lPluginNames.push_back("Plugin_CgProgramManager");
			//lPluginNames.push_back("Plugin_PCZSceneManager");
			//lPluginNames.push_back("Plugin_OctreeZone");
			lPluginNames.push_back("Plugin_OctreeSceneManager");
			//lPluginNames.push_back("Plugin_BSPSceneManager");
			{
				Strings::iterator lIter = lPluginNames.begin();
				Strings::iterator lIterEnd = lPluginNames.end();
				for(;lIter != lIterEnd; lIter++)
				{
					Ogre::String& lPluginName = (*lIter);
					// In debug mode, the plugins names are differents, they got a '_d' at the end.
					// So I add it. This is the main reason why I needed to put plugins names in a vector.
					// A macro or a function would have done the trick too...
					bool lIsInDebugMode = OGRE_DEBUG_MODE;
					if(lIsInDebugMode)
					{
						lPluginName.append("_d");
					}
					lRoot->loadPlugin(lPluginName);
				}
			}
		}

		// STEP 3/ Then, we can select from the loaded plugins the unique RenderSystem we want to use.
		{
			// the root provide a method if you want to select
			// the rendersystem and its options visually (lRoot->showConfigDialog()).
			// in that case, you don't need to set the render system manually

			const Ogre::RenderSystemList& lRenderSystemList = lRoot->getAvailableRenderers();
			if( lRenderSystemList.size() == 0 )
			{
				Ogre::LogManager::getSingleton().logMessage("Sorry, no rendersystem was found.");
				return 1;
			}

			Ogre::RenderSystem *lRenderSystem = lRenderSystemList[0];
			lRoot->setRenderSystem(lRenderSystem);
		}
		// STEP 4/ When the RenderSystem is selected, we can initialise the Root. The root can be initialised only when a rendersystem has been selected.
		{
			// I can create a window automatically, but I won't do it.
			bool lCreateAWindowAutomatically = false;
			// name of the automatically generated window. empty for me.
			Ogre::String lWindowTitle = "";
			// custom capabilities of the rendersystem. It's a feature for advanced use.
			Ogre::String lCustomCapacities = "";
			lRoot->initialise(lCreateAWindowAutomatically, lWindowTitle, lCustomCapacities);
		}
		// STEP 5/ Then we can ask to the RenderSystem to create a window.
		Ogre::RenderWindow* lWindow = NULL;
		{
			Ogre::String lWindowTitle = "Hello Ogre World";
			unsigned int lSizeX = 800;
			unsigned int lSizeY = 600;
			//I don't want to use fullscreen during development.
			bool lFullscreen = false;
			// This is just an example of parameters that we can put. Check the API for more details.
			Ogre::NameValuePairList lParams;
			// fullscreen antialiasing. (check wikipedia if needed).
			lParams["FSAA"] = "0";
			// vertical synchronisation will prevent some image-tearing, but also
			// will provide smooth framerate in windowed mode.(check wikipedia if needed).
			lParams["vsync"] = "true";
			lWindow = lRoot->createRenderWindow(lWindowTitle, lSizeX, lSizeY, lFullscreen, &lParams);
		}

		// I wait until the window is closed.
		// The "message pump" thing is something you will see in most GUI application.
		// It allow the binding of messages between the application and the OS.
		// These messages are most of the time : keystroke, mouse moved, ... or window closed.
		// If I don't do this, the message are never caught, and the window won't close.
		while(!lWindow->isClosed())
		{
			Ogre::WindowEventUtilities::messagePump();
		}

		Ogre::LogManager::getSingleton().logMessage("end of the program");
	}catch(Ogre::Exception &e)
	{
		std::cout<<"!!!!Ogre::Exception!!!!"<<e.what()<<std::endl;
	}catch(std::exception &e)
	{
		std::cout<<"!!!!std::exception!!!!"<<e.what()<<std::endl;
	}

	return 0;
}
