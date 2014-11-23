#include "AppDelegate.h"
#include "scenes/SceneMenu.h"
#include "scenes/SceneFinish.h"
#include "scenes/SceneGame.h"

USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

//if you want a different context,just modify the value of glContextAttrs
//it will takes effect on all platforms
void AppDelegate::initGLContextAttrs()
{
    //set OpenGL context attributions,now can only set six attributions:
    //red,green,blue,alpha,depth,stencil
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

    GLView::setGLContextAttrs(glContextAttrs);
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLViewImpl::create("Wonky Monkey");
        director->setOpenGLView(glview);
    }

    // turn on display FPS
    director->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);



	Size screenSize = glview->getFrameSize();

	//screenSize.height = 540;
	//CCLOG("glview->getFrameSize(): %f, %f\n", screenSize.width, screenSize.height);

	std::vector<std::string> searchPaths;
	if (screenSize.height > 1300) {
		searchPaths.push_back("ipadhd");
		director->setContentScaleFactor(1.0);
	} else if (screenSize.height > 480) {
		searchPaths.push_back("hd");
		director->setContentScaleFactor(0.5);
	} else {
		searchPaths.push_back("sd");
		director->setContentScaleFactor(0.25);
	}
	FileUtils::getInstance()->setSearchPaths(searchPaths);

	director->getOpenGLView()->setDesignResolutionSize(2732, 1536, ResolutionPolicy::NO_BORDER);


    auto scene = SceneGame::createWithPhysics();
    director->runWithScene(scene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
