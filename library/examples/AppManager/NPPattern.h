#ifndef _NPPATTERN_
#define _NPPATTERN_

class NPPattern{
protected:
  Adafruit_NeoPixel*strip;
	int brightness;
public:
	NPPattern(Adafruit_NeoPixel*inStrip, int brightness):strip(inStrip),brightness(brightness){}
	
	virtual ~NPPattern(){}
	
	virtual void run(){};
	
	// Input a value 0 to 255 to get a color value.
	// The colours are a transition r - g - b - back to r.
	uint32_t wheel(byte wheelPos) {
		wheelPos = 255 - wheelPos;
		if(wheelPos < 85) {
			return strip->Color(255 - wheelPos * 3, 0, wheelPos * 3);
		}
		if(wheelPos < 170) {
			wheelPos -= 85;
			return strip->Color(0, wheelPos * 3, 255 - wheelPos * 3);
		}
		wheelPos -= 170;
		return strip->Color(wheelPos * 3, 255 - wheelPos * 3, 0);
	}
	
	virtual void setBrightness(int inBrightness){
		strip->setBrightness(inBrightness);
		brightness=strip->getBrightness();
	}
	
	virtual int getBrightness(){return brightness;}
};

#endif