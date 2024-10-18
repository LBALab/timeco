---
title: Game Engine
layout: home
nav_order: 3
permalink: /game-engine
---

# Game Engine

## Overview

Time Commando (TimeCo) was an evolution of the tooling created during the development of Little Big Adventure 1 which is also based on Alone in the Dark (AITD).
These gamees shared pre-rendered backgrounds with 3D software rendered characters, a technique use in the early 90s due to hardware constraints. AITD was the pioneer of pre-rendered backgrounds and use static images that were hand drawn on top of 3D wireframes of a 3D scene. Each image corresponding to a different camera view of the scene.

![AITD]({{ site.baseurl }}/assets/images/others/aitd1.png)

LBA did it differently and use isometric sprite composition in order to create a scene and use a single isometric camera view  panning around the environment.

![LBA]({{ site.baseurl }}/assets/images/others/lba1street.gif)

The isometric scenes were composed in a grid format with limited width,  depth and height. Various objects were composed by a number of sprites following a set of standard dimensions and then placed together to create scenes. They are also used for collision detection with slopes to make the height transition smoothly. 

![LBA1 Isometric Sprite]({{ site.baseurl }}/assets/images/others/bench-sprite.png)
![LBA1 Isometric Scene]({{ site.baseurl }}/assets/images/others/bench-iso.png)


The team continue the trend in Time Commando (TimeCo) and used pre-rendered backgrounds with video motion. A similar technique used in LBA movies but improved to be used not only as cut-scenes but in-game backgrounds with depth information attached. 

![TimeCo Pre-Rendered Background Motion]({{ site.baseurl }}/assets/images/others/tico-prerendermotion.gif)

TimeCo had another enhancement by adding texture mapping to their 3d model formats.

![TimeCo 3d models]({{ site.baseurl }}/assets/images/others/tico.jpg)
