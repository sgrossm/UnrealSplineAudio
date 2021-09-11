# UnrealSplineAudio
An Unreal  C++ project example of creating a volumetric audio source using splines. 

This C++ project creates a Spline Component and attaches an Audio Component to it, using
the player's position and user-defined range parameter to optimize the tick interval.
<br/>
**Getting Started**
1. Drag in SplineAudio asset from C++ Classes folder
2. Set up sound cue in details panel
3. Set up attenuation 
4. Define tick range and other parameters (set in Spline Audio tab in details panel)

![alt text](img/CPPScreenshot.PNG)

You can also convert this actor into a Blueprint, or check out my Blueprint implementation: https://github.com/sgrossm/UnrealSplineAudioBlueprint
<br/>
As a small performance experiment, I replicated this functionality in a Blueprint, and found it to be slower. See the screenshots below:<br/>
![alt text](img/InkedBlueprintProfiling_LI.jpg)
As opposed to the C++ project 
![alt text](img/InkedCPlusPlusProfiling_LI.jpg)
<br/>
For any suggestions or improvements, please email stevegrossman821@gmail.com.
