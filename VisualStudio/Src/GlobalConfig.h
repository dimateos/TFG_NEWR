#pragma once

//static global config to easily edit hotkeys
class GlobalConfig
{
public:
	static char
		ACTION_escape,				//exit application
		ACTION_captureCursor,		//switch free amd hidden cursor
		ACTION_screenPostFilter,	//Switch post-processing effect (hold and press 1-9)

		ACTION_moveRIGHT,			//movement
		ACTION_moveLEFT,
		ACTION_moveBACK,
		ACTION_moveFORE,
		ACTION_moveUP,
		ACTION_moveDOWN,
		ACTION_rotENABLE,			//rotation
		ACTION_rotRIGHT,
		ACTION_rotLEFT,
		ACTION_FASTtransform,		//modifiers
		ACTION_SLOWtransform,
		ACTION_RESETtransform,

		ACTION_switchControl,			//start/stop controling the portal to move/rotate it locally
		ACTION_cycleCamerasPositions,	//switch between camera positions

		ACTION_togglePortalCameraAxis,	//show/hide virtual portal cameras axes
		ACTION_switchPortalRenderModes,	//switch portal rendering options
		ACTION_togglePortalSurfaces,	//toggle portal surfaces
		ACTION_togglePortalFrames,		//toggle portal frames
		ACTION_togglePortalCube,		//toggle cube to render as a portal
		ACTION_increasePortalRec,		//change amount of recursion
		ACTION_decreasePortalRec
		;

private:
	GlobalConfig() {}; //non instanciable
};