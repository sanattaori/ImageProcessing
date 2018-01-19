#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/Texture.h"
#include "cinder/params/Params.h"   // For InterfaceGl show keys to brightness and contrast
#include "cinder/ImageIo.h"
#include "cinder/Surface.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class ImageProcessingApp : public App {
  public:
	void setup() override;
	// space key handling
	void keyDown(KeyEvent event);
	void update() override;
	void draw() override;
	
	
private:
	//original img
	Surface32f mImageInput;
	float mBrightnessPrev;
	float mContrastPrev;

	//Show image when true
	bool mShowOriginal;

	
	
	//output img
	Surface32f mImageOutput;
	float mBrightness;
	float mContrast;
	
	
	params::InterfaceGl mParams;

	static bool equal(float x, float y, float tolerance = 0.001f);

	float adjustBrightnessContrast(float value);

};

void ImageProcessingApp::setup()
{
									//image location
	mImageInput = loadImage(loadAsset("lenna.png"));

	mImageOutput = Surface32f(
		mImageInput.getWidth(),
		mImageInput.getHeight(),        
		false                           
	);

	mBrightness = 0.0f;
	mBrightnessPrev = -0.5f;
	mContrast = 1.0f;
	mContrastPrev = 0.0f;

	mShowOriginal = false;

	
	setWindowSize(mImageInput.getWidth(), mImageInput.getHeight());
	
	// Set GUI title and size
	mParams = params::InterfaceGl("Adjustment Params", vec2(200, 80));

	// Controls for brightness
	mParams.addParam(
		"Brightness",                                    
		&mBrightness,                                    
		"min=-0.5 max=0.5 step=0.01 keyIncr=b keyDecr=v" 
									// b to increment
									// v to decrement
	);

	// Controls for contrast
	mParams.addParam(
		"Contrast",                                     
		&mContrast,                                      
		"min=0.0  max=2.0 step=0.01 keyIncr=c keyDecr=x" 
	);

}

void ImageProcessingApp::keyDown(KeyEvent event)
{
	
	if (event.getChar() == ' ')
	{
		mShowOriginal = !mShowOriginal;
	}
}

bool ImageProcessingApp::equal(float x, float y, float tolerance)
{
	if (fabs(x - y) < tolerance)
		return true;
	else
		return false;
}

float ImageProcessingApp::adjustBrightnessContrast(float value)
{
	return (value - 0.5f) * mContrast + 0.5f + mBrightness;
}


void ImageProcessingApp::update()
{
	if (equal(mBrightness, mBrightnessPrev) && equal(mContrast, mContrastPrev))
	{
		return;
	}

	//
	// *** Image Processing Code ***
	//

	
	Surface32f::ConstIter pixelInIter = mImageInput.getIter();

	Surface32f::Iter pixelOutIter = mImageOutput.getIter();


	while (pixelInIter.line())
	{
		pixelOutIter.line();

		
		while (pixelInIter.pixel())
		{
			pixelOutIter.pixel();


			//
			// *** Pixel Transform ***
			//
			
			pixelOutIter.r() = adjustBrightnessContrast(pixelInIter.r());
			pixelOutIter.g() = adjustBrightnessContrast(pixelInIter.g());
			pixelOutIter.b() = adjustBrightnessContrast(pixelInIter.b());
		}
	}


	
	mBrightnessPrev = mBrightness;
	mContrastPrev = mContrast;
}

void ImageProcessingApp::draw()
{
	if (mShowOriginal)
	{
		// Show the original (input) image
		gl::draw(mImageInput, getWindowBounds());
	}
	else
	{
		// Show the modified (output) image
		gl::draw(mImageOutput, getWindowBounds());

		// Show the InterfaceGl GUI on top of that
		mParams.draw();
	}
}

CINDER_APP( ImageProcessingApp, RendererGl )
