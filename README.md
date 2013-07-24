# Empty Visual System 

Welcome to the CLOUDS Interactive Documentary CodeStorm! We'll be creating Visual Systems, modular visual sketches  used that are used along with the pointcloud interviews to illustrate the concepts presented in the film.

In order to make the process of making a VisualSystem efficient and easy we have put together a wrapper that is a lot like a testApp.cpp but with ofxTimeline and ofxUI built in for variable and animation controls. At the end this Presets are going to be curated inside the documentary.

## Create your own visual system

Download a fresh openFrameworks 0.7.4 http://www.openframeworks.cc/download/ unzip it and do the following commands in the terminal
	
* clone the empty template

		$ cd of_v0.7.4_osx_release/apps/myApps
		$ git clone https://github.com/CLOUDS-Interactive-Documentary/EmptyVisualSystem
		$ cd EmptyVisualSystem/
	
* get the shared code library for Clouds

		$ git submodule init
		$ git submodule update
		
* clone all the addons

		$ chmod 733 cloneaddons.sh
		$ ./cloneaddons.sh
		
Next you need to rename the project to the name of your sketch,
	
* Rename the project file from EmptyVisualSystem to something else
* In EmptyVisualSystem.h modify the system name to match your sketch
		
		string getSystemName(){
			return "MyVisualSystem"
		}

* Change CloudsVisualSystem class name to another class name using find-replace
* Ask us to create a new repo on CLOUDS-Interactive-Documentary, for example 'MyVisualSystem' 
* It's URL would be git@github.com:CLOUDS-Interactive-Documentary/MyVisualSystem
* make a copy of emptyVisualSystem folder in myApps/ and rename it to MyVisualSystem
* in the terminal, cd into Ocean/ and and redirect from the empty repo to your new repo

		$ git remote rm origin
		$ git remote add origin git@github.com:CLOUDS-Interactive-Documentary/MyVisualSystem.git 
		$ git push -u origin master

### Modify ofMaterial & ofLight

To Run you'll need to modify two things in the oF Core

	ofFloatColor &getDiffuseColor();
	ofFloatColor &getAmbientColor();
	ofFloatColor &getSpecularColor();
	ofFloatColor &getEmissiveColor();
	float &getShininess(); 
	
Do the same on the `ofMaterial.cpp`:

	float& ofMaterial::getShininess(){
		return shininess;
	}

	ofFloatColor& ofMaterial::getDiffuseColor() {
		return diffuse;
	}

	ofFloatColor& ofMaterial::getAmbientColor() {
		return ambient;
	}

	ofFloatColor& ofMaterial::getSpecularColor() {
		return specular;
	}

	ofFloatColor& ofMaterial::getEmissiveColor() {
		return emissive;
	}
	
### Included Addons

CLOUDS uses many addons from the community 

* [ofxRange](https://github.com/Flightphase/ofxRange) by James George

		git clone git@github.com:Flightphase/ofxRange.git

* [ofxMSATimer](https://github.com/obviousjim/ofxMSATimer) by Memo Atken, James George, Philip Whitfield, Juan Pablo Manson

		git clone git@github.com:obviousjim/ofxMSATimer.git
		
* [ofxTween](https://github.com/Flightphase/ofxTween) by James George

		git clone git@github.com:Flightphase/ofxTween.git
		
* [ofxTextInputField](https://github.com/Flightphase/ofxTextInputField) by James George & Elliot Woods

		git clone git@github.com:Flightphase/ofxTextInputField.git
		
* [ofxTimecode](https://github.com/YCAMInterlab/ofxTimecode) by James George

		git clone git@github.com:YCAMInterlab/ofxTimecode.git
		
* [ofxTimeline](https://github.com/YCAMInterlab/ofxTimeline) by James George

		git clone git@github.com:YCAMInterlab/ofxTimeline.git
		git checkout develop
		
* [ofxCameraSaveLoad](https://github.com/roymacdonald/ofxCameraSaveLoad) by Roy MacDonald

		git clone git@github.com:roymacdonald/ofxCameraSaveLoad.git
		
* [ofxGenerative](https://github.com/rezaali/ofxGenerative) by Reza Ali

		git clone git@github.com:rezaali/ofxGenerative.git
		
* [ofxUI](https://github.com/rezaali/ofxUI) by Reza Ali

		git clone git@github.com:rezaali/ofxUI.git

### Loading data

Anywhere you want to access things in your bin/data folder you'll need to do so by first calling getVisualSystemDataPath() + "path/to/my/stuff". This will ensure that your data access works when running the module inside of Clouds.

### Saving Presets

Clouds VisualSystems are driven by presets. To create a preset, configure the variables and timing just how you like and then click Save on the main GUI. Enter a name on the pop window and confirm. This will save all your settings into bin/data/Presets/

The Presets GUI now has a button with the name you just entered, and you can click to bring those settings back. Feel free to change anythign after you've created a preset, since you'll always be modifying the Working/ preset.

Make sure to check your presets into GitHub so we can use them in Clouds

### Hot-Keys 

Some useful hotkeys for the interface
* F : Toogle Fullscreen
* H : Hide/Show GUI
* E : Arrange GUI in Cascade  
* R : Arrange GUI at Top
* T : Minimize GUI
* Y : Arrange GUI in circle
* ` : Take a snapshoot
* SPACE : Toggly play on the timeline
* SHIFT+T : Set a camera point on the camera track
* SHIFT+L : Toggle following your camera track





 






