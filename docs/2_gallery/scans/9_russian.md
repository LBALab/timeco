---
title: Russian
layout: home
parent: Scans
nav_order: 9
permalink: /gallery/scans/russian
images_russian:
- image_path: assets/images/scans/Top_Games_1997-09_1.jpg
  title: Top Games 1997-09 Page 1
  link: assets/images/scans/Top_Games_1997-09_1.jpg
- image_path: assets/images/scans/Top_Games_1997-09_2.jpg
  title: Top Games 1997-09 Page 2
  link: assets/images/scans/Top_Games_1997-09_2.jpg
- image_path: assets/images/scans/Top_Games_1997-09_3.jpg
  title: Top Games 1997-09 Page 3
  link: assets/images/scans/Top_Games_1997-09_3.jpg
- image_path: assets/images/scans/Top_Games_1997-09_4.jpg
  title: Top Games 1997-09 Page 4
  link: assets/images/scans/Top_Games_1997-09_4.jpg
---

# Russian Magazines

<div>
    {% for image in page.images_russian %}
        <a href="{{ site.baseurl }}/{{ image.link }}" style="margin: 6px; display: inline-flex; border-radius: 15px; border: 1px solid #80808042; padding: 5px;">
            <img src="{{ site.baseurl }}/{{ image.image_path }}" alt="{{ image.title}}" style="border-radius: 10px" />
        </a>
    {% endfor %}
</div>

Source: [https://magicball.net/other/galleries/time-commando/scans/](https://magicball.net/other/galleries/time-commando/scans/)
