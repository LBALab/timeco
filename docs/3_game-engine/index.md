---
title: Game Engine
layout: home
nav_order: 3
permalink: /game-engine
---

# Game Engine
{: .no_toc }

## Table of Contents
{: .no_toc .text-delta }

1. TOC
{:toc}

## Overview

Time Commando (TimeCo) was an evolution of the tooling created during the development of Little Big Adventure 1 which was based on Alone in the Dark (AITD).
These gamees shared pre-rendered backgrounds with 3D software rendered characters, a technique use in the early 90s due to hardware constraints. AITD was the pioneer of pre-rendered backgrounds and use static images that were hand drawn on top of wireframes of a 3D scene. Each image corresponding to a different camera view of the scene.

<a href="{{ site.baseurl }}/assets/images/others/aitd1.png" style="margin: 6px; display: inline-flex; border-radius: 15px; border: 1px solid #80808042; padding: 5px;">
    <img src="{{ site.baseurl }}/assets/images/others/aitd1.png" alt="Team" style="border-radius: 10px" />
</a>

LBA did it differently and use isometric sprite composition in order to create a scene and use a single isometric camera view panning around the environment. The isometric scenes were composed in a grid format with limited width,  depth and height. Various objects were composed by a number of sprites following a set of standard dimensions and then placed together to create scenes. They are also used for collision detection with slopes to make the height transition smoothly. 

<a href="{{ site.baseurl }}/assets/images/others/lba1street.gif" style="margin: 6px; display: inline-flex; border-radius: 15px; border: 1px solid #80808042; padding: 5px;">
    <img src="{{ site.baseurl }}/assets/images/others/lba1street.gif" alt="Team" style="border-radius: 10px" />
</a>

The team continue the trend in Time Commando (TimeCo) and used pre-rendered backgrounds with video motion. A similar technique used in LBA movies but improved to be used not only as cut-scenes but in-game backgrounds with depth information attached and other scene information.

<a href="{{ site.baseurl }}/assets/images/others/tico-prerendermotion.gif" style="margin: 6px; display: inline-flex; border-radius: 15px; border: 1px solid #80808042; padding: 5px;">
    <img src="{{ site.baseurl }}/assets/images/others/tico-prerendermotion.gif" alt="Team" style="border-radius: 10px" />
</a>

TimeCo had another enhancement by adding texture mapping to their 3d model formats, feature then used in LBA2.

<a href="{{ site.baseurl }}/assets/images/others/tico.jpg" style="margin: 6px; display: inline-flex; border-radius: 15px; border: 1px solid #80808042; padding: 5px;">
    <img src="{{ site.baseurl }}/assets/images/others/tico.jpg" alt="Team" style="border-radius: 10px" />
</a>
