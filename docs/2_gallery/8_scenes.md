---
title: Sequences
layout: home
parent: Gallery
nav_order: 8
permalink: /gallery/sequences
images:
- image_path: assets/images/sequences/multi_rooms.png
  title: Multiple Scene Rooms
  link: assets/images/sequences/multi_rooms.png
---

# Tools

<div>
    {% for image in page.images %}
        <a href="{{ site.baseurl }}/{{ image.link }}" style="margin: 6px; display: inline-flex; border-radius: 15px; border: 1px solid #80808042; padding: 5px;">
            <img src="{{ site.baseurl }}/{{ image.image_path }}" alt="{{ image.title}}" style="border-radius: 10px" />
        </a>
    {% endfor %}
</div>

Source: [https://blog.defence-force.org/?tag=Time%20Commando](https://blog.defence-force.org/?tag=Time%20Commando)
