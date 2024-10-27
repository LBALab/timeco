---
title: Concept Art
layout: home
parent: Gallery
nav_order: 1
permalink: /gallery/concept_art
images:
- image_path: assets/images/concept_art/character_design_sketches.jpg
  title: Concept 1
  link: assets/images/concept_art/character_design_sketches.jpg
- image_path: assets/images/concept_art/img_5410.png
  title: Concept 2
  link: assets/images/concept_art/img_5410.png
- image_path: assets/images/concept_art/setup2.jpg
  title: Concept 3
  link: assets/images/concept_art/setup2.jpg
- image_path: assets/images/concept_art/setup3.jpg
  title: Concept 4
  link: assets/images/concept_art/setup3.jpg
- image_path: assets/images/concept_art/alternative_title_picture.png
  title: Alternative Title Screen
  link: assets/images/concept_art/alternative_title_picture.png
- image_path: assets/images/concept_art/alternate_title_fonts.png
  title: Alternative Title Fonts
  link: assets/images/concept_art/alternate_title_fonts.png
- image_path: assets/images/concept_art/logo.png
  title: Logo
  link: assets/images/concept_art/logo.png
- image_path: assets/images/concept_art/beta-logo.jpg
  title: Beta Logo
  link: assets/images/concept_art/beta-logo.jpg
- image_path: assets/images/concept_art/INST_DOS.png
  title: DOS Setup
  link: assets/images/concept_art/INST_DOS.png
---

# Concept Art

<div>
    {% for image in page.images %}
        <a href="{{ site.baseurl }}/{{ image.link }}" style="margin: 6px; display: inline-flex; border-radius: 15px; border: 1px solid #80808042; padding: 5px;">
            <img src="{{ site.baseurl }}/{{ image.image_path }}" alt="{{ image.title}}" style="border-radius: 10px" />
        </a>
    {% endfor %}
</div>

