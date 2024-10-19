---
title: Italian
layout: home
parent: Scans
nav_order: 5
permalink: /gallery/scans/italian
images_italian:
- image_path: assets/images/scans/PCGameParade_1996-09_1.jpg
  title: PC Game Parade 1996-09 Page 1
  link: assets/images/scans/PCGameParade_1996-09_1.jpg
- image_path: assets/images/scans/PCGameParade_1996-09_2.jpg
  title: PC Game Parade 1996-09 Page 2
  link: assets/images/scans/PCGameParade_1996-09_2.jpg
- image_path: assets/images/scans/PCGameParade_1996-09_3.jpg
  title: PC Game Parade 1996-09 Page 3
  link: assets/images/scans/PCGameParade_1996-09_3.jpg
---

# Italian Magazines

<div>
    {% for image in page.images_italian %}
        <a href="{{ site.baseurl }}/{{ image.link }}" style="margin: 6px; display: inline-flex; border-radius: 15px; border: 1px solid #80808042; padding: 5px;">
            <img src="{{ site.baseurl }}/{{ image.image_path }}" alt="{{ image.title}}" style="border-radius: 10px" />
        </a>
    {% endfor %}
</div>

Source: [https://magicball.net/other/galleries/time-commando/scans/](https://magicball.net/other/galleries/time-commando/scans/)
