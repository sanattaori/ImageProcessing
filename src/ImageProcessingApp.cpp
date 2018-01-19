#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class ImageProcessingApp : public App {
  public:
	void setup() override;
	void mouseDown( MouseEvent event ) override;
	void update() override;
	void draw() override;
};

void ImageProcessingApp::setup()
{
}

void ImageProcessingApp::mouseDown( MouseEvent event )
{
}

void ImageProcessingApp::update()
{
}

void ImageProcessingApp::draw()
{
	gl::clear( Color( 0, 0, 0 ) ); 
}

CINDER_APP( ImageProcessingApp, RendererGl )
