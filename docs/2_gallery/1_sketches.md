---
title: Sketches
layout: home
parent: Gallery
nav_order: 1
permalink: /gallery/sketches
images:
- image_path: assets/images/sketches/sketch-1.png
  title: Sketch 1
  link: assets/images/sketches/sketch-1.png
- image_path: assets/images/sketches/sketch-2.png
  title: Sketch 2
  link: assets/images/sketches/sketch-2.png
- image_path: assets/images/sketches/sketch-3.png
  title: Sketch 3
  link: assets/images/sketches/sketch-3.png
- image_path: assets/images/sketches/canion ambush.jpg
  title: Canion Ambush
  link: assets/images/sketches/canion ambush.jpg
- image_path: assets/images/sketches/canion.jpg
  title: Canion
  link: assets/images/sketches/canion.jpg
- image_path: assets/images/sketches/costumes for each epoch.jpg
  title: Costumes for Each Epoch
  link: assets/images/sketches/costumes for each epoch.jpg
- image_path: assets/images/sketches/japan.jpg
  title: Japan
  link: assets/images/sketches/japan.jpg
- image_path: assets/images/sketches/jungle.jpg
  title: Jungle
  link: assets/images/sketches/jungle.jpg
- image_path: assets/images/sketches/mexico.jpg
  title: Mexico
  link: assets/images/sketches/mexico.jpg
- image_path: assets/images/sketches/millimetric_paper_design_prehistory.jpg
  title: Millimetric Paper Design Prehistory
  link: assets/images/sketches/millimetric_paper_design_prehistory.jpg
- image_path: assets/images/sketches/prehistory.jpg
  title: Prehistory
  link: assets/images/sketches/prehistory.jpg
- image_path: assets/images/sketches/soldier bleeding.jpg
  title: Soldier Bleeding
  link: assets/images/sketches/soldier bleeding.jpg
- image_path: assets/images/sketches/weapons.jpg
  title: Weapons
  link: assets/images/sketches/weapons.jpg
- image_path: assets/images/sketches/wild west - ambush scene.jpg
  title: Wild West - Ambush Scene
  link: assets/images/sketches/wild west - ambush scene.jpg
- image_path: assets/images/sketches/wild west.jpg
  title: Wild West
  link: assets/images/sketches/wild west.jpg
- image_path: assets/images/sketches/wayne_town_design_sketch.jpg
  title: Wayne Town Design Sketch
  link: assets/images/sketches/wayne_town_design_sketch.jpg
---

# Sketches

<div>
    {% for image in page.images %}
        <a href="{{ site.baseurl }}/{{ image.link }}" style="margin: 6px; display: inline-flex; border-radius: 15px; border: 1px solid #80808042; padding: 5px;">
            <img src="{{ site.baseurl }}/{{ image.image_path }}" alt="{{ image.title}}" style="border-radius: 10px" />
        </a>
    {% endfor %}
</div>

