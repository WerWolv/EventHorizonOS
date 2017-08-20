#ifndef __RENDERER_H
#define __RENDERER_H

extern "C" {
	#include "display.h"
}

#include <vector>

#include "layer.h"



#define MAX_LAYERS 16

class Renderer {	
	public:
		Renderer();
		
		void flush(void);
		void clr_layers(void);
		Renderer& operator<<(Layer &layer);
	
	private:
		std::vector<Layer*> m_layers;
		Bitmap m_buffer;
};

#endif
