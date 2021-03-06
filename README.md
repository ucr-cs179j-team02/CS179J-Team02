# Rona Zona 
Rona Zona is a Embedded Senior Design Project 
 
# CS179J-Team02
Rona Zona is a Self contained wearable device that keeps unwanted people six feet away. The Rona Zona is the perfect device if you are cautious about contracting person to person illnesses. The device monitors surroundings using Computer Vision. If a potential hazard gets too close, Rona Zona will alert and disinfect the surroundings.

    
| Development Board | Coding Language | Servos | Buzzer | Lighting System | Arduino IDE Setup |
|-----------------|-------------|---------------------------------|-----------------------------|----|---|
| RexQualis UNO R3 |  Arduino   |   (1) MS24 Digital Servo Motor - Ideally 2 <br> (1) SG90 MicroServo Motor - Temporary  |  5V DC Buzzer | WS2812B LEDs | Visit this website and follow the instructions to download Arduino for yourself <br> https://www.arduino.cc/en/guide/windows
 
# Embedded Components
Rona Zona utilizes several Embedded subsystems in order to perform its many functions. 
 
    Alert System: Contains an alarm buzzer, RGB Belt, and laser to warn surrounding people about the 6 ft safe distance
    Spray System: Sprays and disinfects potential hazards that get with in 6 feet
    Computer Vision: Utilizes a camera to capture live images and analyse them for potential hazards that get too close
    NodeMCU Server: A online server that allows individual systems to be created and connected virtually, allowing for remote construction
 
To learn more about any individual system please go to their corresponding folders.
This project has multiple systems which individually require their own configurations. This guide will go over the necessary dependencies and installations for the following systems: Computer vision on Desktop/on the PI, Server, Belt, spray, and Hat subsystems.

# Starting Up
The first step is to clone the repository within your work environment, either desktop or Rapsberry PI.

Git clone https://github.com/ucr-cs179j-team02/CS179J-Team02

# Computer Vision Setup

For both the raspberry pi and the desktop versions you need to have OpenCV and Tensorflow installed on the machines. 

Raspberry Pi 3 & Desktop
------

For the raspberry pi 3. The first step is to make sure the OS is updated to its latest version. You can use the following commands: 

	sudo apt-get update
	sudo apt-get dist-upgrade

Next you need to configure the environment so that all dependencies have a path to one another. Make a tensorflow file and cd into it. 

	Mkdir TF_folder => cd TF_folder lib

Now we are going to clone the repository containing our model and other software. Make sure to have the most up to date model along with the graph files within your folder. Now move the rpi_run_model.py, label_map_util.py, along with the preprocessing_scripts folder to this new folder. The rest of the application should be installed within this directory.

Second, we need to set up a virtual environment for our model to run on. You can do this by running: sudo pip3 install virtualenv

	And then set up a environment with: 
	python3 -m venv my_enviornment					   
	source my_enviornment/bin/activate

Third, we have to install tensorflow and OpenCV. For tensorflow you can simply use
	
	pip3 install tensorflow

For OpenCV there are many necessary configurations you will need. The first 3 are for configuring your webcam within the raspberry pi along with OpenCV:

	sudo apt-get install libavcodec-dev libavformat-dev libswscale-dev libv4l-dev
	sudo apt-get install libxvidcore-dev libx264-dev
	sudo apt-get install qt4-dev-tools libatlas-base-dev

Finally you can pip install openCV

	pip3 install opencv-python

Lastly you need to make sure that the raspberry pi camera can be activated. Go into the raspberry pis system interface and make sure the pi camera is enabled.
	
# Running Computer Vision from Raspberry Pi

Once everything is installed and configured your can run this command to start the custom model 

	python3 rpi_run_model.py

# Running Computer Vision from Desktop

#### A prerequisite for the following is a web cam. Please make sure that the web camera allows this program to execute it. You can allow access to all and specific apps by following [this link](https://support.microsoft.com/en-us/help/4558611/turn-on-app-permissions-for-camera-and-microphone-on-windows-10).

1. Please follow the same installation steps as mentioned in the previous section.

2. Now, download the repository and keep the directory structures as is.

3. From the root directory, execute:

	python new_run_model.py

#### If everything is successful, you will have a working computer vision model that can classify between masked and unmasked persons:

![Imgur](https://i.imgur.com/8ZKzp5z.jpg)

# Running the Server-Client Interface
* If you are running the Rona Zona using the local framework (without an external internet connection), there is no need for any setup. Just upload the code to your NodeMCUs and you should be good to go.
* If you are running the Rona Zona using the remote framework (with an external internet connection), you have to make a few edits.
	* Edit the server and client code in the following files with your WiFi Network name and password 
		1. ./components/server-client_framework/src/Server/Remote/hat_server/hat_server.ino (lines 10 and 11)
		2. ./components/server-client_framework/src/Server/Remote/belt_server/belt_server.ino (lines 14 and 15)
		3. ./components/server-client_framework/src/Client/belt_client/belt_client.ino (line 8)
		4. ./components/server-client_framework/src/Client/hat_client/hat_client.ino (line 8)
	* Next, you'll have to port forward your router. [Here](https://www.whatismyip.com/port-forwarding/) is a guide in doing so.
	* After that, you will need to go [here](https://www.whatismyip.com/) to find your public IPv4.
	* Finally, replace "192.168.1.1:80" with your public IPv4 in the following files
		5. ./components/server-client_framework/src/Client/belt_client/belt_client.ino (lines 21, 24, 27. 30)
		6. ./components/server-client_framework/src/Client/hat_client/hat_client.ino (lines 21, 24, 27. 30)
