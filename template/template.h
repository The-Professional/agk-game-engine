#ifndef _H_AGK_TEMPLATE_
#define _H_AGK_TEMPLATE_

// Link to GDK libraries
#include "AGK.h"

#define DEVICE_POS_X 32
#define DEVICE_POS_Y 32

// used to make a more unique folder for the write path
#define COMPANY_NAME "Lap Cat Games"

// Global values for the app
class app
{
	public:

		// constructor
		app() { memset ( this, 0, sizeof(app)); }

        void Init();

		// main app functions - mike to experiment with a derived class for this..
		void Begin();
		int Loop();
		void End();
};

extern app App;

#endif

// Allow us to use the LoadImage function name
#ifdef LoadImage
 #undef LoadImage
#endif