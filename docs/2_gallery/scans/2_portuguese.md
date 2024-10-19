---
title: Brazilian Portuguese
layout: home
parent: Scans
nav_order: 2
permalink: /gallery/scans/portuguese
images_brazilian:
- image_path: assets/images/scans/Computer_Games_BR_1996-10_cover.jpg
  title: Computer Games BR 1996-10 Cover
  link: assets/images/scans/Computer_Games_BR_1996-10_cover.jpg
- image_path: assets/images/scans/Computer_Games_BR_1996-10_1.jpg
  title: Computer Games BR 1996-10 Page 1
  link: assets/images/scans/Computer_Games_BR_1996-10_1.jpg
- image_path: assets/images/scans/Computer_Games_BR_1996-10_2.jpg
  title: Computer Games BR 1996-10 Page 2
  link: assets/images/scans/Computer_Games_BR_1996-10_2.jpg
- image_path: assets/images/scans/Computer_Games_BR_1996-10_3.jpg
  title: Computer Games BR 1996-10 Page 3
  link: assets/images/scans/Computer_Games_BR_1996-10_3.jpg
- image_path: assets/images/scans/Computer_Games_BR_1997-09_1.jpg
  title: Computer Games BR 1997-09 Page 1
  link: assets/images/scans/Computer_Games_BR_1997-09_1.jpg
- image_path: assets/images/scans/Computer_Games_BR_1997-09_2.jpg
  title: Computer Games BR 1997-09 Page 2
  link: assets/images/scans/Computer_Games_BR_1997-09_2.jpg
---

# Brazilian Portuguese Magazines

<div>
    {% for image in page.images_brazilian %}
        <a href="{{ site.baseurl }}/{{ image.link }}" style="margin: 6px; display: inline-flex; border-radius: 15px; border: 1px solid #80808042; padding: 5px;">
            <img src="{{ site.baseurl }}/{{ image.image_path }}" alt="{{ image.title}}" style="border-radius: 10px" />
        </a>
    {% endfor %}
</div>

Source: [https://magicball.net/other/galleries/time-commando/scans/](https://magicball.net/other/galleries/time-commando/scans/)
