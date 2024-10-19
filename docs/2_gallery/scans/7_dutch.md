---
title: Dutch
layout: home
parent: Scans
nav_order: 7
permalink: /gallery/scans/dutch
images_dutch:
- image_path: assets/images/scans/pc_gameplay_1996-10_cover.jpg
  title: PC Gameplay 1996-10 Cover
  link: assets/images/scans/pc_gameplay_1996-10_cover.jpg
- image_path: assets/images/scans/pc_gameplay_1996-10_1.jpg
  title: PC Gameplay 1996-10 Page 1
  link: assets/images/scans/pc_gameplay_1996-10_1.jpg
- image_path: assets/images/scans/pc_gameplay_1996-10_2.jpg
  title: PC Gameplay 1996-10 Page 2
  link: assets/images/scans/pc_gameplay_1996-10_2.jpg
- image_path: assets/images/scans/power_unlimited.jpg
  title: Power Unlimited
  link: assets/images/scans/power_unlimited.jpg
- image_path: assets/images/scans/powerplay_1996-09_1.jpg
  title: Powerplay 1996-09 Page 1
  link: assets/images/scans/powerplay_1996-09_1.jpg
- image_path: assets/images/scans/powerplay_1996-09_2.jpg
  title: Powerplay 1996-09 Page 2
  link: assets/images/scans/powerplay_1996-09_2.jpg
- image_path: assets/images/scans/powerplay_1996-09_3.jpg
  title: Powerplay 1996-09 Page 3
  link: assets/images/scans/powerplay_1996-09_3.jpg
- image_path: assets/images/scans/powerplay_1996-09_4.jpg
  title: Powerplay 1996-09 Page 4
  link: assets/images/scans/powerplay_1996-09_4.jpg
---

# Dutch Magazines

<div>
    {% for image in page.images_dutch %}
        <a href="{{ site.baseurl }}/{{ image.link }}" style="margin: 6px; display: inline-flex; border-radius: 15px; border: 1px solid #80808042; padding: 5px;">
            <img src="{{ site.baseurl }}/{{ image.image_path }}" alt="{{ image.title}}" style="border-radius: 10px" />
        </a>
    {% endfor %}
</div>

Source: [https://magicball.net/other/galleries/time-commando/scans/](https://magicball.net/other/galleries/time-commando/scans/)
