---
title: Spanish
layout: home
parent: Scans
nav_order: 3
permalink: /gallery/scans/spanish
images_spanish:
- image_path: assets/images/scans/Micromania_1996-03_1.jpg
  title: Micromania 1996-03 Page 1
  link: assets/images/scans/Micromania_1996-03_1.jpg
- image_path: assets/images/scans/Micromania_1996-03_2.jpg
  title: Micromania 1996-03 Page 2
  link: assets/images/scans/Micromania_1996-03_2.jpg
- image_path: assets/images/scans/Micromania_1996-03_3.jpg
  title: Micromania 1996-03 Page 3
  link: assets/images/scans/Micromania_1996-03_3.jpg
- image_path: assets/images/scans/HobbyConsolas_ES_060_001.PNG
  title: HobbyConsolas ES 060 Page 1
  link: assets/images/scans/HobbyConsolas_ES_060_001.PNG
- image_path: assets/images/scans/HobbyConsolas_ES_060_015.PNG
  title: HobbyConsolas ES 060 Page 15
  link: assets/images/scans/HobbyConsolas_ES_060_015.PNG
- image_path: assets/images/scans/HobbyConsolas_ES_060_042.PNG
  title: HobbyConsolas ES 060 Page 42
  link: assets/images/scans/HobbyConsolas_ES_060_042.PNG
- image_path: assets/images/scans/HobbyConsolas_ES_060_043.PNG
  title: HobbyConsolas ES 060 Page 43
  link: assets/images/scans/HobbyConsolas_ES_060_043.PNG
- image_path: assets/images/scans/HobbyConsolas_ES_060_044.PNG
  title: HobbyConsolas ES 060 Page 44
  link: assets/images/scans/HobbyConsolas_ES_060_044.PNG
- image_path: assets/images/scans/HobbyConsolas_ES_060_045.PNG
  title: HobbyConsolas ES 060 Page 45
  link: assets/images/scans/HobbyConsolas_ES_060_045.PNG
- image_path: assets/images/scans/Micromania_Tercera_Epoca_Spanish_Issue_19_001.PNG
  title: Micromania Tercera Epoca Spanish Issue 19 Page 1
  link: assets/images/scans/Micromania_Tercera_Epoca_Spanish_Issue_19_001.PNG
- image_path: assets/images/scans/Micromania_Tercera_Epoca_Spanish_Issue_19_028.PNG
  title: Micromania Tercera Epoca Spanish Issue 19 Page 28
  link: assets/images/scans/Micromania_Tercera_Epoca_Spanish_Issue_19_028.PNG
- image_path: assets/images/scans/Micromania_Tercera_Epoca_Spanish_Issue_19_029.PNG
  title: Micromania Tercera Epoca Spanish Issue 19 Page 29
  link: assets/images/scans/Micromania_Tercera_Epoca_Spanish_Issue_19_029.PNG
- image_path: assets/images/scans/Micromania_Tercera_Epoca_Spanish_Issue_19_030.PNG
  title: Micromania Tercera Epoca Spanish Issue 19 Page 30
  link: assets/images/scans/Micromania_Tercera_Epoca_Spanish_Issue_19_030.PNG
- image_path: assets/images/scans/Micromania_Tercera_Epoca_Spanish_Issue_19_031.PNG
  title: Micromania Tercera Epoca Spanish Issue 19 Page 31
  link: assets/images/scans/Micromania_Tercera_Epoca_Spanish_Issue_19_031.PNG
- image_path: assets/images/scans/Micromania_Tercera_Epoca_Spanish_Issue_19_032.PNG
  title: Micromania Tercera Epoca Spanish Issue 19 Page 32
  link: assets/images/scans/Micromania_Tercera_Epoca_Spanish_Issue_19_032.PNG
- image_path: assets/images/scans/Micromania_Tercera_Epoca_Spanish_Issue_19_033.PNG
  title: Micromania Tercera Epoca Spanish Issue 19 Page 33
  link: assets/images/scans/Micromania_Tercera_Epoca_Spanish_Issue_19_033.PNG
---

# Spanish Magazines

<div>
    {% for image in page.images_spanish %}
        <a href="{{ site.baseurl }}/{{ image.link }}" style="margin: 6px; display: inline-flex; border-radius: 15px; border: 1px solid #80808042; padding: 5px;">
            <img src="{{ site.baseurl }}/{{ image.image_path }}" alt="{{ image.title}}" style="border-radius: 10px" />
        </a>
    {% endfor %}
</div>

Partial Source: [https://magicball.net/other/galleries/time-commando/scans/](https://magicball.net/other/galleries/time-commando/scans/)
