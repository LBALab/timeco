---
title: Polish
layout: home
parent: Scans
nav_order: 8
permalink: /gallery/scans/polish
images_polish:
- image_path: assets/images/scans/SecretService_1996-10_1.jpg
  title: Secret Service 1996-10 Page 1
  link: assets/images/scans/SecretService_1996-10_1.jpg
- image_path: assets/images/scans/SecretService_1996-10_2.jpg
  title: Secret Service 1996-10 Page 2
  link: assets/images/scans/SecretService_1996-10_2.jpg
---

# Polish Magazines

<div>
    {% for image in page.images_polish %}
        <a href="{{ site.baseurl }}/{{ image.link }}" style="margin: 6px; display: inline-flex; border-radius: 15px; border: 1px solid #80808042; padding: 5px;">
            <img src="{{ site.baseurl }}/{{ image.image_path }}" alt="{{ image.title}}" style="border-radius: 10px" />
        </a>
    {% endfor %}
</div>

Source: [https://magicball.net/other/galleries/time-commando/scans/](https://magicball.net/other/galleries/time-commando/scans/)
