---
title: Models
layout: home
parent: Gallery
nav_order: 1
permalink: /gallery/models
images:
- image_path: assets/images/models/a5.png
  title: Stanley Model
  link: assets/images/models/a5.png
- image_path: assets/images/models/stanley_wireframe.png
  title: Stanley Model
  link: assets/images/models/stanley_wireframe.png
- image_path: assets/images/models/stanley.png
  title: Stanley Model
  link: assets/images/models/stanley.png
- image_path: assets/images/models/stanley_beardy_man.png
  title: Stanley Model Texture
  link: assets/images/models/stanley
- image_path: assets/images/models/stanley_betty.png
  title: Betty Model
  link: assets/images/models/stanley_betty.png
---

# Models

<div>
    {% for image in page.images %}
        <a href="{{ site.baseurl }}/{{ image.link }}" style="margin: 6px; display: inline-flex; border-radius: 15px; border: 1px solid #80808042; padding: 5px;">
            <img src="{{ site.baseurl }}/{{ image.image_path }}" alt="{{ image.title}}" style="border-radius: 10px" />
        </a>
    {% endfor %}
</div>

