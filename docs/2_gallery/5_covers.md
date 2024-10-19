---
title: Covers
layout: home
parent: Gallery
nav_order: 5
permalink: /gallery/covers
images:
- image_path: assets/images/covers/usa_release_box_front.jpg
  title: USA Release Box Front
  link: assets/images/covers/usa_release_box_front.jpg
- image_path: assets/images/covers/usa_release_box_back.jpg
  title: USA Release Box Back
  link: assets/images/covers/usa_release_box_back.jpg
- image_path: assets/images/covers/jewel_case_booklet_front.jpg
  title: Jewel Case Booklet Front
  link: assets/images/covers/jewel_case_booklet_front.jpg
- image_path: assets/images/covers/jewel_case_booklet_back.jpg
  title: Jewel Case Booklet Back
  link: assets/images/covers/jewel_case_booklet_back.jpg
- image_path: assets/images/covers/jewel_case_inlay_front.jpg
  title: Jewel Case Inlay Front
  link: assets/images/covers/jewel_case_inlay_front.jpg
- image_path: assets/images/covers/jewel_case_inlay_back.jpg
  title: Jewel Case Inlay Back
  link: assets/images/covers/jewel_case_inlay_back.jpg
- image_path: assets/images/covers/usa_release_cd.jpg
  title: USA Release CD
  link: assets/images/covers/usa_release_cd.jpg
- image_path: assets/images/covers/usa_release_jewelcase_front.jpg
  title: USA Release Jewelcase Front
  link: assets/images/covers/usa_release_jewelcase_front.jpg
- image_path: assets/images/covers/usa_release_jewelcase_back.jpg
  title: USA Release Jewelcase Back
  link: assets/images/covers/usa_release_jewelcase_back.jpg
- image_path: assets/images/covers/usa_release_jewelcase_inlay.jpg
  title: USA Release Jewelcase Inlay
  link: assets/images/covers/usa_release_jewelcase_inlay.jpg
---

# Covers

<div>
    {% for image in page.images %}
        <a href="{{ site.baseurl }}/{{ image.link }}" style="margin: 6px; display: inline-flex; border-radius: 15px; border: 1px solid #80808042; padding: 5px;">
            <img src="{{ site.baseurl }}/{{ image.image_path }}" alt="{{ image.title}}" style="border-radius: 10px" />
        </a>
    {% endfor %}
</div>

Source: [https://magicball.net/other/galleries/time-commando/cover-art/](https://magicball.net/other/galleries/time-commando/cover-art/)
